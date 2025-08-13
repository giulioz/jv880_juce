/*
  ==============================================================================

    EditCommonTab.h
    Created: 20 Aug 2024 2:33:58pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once

#include "../PluginProcessor.h"
#include <JuceHeader.h>

constexpr int MAX_PATCH_NAME_CHARS = 12;

class EditCommonTab : public juce::Component,
                      public juce::Slider::Listener,
                      public juce::Button::Listener,
                      public juce::ComboBox::Listener,
                      public juce::TextEditor::Listener {
public:
  EditCommonTab(Jv880_juceAudioProcessor &);
  ~EditCommonTab() override;

  void updateValues();

  void visibilityChanged() override;
  void resized() override;
  void sliderValueChanged(juce::Slider *) override;
  void buttonClicked(juce::Button *) override;
  void buttonStateChanged(juce::Button *) override;
  void comboBoxChanged(juce::ComboBox *) override;
  void textEditorTextChanged(juce::TextEditor &) override;
  void sendSysexPatchCommonChange();

private:
  Jv880_juceAudioProcessor &audioProcessor;

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
  juce::Slider chorusRateSlider;
  juce::Label chorusRateLabel;
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

  juce::Label bendRangeLabel;
  juce::Slider bendRangeDownSlider;
  juce::Slider bendRangeUpSlider;
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

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditCommonTab)
};
