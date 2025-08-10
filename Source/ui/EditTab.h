/*
  ==============================================================================

    EditTab.h
    Created: 18 Aug 2024 1:04:53pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "EditCommonTab.h"
#include "EditToneTab.h"

//==============================================================================
/*
*/
class EditTab  : public juce::Component
{
public:
    EditTab(Jv880_juceAudioProcessor&);
    ~EditTab() override;

    void resized() override;

private:
    Jv880_juceAudioProcessor& audioProcessor;

    juce::TabbedComponent tabs;
    EditCommonTab editCommon;
    EditToneTab editTone1;
    EditToneTab editTone2;
    EditToneTab editTone3;
    EditToneTab editTone4;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditTab)
};
