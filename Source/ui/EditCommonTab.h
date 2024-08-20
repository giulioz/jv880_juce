/*
  ==============================================================================

    EditCommonTab.h
    Created: 20 Aug 2024 2:33:58pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class EditCommonTab  : public juce::Component, public juce::Slider::Listener, public juce::Button::Listener, public juce::ComboBox::Listener
{
public:
    EditCommonTab(Jv880_juceAudioProcessor&);
    ~EditCommonTab() override;

    void updateValues();

    void visibilityChanged() override;
    void resized() override;
    void sliderValueChanged (juce::Slider*) override;
    void buttonClicked (juce::Button*) override;
    void buttonStateChanged (juce::Button*) override;
    void comboBoxChanged (juce::ComboBox*);

private:
    Jv880_juceAudioProcessor& audioProcessor;

    juce::TextEditor patchNameEditor;
    juce::Label patchNameLabel;
    juce::ToggleButton velocitySwitchToggle;
    
    juce::Label reverbTypeLabel;
    juce::ComboBox reverbTypeComboBox;
    juce::Slider reverbLevelSlider;
    juce::Label reverbLevelLabel;
    juce::Slider reverbTimeSlider;
    juce::Label reverbTimeLabel;
    juce::Slider delayFeedbackSlider;
    juce::Label delayFeedbackLabel;

    juce::Label chorusTypeLabel;
    juce::ComboBox chorusTypeComboBox;
    juce::Slider chorusLevelSlider;
    juce::Label chorusLevelLabel;
    juce::Slider chorusDepthSlider;
    juce::Label chorusDepthLabel;
    juce::Slider chorusFeedbackSlider;
    juce::Label chorusFeedbackLabel;
    juce::Label chorusOutputLabel;
    juce::ComboBox chorusOutputComboBox;

    juce::Slider analogFeelSlider;
    juce::Label analogFeelLabel;
    juce::Slider levelSlider;
    juce::Label levelLabel;
    juce::Slider panSlider;
    juce::Label panLabel;

    juce::Slider bendRangeDownSlider;
    juce::Label bendRangeDownLabel;
    juce::Slider bendRangeUpSlider;
    juce::Label bendRangeUpLabel;
    juce::Label keyAssignLabel;
    juce::ComboBox keyAssignComboBox;
    juce::ToggleButton soloLegatoToggle;
    juce::ToggleButton portamentoToggle;
    juce::Label portamentoModeLabel;
    juce::ComboBox portamentoModeComboBox;
    juce::Label portamentoTypeLabel;
    juce::ComboBox portamentoTypeComboBox;
    juce::Slider portamentoTimeSlider;
    juce::Label portamentoTimeLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditCommonTab)
};
