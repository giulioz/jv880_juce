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
SettingsTab::SettingsTab(VirtualJVProcessor &p) : processor(p)
{
  addAndMakeVisible(masterTuneSlider);

  masterTuneSlider.setRange(1, 127);
  masterTuneSlider.setTextValueSuffix(" Hz");
  masterTuneSlider.addListener(this);
  masterTuneSlider.textFromValueFunction =
      [this](double value)
      {
        double floatValue = (value - 1) / 126;
        return juce::String(floatValue * (452.6 - 427.4) + 427.4, 0, false);
      };
  masterTuneSlider.valueFromTextFunction = 
      [this](const juce::String &text)
      {
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

  const auto buildTime = juce::Time::getCompilationDate();
  const juce::String buildInfo = "Build Date: " + buildTime.formatted("%d %b %Y, %H:%M:%S");

  addAndMakeVisible(buildDateLabel);
  buildDateLabel.setText(buildInfo, juce::dontSendNotification);
  buildDateLabel.setJustificationType(juce::Justification::centredRight);
}

SettingsTab::~SettingsTab() {}

void SettingsTab::updateValues()
{
  masterTuneSlider.setValue(((int8_t *)processor.mcu->nvram)[0x00] + 64, juce::dontSendNotification);
  reverbToggle.setToggleState((processor.mcu->nvram[0x02] >> 0) & 1, juce::dontSendNotification);
  chorusToggle.setToggleState((processor.mcu->nvram[0x02] >> 1) & 1, juce::dontSendNotification);
}

void SettingsTab::resized()
{
  auto sliderLeft = 120;

  masterTuneSlider.setBounds(sliderLeft, 40, getWidth() - sliderLeft - 10, 40);
  reverbToggle.setBounds(sliderLeft, 100, 200, 40);
  chorusToggle.setBounds(sliderLeft, 140, 200, 40);
  buildDateLabel.setBounds(10, 735, 800, 20);
}

void SettingsTab::sliderValueChanged(juce::Slider *slider)
{
  if (slider == &masterTuneSlider)
  {
    processor.sendSysexParamChange(0x01, (uint8_t)masterTuneSlider.getValue());
  }
}

void SettingsTab::buttonClicked(juce::Button *button)
{
  if (button == &reverbToggle)
  {
    processor.sendSysexParamChange(0x04, reverbToggle.getToggleState());
  }
  else if (button == &chorusToggle)
  {
    processor.sendSysexParamChange(0x05, chorusToggle.getToggleState());
  }
}
