/*
  ==============================================================================

    EditRhythmTab.h
    Created: 20 Aug 2024 2:34:06pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>

#include "../PluginProcessor.h"

#include "widgets/Button.h"
#include "widgets/Menu.h"
#include "widgets/Slider.h"

class VirtualJVEditor;

//==============================================================================

class EditRhythmTab : public juce::Component,
    public juce::Slider::Listener,
    public juce::Button::Listener,
    public juce::ComboBox::Listener
{
public:
    EditRhythmTab(VirtualJVProcessor&, VirtualJVEditor*);
    ~EditRhythmTab() override;

    void resized() override;
    void sliderValueChanged(juce::Slider*) override;
    void buttonClicked(juce::Button*) override;
    void buttonStateChanged(juce::Button*) override {}
    void comboBoxChanged(juce::ComboBox*) override;

    void updateValues();

    void sendSysexPatchRhythmChange1Byte(uint8_t address, uint8_t value);
    void sendSysexPatchRhythmChange2Byte(uint8_t address, uint8_t value);

private:
    enum EditRhythmWidgets
    {
        SelectKey           = 400U,
        WaveGroup           = 401U,
        Waveform            = 402U,
        ToneSwitch          = 403U,
        MuteGroup           = 404U,
        EnvMode             = 405U,
        BendRange           = 406U,

        PitchCoarse         = 410U,
        PitchFine           = 411U,
        PitchRandom         = 412U,
        PitchEnvLevelSense  = 413U,
        PitchEnvTimeSense   = 414U,
        PitchEnvDepth       = 415U,

        PitchEnvTime1       = 420U,
        PitchEnvLevel1      = 421U,
        PitchEnvTime2       = 422U,
        PitchEnvLevel2      = 423U,
        PitchEnvTime3       = 424U,
        PitchEnvLevel3      = 425U,
        PitchEnvTime4       = 426U,
        PitchEnvLevel4      = 427U,

        FilterMode          = 430U,
        FilterCutoff        = 431U,
        FilterReso          = 432U,
        FilterResoMode      = 433U,
        FilterEnvLevelSense = 434U,
        FilterEnvTimeSense  = 435U,
        FilterEnvDepth      = 436U,

        FilterEnvTime1      = 440U,
        FilterEnvLevel1     = 441U,
        FilterEnvTime2      = 442U,
        FilterEnvLevel2     = 443U,
        FilterEnvTime3      = 444U,
        FilterEnvLevel3     = 445U,
        FilterEnvTime4      = 446U,
        FilterEnvLevel4     = 447U,

        Level               = 450U,
        Pan                 = 451U,
        AmpEnvLevelSense    = 452U,
        AmpEnvTimeSense     = 453U,

        AmpEnvTime1         = 460U,
        AmpEnvLevel1        = 461U,
        AmpEnvTime2         = 462U,
        AmpEnvLevel2        = 463U,
        AmpEnvTime3         = 464U,
        AmpEnvLevel3        = 465U,
        AmpEnvTime4         = 466U,

        DrySend             = 470U,
        ReverbSend          = 471U,
        ChorusSend          = 472U,
        Output              = 473U
    };

    void addMenuEntriesFromArray(Menu& menu, const std::vector<std::string>& array);
    void updateWaveformComboBox(Menu& wfMenu);

    VirtualJVProcessor& processor;
    VirtualJVEditor* editor;

    uint8_t toneCount;

    juce::Label toneLabel{ "", "Key" };
    Menu selectKeyComboBox{ SelectKey };

    juce::Label waveGroupLabel{ "", "Wave Group" };
    Menu waveGroupComboBox{ WaveGroup };
    juce::Label waveformLabel{ "", "Waveform" };
    Menu waveformComboBox{ Waveform };
    Button toneSwitchToggle{ ToneSwitch, "Enable" };

    juce::Label muteLabel{ "", "Mute Group" };
    Slider muteGroupSlider{ MuteGroup, 0, 31, 1 };
    juce::Label envModeLabel{ "", "Env Mode" };
    Menu envModeComboBox{ EnvMode };
    juce::Label bendRangeLabel{ "", "Bend Range" };
    Slider bendRangeSlider{ BendRange, 0, 12, 1 };

    juce::Label pitchCoarseLabel{ "", "Coarse" };
    Slider pitchCoarseSlider{ PitchCoarse, -48, 48, 1, 0, true };
    juce::Label pitchFineLabel{ "", "Fine" };
    Slider pitchFineSlider{ PitchFine, -50, 50, 1, 0, true };
    juce::Label pitchRandomLabel{ "", "Random" };
    Menu pitchRandomComboBox{ PitchRandom };
    juce::Label penvLevSensLabel{ "", u8"Vel\U00002192Env Depth" };
    Slider penvLevSensSlider{ PitchEnvLevelSense, -63, 63, 1, 0, true };
    juce::Label penvTimeSensLabel{ "", u8"Vel\U00002192Env Time" };
    Menu penvTimeSensComboBox{ PitchEnvTimeSense, 7 };
    juce::Label penvDepthLabel{ "", u8"Env\U00002192Pitch" };
    Slider penvDepthSlider{ PitchEnvDepth, -12, 12, 1, 0, true };
    juce::Label penv1TimeLabel{ "", "Time | Level 1" };
    Slider penv1TimeSlider{ PitchEnvTime1, 0, 127, 1 };
    Slider penv1LevelSlider{ PitchEnvLevel1, -63, 63, 1, 63, true };
    juce::Label penv2TimeLabel{ "", "2" };
    Slider penv2TimeSlider{ PitchEnvTime2, 0, 127, 1 };
    Slider penv2LevelSlider{ PitchEnvLevel2, -63, 63, 1, 0, true };
    juce::Label penv3TimeLabel{ "", "3" };
    Slider penv3TimeSlider{ PitchEnvTime3, 0, 127, 1 };
    Slider penv3LevelSlider{ PitchEnvLevel3, -63, 63, 1, 0, true };
    juce::Label penv4TimeLabel{ "", "4" };
    Slider penv4TimeSlider{ PitchEnvTime4, 0, 127, 1 };
    Slider penv4LevelSlider{ PitchEnvLevel4, -63, 63, 1, 0, true };

    juce::Label filterModeLabel{ "", "Filter Mode" };
    Menu filterModeComboBox{ FilterMode, 1 };
    juce::Label filterCutoffLabel{ "", "Cutoff" };
    Slider filterCutoffSlider{ FilterCutoff, 0, 127, 1, 127 };
    juce::Label filterResoLabel{ "", "Reso | Mode" };
    Slider filterResoSlider{ FilterReso, 0, 127, 1 };
    Menu filterResoModeComboBox{ FilterReso };
    juce::Label fenvLevSensLabel{ "", u8"Vel\U00002192Env Depth" };
    Slider fenvLevSensSlider{ FilterEnvLevelSense, -63, 63, 1, 0, true };
    juce::Label fenvTimeSensLabel{ "", u8"Vel\U00002192Env Times" };
    Menu fenvTimeSensComboBox{ FilterEnvTimeSense, 7 };
    juce::Label fenvDepthLabel{ "", u8"Env\U00002192Cutoff" };
    Slider fenvDepthSlider{ FilterEnvDepth, -63, 63, 1, 0, true };
    juce::Label fenv1TimeLabel{ "", "Time | Level 1" };
    Slider fenv1TimeSlider{ FilterEnvTime1, 0, 127, 1 };
    Slider fenv1LevelSlider{ FilterEnvLevel1, 0, 127, 1, 127 };
    juce::Label fenv2TimeLabel{ "", "2" };
    Slider fenv2TimeSlider{ FilterEnvTime2, 0, 127, 1 };
    Slider fenv2LevelSlider{ FilterEnvLevel2, 0, 127, 1 };
    juce::Label fenv3TimeLabel{ "", "3" };
    Slider fenv3TimeSlider{ FilterEnvTime3, 0, 127, 1 };
    Slider fenv3LevelSlider{ FilterEnvLevel3, 0, 127, 1 };
    juce::Label fenv4TimeLabel{ "", "4" };
    Slider fenv4TimeSlider{ FilterEnvTime4, 0, 127, 1 };
    Slider fenv4LevelSlider{ FilterEnvLevel4, 0, 127, 1 };

    juce::Label levelLabel{ "", "Level" };
    Slider levelSlider{ Level, 0, 127, 1, 96 };
    juce::Label panLabel{ "", "Pan" };
    Slider panSlider{ Pan, -64, 64, 1, 0, true };
    juce::Label aenvLevSensLabel{ "", u8"Vel\U00002192Amp" };
    Slider aenvLevSensSlider{ AmpEnvLevelSense, -63, 63, 1, 0, true };
    juce::Label aenvTimeSensLabel{ "", u8"Vel\U00002192Env Times" };
    Menu aenvTimeSensComboBox{ AmpEnvTimeSense, 7 };
    juce::Label aenv1TimeLabel{ "", "Time | Level 1" };
    Slider aenv1TimeSlider{ AmpEnvTime1, 0, 127, 1 };
    Slider aenv1LevelSlider{ AmpEnvLevel1, 0, 127, 1, 127 };
    juce::Label aenv2TimeLabel{ "", "2" };
    Slider aenv2TimeSlider{ AmpEnvTime2, 0, 127, 1 };
    Slider aenv2LevelSlider{ AmpEnvLevel2, 0, 127, 1 };
    juce::Label aenv3TimeLabel{ "", "3" };
    Slider aenv3TimeSlider{ AmpEnvTime3, 0, 127, 1 };
    Slider aenv3LevelSlider{ AmpEnvLevel3, 0, 127, 1 };
    juce::Label aenv4TimeLabel{ "", "4" };
    Slider aenv4TimeSlider{ AmpEnvTime4, 0, 127, 1 };

    juce::Label dryLabel{ "", "Dry Send" };
    Slider drySlider{ DrySend, 0, 127, 1, 127 };
    juce::Label reverbLabel{ "", "Reverb Send" };
    Slider reverbSlider{ ReverbSend, 0, 127, 1 };
    juce::Label chorusLabel{ "", "Chorus Send" };
    Slider chorusSlider{ ChorusSend, 0, 127, 1 };
    juce::Label outputLabel{ "", "Output" };
    Menu outputComboBox{ Output };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditRhythmTab)
};

