/*
  ==============================================================================

    SettingsTab.h
    Created: 18 Aug 2024 1:05:04pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class SettingsTab  : public juce::Component, public juce::Slider::Listener, public juce::Button::Listener
{
public:
    SettingsTab(Jv880_juceAudioProcessor&);
    ~SettingsTab() override;

    void updateValues();
    void resized() override;
    void sliderValueChanged (juce::Slider*) override;
    void buttonClicked (juce::Button*) override;
    void buttonStateChanged(juce::Button*) override {}

private:
    Jv880_juceAudioProcessor& audioProcessor;

    juce::Slider masterTuneSlider;
    juce::Label masterTuneLabel;
    juce::ToggleButton reverbToggle;
    juce::ToggleButton chorusToggle;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsTab)
};
