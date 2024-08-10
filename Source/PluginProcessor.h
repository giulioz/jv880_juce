/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "emulator/mcu.h"

constexpr int NUM_EXPS = 19;

//==============================================================================
/**
*/
class Jv880_juceAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Jv880_juceAudioProcessor();
    ~Jv880_juceAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

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

    struct PatchInfos
    {
        const char* name;
        const char* ptr;
        int nameLength;
        int expansionI; // 0xff: no expansion
        int patchI;
        bool present = false;
        bool drums = false;
    };

    MCU *mcu;
    int currentProgram = 0;
    int currentExpansion = 0;
    const uint8_t* expansionsDescr[NUM_EXPS];
    PatchInfos patchInfos[192 + 256 * NUM_EXPS] = {0};
    int totalPatchesExp = 0;

    class KeyupTimer : public juce::Timer
    {
    public:
        KeyupTimer(Jv880_juceAudioProcessor *prc) : prc(prc) {}
        void timerCallback() override
        {
            stopTimer();

            prc->mcu->lcd.LCD_SendButton(MCU_BUTTON_PATCH_PERFORM, 0);
            if (prc->patchInfos[prc->currentProgram].drums)
            {
                memcpy(&prc->mcu->nvram[0x67f0], (uint8_t*)prc->patchInfos[prc->currentProgram].ptr, 0xa7c);
                uint8_t buffer[2] = { 0xCA, 0x00 };
                prc->mcu->postMidiSC55(buffer, sizeof(buffer));
            }
            else
            {
                memcpy(&prc->mcu->nvram[0x0d70], (uint8_t*)prc->patchInfos[prc->currentProgram].name, 0x16a);
                uint8_t buffer[2] = { 0xC0, 0x00 };
                prc->mcu->postMidiSC55(buffer, sizeof(buffer));
            }
        }
    private:
      Jv880_juceAudioProcessor *prc;
    };
    KeyupTimer keyupTimer;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Jv880_juceAudioProcessor)
};
