/*
  ==============================================================================

    EditToneTab.h
    Created: 20 Aug 2024 2:34:06pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class EditToneTab  : public juce::Component
{
public:
    EditToneTab(Jv880_juceAudioProcessor&);
    ~EditToneTab() override;

    void resized() override;

private:
    Jv880_juceAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditToneTab)
};
