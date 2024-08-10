/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

static const uint8_t* expansions[] = {
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

static const char* expansionNames[] = {
    "======== SR-JV80: 01 Pop ========",
    "======== SR-JV80: 02 Orchestral ========",
    "======== SR-JV80: 03 Piano ========",
    "======== SR-JV80: 04 Vintage Synth ========",
    "======== SR-JV80: 05 World ========",
    "======== SR-JV80: 06 Dance ========",
    "======== SR-JV80: 07 Super Sound Set ========",
    "======== SR-JV80: 08 Keyboards of the 60s and 70s ========",
    "======== SR-JV80: 09 Session ========",
    "======== SR-JV80: 10 Bass & Drum ========",
    "======== SR-JV80: 11 Techno ========",
    "======== SR-JV80: 12 HipHop ========",
    "======== SR-JV80: 13 Vocal ========",
    "======== SR-JV80: 14 Asia ========",
    "======== SR-JV80: 15 Special FX ========",
    "======== SR-JV80: 16 Orchestral II ========",
    "======== SR-JV80: 17 Country ========",
    "======== SR-JV80: 18 Latin ========",
    "======== SR-JV80: 19 House ========",
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
                       ), keyupTimer(this)
#endif
{
    mcu = new MCU();
    mcu->startSC55(BinaryData::jv880_rom1_bin, BinaryData::jv880_rom2_bin,
                   BinaryData::jv880_waverom1_bin, BinaryData::jv880_waverom2_bin,
                   BinaryData::jv880_nvram_bin);

    int currentPatchI = 0;

    // Internal User
    for (int j = 0; j < 64; j++)
    {
        patchInfos[currentPatchI].name = (const char*)&BinaryData::jv880_rom2_bin[0x008ce0 + j * 0x16a];
        patchInfos[currentPatchI].nameLength = 0xc;
        patchInfos[currentPatchI].expansionI = 0xff;
        patchInfos[currentPatchI].patchI = j;
        patchInfos[currentPatchI].present = true;
        patchInfos[currentPatchI].drums = false;
        currentPatchI++;
    }
    patchInfos[currentPatchI].name = "Drums Internal User";
    patchInfos[currentPatchI].ptr = &BinaryData::jv880_rom2_bin[0x00e760];
    patchInfos[currentPatchI].nameLength = 21;
    patchInfos[currentPatchI].expansionI = 0xff;
    patchInfos[currentPatchI].patchI = 0;
    patchInfos[currentPatchI].present = true;
    patchInfos[currentPatchI].drums = true;
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
        currentPatchI++;
    }
    patchInfos[currentPatchI].name = "Drums Internal A";
    patchInfos[currentPatchI].ptr = &BinaryData::jv880_rom2_bin[0x016760];
    patchInfos[currentPatchI].nameLength = 21;
    patchInfos[currentPatchI].expansionI = 0xff;
    patchInfos[currentPatchI].patchI = 0;
    patchInfos[currentPatchI].present = true;
    patchInfos[currentPatchI].drums = true;
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
        currentPatchI++;
    }
    patchInfos[currentPatchI].name = "Drums Internal B";
    patchInfos[currentPatchI].ptr = &BinaryData::jv880_rom2_bin[0x01e760];
    patchInfos[currentPatchI].nameLength = 21;
    patchInfos[currentPatchI].expansionI = 0xff;
    patchInfos[currentPatchI].patchI = 0;
    patchInfos[currentPatchI].present = true;
    patchInfos[currentPatchI].drums = true;
    currentPatchI++;

    for (int i = 0; i < NUM_EXPS; i++)
    {
        expansionsDescr[i] = expansions[i];

        // unscramble
        // uint8_t* dest = (uint8_t*) malloc(0x800000);
        // unscramble(expansions[i], dest, 0x800000);
        // FILE* f = fopen((juce::String("/Users/giuliozausa/personal/programming/jv880_juce/expansions_desc/") + BinaryData::originalFilenames[i]).toRawUTF8(), "wb");
        // fwrite(dest, 0x800000, 1, f);
        // fclose(f);

        // header patch
        patchInfos[currentPatchI].name = expansionNames[i];
        patchInfos[currentPatchI].nameLength = strlen(expansionNames[i]);
        patchInfos[currentPatchI].expansionI = i;
        patchInfos[currentPatchI].patchI = 0;
        patchInfos[currentPatchI].present = true;
        patchInfos[currentPatchI].drums = false;
        currentPatchI++;

        // get patches
        int nPatches = expansionsDescr[i][0x67] | expansionsDescr[i][0x66] << 8;
        for (int j = 0; j < nPatches; j++)
        {
            size_t patchesOffset = expansionsDescr[i][0x8f] | expansionsDescr[i][0x8e] << 8
                                 | expansionsDescr[i][0x8d] << 16 | expansionsDescr[i][0x8c] << 24;
            patchInfos[currentPatchI].name = (const char*)&expansionsDescr[i][patchesOffset + j * 0x16a];
            patchInfos[currentPatchI].nameLength = 0xc;
            patchInfos[currentPatchI].expansionI = i;
            patchInfos[currentPatchI].patchI = j;
            patchInfos[currentPatchI].present = true;
            currentPatchI++;
        }

        // get drumkits
        int nDrumkits = expansionsDescr[i][0x69] | expansionsDescr[i][0x68] << 8;
        for (int j = 0; j < nDrumkits; j++)
        {
            size_t patchesOffset = expansionsDescr[i][0x93] | expansionsDescr[i][0x92] << 8
                | expansionsDescr[i][0x91] << 16 | expansionsDescr[i][0x90] << 24;
            char* namePtr = (char*)calloc(32, 1);
            patchInfos[currentPatchI].name = namePtr;
            sprintf(namePtr, "Expansion %d Drums %d", i, j);
            patchInfos[currentPatchI].ptr = (const char*)&expansionsDescr[i][patchesOffset + j * 0xa7c];
            patchInfos[currentPatchI].nameLength = strlen(namePtr);
            patchInfos[currentPatchI].expansionI = i;
            patchInfos[currentPatchI].patchI = j;
            patchInfos[currentPatchI].present = true;
            patchInfos[currentPatchI].drums = true;
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
    return currentProgram;
}

void Jv880_juceAudioProcessor::setCurrentProgram (int index)
{
    if (index < 0 || index >= getNumPrograms())
        return;

    currentProgram = index;

    int expansionI = patchInfos[index].expansionI;
    if (expansionI != 0xff && currentExpansion != expansionI)
    {
        currentExpansion = expansionI;
        memcpy(mcu->pcm.waverom_exp, expansionsDescr[expansionI], 0x800000);
        mcu->SC55_Reset();
    }

    if (patchInfos[index].drums)
    {
        if (mcu->nvram[0x11] != 0)
        {
            mcu->lcd.LCD_SendButton(MCU_BUTTON_PATCH_PERFORM, 1);
            keyupTimer.startTimer(200);
        }
        else
        {
            memcpy(&mcu->nvram[0x67f0], (uint8_t*)patchInfos[currentProgram].ptr, 0xa7c);
            uint8_t buffer[2] = { 0xCA, 0x00 };
            mcu->postMidiSC55(buffer, sizeof(buffer));
        }
    }
    else
    {
        if (mcu->nvram[0x11] != 1)
        {
            mcu->lcd.LCD_SendButton(MCU_BUTTON_PATCH_PERFORM, 1);
            keyupTimer.startTimer(200);
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
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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
        if (patchInfos[currentProgram].drums)
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

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    // for (int channel = 0; channel < totalNumInputChannels; ++channel)
    // {
    //     auto* channelData = buffer.getWritePointer (channel);

    //     // ..do something to the data...
    // }
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
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Jv880_juceAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Jv880_juceAudioProcessor();
}
