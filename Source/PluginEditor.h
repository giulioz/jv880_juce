/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ui/JV880LCD.h"
#include "ui/PatchBrowser.h"
#include "ui/EditTab.h"
#include "ui/SettingsTab.h"

//==============================================================================
/**
*/
class Jv880_juceAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Jv880_juceAudioProcessorEditor (Jv880_juceAudioProcessor&);
    ~Jv880_juceAudioProcessorEditor() override;

    //==============================================================================
    void resized() override;

private:
    Jv880_juceAudioProcessor& audioProcessor;

    // UI Components
    JV880LCD lcd;
    juce::TabbedComponent tabs;
    PatchBrowser patchBrowser;
    EditTab editTab;
    SettingsTab settingsTab;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Jv880_juceAudioProcessorEditor)
};
