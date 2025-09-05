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
  masterTuneSlider.addListener(this);
  masterTuneSlider.setTextValueSuffix(" Hz");
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

  addAndMakeVisible(chorusToggle);
  chorusToggle.addListener(this);

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
  const auto top = 10;
  const auto sliderLeft1 = 100;
  const auto width = getWidth() / 3 - sliderLeft1 - 10;
  const auto sliderLeft2 = sliderLeft1 + getWidth() / 3 + 2;
  const auto sliderLeft3 = sliderLeft2 + getWidth() / 3;
  const auto height = 24;

  auto sliderLeft = 120;

  reverbToggle    .setBounds(sliderLeft1 - 90, top, width, height);
  chorusToggle    .setBounds(sliderLeft2 - 90, top, width, height);
  masterTuneSlider.setBounds(sliderLeft3, top, width, height);
  buildDateLabel  .setBounds(10, 735, 800, 20);
}

void SettingsTab::sliderValueChanged(juce::Slider *slider)
{
  uint32_t id = 0xFFFFFFF;

  if (auto i = dynamic_cast<Slider*>(slider))
  {
    id = i->getID();
  }

  if (id == MasterTune)
  {
    processor.sendSysexParamChange(0x01, (uint8_t)masterTuneSlider.getValue());
  }
}

void SettingsTab::buttonClicked(juce::Button *button)
{
  uint32_t id = 0xFFFFFFF;

  if (auto i = dynamic_cast<Button*>(button))
  {
    id = i->getID();
  }

  switch (id)
  {
  case Reverb:
    processor.sendSysexParamChange(0x04, reverbToggle.getToggleState());
    break;
  case Chorus:
    processor.sendSysexParamChange(0x05, chorusToggle.getToggleState());
    break;
  }
}
