/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <vector>
#include <JuceHeader.h>
#include "emulator/mcu.h"
#include "rom.h"

constexpr int NUM_EXPS = romCount - 6;

//==============================================================================
/**
*/

class VirtualJVEditor;

class VirtualJVProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    VirtualJVProcessor();
    ~VirtualJVProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    void sendSysexParamChange(uint32_t address, uint8_t value);

    std::vector<std::string> readMultisampleNames(uint8_t romIdx);

    struct PatchInfo
    {
        const char* name;
        const char* ptr;
        int nameLength;
        int expansionI; // 0xff: no expansion
        int patchI;
        bool present = false;
        bool drums = false;
        int iInList;
    };

    struct DataToSave
    {
        int8_t masterTune = 0;
        bool reverbEnabled = 1;
        bool chorusEnabled = 1;

        int currentExpansion = 0;
        bool isDrums = false;
        uint8_t patch[0x16a] = {0};
        uint8_t drums[0xa7c] = {0};
    };

    DataToSave status;
    MCU *mcu;
    const uint8_t* expansionsDescr[NUM_EXPS];
    PatchInfo patchInfos[192 + 256 * NUM_EXPS] = {0};
    std::vector<std::vector<PatchInfo*>> patchInfoPerGroup;
    int totalPatchesExp = 0;

    std::array<uint8_t*, romCount> loadedRoms = {0};
    bool loaded = false;

    juce::SpinLock mcuLock;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualJVProcessor)
};
