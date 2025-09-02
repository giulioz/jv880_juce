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

#include "widgets/Button.h"
#include "widgets/Menu.h"
#include "widgets/Slider.h"

class VirtualJVEditor;

//==============================================================================

class EditToneTab : public juce::Component,
                    public juce::Slider::Listener,
                    public juce::Button::Listener,
                    public juce::ComboBox::Listener
{
public:
    EditToneTab(VirtualJVProcessor &, VirtualJVEditor *, uint8_t);
    ~EditToneTab() override;

    void resized() override;
    void sliderValueChanged(juce::Slider *) override;
    void buttonClicked(juce::Button *) override;
    void buttonStateChanged(juce::Button*) override {}
    void comboBoxChanged(juce::ComboBox *) override;

    void updateValues();

    void sendSysexPatchToneChange1Byte(uint8_t address, uint8_t value);
    void sendSysexPatchToneChange2Byte(uint8_t address, uint8_t value);

private:
    enum EditToneWidgets
    {
        ToneSwitch             = 200U,

        WaveGroup              = 201U,
        Waveform               = 202U,

        VelRangeLow            = 203U,
        VelRangeHigh           = 204U,

        FXMSwitch              = 205U,
        FXMDepth               = 206U,

        PitchCoarse            = 210U,
        PitchFine              = 211U,
        PitchRandom            = 212U,
        PitchKeyfollow         = 213U,
        PitchEnvLevelSense     = 214U,
        PitchEnvTime1Sense     = 215U,
        PitchEnvTime4Sense     = 216U,
        PitchEnvTimeKeyfollow  = 217U,
        PitchEnvDepth          = 218U,

        PitchEnvTime1          = 220U,
        PitchEnvLevel1         = 221U,
        PitchEnvTime2          = 222U,
        PitchEnvLevel2         = 223U,
        PitchEnvTime3          = 224U,
        PitchEnvLevel3         = 225U,
        PitchEnvTime4          = 226U,
        PitchEnvLevel4         = 227U,

        FilterMode             = 230U,
        FilterCutoff           = 231U,
        FilterReso             = 232U,
        FilterResoMode         = 233U,
        FilterKeyfollow        = 234U,
        FilterVelCurve         = 235U,
        FilterEnvLevelSense    = 236U,
        FilterEnvTime1Sense    = 237U,
        FilterEnvTime4Sense    = 238U,
        FilterEnvTimeKeyfollow = 239U,
        FilterEnvDepth         = 240U,

        FilterEnvTime1         = 241U,
        FilterEnvLevel1        = 242U,
        FilterEnvTime2         = 243U,
        FilterEnvLevel2        = 244U,
        FilterEnvTime3         = 245U,
        FilterEnvLevel3        = 246U,
        FilterEnvTime4         = 247U,
        FilterEnvLevel4        = 248U,

        Level                  = 250U,
        Pan                    = 251U,
        LevelKeyfollow         = 252U,
        PanKeyfollow           = 253U,
        DelayMode              = 254U,
        DelayTime              = 255U,
        AmpVelCurve            = 256U,
        AmpEnvLevelSense       = 257U,
        AmpEnvTime1Sense       = 258U,
        AmpEnvTime4Sense       = 259U,
        AmpEnvTimeKeyfollow    = 260U,

        AmpEnvTime1            = 261U,
        AmpEnvLevel1           = 262U,
        AmpEnvTime2            = 263U,
        AmpEnvLevel2           = 264U,
        AmpEnvTime3            = 265U,
        AmpEnvLevel3           = 266U,
        AmpEnvTime4            = 267U,

        DrySend                = 270U,
        ReverbSend             = 271U,
        ChorusSend             = 272U,
        Output                 = 273U,

        LFO1Waveform           = 280U,
        LFO1Offset             = 281U,
        LFO1Rate               = 282U,
        LFO1Delay              = 283U,
        LFO1KeySync            = 284U,
        LFO1FadeTime           = 285U,
        LFO1FadeOut            = 286U,
        LFO1ToPitch            = 287U,
        LFO1ToFilter           = 288U,
        LFO1ToAmp              = 289U,

        LFO2Waveform           = 290U,
        LFO2Offset             = 291U,
        LFO2Rate               = 292U,
        LFO2Delay              = 293U,
        LFO2KeySync            = 294U,
        LFO2FadeTime           = 295U,
        LFO2FadeOut            = 296U,
        LFO2ToPitch            = 297U,
        LFO2ToFilter           = 298U,
        LFO2ToAmp              = 299U,

        CC7Receive             = 300U,
        SustainPedalReceive    = 301U,

        MW1Target              = 310U,
        MW1Depth               = 311U,
        MW2Target              = 312U,
        MW2Depth               = 313U,
        MW3Target              = 314U,
        MW3Depth               = 315U,
        MW4Target              = 316U,
        MW4Depth               = 317U,

        AT1Target              = 320U,
        AT1Depth               = 321U,
        AT2Target              = 322U,
        AT2Depth               = 323U,
        AT3Target              = 324U,
        AT3Depth               = 325U,
        AT4Target              = 326U,
        AT4Depth               = 327U,

        EXP1Target             = 330U,
        EXP1Depth              = 331U,
        EXP2Target             = 332U,
        EXP2Depth              = 333U,
        EXP3Target             = 334U,
        EXP3Depth              = 335U,
        EXP4Target             = 336U,
        EXP4Depth              = 337U,
    };

    void addMenuEntriesFromArray(juce::ComboBox &menu, const std::vector<std::string> &array);
    void updateWaveformComboBox(juce::ComboBox &wfMenu);

    VirtualJVProcessor &processor;
    VirtualJVEditor *editor;

    uint8_t toneCount;

    juce::Label waveGroupLabel{ "", "Wave Group" };
    Menu waveGroupComboBox{ WaveGroup };
    juce::Label waveformLabel{ "", "Waveform" };
    Menu waveformComboBox{ Waveform };
    Button toneSwitchToggle{ ToneSwitch , "Enable" };
    Button FXMSwitchToggle{ FXMSwitch , "FXM" };
    juce::Label FXMDepthLabel{ "", "Depth" };
    Slider FXMDepthSlider{ FXMDepth, 1, 16, 1 };

    juce::Label velRangeLabel{ "", "Velocity Range" };
    Slider velRangeLowSlider{ VelRangeLow, 0, 127, 1 };
    Slider velRangeHighSlider{ VelRangeHigh, 0, 127, 1, 127 };

    Button volumeSwitchToggle{ CC7Receive, "CC7 Volume" };
    Button holdSwitchToggle{ SustainPedalReceive, "Sustain Pedal" };

    juce::Label modDestALabel{ "", "MW 1" };
    Menu modDestAComboBox{ MW1Target };
    Slider modSensASlider{ MW1Depth, -63, 63, 1, 0, true };
    juce::Label modDestBLabel{ "", "2" };
    Menu modDestBComboBox{ MW2Target };
    Slider modSensBSlider{ MW2Depth, -63, 63, 1, 0, true };
    juce::Label modDestCLabel{ "", "3" };
    Menu modDestCComboBox{ MW3Target };
    Slider modSensCSlider{ MW3Depth, -63, 63, 1, 0, true };
    juce::Label modDestDLabel{ "", "4" };
    Menu modDestDComboBox{ MW4Target };
    Slider modSensDSlider{ MW4Depth, -63, 63, 1, 0, true };

    juce::Label aftDestALabel{ "", "AT 1" };
    Menu aftDestAComboBox{ AT1Target };
    Slider aftSensASlider{ AT1Depth, -63, 63, 1, 0, true };
    juce::Label aftDestBLabel{ "", "2" };
    Menu aftDestBComboBox{ AT2Target };
    Slider aftSensBSlider{ AT2Depth, -63, 63, 1, 0, true };
    juce::Label aftDestCLabel{ "", "3" };
    Menu aftDestCComboBox{ AT3Target };
    Slider aftSensCSlider{ AT3Depth, -63, 63, 1, 0, true };
    juce::Label aftDestDLabel{ "", "4" };
    Menu aftDestDComboBox{ AT4Target };
    Slider aftSensDSlider{ AT4Depth, -63, 63, 1, 0, true };

    juce::Label expDestALabel{ "", "EXP 1" };
    Menu expDestAComboBox{ EXP1Target };
    Slider expSensASlider{ EXP1Depth, -63, 63, 1, 0, true };
    juce::Label expDestBLabel{ "", "2" };
    Menu expDestBComboBox{ EXP2Target };
    Slider expSensBSlider{ EXP2Depth, -63, 63, 1, 0, true };
    juce::Label expDestCLabel{ "", "3" };
    Menu expDestCComboBox{ EXP3Target };
    Slider expSensCSlider{ EXP3Depth, -63, 63, 1, 0, true };
    juce::Label expDestDLabel{ "", "4" };
    Menu expDestDComboBox{ EXP4Target };
    Slider expSensDSlider{ EXP4Depth, -63, 63, 1, 0, true };

    juce::Label lfo1FormLabel{ "", "LFO 1" };
    Menu lfo1FormComboBox{ LFO1Waveform };
    juce::Label lfo1OffsetLabel{ "", "Offset" };
    Menu lfo1OffsetComboBox{ LFO1Offset, 2 };
    Button lfo1SyncToggle{ LFO1KeySync, "Key Sync" };
    juce::Label lfo1RateLabel{ "", "Rate" };
    Slider lfo1RateSlider{ LFO1Rate, 0, 127, 1, 64 };
    juce::Label lfo1DelayLabel{ "", "Delay" };
    Slider lfo1DelaySlider{ LFO1Delay, 0, 128, 1 };
    Button lfo1FadeToggle{ LFO1FadeOut, "Fade Out" };
    juce::Label lfo1FadeTimeLabel{ "", "Fade Time" };
    Slider lfo1FadeTimeSlider{ LFO1FadeTime, 0, 127, 1 };
    juce::Label lfo1PitchDepthLabel{ "", u8"/U2192Pitch" };
    Slider lfo1PitchDepthSlider{ LFO1ToPitch, -60, 60, 1, 0, true };
    juce::Label lfo1TVFDepthLabel{ "", u8"\U00002192Filter" };
    Slider lfo1TVFDepthSlider{ LFO1ToFilter, -63, 63, 1, 0, true };
    juce::Label lfo1TVADepthLabel{ "", u8"\U00002192Amp" };
    Slider lfo1TVADepthSlider{ LFO1ToAmp, -63, 63, 1, 0, true };

    juce::Label lfo2FormLabel{ "", "LFO 2" };
    Menu lfo2FormComboBox{ LFO2Waveform };
    juce::Label lfo2OffsetLabel{ "", "Offset" };
    Menu lfo2OffsetComboBox{ LFO2Offset, 2 };
    Button lfo2SyncToggle{ LFO2KeySync, "Key Sync" };
    juce::Label lfo2RateLabel{ "", "Rate" };
    Slider lfo2RateSlider{ LFO2Rate, 0, 127, 1, 64 };
    juce::Label lfo2DelayLabel{ "", "Delay" };
    Slider lfo2DelaySlider{ LFO2Delay, 0, 128, 1 };
    Button lfo2FadeToggle{ LFO2FadeOut, "Fade Out" };
    juce::Label lfo2FadeTimeLabel{ "", "Fade Time" };
    Slider lfo2FadeTimeSlider{ LFO2FadeTime, 0, 127, 1 };
    juce::Label lfo2PitchDepthLabel{ "", u8"\U00002192Pitch" };
    Slider lfo2PitchDepthSlider{ LFO2ToPitch, -60, 60, 1, 0, true };
    juce::Label lfo2TVFDepthLabel{ "", u8"\U00002192Filter" };
    Slider lfo2TVFDepthSlider{ LFO2ToFilter, -63, 63, 1, 0, true };
    juce::Label lfo2TVADepthLabel{ "", u8"\U00002192Amp" };
    Slider lfo2TVADepthSlider{ LFO2ToAmp, -63, 63, 1, 0, true };

    juce::Label pitchCoarseLabel{ "", "Coarse" };
    Slider pitchCoarseSlider{ PitchCoarse, -48, 48, 1, 0, true };
    juce::Label pitchFineLabel{ "", "Fine" };
    Slider pitchFineSlider{ PitchFine, -50, 50, 1, 0, true };
    juce::Label pitchRandomLabel{ "", "Random | KF" };
    Menu pitchRandomComboBox{ PitchRandom };
    Menu pitchKFComboBox{ PitchKeyfollow, 12 };
    juce::Label penvLevSensLabel{ "", u8"Vel\U00002192Env Depth" };
    Slider penvLevSensSlider{ PitchEnvLevelSense, -63, 63, 1, 0, true };
    juce::Label penvTime1SensLabel{ "", u8"Vel\U00002192Env T1 | T4" };
    Menu penvTime1SensComboBox{ PitchEnvTime1Sense, 7 };
    Menu penvTime4SensComboBox{ PitchEnvTime4Sense, 7 };
    juce::Label penvTimeKFSensLabel{ "", u8"KF\U00002192Env Time" };
    Menu penvTimeKFSensComboBox{ PitchEnvTimeKeyfollow, 7 };
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
    Menu filterResoModeComboBox{ FilterResoMode };
    juce::Label filterKFLabel{ "", "KF | Vel Curve" };
    Menu filterKFComboBox{ FilterKeyfollow, 5 };
    Menu fenvVelCurveComboBox{ FilterVelCurve };
    juce::Label fenvLevSensLabel{ "", u8"Vel\U00002192Env Depth" };
    Slider fenvLevSensSlider{ FilterEnvLevelSense, -63, 63, 1, 0, true };
    juce::Label fenvTime1SensLabel{ "", u8"Vel\U00002192Env T1 | T4" };
    Menu fenvTime1SensComboBox{ FilterEnvTime1Sense, 7 };
    Menu fenvTime4SensComboBox{ FilterEnvTime4Sense, 7 };
    juce::Label fenvTimeKFSensLabel{ "", u8"KF\U00002192Env Time" };
    Menu fenvTimeKFSensComboBox{ FilterEnvTimeKeyfollow, 7 };
    juce::Label fenvDepthLabel{ "", u8"Env\U00002192Cutoff" };
    Slider fenvDepthSlider{ FilterEnvDepth, -63, 63, 1, 0, true };
    juce::Label fenv1TimeLabel{ "", "Time | Level 1" };
    Slider fenv1TimeSlider{ FilterEnvTime1, 0, 127, 1, 127 };
    Slider fenv1LevelSlider{ FilterEnvLevel1, 0, 127, 1 };
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
    juce::Label levelKFLabel{ "", u8"KF\U00002192Level | Pan" };
    Menu levelKFComboBox{ LevelKeyfollow, 7 };
    Menu panKFComboBox{ PanKeyfollow, 7 };
    juce::Label toneDelayLabel{ "", "Delay Mode" };
    Menu toneDelayComboBox{ DelayMode };
    juce::Label toneDelayTimeLabel{ "", "Delay Time" };
    Slider toneDelayTimeSlider{ DelayTime, 0, 128, 1 };
    juce::Label aenvVelCurveLabel{ "", "Vel Curve" };
    Menu aenvVelCurveComboBox{ AmpVelCurve };
    juce::Label aenvLevSensLabel{ "", u8"Vel\U00002192Amp" };
    Slider aenvLevSensSlider{ AmpEnvLevelSense, -63, 63, 1, 0, true };
    juce::Label aenvTime1SensLabel{ "", u8"Vel\U00002192Env T1 | T4" };
    Menu aenvTime1SensComboBox{ AmpEnvTime1Sense, 7 };
    Menu aenvTime4SensComboBox{ AmpEnvTime4Sense, 7 };
    juce::Label aenvTimeKFSensLabel{ "", "Time KF" };
    Menu aenvTimeKFSensComboBox{ AmpEnvTimeKeyfollow, 7 };
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditToneTab)
};
