/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

static const uint8_t* expansions[] = {
    (const uint8_t*)BinaryData::rd500_expansion_bin,
    (const uint8_t*)BinaryData::jd990_expansion_bin,
    (const uint8_t*)BinaryData::SRJV8001_Pop__CS_0x3F1CF705_bin,
    (const uint8_t*)BinaryData::SRJV8002_Orchestral__CS_0x3F0E09E2_BIN,
    (const uint8_t*)BinaryData::SRJV8003_Piano__CS_0x3F8DB303_bin,
    (const uint8_t*)BinaryData::SRJV8004_Vintage_Synth__CS_0x3E23B90C_BIN,
    (const uint8_t*)BinaryData::SRJV8005_World__CS_0x3E8E8A0D_bin,
    (const uint8_t*)BinaryData::SRJV8006_Dance__CS_0x3EC462E0_bin,
    (const uint8_t*)BinaryData::SRJV8007_Super_Sound_Set__CS_0x3F1EE208_bin,
    (const uint8_t*)BinaryData::SRJV8008_Keyboards_of_the_60s_and_70s__CS_0x3F1E3F0A_BIN,
    (const uint8_t*)BinaryData::SRJV8009_Session__CS_0x3F381791_BIN,
    (const uint8_t*)BinaryData::SRJV8010_Bass__Drum__CS_0x3D83D02A_BIN,
    (const uint8_t*)BinaryData::SRJV8011_Techno__CS_0x3F046250_bin,
    (const uint8_t*)BinaryData::SRJV8012_HipHop__CS_0x3EA08A19_BIN,
    (const uint8_t*)BinaryData::SRJV8013_Vocal__CS_0x3ECE78AA_bin,
    (const uint8_t*)BinaryData::SRJV8014_Asia__CS_0x3C8A1582_bin,
    (const uint8_t*)BinaryData::SRJV8015_Special_FX__CS_0x3F591CE4_bin,
    (const uint8_t*)BinaryData::SRJV8016_Orchestral_II__CS_0x3F35B03B_bin,
    (const uint8_t*)BinaryData::SRJV8017_Country__CS_0x3ED75089_bin,
    (const uint8_t*)BinaryData::SRJV8018_Latin__CS_0x3EA51033_BIN,
    (const uint8_t*)BinaryData::SRJV8019_House__CS_0x3E330C41_BIN
};

// static void unscramble(const uint8_t *src, uint8_t *dst, int len)
// {
//     for (int i = 0; i < len; i++)
//     {
//         int address = i & ~0xfffff;
//         static const int aa[] = {
//             2, 0, 3, 4, 1, 9, 13, 10, 18, 17, 6, 15, 11, 16, 8, 5, 12, 7, 14, 19
//         };
//         for (int j = 0; j < 20; j++)
//         {
//             if (i & (1 << j))
//                 address |= 1<<aa[j];
//         }
//         uint8_t srcdata = src[address];
//         uint8_t data = 0;
//         static const int dd[] = {
//             2, 0, 4, 5, 7, 6, 3, 1
//         };
//         for (int j = 0; j < 8; j++)
//         {
//             if (srcdata & (1 << dd[j]))
//                 data |= 1<<j;
//         }
//         dst[i] = data;
//     }
// }

//==============================================================================
Jv880_juceAudioProcessor::Jv880_juceAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    mcu = new MCU();
    mcu->startSC55(BinaryData::jv880_rom1_bin, BinaryData::jv880_rom2_bin,
                   BinaryData::jv880_waverom1_bin, BinaryData::jv880_waverom2_bin,
                   BinaryData::jv880_nvram_bin);

    // unscramble
    // FILE *f;
    // f = fopen("/Users/giuliozausa/personal/programming/jv880_juce/expansions/rd500_expansion.bin", "rb");
    // uint8_t* src = (uint8_t*) malloc(0x800000);
    // fread(src, 0x800000, 1, f);
    // fclose(f);
    // uint8_t* dest = (uint8_t*) malloc(0x800000);
    // unscramble(src, dest, 0x800000);
    // f = fopen("/Users/giuliozausa/personal/programming/jv880_juce/expansions_desc/rd500_expansion.bin", "wb");
    // fwrite(dest, 0x800000, 1, f);
    // fclose(f);

    int currentPatchI = 0;

    // Internal User
    patchInfoPerGroup.push_back(std::vector<PatchInfo*>());
    for (int j = 0; j < 64; j++)
    {
        patchInfos[currentPatchI].name = (const char*)&BinaryData::jv880_rom2_bin[0x008ce0 + j * 0x16a];
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
    patchInfos[currentPatchI].ptr = &BinaryData::jv880_rom2_bin[0x00e760];
    patchInfos[currentPatchI].nameLength = 21;
    patchInfos[currentPatchI].expansionI = 0xff;
    patchInfos[currentPatchI].patchI = 0;
    patchInfos[currentPatchI].present = true;
    patchInfos[currentPatchI].drums = true;
    patchInfos[currentPatchI].iInList = currentPatchI;
    patchInfoPerGroup[0].push_back(&patchInfos[currentPatchI]);
    currentPatchI++;
    
    // Internal A
    for (int j = 0; j < 64; j++)
    {
        patchInfos[currentPatchI].name = (const char*)&BinaryData::jv880_rom2_bin[0x010ce0 + j * 0x16a];
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
    patchInfos[currentPatchI].ptr = &BinaryData::jv880_rom2_bin[0x016760];
    patchInfos[currentPatchI].nameLength = 21;
    patchInfos[currentPatchI].expansionI = 0xff;
    patchInfos[currentPatchI].patchI = 0;
    patchInfos[currentPatchI].present = true;
    patchInfos[currentPatchI].drums = true;
    patchInfos[currentPatchI].iInList = currentPatchI;
    patchInfoPerGroup[0].push_back(&patchInfos[currentPatchI]);
    currentPatchI++;
    
    // Internal B
    for (int j = 0; j < 64; j++)
    {
        patchInfos[currentPatchI].name = (const char*)&BinaryData::jv880_rom2_bin[0x018ce0 + j * 0x16a];
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
    patchInfos[currentPatchI].ptr = &BinaryData::jv880_rom2_bin[0x01e760];
    patchInfos[currentPatchI].nameLength = 21;
    patchInfos[currentPatchI].expansionI = 0xff;
    patchInfos[currentPatchI].patchI = 0;
    patchInfos[currentPatchI].present = true;
    patchInfos[currentPatchI].drums = true;
    patchInfos[currentPatchI].iInList = currentPatchI;
    patchInfoPerGroup[0].push_back(&patchInfos[currentPatchI]);
    currentPatchI++;

    for (int i = 0; i < NUM_EXPS; i++)
    {
        patchInfoPerGroup.push_back(std::vector<PatchInfo*>());

        expansionsDescr[i] = expansions[i];

        // get patches
        int nPatches = expansionsDescr[i][0x67] | expansionsDescr[i][0x66] << 8;
        if (i == 0) nPatches = 192; // RD-500
        for (int j = 0; j < nPatches; j++)
        {
            size_t patchesOffset = expansionsDescr[i][0x8f] | expansionsDescr[i][0x8e] << 8
                                 | expansionsDescr[i][0x8d] << 16 | expansionsDescr[i][0x8c] << 24;
            // RD-500
            if (i == 0 && j < 64) patchesOffset = 0x0ce0;
            else if (i == 0 && j < 128) patchesOffset = 0x8370;
            else if (i == 0) patchesOffset = 0x12b82;
            patchInfos[currentPatchI].name = (const char*)&expansionsDescr[i][patchesOffset + j * 0x16a];
            if (i == 0)
                patchInfos[currentPatchI].name = (const char*)&BinaryData::rd500_patches_bin[patchesOffset + (j % 64) * 0x16a];
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
        int nDrumkits = expansionsDescr[i][0x69] | expansionsDescr[i][0x68] << 8;
        if (i == 0) nDrumkits = 3; // RD-500
        for (int j = 0; j < nDrumkits; j++)
        {
            size_t patchesOffset = expansionsDescr[i][0x93] | expansionsDescr[i][0x92] << 8
                | expansionsDescr[i][0x91] << 16 | expansionsDescr[i][0x90] << 24;
            // RD-500
            if (i == 0 && j < 64) patchesOffset = 0x6760;
            else if (i == 0 && j < 128) patchesOffset = 0xd2a0;
            else if (i == 0) patchesOffset = 0x18602;
            char* namePtr = (char*)calloc(32, 1);
            patchInfos[currentPatchI].name = namePtr;
            sprintf(namePtr, "Exp %d Drums %d", i, j);
            patchInfos[currentPatchI].ptr = (const char*)&expansionsDescr[i][patchesOffset + j * 0xa7c];
            if (i == 0)
                patchInfos[currentPatchI].ptr = (const char*)&BinaryData::rd500_patches_bin[patchesOffset];
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
    }

    memcpy(mcu->pcm.waverom_exp, expansionsDescr[currentExpansion], 0x800000);
}

Jv880_juceAudioProcessor::~Jv880_juceAudioProcessor()
{
    memset(mcu, 0, sizeof(MCU));
    delete mcu;
}

//==============================================================================
const juce::String Jv880_juceAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Jv880_juceAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Jv880_juceAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Jv880_juceAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Jv880_juceAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Jv880_juceAudioProcessor::getNumPrograms()
{
    return 64 // internal
         + 64 // bank A
         + 64 // bank B
         + totalPatchesExp // expansions
    ;
}

int Jv880_juceAudioProcessor::getCurrentProgram()
{
    return status.currentProgram;
}

void Jv880_juceAudioProcessor::setCurrentProgram (int index)
{
    if (index < 0 || index >= getNumPrograms())
        return;

    status.currentProgram = index;

    int expansionI = patchInfos[index].expansionI;
    if (expansionI != 0xff && currentExpansion != expansionI)
    {
        currentExpansion = expansionI;
        memcpy(mcu->pcm.waverom_exp, expansionsDescr[expansionI], 0x800000);
        mcu->SC55_Reset();
    }

    if (patchInfos[index].drums)
    {
        mcu->nvram[0x11] = 0;
        memcpy(&mcu->nvram[0x67f0], (uint8_t*)patchInfos[status.currentProgram].ptr, 0xa7c);
        mcu->SC55_Reset();
    }
    else
    {
        if (mcu->nvram[0x11] != 1)
        {
            mcu->nvram[0x11] = 1;
            memcpy(&mcu->nvram[0x0d70], (uint8_t*)patchInfos[index].name, 0x16a);
            mcu->SC55_Reset();
        }
        else
        {
            memcpy(&mcu->nvram[0x0d70], (uint8_t*)patchInfos[index].name, 0x16a);
            uint8_t buffer[2] = { 0xC0, 0x00 };
            mcu->postMidiSC55(buffer, sizeof(buffer));
        }
    }
}

const juce::String Jv880_juceAudioProcessor::getProgramName (int index)
{
    int length = patchInfos[index].nameLength;
    const char* strPtr = (const char*)patchInfos[index].name;
    return juce::String(strPtr, length);
}

void Jv880_juceAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Jv880_juceAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Jv880_juceAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Jv880_juceAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Jv880_juceAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for (const auto metadata : midiMessages)
    {
        auto message = metadata.getMessage();
        if (patchInfos[status.currentProgram].drums)
            message.setChannel(10);
        else
            message.setChannel(1);
        mcu->postMidiSC55(message.getRawData(), message.getRawDataSize());
    }
 
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);
    mcu->updateSC55WithSampleRate(channelDataL, channelDataR, buffer.getNumSamples(), getSampleRate());
}

//==============================================================================
bool Jv880_juceAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Jv880_juceAudioProcessor::createEditor()
{
    return new Jv880_juceAudioProcessorEditor (*this);
}

//==============================================================================
void Jv880_juceAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    destData.ensureSize(sizeof(DataToSave));
    destData.replaceAll(&status, sizeof(DataToSave));
}

void Jv880_juceAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    memcpy(&status, data, sizeof(DataToSave));
    setCurrentProgram(status.currentProgram);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Jv880_juceAudioProcessor();
}
