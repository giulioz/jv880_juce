/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Jv880_juceAudioProcessor::Jv880_juceAudioProcessor()
    : AudioProcessor(
          BusesProperties()
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)) {

  mcu = new MCU();

  if (!preloadAll(loadedRoms))
    return;

  mcu->startSC55(loadedRoms[getRomIndex("jv880_rom1.bin")],
                 loadedRoms[getRomIndex("jv880_rom2.bin")],
                 loadedRoms[getRomIndex("jv880_waverom1.bin")],
                 loadedRoms[getRomIndex("jv880_waverom2.bin")],
                 loadedRoms[getRomIndex("jv880_nvram.bin")]);

  int currentPatchI = 0;

  patchInfoPerGroup.push_back(std::vector<PatchInfo *>());

  // Internal User
  for (int j = 0; j < 64; j++) {
    patchInfos[currentPatchI].name =
        (const char *)&loadedRoms[getRomIndex("jv880_rom2.bin")]
                                 [0x008ce0 + j * 0x16a];
    patchInfos[currentPatchI].nameLength = 0xc;
    patchInfos[currentPatchI].expansionI = 0xff;
    patchInfos[currentPatchI].patchI = j;
    patchInfos[currentPatchI].present = true;
    patchInfos[currentPatchI].drums = false;
    patchInfos[currentPatchI].iInList = currentPatchI;
    patchInfoPerGroup[0].push_back(&patchInfos[currentPatchI]);
    currentPatchI++;
  }
  patchInfos[currentPatchI].name = "Drums Internal User";
  patchInfos[currentPatchI].ptr =
      (char *)&loadedRoms[getRomIndex("jv880_rom2.bin")][0x00e760];
  patchInfos[currentPatchI].nameLength = 21;
  patchInfos[currentPatchI].expansionI = 0xff;
  patchInfos[currentPatchI].patchI = 0;
  patchInfos[currentPatchI].present = true;
  patchInfos[currentPatchI].drums = true;
  patchInfos[currentPatchI].iInList = currentPatchI;
  patchInfoPerGroup[0].push_back(&patchInfos[currentPatchI]);
  currentPatchI++;

  // Internal A
  for (int j = 0; j < 64; j++) {
    patchInfos[currentPatchI].name =
        (const char *)&loadedRoms[getRomIndex("jv880_rom2.bin")]
                                 [0x010ce0 + j * 0x16a];
    patchInfos[currentPatchI].nameLength = 0xc;
    patchInfos[currentPatchI].expansionI = 0xff;
    patchInfos[currentPatchI].patchI = j;
    patchInfos[currentPatchI].present = true;
    patchInfos[currentPatchI].drums = false;
    patchInfos[currentPatchI].iInList = currentPatchI;
    patchInfoPerGroup[0].push_back(&patchInfos[currentPatchI]);
    currentPatchI++;
  }
  patchInfos[currentPatchI].name = "Drums Internal A";
  patchInfos[currentPatchI].ptr =
      (char *)&loadedRoms[getRomIndex("jv880_rom2.bin")][0x016760];
  patchInfos[currentPatchI].nameLength = 21;
  patchInfos[currentPatchI].expansionI = 0xff;
  patchInfos[currentPatchI].patchI = 0;
  patchInfos[currentPatchI].present = true;
  patchInfos[currentPatchI].drums = true;
  patchInfos[currentPatchI].iInList = currentPatchI;
  patchInfoPerGroup[0].push_back(&patchInfos[currentPatchI]);
  currentPatchI++;

  // Internal B
  for (int j = 0; j < 64; j++) {
    patchInfos[currentPatchI].name =
        (const char *)&loadedRoms[getRomIndex("jv880_rom2.bin")]
                                 [0x018ce0 + j * 0x16a];
    patchInfos[currentPatchI].nameLength = 0xc;
    patchInfos[currentPatchI].expansionI = 0xff;
    patchInfos[currentPatchI].patchI = j;
    patchInfos[currentPatchI].present = true;
    patchInfos[currentPatchI].drums = false;
    patchInfos[currentPatchI].iInList = currentPatchI;
    patchInfoPerGroup[0].push_back(&patchInfos[currentPatchI]);
    currentPatchI++;
  }
  patchInfos[currentPatchI].name = "Drums Internal B";
  patchInfos[currentPatchI].ptr =
      (char *)&loadedRoms[getRomIndex("jv880_rom2.bin")][0x01e760];
  patchInfos[currentPatchI].nameLength = 21;
  patchInfos[currentPatchI].expansionI = 0xff;
  patchInfos[currentPatchI].patchI = 0;
  patchInfos[currentPatchI].present = true;
  patchInfos[currentPatchI].drums = true;
  patchInfos[currentPatchI].iInList = currentPatchI;
  patchInfoPerGroup[0].push_back(&patchInfos[currentPatchI]);
  currentPatchI++;

  for (int i = 0; i < NUM_EXPS; i++) {
    const int isRD500 = (i == 0);

    patchInfoPerGroup.push_back(std::vector<PatchInfo *>());

    if ((isRD500 && !romInfos[romCountRequired].loaded) || !romInfos[i + romCountRequired + 1].loaded)
      continue;

    expansionsDescr[i] = loadedRoms[i + 6];

    // get patches
    int nPatches = isRD500 ? 192 : expansionsDescr[i][0x67] | expansionsDescr[i][0x66] << 8;

    for (int j = 0; j < nPatches; j++) {
      size_t patchesOffset =
          expansionsDescr[i][0x8f] | expansionsDescr[i][0x8e] << 8 |
          expansionsDescr[i][0x8d] << 16 | expansionsDescr[i][0x8c] << 24;

      if (isRD500)
      {
        if (j < 64)
          patchesOffset = 0x0ce0;
        else if (j < 128)
          patchesOffset = 0x8370;
        else
          patchesOffset = 0x12b82;
      }

      patchInfos[currentPatchI].name =
          (char *)&expansionsDescr[i][patchesOffset + j * 0x16a];

      if (isRD500)
        patchInfos[currentPatchI].name =
            (char *)&loadedRoms[getRomIndex("rd500_patches.bin")]
                               [patchesOffset + (j % 64) * 0x16a];

      patchInfos[currentPatchI].nameLength = 0xc;
      patchInfos[currentPatchI].expansionI = i;
      patchInfos[currentPatchI].patchI = j;
      patchInfos[currentPatchI].present = true;
      patchInfos[currentPatchI].drums = false;
      patchInfos[currentPatchI].iInList = currentPatchI;
      patchInfoPerGroup[i + 1].push_back(&patchInfos[currentPatchI]);
      currentPatchI++;
    }

    // get drumkits
    int nDrumkits = isRD500 ? 3 : expansionsDescr[i][0x69] | expansionsDescr[i][0x68] << 8;

    for (int j = 0; j < nDrumkits; j++) {
      size_t patchesOffset =
          expansionsDescr[i][0x93] | expansionsDescr[i][0x92] << 8 |
          expansionsDescr[i][0x91] << 16 | expansionsDescr[i][0x90] << 24;

      if (isRD500)
      {
        if (j < 64)
          patchesOffset = 0x6760;
        else if (j < 128)
          patchesOffset = 0xd2a0;
        else
          patchesOffset = 0x18602;
      }

      char *namePtr = (char *)calloc(32, 1);
      patchInfos[currentPatchI].name = namePtr;
      sprintf(namePtr, "Exp %d Drums %d", i, j);

      patchInfos[currentPatchI].ptr =
          (const char *)&expansionsDescr[i][patchesOffset + j * 0xa7c];

      if (isRD500)
        patchInfos[currentPatchI].ptr =
            (const char *)&loadedRoms[getRomIndex("rd500_patches.bin")]
                                     [patchesOffset];

      patchInfos[currentPatchI].nameLength = strlen(namePtr);
      patchInfos[currentPatchI].expansionI = i;
      patchInfos[currentPatchI].patchI = j;
      patchInfos[currentPatchI].present = true;
      patchInfos[currentPatchI].drums = true;
      patchInfos[currentPatchI].iInList = currentPatchI;
      patchInfoPerGroup[i + 1].push_back(&patchInfos[currentPatchI]);
      currentPatchI++;
    }

    // total count
    totalPatchesExp += nPatches;
    totalPatchesExp += nDrumkits;
  }

  loaded = true;
}

Jv880_juceAudioProcessor::~Jv880_juceAudioProcessor() {
  mcuLock.enter();
  memset(mcu, 0, sizeof(MCU));
  delete mcu;
  mcuLock.exit();
}

//==============================================================================
const juce::String Jv880_juceAudioProcessor::getName() const {
  return JucePlugin_Name;
}

bool Jv880_juceAudioProcessor::acceptsMidi() const { return true; }

bool Jv880_juceAudioProcessor::producesMidi() const { return false; }

bool Jv880_juceAudioProcessor::isMidiEffect() const { return false; }

double Jv880_juceAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int Jv880_juceAudioProcessor::getNumPrograms() {
  return 65                // internal
         + 65              // bank A
         + 65              // bank B
         + totalPatchesExp // expansions
      ;
}

int Jv880_juceAudioProcessor::getCurrentProgram() {
  return 0; // TODO
}

void Jv880_juceAudioProcessor::setCurrentProgram(int index) {
  if (index < 0 || index >= getNumPrograms())
    return;

  if (!loaded)
    return;

  mcuLock.enter();

  int expansionI = patchInfos[index].expansionI;
  if (expansionI != 0xff && status.currentExpansion != expansionI) {
    status.currentExpansion = expansionI;
    memcpy(mcu->pcm.waverom_exp, expansionsDescr[expansionI], 0x800000);
    mcu->SC55_Reset();
  }

  if (patchInfos[index].drums) {
    status.isDrums = true;
    mcu->nvram[0x11] = 0;
    memcpy(&mcu->nvram[0x67f0], (uint8_t *)patchInfos[index].ptr, 0xa7c);
    memcpy(status.drums, &mcu->nvram[0x67f0], 0xa7c);
    mcu->SC55_Reset();
  } else {
    status.isDrums = false;
    if (mcu->nvram[0x11] != 1) {
      mcu->nvram[0x11] = 1;
      memcpy(&mcu->nvram[0x0d70], (uint8_t *)patchInfos[index].name, 0x16a);
      memcpy(status.patch, &mcu->nvram[0x0d70], 0x16a);
      mcu->SC55_Reset();
    } else {
      memcpy(&mcu->nvram[0x0d70], (uint8_t *)patchInfos[index].name, 0x16a);
      memcpy(status.patch, &mcu->nvram[0x0d70], 0x16a);
      uint8_t buffer[2] = {0xC0, 0x00};
      mcu->postMidiSC55(buffer, sizeof(buffer));
    }
  }

  mcuLock.exit();
}

const juce::String Jv880_juceAudioProcessor::getProgramName(int index) {
  int length = patchInfos[index].nameLength;
  const char *strPtr = (const char *)patchInfos[index].name;
  return juce::String(strPtr, length);
}

void Jv880_juceAudioProcessor::changeProgramName(int index,
                                                 const juce::String &newName) {}

//==============================================================================
void Jv880_juceAudioProcessor::prepareToPlay(double sampleRate,
                                             int samplesPerBlock) {
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
}

void Jv880_juceAudioProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

bool Jv880_juceAudioProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    return false;

  return true;
}

void Jv880_juceAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                            juce::MidiBuffer &midiMessages) {
  mcuLock.enter();

  for (const auto metadata : midiMessages) {
    auto message = metadata.getMessage();
    if (status.isDrums)
      message.setChannel(10);
    else
      message.setChannel(1);
    int samplePos = (double)metadata.samplePosition / getSampleRate() * 64000;
    mcu->enqueueMidiSC55(message.getRawData(), message.getRawDataSize(),
                         samplePos);
  }

  juce::ScopedNoDenormals noDenormals;
  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

  if (!loaded) {
    mcuLock.exit();
    return;
  }

  float *channelDataL = buffer.getWritePointer(0);
  float *channelDataR = buffer.getWritePointer(1);
  mcu->updateSC55WithSampleRate(channelDataL, channelDataR,
                                buffer.getNumSamples(), getSampleRate());

  mcuLock.exit();
}

//==============================================================================
bool Jv880_juceAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor *Jv880_juceAudioProcessor::createEditor() {
  return new Jv880_juceAudioProcessorEditor(*this);
}

//==============================================================================
void Jv880_juceAudioProcessor::getStateInformation(
    juce::MemoryBlock &destData) {
  mcuLock.enter();
  status.masterTune = mcu->nvram[0x00];
  status.reverbEnabled = ((mcu->nvram[0x02] >> 0) & 1) == 1;
  status.chorusEnabled = ((mcu->nvram[0x02] >> 1) & 1) == 1;
  mcuLock.exit();

  destData.ensureSize(sizeof(DataToSave));
  destData.replaceAll(&status, sizeof(DataToSave));
}

void Jv880_juceAudioProcessor::setStateInformation(const void *data,
                                                   int sizeInBytes) {
  memcpy(&status, data, sizeof(DataToSave));

  mcuLock.enter();

  mcu->nvram[0x0d] |= 1 << 5; // LastSet
  mcu->nvram[0x00] = status.masterTune;
  mcu->nvram[0x02] = status.reverbEnabled | status.chorusEnabled << 1;

  if (expansionsDescr[status.currentExpansion] == nullptr) {
    mcuLock.exit();
    return;
  }

  memcpy(mcu->pcm.waverom_exp, expansionsDescr[status.currentExpansion],
         0x800000);
  mcu->nvram[0x11] = status.isDrums ? 0 : 1;
  memcpy(&mcu->nvram[0x67f0], status.drums, 0xa7c);
  memcpy(&mcu->nvram[0x0d70], status.patch, 0x16a);
  mcu->SC55_Reset();
  mcuLock.exit();
}

void Jv880_juceAudioProcessor::sendSysexParamChange(uint32_t address,
                                                    uint8_t value) {
  uint8_t data[5];
  data[0] = (address >> 21) & 127; // address MSB
  data[1] = (address >> 14) & 127; // address
  data[2] = (address >> 7) & 127;  // address
  data[3] = (address >> 0) & 127;  // address LSB
  data[4] = value;                 // data

  uint32_t checksum = 0;

  for (size_t i = 0; i < 5; i++) {
    checksum += data[i];

    if (checksum >= 128) {
      checksum -= 128;
    }
  }

  uint8_t buf[12];
  buf[0] = 0xf0;
  buf[1] = 0x41;
  buf[2] = 0x10; // unit number
  buf[3] = 0x46;
  buf[4] = 0x12; // command

  checksum = 128 - checksum;

  for (size_t i = 0; i < 5; i++) {
    buf[i + 5] = data[i];
  }

  buf[10] = checksum;
  buf[11] = 0xf7;

  mcuLock.enter();
  mcu->postMidiSC55(buf, 12);
  mcuLock.exit();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new Jv880_juceAudioProcessor();
}
