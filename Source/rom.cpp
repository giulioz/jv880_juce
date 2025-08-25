#include "rom.h"

#include "sha1.h"
#include <JuceHeader.h>
#include <algorithm>

const size_t sz8M = 8 * 1024 * 1024;
const size_t sz2M = 2 * 1024 * 1024;
const size_t sz32K = 32 * 1024;
const size_t sz128K = 128 * 1024;
const size_t sz256K = 256 * 1024;

RomInfo romInfos[romCount] = {
    RomInfo{sz32K, "jv880_nvram.bin", "d2bc039f4e9748f2aa72db0dc8822591c53d580f", false, "", false},
    RomInfo{sz32K, "jv880_rom1.bin", "6c1b59905b361ac3c4803d39589406bc3e1d0647", false, "", false},
    RomInfo{sz256K, "jv880_rom2.bin", "282116e8e8471053cf159d22675931592b7f7c8f", false, "", false},
    RomInfo{sz2M, "jv880_waverom1.bin", "37e28498351fb502f6d43398d288a026c02b446d", true, "3e2eaf248a81960b2849441a2ab6e2ac8cf58037", false},
    RomInfo{sz2M, "jv880_waverom2.bin", "963ce75b6668dab377d3a2fd895630a745491be5", true, "b2d922dad4169bd30ab517418cc4263a0f20c22e", false},
    RomInfo{sz128K, "rd500_patches.bin", "7cabda023e41a8fe4398074457bd85d6732e9914", false, "", false},
    RomInfo{sz8M, "rd500_expansion.bin", "c81b491c8536298470f5444dd4cdd45c2c93c6f2", true, "5f8fbdcb30f8d353bad6860f74686b3419fed889", false},
    RomInfo{sz8M, "SR-JV80-01 Pop - CS 0x3F1CF705.bin", "aeb02a1af5031194c723030b133fda6bfb5463f6", true, "b1a825c60cebedd5bcb0709f4ed874322df4da9b", false},
    RomInfo{sz8M, "SR-JV80-02 Orchestral - CS 0x3F0E09E2.BIN", "6f8e3113e7f53b0df1f7f0bd9a0627cc655a6a1c", true, "635850b86e9682f090ad49e87cb1f59ab1d31b4d", false},
    RomInfo{sz8M, "SR-JV80-03 Piano - CS 0x3F8DB303.bin", "899b68001674b92d82ad86dfb69c62365e368284", true, "3450d81ffeec8f2e46fd1711ea636956c19f17ca", false},
    RomInfo{sz8M, "SR-JV80-04 Vintage Synth - CS 0x3E23B90C.BIN", "29fe6c1dde042ff2147c73f1c9d5fcf58092879a", true, "461907c2208abe2e66f11112810667c13da890bf", false},
    RomInfo{sz8M, "SR-JV80-05 World - CS 0x3E8E8A0D.bin", "c0a64d6ab04fac96ceba09becd4be888304c72a6", true, "f91d717d0ac8b530b9887a1b0b751fc15c80fea0", false},
    RomInfo{sz8M, "SR-JV80-06 Dance - CS 0x3EC462E0.bin", "e2bed925027ed2f73e15aba3c46bf951c93a0716", true, "b18c3ec3d5d0308de393dee8e8e603126d51f01f", false},
    RomInfo{sz8M, "SR-JV80-07 Super Sound Set - CS 0x3F1EE208.bin", "be45e76154cee6571e7bacb5633b21945b055843", true, "d403b1e8d77dd374a8fa753f13ba83577410d377", false},
    RomInfo{sz8M, "SR-JV80-08 Keyboards of the 60s and 70s - CS 0x3F1E3F0A.BIN", "9652aa26ed091c11d3a89449e8feba5ab73b4bc7", true, "03054a4695f8e451368fb621b0a36e7026c688a0", false},
    RomInfo{sz8M, "SR-JV80-09 Session - CS 0x3F381791.BIN", "50e67516a0c996b9813dfdac6c1d08709057e405", true, "ffb8957b0fb894aa36e4879a9b5eb800b4185cb7", false},
    RomInfo{sz8M, "SR-JV80-10 Bass & Drum - CS 0x3D83D02A.BIN", "0719e32f001d012769cc92b5dc1ea75882fa0656", true, "1a1af6a99cd34d149ccf37f0de70d862ce6e48ca", false},
    RomInfo{sz8M, "SR-JV80-11 Techno - CS 0x3F046250.bin", "880d032b9b2ae97869358161b427c6c8d529f2f8", true, "8987499c2d1c77e70ac7c386f194858375e53a19", false},
    RomInfo{sz8M, "SR-JV80-12 HipHop - CS 0x3EA08A19.BIN", "d3d4ff39659bbe993cf6582c145d0db1f1e79b26", true, "bfea6a3e20d7ba4d0601a4948ecdf67ab6756980", false},
    RomInfo{sz8M, "SR-JV80-13 Vocal - CS 0x3ECE78AA.bin", "6fd05df901127291e0b74304038ccea79c9a8812", true, "4421ed9fd1b59c79d00530f186fe49eff191cbf2", false},
    RomInfo{sz8M, "SR-JV80-14 Asia - CS 0x3C8A1582.bin", "4127864976393052f74fddf9e0a3bbe27f9324df", true, "0841a2415fa28c02c2b62b998e6567569f4f98dc", false},
    RomInfo{sz8M, "SR-JV80-15 Special FX - CS 0x3F591CE4.bin", "54b898f76e698e7bafbf093d616ad2df4df6dc82", true, "3648b448f29d7a59db733d8d676ddb82caeefff0", false},
    RomInfo{sz8M, "SR-JV80-16 Orchestral II - CS 0x3F35B03B.bin", "216cde7393d5fd57cabe4c2d4bbc5f65f0c07e90", true, "e0a3da9e41677606810acd37300f0671a212f46d", false},
    RomInfo{sz8M, "SR-JV80-17 Country - CS 0x3ED75089.bin", "07eaf0a7f822d8369c33b77a9fe2f2a3ea2f7713", true, "a779038e3f6dcca89db26fe98767579be74f6713", false},
    RomInfo{sz8M, "SR-JV80-18 Latin - CS 0x3EA51033.BIN", "bb177db61f6f32d7bcc693e4c23d162a3ade3801", true, "402eacaecdaa7d04747887700b23d9f1edda2acf", false},
    RomInfo{sz8M, "SR-JV80-19 House - CS 0x3E330C41.BIN", "23ce90ce898ef59a6268070644ab18c7b7834509", true, "1aded637852277ec600a7504fa10cee4053c36e1", false},
    RomInfo{sz8M, "Custom.bin", "", true, "", false}
};

int getRomIndex(std::string filename) {
  for (int i = 0; i < romCount; i++) {
    std::string fn = filename;
    std::string romfn = romInfos[i].filename;

    if (fn.compare(romfn) == 0)
      return i;
  }
  return -1;
}

bool loadRom(int romI, uint8_t *dst, std::array<uint8_t *, romCount> &cache) {
  if (romI < romCountChk && cache[romI] != nullptr) {
    if (dst != nullptr)
      memcpy(dst, cache[romI], romInfos[romI].length);
    romInfos[romI].loaded = true;
    return true;
  }

  RomInfo *romInfo = &romInfos[romI];

  juce::File romsDir(
      juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)
          .getChildFile("JV880"));
  if (!romsDir.exists())
    romsDir.createDirectory();

  juce::File cacheDir(romsDir.getChildFile("Cache"));
  if (!cacheDir.exists())
    cacheDir.createDirectory();

  juce::File romFileUnscrambled(cacheDir.getChildFile(romInfo->filename));
  juce::File romFile(romsDir.getChildFile(romInfo->filename));

  bool shouldUnscramble = false;
  juce::File *finalFileToRead = nullptr;

  // Already unscrambled
  if (romFileUnscrambled.exists()) {
    finalFileToRead = &romFileUnscrambled;
    shouldUnscramble = false;
  }

  // No unscrambling needed
  else if (!romInfo->needsUnscramble) {
    finalFileToRead = &romFile;
    shouldUnscramble = false;
  }

  // Unscrambling needed
  else {
    finalFileToRead = &romFile;
    shouldUnscramble = true;
  }

  juce::FileInputStream inputStream(*finalFileToRead);
  if (inputStream.failedToOpen()) {
    return false;
  }
  uint8_t *data = (uint8_t *)malloc(romInfo->length);
  int readt = inputStream.read(data, romInfo->length);

  uint8_t shasum[20] = {0};
  char shasumHex[41] = {0};
  sha1::calc(data, readt, shasum);
  sha1::toHexString(shasum, shasumHex);
  auto &sumToCompare = !shouldUnscramble && romInfo->needsUnscramble
                                 ? romInfo->checksumUnscrambled
                                 : romInfo->checksum;
  if (readt != romInfo->length || (strcmp(shasumHex, sumToCompare.c_str()) != 0 && romI < romCountChk)) {
    free(data);
    romInfos[romI].loaded = false;
    return false;
  }

  uint8_t *dataOut = (uint8_t *)malloc(romInfo->length);

  if (shouldUnscramble) {
    unscrambleRom(data, dataOut, romInfo->length);
    romFileUnscrambled.create();
    juce::FileOutputStream outputStream(romFileUnscrambled);
    outputStream.write(dataOut, romInfo->length);
  } else {
    memcpy(dataOut, data, romInfo->length);
  }
  free(data);

  cache[romI] = (uint8_t *)malloc(romInfo->length);
  memcpy(cache[romI], dataOut, romInfo->length);
  if (dst != nullptr)
    memcpy(dst, dataOut, romInfo->length);
  free(dataOut);
    
  romInfos[romI].loaded = true;
  return true;
}

//static void openRomFolder(int /* param */) {
//  juce::File romsDir(
//      juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)
//          .getChildFile("JV880"));
//  if (romsDir.exists()) {
//    juce::Process::openDocument(romsDir.getFullPathName(), "");
//  }
//}

bool preloadAll(std::array<uint8_t *, romCount> &cache) {
  auto showNoRomError = [](const char* /* name */) {
    //     juce::AlertWindow::showAsync(
    //         juce::MessageBoxOptions()
    //             .withIconType(juce::MessageBoxIconType::WarningIcon)
    //             .withTitle("Error")
    //             .withMessage(
    //                 juce::String("Cannot load rom file: ") + name +
    //                 juce::String("Please check the file path and try
    //                 again."))
    //             .withButton("OK"),
    //         nullptr);
  };

  auto showNoRomFolderError = []() {
    //     juce::AlertWindow::showAsync(
    //         juce::MessageBoxOptions()
    //             .withIconType(juce::MessageBoxIconType::WarningIcon)
    //             .withTitle("Error")
    //             .withMessage(
    //                 "The ROM folder is empty. Please copy your rom files to
    //                 the " "ROM folder to continue.")
    //             .withButton("Open Folder"),
    //         openRomFolder);
  };

  juce::File romsDir(
      juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)
          .getChildFile("JV880"));
  if (!romsDir.exists()) {
    romsDir.createDirectory();
    showNoRomFolderError();
    return false;
  }

  juce::File cacheDir(romsDir.getChildFile("Cache"));
  if (!cacheDir.exists()) {
    cacheDir.createDirectory();
  }

  for (int i = 0; i < romCount; i++) {
    if (!loadRom(i, nullptr, cache) && i < romCountRequired)
      return false;
  }
  return true;
}

void unscrambleRom(const uint8_t *src, uint8_t *dst, int len) {
  for (int i = 0; i < len; i++) {
    int address = i & ~0xfffff;
    static const int aa[] = {2, 0,  3,  4,  1, 9, 13, 10, 18, 17,
                             6, 15, 11, 16, 8, 5, 12, 7,  14, 19};
    for (int j = 0; j < 20; j++) {
      if (i & (1 << j))
        address |= 1 << aa[j];
    }
    uint8_t srcdata = src[address];
    uint8_t data = 0;
    static const int dd[] = {2, 0, 4, 5, 7, 6, 3, 1};
    for (int j = 0; j < 8; j++) {
      if (srcdata & (1 << dd[j]))
        data |= 1 << j;
    }
    dst[i] = data;
  }
}
