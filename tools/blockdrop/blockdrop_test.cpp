/*
 * blockdrop_test.cpp — does updateSC55WithSampleRate() drop a sample per block?
 *
 * Standalone: links the emulator core only, no JUCE. Renders the same chord on
 * the power-on default patch at several (host rate, block size) pairs and
 * reports the 4-8 kHz band RMS of the result.
 *
 * The reasoning the measurement rests on:
 *
 *   renderBufferFrames = ceil(nFrames * 64000 / hostRate). PCM_Update posts
 *   samples in PAIRS, so a loop stopping at `sample_write_ptr >=
 *   renderBufferFrames` overshoots by one exactly when that count is ODD.
 *
 *   At hostRate == 64000 the resampler is a 1:1 pass, so a 32- vs 33-frame
 *   block at 64000 differs in NOTHING except the parity of renderBufferFrames.
 *   That pair is the controlled experiment; everything else is corroboration.
 *
 * Usage:  blockdrop_test <rom-dir>
 *
 * <rom-dir> holds the five core dumps under their upstream names:
 *   jv880_rom1.bin jv880_rom2.bin jv880_waverom1.bin jv880_waverom2.bin
 *   jv880_nvram.bin
 * The waveroms are unscrambled here, exactly as rom.cpp does it, because
 * startSC55() expects them descrambled.
 */
#include "../../Source/emulator/mcu.h"

#include <cmath>
#include <complex>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

// ---------------------------------------------------------------- ROM loading

static bool readFile(const std::string &path, std::vector<uint8_t> &out, size_t expect) {
    FILE *f = fopen(path.c_str(), "rb");
    if (!f) { fprintf(stderr, "cannot open %s\n", path.c_str()); return false; }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (expect && (size_t)len != expect) {
        fprintf(stderr, "%s: expected %zu bytes, got %ld\n", path.c_str(), expect, len);
        fclose(f);
        return false;
    }
    out.resize((size_t)len);
    size_t got = fread(out.data(), 1, out.size(), f);
    fclose(f);
    if (got != out.size()) { fprintf(stderr, "short read on %s\n", path.c_str()); return false; }
    return true;
}

// Verbatim from Source/rom.cpp so the harness cannot disagree with the plugin
// about what the wave ROMs contain.
static void unscrambleRomLocal(const uint8_t *src, uint8_t *dst, int len) {
    for (int i = 0; i < len; i++) {
        int address = i & ~0xfffff;
        static const int aa[] = {2, 0,  3,  4,  1, 9, 13, 10, 18, 17,
                                 6, 15, 11, 16, 8, 5, 12, 7,  14, 19};
        for (int j = 0; j < 20; j++)
            if (i & (1 << j)) address |= 1 << aa[j];
        uint8_t srcdata = src[address];
        uint8_t data = 0;
        static const int dd[] = {2, 0, 4, 5, 7, 6, 3, 1};
        for (int j = 0; j < 8; j++)
            if (srcdata & (1 << dd[j])) data |= 1 << j;
        dst[i] = data;
    }
}

// ------------------------------------------------------------------- analysis

// Iterative radix-2 FFT, in place. n must be a power of two.
static void fft(std::vector<std::complex<double>> &a) {
    const size_t n = a.size();
    for (size_t i = 1, j = 0; i < n; i++) {
        size_t bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) std::swap(a[i], a[j]);
    }
    for (size_t len = 2; len <= n; len <<= 1) {
        const double ang = -2.0 * M_PI / (double)len;
        const std::complex<double> wl(std::cos(ang), std::sin(ang));
        for (size_t i = 0; i < n; i += len) {
            std::complex<double> w(1.0, 0.0);
            for (size_t k = 0; k < len / 2; k++) {
                const std::complex<double> u = a[i + k];
                const std::complex<double> v = a[i + k + len / 2] * w;
                a[i + k] = u + v;
                a[i + k + len / 2] = u - v;
                w *= wl;
            }
        }
    }
}

// RMS of x restricted to [loHz, hiHz), via Parseval on a zero-padded FFT.
// Passing 0 / rate/2 gives the full-band RMS, which is how the level sanity
// check below is computed — same code path, so the two cannot drift apart.
static double bandRms(const std::vector<float> &x, double rate, double loHz, double hiHz) {
    if (x.empty()) return 0.0;
    size_t m = 1;
    while (m < x.size()) m <<= 1;
    std::vector<std::complex<double>> buf(m, {0.0, 0.0});
    for (size_t i = 0; i < x.size(); i++) buf[i] = {(double)x[i], 0.0};
    fft(buf);

    const double binHz = rate / (double)m;
    const size_t kLo = (size_t)std::ceil(loHz / binHz);
    const size_t kHi = (size_t)std::min((double)(m / 2), std::floor(hiHz / binHz));

    double sum = 0.0;
    for (size_t k = kLo; k < kHi; k++) sum += std::norm(buf[k]);
    sum *= 2.0; // the mirrored negative-frequency half

    // Power averaged over the ORIGINAL sample count, not the padded length.
    const double power = sum / ((double)x.size() * (double)m);
    return std::sqrt(power);
}

static double db(double v) { return v > 0.0 ? 20.0 * std::log10(v) : -999.0; }

// FNV-1a over the raw bytes of the render. Two runs agreeing here agree
// sample-for-sample, which is how "the fix is a no-op on even lengths" gets
// stated as a fact rather than as agreement to two decimal places.
static uint64_t hashSamples(const std::vector<float> &x) {
    uint64_t h = 1469598103934665603ULL;
    const unsigned char *p = (const unsigned char *)x.data();
    for (size_t i = 0; i < x.size() * sizeof(float); i++) {
        h ^= p[i];
        h *= 1099511628211ULL;
    }
    return h;
}

// ------------------------------------------------------------ patch selection

// The 192 internal patches, at the ROM2 offsets PluginProcessor.cpp uses. Each
// record is 0x16a bytes and opens with a 12-character name.
struct PatchSlot { const char *bank; int base; };
static const PatchSlot kBanks[] = {
    {"User",       0x008ce0},
    {"Internal A", 0x010ce0},
    {"Internal B", 0x018ce0},
};
static const int kPatchesPerBank = 64;
static const int kPatchRecord = 0x16a;

static std::string patchName(const std::vector<uint8_t> &rom2, int bank, int j) {
    const uint8_t *p = &rom2[kBanks[bank].base + j * kPatchRecord];
    std::string n((const char *)p, 12);
    while (!n.empty() && (n.back() == ' ' || n.back() == '\0')) n.pop_back();
    return n;
}

// Loads a descrambled expansion card into the PCM expansion window, exactly as
// setCurrentProgram does when the selected patch lives on a card. The Cache
// copies written by the plugin are already descrambled, so they go in verbatim.
static std::vector<uint8_t> g_card;
static bool loadCard(MCU &mcu, const std::string &cachePath) {
    if (!readFile(cachePath, g_card, 0)) return false;
    if (g_card.size() < 0x800000) g_card.resize(0x800000, 0);
    memcpy(mcu.pcm.waverom_exp, g_card.data(), 0x800000);
    return true;
}

// Card patch / rhythm-set tables, at the offsets PluginProcessor.cpp reads.
static int cardPatchCount(const std::vector<uint8_t> &c) {
    return c[0x67] | c[0x66] << 8;
}
static size_t cardPatchOffset(const std::vector<uint8_t> &c) {
    return (size_t)(c[0x8f] | c[0x8e] << 8 | c[0x8d] << 16 | (uint32_t)c[0x8c] << 24);
}
static int cardDrumCount(const std::vector<uint8_t> &c) {
    return c[0x69] | c[0x68] << 8;
}
static size_t cardDrumOffset(const std::vector<uint8_t> &c) {
    return (size_t)(c[0x93] | c[0x92] << 8 | c[0x91] << 16 | (uint32_t)c[0x90] << 24);
}

// A card patch: same nvram write as an internal one, but the record comes from
// the card image rather than ROM2.
static void selectCardPatch(MCU &mcu, int j) {
    mcu.nvram[0x11] = 1;
    memcpy(&mcu.nvram[0x0d70], &g_card[cardPatchOffset(g_card) + (size_t)j * 0x16a], 0x16a);
    mcu.SC55_Reset();
}

// A rhythm set. Different area, different size, and nvram[0x11] = 0 -- this is
// the drum path, which keys many slots at once and is therefore the workload
// most unlike a sustained melodic patch.
static void selectDrumKit(MCU &mcu, int j) {
    mcu.nvram[0x11] = 0;
    memcpy(&mcu.nvram[0x67f0], &g_card[cardDrumOffset(g_card) + (size_t)j * 0xa7c], 0xa7c);
    mcu.SC55_Reset();
}

// Mirrors the non-drum half of VirtualJVProcessor::setCurrentProgram: mark the
// temp area as holding a patch, copy the record in, reset. Must run AFTER
// startSC55, which reloads nvram from the dump and resets on its own.
static void selectPatch(MCU &mcu, const std::vector<uint8_t> &rom2, int bank, int j) {
    mcu.nvram[0x11] = 1;
    memcpy(&mcu.nvram[0x0d70], &rom2[kBanks[bank].base + j * kPatchRecord], kPatchRecord);
    mcu.SC55_Reset();
}

// ---------------------------------------------------------------------- render

struct Result {
    double bandDb;
    double fullDb;
    double peak;
    unsigned int renderBufferFrames;
    double renderSeconds;   // wall time of the render loop alone
    uint64_t emulatedCycles; // mcu.cycles at the end -- the emulated timeline
    uint64_t hash;       // FNV-1a over the rendered samples, for bit-exactness
    long long dropped;   // emulator samples that never reached the resampler
    long long carried;   // emulator samples held over for the next block
};

// Recomputes renderBufferFrames exactly as updateSC55WithSampleRate does,
// including the samplesError half-buffer compensation. Both inputs are public
// MCU members, so the harness can predict the value without instrumenting the
// emulator at all — which is what lets the identical binary-level measurement
// run against the patched and unpatched trees.
static unsigned int predictRenderBufferFrames(double samplesError, int nFrames, int rate) {
    const double f = (double)nFrames / rate * 64000.0;
    unsigned int rbf = (unsigned int)std::ceil(f);
    const int limit = nFrames / 2;
    if (samplesError > limit)       rbf -= limit;
    else if (-samplesError > limit) rbf += limit;
    return rbf;
}

static Result renderChord(MCU &mcu, const std::vector<uint8_t> &rom1,
                          const std::vector<uint8_t> &rom2,
                          const std::vector<uint8_t> &wave1,
                          const std::vector<uint8_t> &wave2,
                          const std::vector<uint8_t> &nvram,
                          int rate, int block, double seconds,
                          int bank, int patchIdx) {
    // Full restart per configuration: startSC55 memsets the MCU, reloads every
    // ROM and calls SC55_Reset, so no state can leak between configurations and
    // bias the comparison.
    mcu.startSC55(rom1.data(), rom2.data(), wave1.data(), wave2.data(), nvram.data());
    if (!g_card.empty()) memcpy(mcu.pcm.waverom_exp, g_card.data(), 0x800000);
    if (bank >= 0)        selectPatch(mcu, rom2, bank, patchIdx);
    else if (bank == -2)  selectCardPatch(mcu, patchIdx);
    else if (bank == -3)  selectDrumKit(mcu, patchIdx);

    std::vector<float> l((size_t)block), r((size_t)block);

    // The emulated firmware ignores MIDI for roughly a second after a reset.
    // Two seconds of silent blocks clears that window with margin.
    const int warmup = (int)(2.0 * rate / block);
    for (int b = 0; b < warmup; b++)
        mcu.updateSC55WithSampleRate(l.data(), r.data(), (unsigned)block, rate);

    const int blocks = (int)(seconds * rate / block);
    std::vector<float> rec;
    rec.reserve((size_t)blocks * (size_t)block);

    long long dropped = 0, carried = 0;

    const auto t0 = std::chrono::steady_clock::now();

    for (int b = 0; b < blocks; b++) {
        if (b == 2) {
            // A four-note chord: far more broadband content than one note, and
            // the same notes our fork's harness uses.
            const uint8_t notes[4] = {60, 64, 67, 71};
            const int nNotes = getenv("JV880_NOTES") ? atoi(getenv("JV880_NOTES")) : 4;
            for (int ni = 0; ni < nNotes && ni < 4; ni++) {
                const uint8_t n = notes[ni];
                const uint8_t msg[3] = {0x90, n, 100};
                mcu.postMidiSC55(msg, 3);
            }
        }
        // Predict the target BEFORE the call, while samplesError still holds the
        // value the call will read.
        const long long rbf = (long long)predictRenderBufferFrames(mcu.samplesError, block, rate);
        mcu.updateSC55WithSampleRate(l.data(), r.data(), (unsigned)block, rate);

        // The render loop stops at the first sample_write_ptr >= rbf and the
        // resampler is handed exactly rbf samples, so anything beyond rbf is
        // overshoot. What sample_write_ptr holds on return tells us its fate,
        // and the two trees leave different things there:
        //
        //   unpatched: the loop-exit count, >= rbf. The next call's
        //              `sample_write_ptr = 0` discards the excess.
        //              -> (swp - rbf) samples DROPPED.
        //   patched:   the leftover, 0 or 1, already memmoved to the front of
        //              the buffer for the next block to consume.
        //              -> (swp) samples CARRIED, none dropped.
        //
        // One expression covers both, and the counter it feeds means the same
        // thing in each: how many emulator samples never reached the resampler.
        // Note >=, not >. Unpatched with an EVEN count the loop lands exactly on
        // rbf; that is the unpatched path with nothing dropped, not a carry.
        const long long swp = (long long)mcu.sample_write_ptr;
        if (swp >= rbf) dropped += swp - rbf;
        else            carried += swp;

        rec.insert(rec.end(), l.begin(), l.end());
    }

    const auto t1 = std::chrono::steady_clock::now();

    Result out{};
    out.renderSeconds = std::chrono::duration<double>(t1 - t0).count();
    out.emulatedCycles = mcu.mcu.cycles;
    out.bandDb = db(bandRms(rec, rate, 4000.0, 8000.0));
    out.fullDb = db(bandRms(rec, rate, 0.0, rate / 2.0));
    out.peak = 0.0;
    for (float v : rec) out.peak = std::max(out.peak, (double)std::fabs(v));
    out.renderBufferFrames = (unsigned int)std::ceil((double)block / rate * 64000.0);
    out.hash = hashSamples(rec);
    out.dropped = dropped;
    out.carried = carried;
    return out;
}

// ------------------------------------------------------------------------ main

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: blockdrop_test <rom-dir>\n");
        return 2;
    }
    const std::string dir = std::string(argv[1]) + "/";

    std::vector<uint8_t> rom1, rom2, nvram, wave1s, wave2s;
    if (!readFile(dir + "jv880_rom1.bin", rom1, 32 * 1024)) return 1;
    if (!readFile(dir + "jv880_rom2.bin", rom2, 256 * 1024)) return 1;
    if (!readFile(dir + "jv880_nvram.bin", nvram, 32 * 1024)) return 1;
    if (!readFile(dir + "jv880_waverom1.bin", wave1s, 2 * 1024 * 1024)) return 1;
    if (!readFile(dir + "jv880_waverom2.bin", wave2s, 2 * 1024 * 1024)) return 1;

    std::vector<uint8_t> wave1(wave1s.size()), wave2(wave2s.size());
    unscrambleRomLocal(wave1s.data(), wave1.data(), (int)wave1s.size());
    unscrambleRomLocal(wave2s.data(), wave2.data(), (int)wave2s.size());

    const double seconds = getenv("JV880_SECS") ? atof(getenv("JV880_SECS")) : 3.0;

    std::unique_ptr<MCU> scanMcu(new MCU());
    std::unique_ptr<MCU> mcu(new MCU());

    // --scan: rank every internal patch by how much 4-8 kHz content it makes on
    // its own, rendered in a configuration that has no artifact (even length,
    // resampler bypassed). A patch near the bottom of this list leaves the most
    // headroom for the defect to show above, which is the whole point of
    // choosing one rather than accepting the power-on default.
    if (argc > 2 && std::string(argv[2]) == "--scan") {
        struct Row { double band; double peak; int bank; int idx; std::string name; };
        std::vector<Row> rows;
        for (int b = 0; b < 3; b++)
            for (int j = 0; j < kPatchesPerBank; j++) {
                Result r = renderChord(*scanMcu, rom1, rom2, wave1, wave2, nvram,
                                       64000, 32, 1.5, b, j);
                rows.push_back({r.bandDb, r.peak, b, j, patchName(rom2, b, j)});
            }
        std::sort(rows.begin(), rows.end(),
                  [](const Row &a, const Row &c) { return a.band < c.band; });
        printf("%-12s %-4s %-14s %10s %9s\n", "bank", "idx", "name", "4-8kHz dB", "peak");
        printf("--------------------------------------------------------------\n");
        for (const Row &r : rows) {
            // Skip anything too quiet to measure meaningfully -- a silent patch
            // trivially has no 4-8 kHz content and would top this list.
            if (r.peak < 0.02) continue;
            printf("%-12s %-4d %-14s %10.2f %9.5f\n",
                   kBanks[r.bank].bank, r.idx, r.name.c_str(), r.band, r.peak);
        }
        return 0;
    }

    // --stress <rate> <block>: the bit-exactness workload the plain sweep does
    // NOT cover. A sustained chord exercises almost no MIDI traffic and never
    // releases a voice, which is exactly the wrong shape for validating changes
    // to interrupt dispatch, timer scheduling and PCM voice state. This drives
    // continuous note on/off churn across the whole keyboard plus periodic
    // program changes, so the UART keeps delivering bytes, voices keep entering
    // and leaving release, and the firmware keeps being interrupted.
    if (argc > 4 && std::string(argv[2]) == "--stress") {
        const int rate = atoi(argv[3]);
        const int block = atoi(argv[4]);
        // Optional trailing "<cache-file> patch|drum <idx>" runs the churn on a
        // card patch or a rhythm set instead of the default internal patch.
        int sBank = 1, sIdx = 48;
        if (argc > 7) {
            if (!loadCard(*mcu, argv[5])) return 1;
            sBank = std::string(argv[6]) == "drum" ? -3 : -2;
            sIdx = atoi(argv[7]);
            printf("card: %s %s #%d\n", argv[5], argv[6], sIdx);
        }
        mcu->startSC55(rom1.data(), rom2.data(), wave1.data(), wave2.data(), nvram.data());
        if (!g_card.empty()) memcpy(mcu->pcm.waverom_exp, g_card.data(), 0x800000);
        if (sBank >= 0)       selectPatch(*mcu, rom2, sBank, sIdx);
        else if (sBank == -2) selectCardPatch(*mcu, sIdx);
        else                  selectDrumKit(*mcu, sIdx);

        std::vector<float> l((size_t)block), r((size_t)block);
        const int warmup = (int)(2.0 * rate / block);
        for (int b = 0; b < warmup; b++)
            mcu->updateSC55WithSampleRate(l.data(), r.data(), (unsigned)block, rate);

        const int blocks = (int)(seconds * rate / block);
        std::vector<float> rec;
        rec.reserve((size_t)blocks * (size_t)block);

        // Deterministic pseudo-random churn: same sequence in both trees, so a
        // hash mismatch means the emulator diverged, not the stimulus.
        uint32_t rng = 0x12345678;
        auto next = [&rng]() { rng = rng * 1664525u + 1013904223u; return rng >> 16; };
        std::vector<uint8_t> held;

        for (int b = 0; b < blocks; b++) {
            const uint32_t roll = next() % 100;
            if (roll < 30) {
                const uint8_t note = (uint8_t)(36 + next() % 48);
                const uint8_t on[3] = {0x90, note, (uint8_t)(40 + next() % 80)};
                mcu->postMidiSC55(on, 3);
                held.push_back(note);
            } else if (roll < 55 && !held.empty()) {
                const size_t k = next() % held.size();
                const uint8_t off[3] = {0x80, held[k], 64};
                mcu->postMidiSC55(off, 3);
                held.erase(held.begin() + (long)k);
            } else if (roll < 60) {
                const uint8_t cc[3] = {0xB0, 1, (uint8_t)(next() % 128)}; // mod wheel
                mcu->postMidiSC55(cc, 3);
            } else if (roll == 61) {
                const uint8_t pc[2] = {0xC0, (uint8_t)(next() % 64)};
                mcu->postMidiSC55(pc, 2);
            } else if (roll == 62) {
                // Front-panel input. Named explicitly in the SLEEP
                // fast-forward's correctness argument as state arriving from
                // outside the render call, so it has to be in the workload that
                // validates it -- MIDI alone would leave that claim untested.
                mcu->MCU_EncoderTrigger((int)(next() & 1));
            } else if (roll == 63) {
                mcu->mcu_button_pressed = 1u << (next() % 8);
            } else if (roll == 64) {
                mcu->mcu_button_pressed = 0;
            }
            mcu->updateSC55WithSampleRate(l.data(), r.data(), (unsigned)block, rate);
            rec.insert(rec.end(), l.begin(), l.end());
        }

        double peak = 0.0;
        for (float v : rec) peak = std::max(peak, (double)std::fabs(v));
        printf("stress %d/%d  %.1fs  events~%d  peak=%.5f  cycles=%llu  hash=%llx\n",
               rate, block, seconds, blocks, peak,
               (unsigned long long)mcu->mcu.cycles,
               (unsigned long long)hashSamples(rec));
        if (peak < 1e-4) { printf("FAIL: stress rendered silence\n"); return 1; }
        return 0;
    }

    // --bench <rate> <block> [reps]: time the render loop alone, best of reps.
    // Best-of rather than mean: scheduling noise only ever ADDS time, so the
    // minimum is the least-contaminated estimate of the work actually done.
    // Also reports mcu.cycles, the emulated timeline -- an optimisation that is
    // genuinely just doing less work per step leaves this identical, while one
    // that changed WHEN things happen would move it.
    if (argc > 4 && std::string(argv[2]) == "--bench") {
        const int rate = atoi(argv[3]);
        const int block = atoi(argv[4]);
        const int reps = argc > 5 ? atoi(argv[5]) : 5;
        const int bank = argc > 7 ? atoi(argv[6]) : 1;
        const int idx  = argc > 7 ? atoi(argv[7]) : 48;

        double best = 1e30;
        uint64_t cycles = 0, hash = 0;
        for (int i = 0; i < reps; i++) {
            Result r = renderChord(*scanMcu, rom1, rom2, wave1, wave2, nvram,
                                   rate, block, seconds, bank, idx);
            best = std::min(best, r.renderSeconds);
            cycles = r.emulatedCycles;
            hash = r.hash;
        }
        printf("bench %d/%d  %.1fs audio  best-of-%d: %.4f s   cycles=%llu   hash=%llx\n",
               rate, block, seconds, reps, best,
               (unsigned long long)cycles, (unsigned long long)hash);
        return 0;
    }

    // --card <cache-file> <patch|drum> <idx>: run the same 5-config sweep, but
    // with an expansion card mapped into the PCM expansion window and either one
    // of its patches or one of its rhythm sets selected. Rhythm sets matter most
    // here: they key many PCM slots at once, which is the workload least like
    // the sustained melodic patches the other modes render.
    int useBank = -1, useIdx = 0;
    if (argc > 5 && std::string(argv[2]) == "--card") {
        if (!loadCard(*mcu, argv[3])) return 1;
        const bool drum = std::string(argv[4]) == "drum";
        useIdx = atoi(argv[5]);
        useBank = drum ? -3 : -2;
        printf("card: %s  %s #%d  (card has %d patches, %d rhythm sets)\n\n",
               argv[3], drum ? "rhythm set" : "patch", useIdx,
               cardPatchCount(g_card), cardDrumCount(g_card));
    }

    // --patch <bank> <idx> selects one for the sweep; default -1 keeps the
    // power-on patch.
    if (argc > 4 && std::string(argv[2]) == "--patch") {
        useBank = atoi(argv[3]);
        useIdx = atoi(argv[4]);
        printf("patch: %s #%d  \"%s\"\n\n", kBanks[useBank].bank, useIdx,
               patchName(rom2, useBank, useIdx).c_str());
    } else if (useBank == -1) {
        printf("patch: power-on default\n\n");
    }

    struct Config { int rate; int block; const char *note; };
    const Config configs[] = {
        {64000, 32, "resampler bypassed, even"},
        {64000, 33, "resampler bypassed, ODD"},
        {48000, 32, "ODD"},
        {44100, 32, "ODD"},
        {48000, 48, "even (control)"},
    };


    printf("%-7s %-6s %-6s %-5s %10s %9s %8s %18s  %s\n",
           "rate", "block", "rbFrm", "par", "4-8kHz dB", "DROPPED", "carried", "render hash", "note");
    printf("---------------------------------------------------------------------------------------------\n");

    bool anySilent = false;
    for (const Config &c : configs) {
        Result res = renderChord(*mcu, rom1, rom2, wave1, wave2, nvram,
                                 c.rate, c.block, seconds, useBank, useIdx);
        const bool odd = (res.renderBufferFrames % 2) != 0;
        printf("%-7d %-6d %-6u %-5s %10.2f %9lld %8lld %18llx  %s\n",
               c.rate, c.block, res.renderBufferFrames, odd ? "odd" : "even",
               res.bandDb, res.dropped, res.carried,
               (unsigned long long)res.hash, c.note);
        if (res.peak < 1e-4) anySilent = true;
        fflush(stdout);
    }

    // A measurement over silence is deterministic, reproducible and completely
    // meaningless. Refuse to report one as a result.
    if (anySilent) {
        printf("\nFAIL: at least one configuration rendered silence — the numbers above\n"
               "      describe nothing. Check the ROM set and the MIDI path.\n");
        return 1;
    }
    printf("\nAll configurations rendered audible signal (peak > 1e-4).\n");
    return 0;
}
