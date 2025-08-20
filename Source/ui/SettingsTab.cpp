/*
  ==============================================================================

    SettingsTab.cpp
    Created: 18 Aug 2024 1:05:04pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#include "SettingsTab.h"
#include <JuceHeader.h>

//==============================================================================
SettingsTab::SettingsTab(Jv880_juceAudioProcessor &p) : audioProcessor(p) {
  addAndMakeVisible(masterTuneSlider);

  masterTuneSlider.setRange(1, 127);
  masterTuneSlider.setTextValueSuffix(" Hz");
  masterTuneSlider.addListener(this);
  masterTuneSlider.textFromValueFunction = [this](double value) {
    double floatValue = (value - 1) / 126;
    return juce::String(floatValue * (452.6 - 427.4) + 427.4, 0, false);
  };
  masterTuneSlider.valueFromTextFunction = [this](const juce::String &text) {
    double floatValue = text.getDoubleValue();
    return (floatValue - 427.4) / (452.6 - 427.4) * 126 + 1;
  };
  addAndMakeVisible(masterTuneLabel);
  masterTuneLabel.setText("Master Tune", juce::dontSendNotification);
  masterTuneLabel.attachToComponent(&masterTuneSlider, true);

  addAndMakeVisible(reverbToggle);
  reverbToggle.addListener(this);
  reverbToggle.setButtonText("Reverb");

  addAndMakeVisible(chorusToggle);
  chorusToggle.addListener(this);
  chorusToggle.setButtonText("Chorus");
}

SettingsTab::~SettingsTab() {}

void SettingsTab::visibilityChanged() {
  masterTuneSlider.setValue(((int8_t *)audioProcessor.mcu->nvram)[0x00] + 64,
                            juce::dontSendNotification);
  reverbToggle.setToggleState(((audioProcessor.mcu->nvram[0x02] >> 0) & 1) == 1,
                              juce::dontSendNotification);
  chorusToggle.setToggleState(((audioProcessor.mcu->nvram[0x02] >> 1) & 1) == 1,
                              juce::dontSendNotification);
}

void SettingsTab::resized() {
  auto sliderLeft = 120;
  masterTuneSlider.setBounds(sliderLeft, 40, getWidth() - sliderLeft - 10, 40);
  reverbToggle.setBounds(sliderLeft, 100, 200, 40);
  chorusToggle.setBounds(sliderLeft, 140, 200, 40);
}

void SettingsTab::sliderValueChanged(juce::Slider *slider) {
  if (slider == &masterTuneSlider)
  {
    uint32_t address = 0x01;
    uint8_t value = (uint8_t)masterTuneSlider.getValue();
    audioProcessor.sendSysexParamChange(address, value);
  }
}

void SettingsTab::buttonClicked(juce::Button *button) {
  if (button == &reverbToggle)
  {
    uint32_t address = 0x04;
    uint8_t value = reverbToggle.getToggleState() ? 1U : 0U;
    audioProcessor.sendSysexParamChange(address, value);
  }
  else if (button == &chorusToggle)
  {
    uint32_t address = 0x05;
    uint8_t value = chorusToggle.getToggleState() ? 1U : 0U;
    audioProcessor.sendSysexParamChange(address, value);
  }
}

void SettingsTab::buttonStateChanged(juce::Button* /* button */) {}
