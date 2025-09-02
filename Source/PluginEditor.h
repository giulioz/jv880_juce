/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

#include "ui/widgets/LCDisplay.h"
#include "ui/widgets/TabBar.h"
#include "ui/PatchBrowser.h"
#include "ui/EditCommonTab.h"
#include "ui/EditToneTab.h"
#include "ui/EditRhythmTab.h"
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
    void showToneOrRhythmEditTabs(const bool isRhythm);

    void setSelectedTab(const int index) { tabs.setCurrentTabIndex(index); }

private:
    VirtualJVProcessor& processor;

    LCDisplay lcd;
    TabBar tabs;
    PatchBrowser patchBrowser;
    EditCommonTab editCommonTab;
    EditToneTab editTone1Tab;
    EditToneTab editTone2Tab;
    EditToneTab editTone3Tab;
    EditToneTab editTone4Tab;
    EditRhythmTab editRhythmTab;
    SettingsTab settingsTab;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualJVEditor)
};
