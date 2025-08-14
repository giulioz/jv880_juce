/*
  ==============================================================================

    EditToneTab.h
    Created: 20 Aug 2024 2:34:06pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once

#include "../PluginProcessor.h"
#include <JuceHeader.h>

//==============================================================================

class EditToneTab : public juce::Component,
                    public juce::Slider::Listener,
                    public juce::Button::Listener,
                    public juce::ComboBox::Listener
{
public:
    EditToneTab(Jv880_juceAudioProcessor &, uint8_t toneIn);
    ~EditToneTab() override;

    void updateValues();

    void visibilityChanged() override;
    void resized() override;
    void sliderValueChanged(juce::Slider *) override;
    void buttonClicked(juce::Button *) override;
    void buttonStateChanged(juce::Button *) override;
    void comboBoxChanged(juce::ComboBox *) override;
    void sendSysexPatchToneChange1Byte(uint8_t address, uint8_t value);
    void sendSysexPatchToneChange2Byte(uint8_t address, uint8_t value);
    void sendSysexPatchToneChange();

private:
    void addMenuEntriesFromArray(juce::ComboBox &menu,
    const std::vector<std::string> &array);

    Jv880_juceAudioProcessor &audioProcessor;
    uint8_t toneCount;

    juce::ComboBox waveGroupComboBox;
    juce::Label waveGroupLabel;
    juce::Slider waveformSlider;
    juce::Label waveformLabel;
    juce::ToggleButton toneSwitchToggle;
    juce::Label toneSwitchLabel;
    juce::ToggleButton FXMSwitchToggle;
    juce::Label FXMSwitchLabel;
    juce::Slider FXMDepthSlider;
    juce::Label FXMDepthLabel;

    juce::Label velRangeLabel;
    juce::Slider velRangeLowSlider;
    juce::Slider velRangeHighSlider;

    juce::ToggleButton volumeSwitchToggle;
    juce::Label volumeSwitchLabel;
    juce::ToggleButton holdSwitchToggle;
    juce::Label holdSwitchLabel;
    juce::Slider modSensASlider;
    juce::Label modSensALabel;
    juce::ComboBox modDestAComboBox;
    juce::Label modDestALabel;
    juce::Slider modSensBSlider;
    juce::Label modSensBLabel;
    juce::ComboBox modDestBComboBox;
    juce::Label modDestBLabel;
    juce::Slider modSensCSlider;
    juce::Label modSensCLabel;
    juce::ComboBox modDestCComboBox;
    juce::Label modDestCLabel;
    juce::Slider modSensDSlider;
    juce::Label modSensDLabel;
    juce::ComboBox modDestDComboBox;
    juce::Label modDestDLabel;
    juce::Slider aftSensASlider;
    juce::Label aftSensALabel;
    juce::ComboBox aftDestAComboBox;
    juce::Label aftDestALabel;
    juce::Slider aftSensBSlider;
    juce::Label aftSensBLabel;
    juce::ComboBox aftDestBComboBox;
    juce::Label aftDestBLabel;
    juce::Slider aftSensCSlider;
    juce::Label aftSensCLabel;
    juce::ComboBox aftDestCComboBox;
    juce::Label aftDestCLabel;
    juce::Slider aftSensDSlider;
    juce::Label aftSensDLabel;
    juce::ComboBox aftDestDComboBox;
    juce::Label aftDestDLabel;
    juce::Slider expSensASlider;
    juce::Label expSensALabel;
    juce::ComboBox expDestAComboBox;
    juce::Label expDestALabel;
    juce::Slider expSensBSlider;
    juce::Label expSensBLabel;
    juce::ComboBox expDestBComboBox;
    juce::Label expDestBLabel;
    juce::Slider expSensCSlider;
    juce::Label expSensCLabel;
    juce::ComboBox expDestCComboBox;
    juce::Label expDestCLabel;
    juce::Slider expSensDSlider;
    juce::Label expSensDLabel;
    juce::ComboBox expDestDComboBox;
    juce::Label expDestDLabel;

    juce::ComboBox lfo1FormComboBox;
    juce::Label lfo1FormLabel;
    juce::ComboBox lfo1OffsetComboBox;
    juce::Label lfo1OffsetLabel;
    juce::ToggleButton lfo1SyncToggle;
    juce::Label lfo1SyncLabel;
    juce::Slider lfo1RateSlider;
    juce::Label lfo1RateLabel;
    juce::Slider lfo1DelaySlider;
    juce::Label lfo1DelayLabel;
    juce::ToggleButton lfo1FadeToggle;
    juce::Label lfo1FadeLabel;
    juce::Slider lfo1FadeTimeSlider;
    juce::Label lfo1FadeTimeLabel;
    juce::Slider lfo1PitchDepthSlider;
    juce::Label lfo1PitchDepthLabel;
    juce::Slider lfo1TVFDepthSlider;
    juce::Label lfo1TVFDepthLabel;
    juce::Slider lfo1TVADepthSlider;
    juce::Label lfo1TVADepthLabel;

    juce::ComboBox lfo2FormComboBox;
    juce::Label lfo2FormLabel;
    juce::ComboBox lfo2OffsetComboBox;
    juce::Label lfo2OffsetLabel;
    juce::ToggleButton lfo2SyncToggle;
    juce::Label lfo2SyncLabel;
    juce::Slider lfo2RateSlider;
    juce::Label lfo2RateLabel;
    juce::Slider lfo2DelaySlider;
    juce::Label lfo2DelayLabel;
    juce::ToggleButton lfo2FadeToggle;
    juce::Label lfo2FadeLabel;
    juce::Slider lfo2FadeTimeSlider;
    juce::Label lfo2FadeTimeLabel;
    juce::Slider lfo2PitchDepthSlider;
    juce::Label lfo2PitchDepthLabel;
    juce::Slider lfo2TVFDepthSlider;
    juce::Label lfo2TVFDepthLabel;
    juce::Slider lfo2TVADepthSlider;
    juce::Label lfo2TVADepthLabel;

    juce::Slider pitchCoarseSlider;
    juce::Label pitchCoarseLabel;
    juce::Slider pitchFineSlider;
    juce::Label pitchFineLabel;
    juce::ComboBox pitchRandomComboBox;
    juce::Label pitchRandomLabel;
    juce::ComboBox pitchKFComboBox;
    juce::Label pitchKFLabel;
    juce::Slider penvLevSensSlider;
    juce::Label penvLevSensLabel;
    juce::ComboBox penvTime1SensComboBox;
    juce::Label penvTime1SensLabel;
    juce::ComboBox penvTime4SensComboBox;
    juce::Label penvTime4SensLabel;
    juce::ComboBox penvTimeKFSensComboBox;
    juce::Label penvTimeKFSensLabel;
    juce::Slider penvDepthSlider;
    juce::Label penvDepthLabel;
    juce::Slider penv1TimeSlider;
    juce::Label penv1TimeLabel;
    juce::Slider penv1LevelSlider;
    juce::Label penv1LevelLabel;
    juce::Slider penv2TimeSlider;
    juce::Label penv2TimeLabel;
    juce::Slider penv2LevelSlider;
    juce::Label penv2LevelLabel;
    juce::Slider penv3TimeSlider;
    juce::Label penv3TimeLabel;
    juce::Slider penv3LevelSlider;
    juce::Label penv3LevelLabel;
    juce::Slider penv4TimeSlider;
    juce::Label penv4TimeLabel;
    juce::Slider penv4LevelSlider;
    juce::Label penv4LevelLabel;

    juce::ComboBox filterModeComboBox;
    juce::Label filterModeLabel;
    juce::Slider filterCutoffSlider;
    juce::Label filterCutoffLabel;
    juce::Slider filterResoSlider;
    juce::Label filterResoLabel;
    juce::ComboBox filterResoModeComboBox;
    juce::ComboBox filterKFComboBox;
    juce::Label filterKFLabel;
    juce::ComboBox fenvVelCurveComboBox;
    juce::Label fenvVelCurveLabel;
    juce::Slider fenvLevSensSlider;
    juce::Label fenvLevSensLabel;
    juce::ComboBox fenvTime1SensComboBox;
    juce::Label fenvTime1SensLabel;
    juce::ComboBox fenvTime4SensComboBox;
    juce::Label fenvTime4SensLabel;
    juce::ComboBox fenvTimeKFSensComboBox;
    juce::Label fenvTimeKFSensLabel;
    juce::Slider fenvDepthSlider;
    juce::Label fenvDepthLabel;
    juce::Slider fenv1TimeSlider;
    juce::Label fenv1TimeLabel;
    juce::Slider fenv1LevelSlider;
    juce::Label fenv1LevelLabel;
    juce::Slider fenv2TimeSlider;
    juce::Label fenv2TimeLabel;
    juce::Slider fenv2LevelSlider;
    juce::Label fenv2LevelLabel;
    juce::Slider fenv3TimeSlider;
    juce::Label fenv3TimeLabel;
    juce::Slider fenv3LevelSlider;
    juce::Label fenv3LevelLabel;
    juce::Slider fenv4TimeSlider;
    juce::Label fenv4TimeLabel;
    juce::Slider fenv4LevelSlider;
    juce::Label fenv4LevelLabel;

    juce::Slider levelSlider;
    juce::Label levelLabel;
    juce::ComboBox levelKFComboBox;
    juce::Label levelKFLabel;
    juce::Slider panSlider;
    juce::Label panLabel;
    juce::ComboBox panKFComboBox;
    juce::Label panKFLabel;
    juce::ComboBox toneDelayComboBox;
    juce::Label toneDelayLabel;
    juce::Slider toneDelayTimeSlider;
    juce::Label toneDelayTimeLabel;
    juce::ComboBox aenvVelCurveComboBox;
    juce::Label aenvVelCurveLabel;
    juce::Slider aenvLevSensSlider;
    juce::Label aenvLevSensLabel;
    juce::ComboBox aenvTime1SensComboBox;
    juce::Label aenvTime1SensLabel;
    juce::ComboBox aenvTime4SensComboBox;
    juce::Label aenvTime4SensLabel;
    juce::ComboBox aenvTimeKFSensComboBox;
    juce::Label aenvTimeKFSensLabel;
    juce::Slider aenvDepthComboBox;
    juce::Label aenvDepthLabel;
    juce::Slider aenv1TimeSlider;
    juce::Label aenv1TimeLabel;
    juce::Slider aenv1LevelSlider;
    juce::Label aenv1LevelLabel;
    juce::Slider aenv2TimeSlider;
    juce::Label aenv2TimeLabel;
    juce::Slider aenv2LevelSlider;
    juce::Label aenv2LevelLabel;
    juce::Slider aenv3TimeSlider;
    juce::Label aenv3TimeLabel;
    juce::Slider aenv3LevelSlider;
    juce::Label aenv3LevelLabel;
    juce::Slider aenv4TimeSlider;
    juce::Label aenv4TimeLabel;

    juce::Slider drySlider;
    juce::Label dryLabel;
    juce::Slider reverbSlider;
    juce::Label reverbLabel;
    juce::Slider chorusSlider;
    juce::Label chorusLabel;
    juce::ComboBox outputComboBox;
    juce::Label outputLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditToneTab)
};
