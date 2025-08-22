/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ui/widgets/LCDisplay.h"
#include "ui/PatchBrowser.h"
#include "ui/EditCommonTab.h"
#include "ui/EditToneTab.h"
#include "ui/SettingsTab.h"

//==============================================================================
/**
*/
class VirtualJVEditor  : public juce::AudioProcessorEditor
{
public:
    VirtualJVEditor (VirtualJVProcessor&);
    ~VirtualJVEditor() override;

    //==============================================================================
    void resized() override;

    uint8_t getSelectedRomIdx();
    void updateEditTabs();

private:
    VirtualJVProcessor& processor;

    LCDisplay lcd;
    juce::TabbedComponent tabs;
    PatchBrowser patchBrowser;
    EditCommonTab editCommonTab;
    EditToneTab editTone1Tab;
    EditToneTab editTone2Tab;
    EditToneTab editTone3Tab;
    EditToneTab editTone4Tab;
    SettingsTab settingsTab;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualJVEditor)
};
