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
#include "../dataStructures.h"

#include "widgets/Button.h"
#include "widgets/Menu.h"
#include "widgets/Slider.h"
#include "widgets/TextEdit.h"

constexpr int MAX_PATCH_NAME_CHARS = 12;

class EditCommonTab : public juce::Component,
                      public juce::Slider::Listener,
                      public juce::Button::Listener,
                      public juce::ComboBox::Listener,
                      public juce::TextEditor::Listener
{
public:
  EditCommonTab(VirtualJVProcessor &);
  ~EditCommonTab() override;


  void resized() override;
  void sliderValueChanged(juce::Slider*) override;
  void buttonClicked(juce::Button *) override;
  void buttonStateChanged(juce::Button*) override {}
  void comboBoxChanged(juce::ComboBox *) override;
  void textEditorTextChanged(juce::TextEditor &) override;

  void updateValues();
  void rhythmSetMode(const bool isRhythm);

  void sendSysexPatchNameChange();
  void sendSysexPatchCommonParamChange(const uint8_t address, const uint8_t value);

private:
  enum EditCommonWidgets
  {
      PatchName           = 100U,
      VelocitySwitch      = 101U,

      ReverbType          = 110U,
      ReverbLevel         = 111U,
      ReverbTime          = 112U,
      DelayFeedback       = 113U,

      ChorusType          = 120U,
      ChorusLevel         = 121U,
      ChorusDepth         = 122U,
      ChorusRate          = 123U,
      ChorusFeedback      = 124U,
      ChorusOutput        = 125U,

      AnalogFeel          = 130U,
      Level               = 131U,
      Pan                 = 132U,

      BendRangeDown       = 140U,
      BendRangeUp         = 141U,
      KeyAssign           = 142U,
      SoloLegato          = 143U,
      Portamento          = 144U,
      PortamentoMode      = 145U,
      PortamentoType      = 146U,
      PortamentoTime      = 147U,
  };
  VirtualJVProcessor &processor;

  juce::Label patchNameLabel{ "", "Patch Name" };
  TextEdit patchNameEditor{ PatchName };
  Button velocitySwitchToggle{ VelocitySwitch, "Velocity Switch" };

  juce::Label reverbTypeLabel{ "", "Reverb" };
  juce::Label reverbLevelLabel{ "", "Level" };
  juce::Label reverbTimeLabel{ "", "Time" };
  juce::Label delayFeedbackLabel{ "", "Feedback" };
  Menu reverbTypeComboBox{ ReverbType };
  Slider reverbLevelSlider{ ReverbLevel, 0, 127, 1 };
  Slider reverbTimeSlider{ ReverbTime, 0, 127, 1 };
  Slider delayFeedbackSlider{ DelayFeedback, 0, 127, 1 };

  juce::Label chorusTypeLabel{ "", "Chorus" };
  juce::Label chorusLevelLabel{ "", "Level" };
  juce::Label chorusDepthLabel{ "", "Depth" };
  juce::Label chorusRateLabel{ "", "Rate" };
  juce::Label chorusFeedbackLabel{ "", "Feedback" };
  juce::Label chorusOutputLabel{ "", "Output" };
  Menu chorusTypeComboBox{ ChorusType };
  Slider chorusLevelSlider{ ChorusLevel, 0, 127, 1 };
  Slider chorusDepthSlider{ ChorusDepth, 0, 127, 1 };
  Slider chorusRateSlider{ ChorusRate, 0, 127, 1 };
  Slider chorusFeedbackSlider{ ChorusFeedback, 0, 127, 1 };
  Menu chorusOutputComboBox{ ChorusOutput };

  juce::Label analogFeelLabel{ "", "Analog Feel" };
  juce::Label levelLabel{ "", "Level" };
  juce::Label panLabel{ "", "Pan" };
  Slider analogFeelSlider{ AnalogFeel, 0, 127, 1 };
  Slider levelSlider{ Level, 0, 127, 1 };
  Slider panSlider{ Pan, 0, 127, 1 };

  juce::Label bendRangeLabel{ "", "Bend Range" };
  juce::Label keyAssignLabel{ "", "Key Assign" };
  juce::Label portamentoModeLabel{ "", "Mode" };
  juce::Label portamentoTypeLabel{ "", "Type" };
  juce::Label portamentoTimeLabel{ "", "Time" };
  Slider bendRangeDownSlider{ BendRangeDown, -48, 0, 1 };
  Slider bendRangeUpSlider{ BendRangeUp, 0, 12, 1 };
  Menu keyAssignComboBox{ KeyAssign };
  Button soloLegatoToggle{ SoloLegato, "Legato" };
  Button portamentoToggle{ Portamento, "Portamento" };
  Menu portamentoModeComboBox{ PortamentoMode };
  Menu portamentoTypeComboBox{ PortamentoType };
  Slider portamentoTimeSlider{ PortamentoTime, 0, 127, 1 };

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditCommonTab)
};
