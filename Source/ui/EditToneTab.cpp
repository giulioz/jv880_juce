/*
  ==============================================================================

    EditToneTab.cpp
    Created: 20 Aug 2024 2:34:06pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EditToneTab.h"
#include "../dataStructures.h"

//==============================================================================
EditToneTab::EditToneTab(Jv880_juceAudioProcessor& p, uint8_t toneIn) : audioProcessor(p), toneCount(toneIn)
{
    addAndMakeVisible(waveGroupLabel);
    waveGroupLabel.setText("Wave Group", juce::dontSendNotification);
    waveGroupLabel.attachToComponent(&waveGroupComboBox, true);
    addAndMakeVisible(waveGroupComboBox);
    waveGroupComboBox.setScrollWheelEnabled(true);
    waveGroupComboBox.addListener(this);
    waveGroupComboBox.addItem("Internal", 1);
    waveGroupComboBox.addItem("Expansion", 2);

    addAndMakeVisible(waveformSlider);
    waveformSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    waveformSlider.setRange(1, 255, 1);
    waveformSlider.addListener(this);
    addAndMakeVisible(waveformLabel);
    waveformLabel.setText("Waveform", juce::dontSendNotification);
    waveformLabel.attachToComponent(&waveformSlider, true);

    addAndMakeVisible(toneSwitchToggle);
    toneSwitchToggle.addListener(this);
    toneSwitchToggle.setButtonText("Enable");

    addAndMakeVisible(FXMSwitchToggle);
    FXMSwitchToggle.addListener(this);
    FXMSwitchToggle.setButtonText("FXM");

    addAndMakeVisible(FXMDepthSlider);
    FXMDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    FXMDepthSlider.setRange(1, 16, 1);
    FXMDepthSlider.addListener(this);
    addAndMakeVisible(FXMDepthLabel);
    FXMDepthLabel.setText("Depth", juce::dontSendNotification);
    FXMDepthLabel.attachToComponent(&FXMDepthSlider, true);

    addAndMakeVisible(velRangeLowSlider);
    velRangeLowSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    velRangeLowSlider.setRange(0, 127, 1);
    velRangeLowSlider.addListener(this);
    addAndMakeVisible(velRangeLabel);
    velRangeLabel.setText("Velocity Range", juce::dontSendNotification);
    velRangeLabel.attachToComponent(&velRangeLowSlider, true);

    addAndMakeVisible(velRangeHighSlider);
    velRangeHighSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    velRangeHighSlider.setRange(0, 127, 1);
    velRangeHighSlider.addListener(this);

    addAndMakeVisible(volumeSwitchToggle);
    volumeSwitchToggle.addListener(this);
    volumeSwitchToggle.setButtonText("CC7 Volume");

    addAndMakeVisible(holdSwitchToggle);
    holdSwitchToggle.addListener(this);
    holdSwitchToggle.setButtonText("Sustain Pedal");

    const std::vector<std::string> modSources
    {
        "Off",
        "Pitch",
        "Cutoff",
        "Resonance",
        "Level",
        "LFO 1→Pitch",
        "LFO 2→Pitch",
        "LFO 1→TVF",
        "LFO 2→TVF",
        "LFO 1→TVA",
        "LFO 2→TVA",
        "LFO 1 Rate",
        "LFO 2 Rate",
    };

    addAndMakeVisible(modDestALabel);
    modDestALabel.setText("MW 1", juce::dontSendNotification);
    modDestALabel.attachToComponent(&modDestAComboBox, true);
    addAndMakeVisible(modDestAComboBox);
    modDestAComboBox.addListener(this);
    modDestAComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(modDestAComboBox, modSources);
    addAndMakeVisible(modSensASlider);
    modSensASlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    modSensASlider.setRange(-63, 63, 1);
    modSensASlider.addListener(this);

    addAndMakeVisible(modDestBLabel);
    modDestBLabel.setText("2", juce::dontSendNotification);
    modDestBLabel.attachToComponent(&modDestBComboBox, true);
    addAndMakeVisible(modDestBComboBox);
    modDestBComboBox.addListener(this);
    modDestBComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(modDestBComboBox, modSources);
    addAndMakeVisible(modSensBSlider);
    modSensBSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    modSensBSlider.setRange(-63, 63, 1);
    modSensBSlider.addListener(this);

    addAndMakeVisible(modDestCLabel);
    modDestCLabel.setText("3", juce::dontSendNotification);
    modDestCLabel.attachToComponent(&modDestCComboBox, true);
    addAndMakeVisible(modDestCComboBox);
    modDestCComboBox.addListener(this);
    modDestCComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(modDestCComboBox, modSources);
    addAndMakeVisible(modSensCSlider);
    modSensCSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    modSensCSlider.setRange(-63, 63, 1);
    modSensCSlider.addListener(this);

    addAndMakeVisible(modDestDLabel);
    modDestDLabel.setText("4", juce::dontSendNotification);
    modDestDLabel.attachToComponent(&modDestDComboBox, true);
    addAndMakeVisible(modDestDComboBox);
    modDestDComboBox.addListener(this);
    modDestDComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(modDestDComboBox, modSources);
    addAndMakeVisible(modSensDSlider);
    modSensDSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    modSensDSlider.setRange(-63, 63, 1);
    modSensDSlider.addListener(this);

    addAndMakeVisible(aftDestALabel);
    aftDestALabel.setText("AT 1", juce::dontSendNotification);
    aftDestALabel.attachToComponent(&aftDestAComboBox, true);
    addAndMakeVisible(aftDestAComboBox);
    aftDestAComboBox.addListener(this);;
    aftDestAComboBox.setScrollWheelEnabled(true);;
    addMenuEntriesFromArray(aftDestAComboBox, modSources);
    addAndMakeVisible(aftSensASlider);
    aftSensASlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aftSensASlider.setRange(-63, 63, 1);
    aftSensASlider.addListener(this);

    addAndMakeVisible(aftDestBLabel);
    aftDestBLabel.setText("2", juce::dontSendNotification);
    aftDestBLabel.attachToComponent(&aftDestBComboBox, true);
    addAndMakeVisible(aftDestBComboBox);
    aftDestBComboBox.addListener(this);
    aftDestBComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(aftDestBComboBox, modSources);
    addAndMakeVisible(aftSensBSlider);
    aftSensBSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aftSensBSlider.setRange(-63, 63, 1);
    aftSensBSlider.addListener(this);

    addAndMakeVisible(aftDestCLabel);
    aftDestCLabel.setText("3", juce::dontSendNotification);
    aftDestCLabel.attachToComponent(&aftDestCComboBox, true);
    addAndMakeVisible(aftDestCComboBox);
    aftDestCComboBox.addListener(this);
    aftDestCComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(aftDestCComboBox, modSources);
    addAndMakeVisible(aftSensCSlider);
    aftSensCSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aftSensCSlider.setRange(-63, 63, 1);
    aftSensCSlider.addListener(this);

    addAndMakeVisible(aftDestDLabel);
    aftDestDLabel.setText("4", juce::dontSendNotification);
    aftDestDLabel.attachToComponent(&aftDestDComboBox, true);
    addAndMakeVisible(aftDestDComboBox);
    aftDestDComboBox.addListener(this);
    aftDestDComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(aftDestDComboBox, modSources);
    addAndMakeVisible(aftSensDSlider);
    aftSensDSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aftSensDSlider.setRange(-63, 63, 1);
    aftSensDSlider.addListener(this);

    addAndMakeVisible(expDestALabel);
    expDestALabel.setText("EXP 1", juce::dontSendNotification);
    expDestALabel.attachToComponent(&expDestAComboBox, true);
    addAndMakeVisible(expDestAComboBox);
    expDestAComboBox.addListener(this);
    expDestAComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(expDestAComboBox, modSources);
    addAndMakeVisible(expSensASlider);
    expSensASlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    expSensASlider.setRange(-63, 63, 1);
    expSensASlider.addListener(this);

    addAndMakeVisible(expDestBLabel);
    expDestBLabel.setText("2", juce::dontSendNotification);
    expDestBLabel.attachToComponent(&expDestBComboBox, true);
    addAndMakeVisible(expDestBComboBox);
    expDestBComboBox.addListener(this);
    expDestBComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(expDestBComboBox, modSources);
    addAndMakeVisible(expSensBSlider);
    expSensBSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    expSensBSlider.setRange(-63, 63, 1);
    expSensBSlider.addListener(this);

    addAndMakeVisible(expDestCLabel);
    expDestCLabel.setText("3", juce::dontSendNotification);
    expDestCLabel.attachToComponent(&expDestCComboBox, true);
    addAndMakeVisible(expDestCComboBox);
    expDestCComboBox.addListener(this);
    expDestCComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(expDestCComboBox, modSources);
    addAndMakeVisible(expSensCSlider);
    expSensCSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    expSensCSlider.setRange(-63, 63, 1);
    expSensCSlider.addListener(this);

    addAndMakeVisible(expDestDLabel);
    expDestDLabel.setText("4", juce::dontSendNotification);
    expDestDLabel.attachToComponent(&expDestDComboBox, true);
    addAndMakeVisible(expDestDComboBox);
    expDestDComboBox.addListener(this);
    expDestDComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(expDestDComboBox, modSources);
    addAndMakeVisible(expSensDSlider);
    expSensDSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    expSensDSlider.setRange(-63, 63, 1);
    expSensDSlider.addListener(this);

    const std::vector<std::string> lfoWaves{"Triangle", "Sine", "Sawtooth", "Square", "Random 1", "Random 2"};

    const std::vector<std::string> lfoOffsets{"-100", "-50", "0", "+50", "+100"};

    addAndMakeVisible(lfo1FormLabel);
    lfo1FormLabel.setText("LFO 1", juce::dontSendNotification);
    lfo1FormLabel.attachToComponent(&lfo1FormComboBox, true);
    addAndMakeVisible(lfo1FormComboBox);
    lfo1FormComboBox.addListener(this);
    lfo1FormComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(lfo1FormComboBox, lfoWaves);
    addAndMakeVisible(lfo1OffsetLabel);
    lfo1OffsetLabel.setText("Offset", juce::dontSendNotification);
    lfo1OffsetLabel.attachToComponent(&lfo1OffsetComboBox, true);
    addAndMakeVisible(lfo1OffsetComboBox);
    lfo1OffsetComboBox.addListener(this);
    lfo1OffsetComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(lfo1OffsetComboBox, lfoOffsets);
    addAndMakeVisible(lfo1SyncToggle);
    lfo1SyncToggle.addListener(this);
    lfo1SyncToggle.setButtonText("Key Sync");
    addAndMakeVisible(lfo1RateSlider);
    lfo1RateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo1RateSlider.setRange(0, 127, 1);
    lfo1RateSlider.addListener(this);
    addAndMakeVisible(lfo1RateLabel);
    lfo1RateLabel.setText("Rate", juce::dontSendNotification);
    lfo1RateLabel.attachToComponent(&lfo1RateSlider, true);
    addAndMakeVisible(lfo1DelaySlider);
    lfo1DelaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo1DelaySlider.setRange(0, 128, 1);
    lfo1DelaySlider.addListener(this);
    addAndMakeVisible(lfo1DelayLabel);
    lfo1DelayLabel.setText("Delay", juce::dontSendNotification);
    lfo1DelayLabel.attachToComponent(&lfo1DelaySlider, true);
    addAndMakeVisible(lfo1FadeToggle);
    lfo1FadeToggle.addListener(this);
    lfo1FadeToggle.setButtonText("Fade Out");
    addAndMakeVisible(lfo1FadeTimeSlider);
    lfo1FadeTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo1FadeTimeSlider.setRange(0, 127, 1);
    lfo1FadeTimeSlider.addListener(this);
    addAndMakeVisible(lfo1FadeTimeLabel);
    lfo1FadeTimeLabel.setText("Fade Time", juce::dontSendNotification);
    lfo1FadeTimeLabel.attachToComponent(&lfo1FadeTimeSlider, true);
    addAndMakeVisible(lfo1PitchDepthSlider);
    lfo1PitchDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo1PitchDepthSlider.setRange(-60, 60, 1);
    lfo1PitchDepthSlider.addListener(this);
    addAndMakeVisible(lfo1PitchDepthLabel);
    lfo1PitchDepthLabel.setText("Pitch", juce::dontSendNotification);
    lfo1PitchDepthLabel.attachToComponent(&lfo1PitchDepthSlider, true);
    addAndMakeVisible(lfo1TVFDepthSlider);
    lfo1TVFDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo1TVFDepthSlider.setRange(-63, 63, 1);
    lfo1TVFDepthSlider.addListener(this);
    addAndMakeVisible(lfo1TVFDepthLabel);
    lfo1TVFDepthLabel.setText("TVF", juce::dontSendNotification);
    lfo1TVFDepthLabel.attachToComponent(&lfo1TVFDepthSlider, true);
    addAndMakeVisible(lfo1TVADepthSlider);
    lfo1TVADepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo1TVADepthSlider.setRange(-63, 63, 1);
    lfo1TVADepthSlider.addListener(this);
    addAndMakeVisible(lfo1TVADepthLabel);
    lfo1TVADepthLabel.setText("TVA", juce::dontSendNotification);
    lfo1TVADepthLabel.attachToComponent(&lfo1TVADepthSlider, true);

    addAndMakeVisible(lfo2FormLabel);
    lfo2FormLabel.setText("LFO 2", juce::dontSendNotification);
    lfo2FormLabel.attachToComponent(&lfo2FormComboBox, true);
    addAndMakeVisible(lfo2FormComboBox);
    lfo2FormComboBox.addListener(this);
    lfo2FormComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(lfo2FormComboBox, lfoWaves);
    addAndMakeVisible(lfo2OffsetLabel);
    lfo2OffsetLabel.setText("Offset", juce::dontSendNotification);
    lfo2OffsetLabel.attachToComponent(&lfo2OffsetComboBox, true);
    addAndMakeVisible(lfo2OffsetComboBox);
    lfo2OffsetComboBox.addListener(this);
    lfo2OffsetComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(lfo2OffsetComboBox, lfoOffsets);
    addAndMakeVisible(lfo2SyncToggle);
    lfo2SyncToggle.addListener(this);
    lfo2SyncToggle.setButtonText("Key Sync");
    addAndMakeVisible(lfo2RateSlider);
    lfo2RateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo2RateSlider.setRange(0, 127, 1);
    lfo2RateSlider.addListener(this);
    addAndMakeVisible(lfo2RateLabel);
    lfo2RateLabel.setText("Rate", juce::dontSendNotification);
    lfo2RateLabel.attachToComponent(&lfo2RateSlider, true);
    addAndMakeVisible(lfo2DelaySlider);
    lfo2DelaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo2DelaySlider.setRange(0, 128, 1);
    lfo2DelaySlider.addListener(this);
    addAndMakeVisible(lfo2DelayLabel);
    lfo2DelayLabel.setText("Delay", juce::dontSendNotification);
    lfo2DelayLabel.attachToComponent(&lfo2DelaySlider, true);
    addAndMakeVisible(lfo2FadeToggle);
    lfo2FadeToggle.addListener(this);
    lfo2FadeToggle.setButtonText("Fade Out");
    addAndMakeVisible(lfo2FadeTimeSlider);
    lfo2FadeTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo2FadeTimeSlider.setRange(0, 127, 1);
    lfo2FadeTimeSlider.addListener(this);
    addAndMakeVisible(lfo2FadeTimeLabel);
    lfo2FadeTimeLabel.setText("Fade Time", juce::dontSendNotification);
    lfo2FadeTimeLabel.attachToComponent(&lfo2FadeTimeSlider, true);
    addAndMakeVisible(lfo2PitchDepthSlider);
    lfo2PitchDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo2PitchDepthSlider.setRange(-60, 60, 1);
    lfo2PitchDepthSlider.addListener(this);
    addAndMakeVisible(lfo2PitchDepthLabel);
    lfo2PitchDepthLabel.setText("Pitch", juce::dontSendNotification);
    lfo2PitchDepthLabel.attachToComponent(&lfo2PitchDepthSlider, true);
    addAndMakeVisible(lfo2TVFDepthSlider);
    lfo2TVFDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo2TVFDepthSlider.setRange(-63, 63, 1);
    lfo2TVFDepthSlider.addListener(this);
    addAndMakeVisible(lfo2TVFDepthLabel);
    lfo2TVFDepthLabel.setText("TVF", juce::dontSendNotification);
    lfo2TVFDepthLabel.attachToComponent(&lfo2TVFDepthSlider, true);
    addAndMakeVisible(lfo2TVADepthSlider);
    lfo2TVADepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo2TVADepthSlider.setRange(-63, 63, 1);
    lfo2TVADepthSlider.addListener(this);
    addAndMakeVisible(lfo2TVADepthLabel);
    lfo2TVADepthLabel.setText("TVA", juce::dontSendNotification);
    lfo2TVADepthLabel.attachToComponent(&lfo2TVADepthSlider, true);

    addAndMakeVisible(pitchCoarseSlider);
    pitchCoarseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    pitchCoarseSlider.setRange(-48, 48, 1);
    pitchCoarseSlider.addListener(this);
    addAndMakeVisible(pitchCoarseLabel);
    pitchCoarseLabel.setText("Coarse", juce::dontSendNotification);
    pitchCoarseLabel.attachToComponent(&pitchCoarseSlider, true);

    addAndMakeVisible(pitchFineSlider);
    pitchFineSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    pitchFineSlider.setRange(-50, 50, 1);
    pitchFineSlider.addListener(this);
    addAndMakeVisible(pitchFineLabel);
    pitchFineLabel.setText("Fine", juce::dontSendNotification);
    pitchFineLabel.attachToComponent(&pitchFineSlider, true);

    const std::vector<std::string> pitchRandoms
    {
          "0",   "5",  "10",   "20",
         "30",  "40",  "50",   "70",
        "100", "200", "300",  "400",
        "500", "600", "800", "1200",
    };

    const std::vector<std::string> keyFollows
    {
        "-100",  "-70",  "-50",  "-30",
         "-10",    "0",  "+10",  "+20",
         "+30",  "+40",  "+50",  "+70",
        "+100", "+120", "+150", "+200",
    };

    const std::vector<std::string> np100
    {
        "-100",  "-70",  "-50",  "-40",
         "-30",  "-20",  "-10",    "0",
         "+10",  "+20",  "+30",  "+40",
         "+50",  "+70", "+100"
    };

    addAndMakeVisible(pitchRandomComboBox);
    pitchRandomComboBox.addListener(this);
    pitchRandomComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(pitchRandomComboBox, pitchRandoms);
    addAndMakeVisible(pitchRandomLabel);
    pitchRandomLabel.setText("Random | KF", juce::dontSendNotification);
    pitchRandomLabel.attachToComponent(&pitchRandomComboBox, true);

    addAndMakeVisible(pitchKFComboBox);
    pitchKFComboBox.addListener(this);
    pitchKFComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(pitchKFComboBox, keyFollows);

    addAndMakeVisible(penvLevSensSlider);
    penvLevSensSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penvLevSensSlider.setRange(-12, 12, 1);
    penvLevSensSlider.addListener(this);
    addAndMakeVisible(penvLevSensLabel);
    penvLevSensLabel.setText("Pitch Sens", juce::dontSendNotification);
    penvLevSensLabel.attachToComponent(&penvLevSensSlider, true);

    addAndMakeVisible(penvTime1SensComboBox);
    penvTime1SensComboBox.addListener(this);
    penvTime1SensComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(penvTime1SensComboBox, np100);
    addAndMakeVisible(penvTime1SensLabel);
    penvTime1SensLabel.setText("Time Sens", juce::dontSendNotification);
    penvTime1SensLabel.attachToComponent(&penvTime1SensComboBox, true);

    addAndMakeVisible(penvTime4SensComboBox);
    penvTime4SensComboBox.addListener(this);
    penvTime4SensComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(penvTime4SensComboBox, np100);

    addAndMakeVisible(penvTimeKFSensComboBox);
    penvTimeKFSensComboBox.addListener(this);
    penvTimeKFSensComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(penvTimeKFSensComboBox, np100);
    addAndMakeVisible(penvTimeKFSensLabel);
    penvTimeKFSensLabel.setText("Time KF", juce::dontSendNotification);
    penvTimeKFSensLabel.attachToComponent(&penvTimeKFSensComboBox, true);

    addAndMakeVisible(penvDepthSlider);
    penvDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penvDepthSlider.setRange(-12, 12, 1);
    penvDepthSlider.addListener(this);
    addAndMakeVisible(penvDepthLabel);
    penvDepthLabel.setText("Pitch Depth", juce::dontSendNotification);
    penvDepthLabel.attachToComponent(&penvDepthSlider, true);

    addAndMakeVisible(penv1TimeSlider);
    penv1TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv1TimeSlider.setRange(0, 127, 1);
    penv1TimeSlider.addListener(this);
    addAndMakeVisible(penv1TimeLabel);
    penv1TimeLabel.setText("Time | Level 1", juce::dontSendNotification);
    penv1TimeLabel.attachToComponent(&penv1TimeSlider, true);
    addAndMakeVisible(penv1LevelSlider);
    penv1LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv1LevelSlider.setRange(-63, 63, 1);
    penv1LevelSlider.addListener(this);

    addAndMakeVisible(penv2TimeSlider);
    penv2TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv2TimeSlider.setRange(0, 127, 1);
    penv2TimeSlider.addListener(this);
    addAndMakeVisible(penv2TimeLabel);
    penv2TimeLabel.setText("2", juce::dontSendNotification);
    penv2TimeLabel.attachToComponent(&penv2TimeSlider, true);
    addAndMakeVisible(penv2LevelSlider);
    penv2LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv2LevelSlider.setRange(-63, 63, 1);
    penv2LevelSlider.addListener(this);

    addAndMakeVisible(penv3TimeSlider);
    penv3TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv3TimeSlider.setRange(0, 127, 1);
    penv3TimeSlider.addListener(this);
    addAndMakeVisible(penv3TimeLabel);
    penv3TimeLabel.setText("3", juce::dontSendNotification);
    penv3TimeLabel.attachToComponent(&penv3TimeSlider, true);
    addAndMakeVisible(penv3LevelSlider);
    penv3LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv3LevelSlider.setRange(-63, 63, 1);
    penv3LevelSlider.addListener(this);

    addAndMakeVisible(penv4TimeSlider);
    penv4TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv4TimeSlider.setRange(0, 127, 1);
    penv4TimeSlider.addListener(this);
    addAndMakeVisible(penv4TimeLabel);
    penv4TimeLabel.setText("4", juce::dontSendNotification);
    penv4TimeLabel.attachToComponent(&penv4TimeSlider, true);
    addAndMakeVisible(penv4LevelSlider);
    penv4LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv4LevelSlider.setRange(-63, 63, 1);
    penv4LevelSlider.addListener(this);

    addAndMakeVisible(filterModeComboBox);
    filterModeComboBox.addListener(this);
    filterModeComboBox.setScrollWheelEnabled(true);
    filterModeComboBox.addItem("Off", 1);
    filterModeComboBox.addItem("Lowpass", 2);
    filterModeComboBox.addItem("Highpass", 3);
    addAndMakeVisible(filterModeLabel);
    filterModeLabel.setText("Filter Mode", juce::dontSendNotification);
    filterModeLabel.attachToComponent(&filterModeComboBox, true);

    addAndMakeVisible(filterCutoffSlider);
    filterCutoffSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    filterCutoffSlider.setRange(0, 127, 1);
    filterCutoffSlider.addListener(this);
    addAndMakeVisible(filterCutoffLabel);
    filterCutoffLabel.setText("Cutoff", juce::dontSendNotification);
    filterCutoffLabel.attachToComponent(&filterCutoffSlider, true);

    addAndMakeVisible(filterResoSlider);
    filterResoSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    filterResoSlider.setRange(0, 127, 1);
    filterResoSlider.addListener(this);
    addAndMakeVisible(filterResoLabel);
    filterResoLabel.setText("Reso | Mode", juce::dontSendNotification);
    filterResoLabel.attachToComponent(&filterResoSlider, true);

    addAndMakeVisible(filterResoModeComboBox);
    filterResoModeComboBox.addListener(this);
    filterResoModeComboBox.setScrollWheelEnabled(true);
    filterResoModeComboBox.addItem("Soft", 1);
    filterResoModeComboBox.addItem("Hard", 2);

    addAndMakeVisible(filterKFComboBox);
    filterKFComboBox.addListener(this);
    filterKFComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(filterKFComboBox, keyFollows);
    addAndMakeVisible(filterKFLabel);
    filterKFLabel.setText("KF | Vel Curve", juce::dontSendNotification);
    filterKFLabel.attachToComponent(&filterKFComboBox, true);

    std::vector<std::string> velCurves{ "1", "2", "3", "4", "5", "6", "7" };

    addAndMakeVisible(fenvVelCurveComboBox);
    fenvVelCurveComboBox.addListener(this);
    fenvVelCurveComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(fenvVelCurveComboBox, velCurves);

    addAndMakeVisible(fenvLevSensSlider);
    fenvLevSensSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenvLevSensSlider.setRange(-63, 63, 1);
    fenvLevSensSlider.addListener(this);
    addAndMakeVisible(fenvLevSensLabel);
    fenvLevSensLabel.setText("TVF Sens", juce::dontSendNotification);
    fenvLevSensLabel.attachToComponent(&fenvLevSensSlider, true);

    addAndMakeVisible(fenvTime1SensComboBox);
    fenvTime1SensComboBox.addListener(this);
    fenvTime1SensComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(fenvTime1SensComboBox, np100);
    addAndMakeVisible(fenvTime1SensLabel);
    fenvTime1SensLabel.setText("Time Sens", juce::dontSendNotification);
    fenvTime1SensLabel.attachToComponent(&fenvTime1SensComboBox, true);

    addAndMakeVisible(fenvTime4SensComboBox);
    fenvTime4SensComboBox.addListener(this);
    fenvTime4SensComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(fenvTime4SensComboBox, np100);

    addAndMakeVisible(fenvTimeKFSensComboBox);
    fenvTimeKFSensComboBox.addListener(this);
    fenvTimeKFSensComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(fenvTimeKFSensComboBox, np100);
    addAndMakeVisible(fenvTimeKFSensLabel);
    fenvTimeKFSensLabel.setText("Time KF", juce::dontSendNotification);
    fenvTimeKFSensLabel.attachToComponent(&fenvTimeKFSensComboBox, true);

    addAndMakeVisible(fenvDepthSlider);
    fenvDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenvDepthSlider.setRange(-63, 63, 1);
    fenvDepthSlider.addListener(this);
    addAndMakeVisible(fenvDepthLabel);
    fenvDepthLabel.setText("TVF Depth", juce::dontSendNotification);
    fenvDepthLabel.attachToComponent(&fenvDepthSlider, true);

    addAndMakeVisible(fenv1TimeSlider);
    fenv1TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv1TimeSlider.setRange(0, 127, 1);
    fenv1TimeSlider.addListener(this);
    addAndMakeVisible(fenv1TimeLabel);
    fenv1TimeLabel.setText("Time | Level 1", juce::dontSendNotification);
    fenv1TimeLabel.attachToComponent(&fenv1TimeSlider, true);
    addAndMakeVisible(fenv1LevelSlider);
    fenv1LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv1LevelSlider.setRange(0, 127, 1);
    fenv1LevelSlider.addListener(this);

    addAndMakeVisible(fenv2TimeSlider);
    fenv2TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv2TimeSlider.setRange(0, 127, 1);
    fenv2TimeSlider.addListener(this);
    addAndMakeVisible(fenv2TimeLabel);
    fenv2TimeLabel.setText("2", juce::dontSendNotification);
    fenv2TimeLabel.attachToComponent(&fenv2TimeSlider, true);
    addAndMakeVisible(fenv2LevelSlider);
    fenv2LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv2LevelSlider.setRange(0, 127, 1);
    fenv2LevelSlider.addListener(this);

    addAndMakeVisible(fenv3TimeSlider);
    fenv3TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv3TimeSlider.setRange(0, 127, 1);
    fenv3TimeSlider.addListener(this);
    addAndMakeVisible(fenv3TimeLabel);
    fenv3TimeLabel.setText("3", juce::dontSendNotification);
    fenv3TimeLabel.attachToComponent(&fenv3TimeSlider, true);
    addAndMakeVisible(fenv3LevelSlider);
    fenv3LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv3LevelSlider.setRange(0, 127, 1);
    fenv3LevelSlider.addListener(this);

    addAndMakeVisible(fenv4TimeSlider);
    fenv4TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv4TimeSlider.setRange(0, 127, 1);
    fenv4TimeSlider.addListener(this);
    addAndMakeVisible(fenv4TimeLabel);
    fenv4TimeLabel.setText("4", juce::dontSendNotification);
    fenv4TimeLabel.attachToComponent(&fenv4TimeSlider, true);
    addAndMakeVisible(fenv4LevelSlider);
    fenv4LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv4LevelSlider.setRange(0, 127, 1);
    fenv4LevelSlider.addListener(this);

    addAndMakeVisible(levelSlider);
    levelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    levelSlider.setRange(0, 127, 1);
    levelSlider.addListener(this);
    addAndMakeVisible(levelLabel);
    levelLabel.setText("Level", juce::dontSendNotification);
    levelLabel.attachToComponent(&levelSlider, true);

    addAndMakeVisible(levelKFComboBox);
    levelKFComboBox.addListener(this);
    levelKFComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(levelKFComboBox, np100);
    addAndMakeVisible(levelKFLabel);
    levelKFLabel.setText("Level/Pan KF", juce::dontSendNotification);
    levelKFLabel.attachToComponent(&levelKFComboBox, true);

    addAndMakeVisible(panSlider);
    panSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    panSlider.setRange(-64, 64, 1);
    panSlider.addListener(this);
    addAndMakeVisible(panLabel);
    panLabel.setText("Pan", juce::dontSendNotification);
    panLabel.attachToComponent(&panSlider, true);

    addAndMakeVisible(panKFComboBox);
    panKFComboBox.addListener(this);
    panKFComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(panKFComboBox, np100);

    addAndMakeVisible(toneDelayComboBox);
    toneDelayComboBox.addListener(this);
    toneDelayComboBox.setScrollWheelEnabled(true);
    toneDelayComboBox.addItem("Normal", 1);
    toneDelayComboBox.addItem("Hold", 2);
    toneDelayComboBox.addItem("Playmate", 3);
    addAndMakeVisible(toneDelayLabel);
    toneDelayLabel.setText("Delay Mode", juce::dontSendNotification);
    toneDelayLabel.attachToComponent(&toneDelayComboBox, true);

    addAndMakeVisible(toneDelayTimeSlider);
    toneDelayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    toneDelayTimeSlider.setRange(-64, 64, 1);
    toneDelayTimeSlider.addListener(this);
    addAndMakeVisible(toneDelayTimeLabel);
    toneDelayTimeLabel.setText("Delay Time", juce::dontSendNotification);
    toneDelayTimeLabel.attachToComponent(&toneDelayTimeSlider, true);

    addAndMakeVisible(aenvVelCurveComboBox);
    aenvVelCurveComboBox.addListener(this);
    aenvVelCurveComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(aenvVelCurveComboBox, velCurves);

    addAndMakeVisible(aenvVelCurveLabel);
    aenvVelCurveLabel.setText("Vel Curve", juce::dontSendNotification);
    aenvVelCurveLabel.attachToComponent(&aenvVelCurveComboBox, true);

    addAndMakeVisible(aenvLevSensSlider);
    aenvLevSensSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenvLevSensSlider.setRange(-63, 63, 1);
    aenvLevSensSlider.addListener(this);
    addAndMakeVisible(aenvLevSensLabel);
    aenvLevSensLabel.setText("TVF Sens", juce::dontSendNotification);
    aenvLevSensLabel.attachToComponent(&aenvLevSensSlider, true);

    addAndMakeVisible(aenvTime1SensComboBox);
    aenvTime1SensComboBox.addListener(this);
    aenvTime1SensComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(aenvTime1SensComboBox, np100);
    addAndMakeVisible(aenvTime1SensLabel);
    aenvTime1SensLabel.setText("Time Sens", juce::dontSendNotification);
    aenvTime1SensLabel.attachToComponent(&aenvTime1SensComboBox, true);

    addAndMakeVisible(aenvTime4SensComboBox);
    aenvTime4SensComboBox.addListener(this);
    aenvTime4SensComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(aenvTime4SensComboBox, np100);

    addAndMakeVisible(aenvTimeKFSensComboBox);
    aenvTimeKFSensComboBox.addListener(this);
    aenvTimeKFSensComboBox.setScrollWheelEnabled(true);
    addMenuEntriesFromArray(aenvTimeKFSensComboBox, np100);
    addAndMakeVisible(aenvTimeKFSensLabel);
    aenvTimeKFSensLabel.setText("Time KF", juce::dontSendNotification);
    aenvTimeKFSensLabel.attachToComponent(&aenvTimeKFSensComboBox, true);

    addAndMakeVisible(aenv1TimeSlider);
    aenv1TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv1TimeSlider.setRange(0, 127, 1);
    aenv1TimeSlider.addListener(this);
    addAndMakeVisible(aenv1TimeLabel);
    aenv1TimeLabel.setText("Time | Level 1", juce::dontSendNotification);
    aenv1TimeLabel.attachToComponent(&aenv1TimeSlider, true);
    addAndMakeVisible(aenv1LevelSlider);
    aenv1LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv1LevelSlider.setRange(0, 127, 1);
    aenv1LevelSlider.addListener(this);

    addAndMakeVisible(aenv2TimeSlider);
    aenv2TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv2TimeSlider.setRange(0, 127, 1);
    aenv2TimeSlider.addListener(this);
    addAndMakeVisible(aenv2TimeLabel);
    aenv2TimeLabel.setText("2", juce::dontSendNotification);
    aenv2TimeLabel.attachToComponent(&aenv2TimeSlider, true);
    addAndMakeVisible(aenv2LevelSlider);
    aenv2LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv2LevelSlider.setRange(0, 127, 1);
    aenv2LevelSlider.addListener(this);

    addAndMakeVisible(aenv3TimeSlider);
    aenv3TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv3TimeSlider.setRange(0, 127, 1);
    aenv3TimeSlider.addListener(this);
    addAndMakeVisible(aenv3TimeLabel);
    aenv3TimeLabel.setText("3", juce::dontSendNotification);
    aenv3TimeLabel.attachToComponent(&aenv3TimeSlider, true);
    addAndMakeVisible(aenv3LevelSlider);
    aenv3LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv3LevelSlider.setRange(0, 127, 1);
    aenv3LevelSlider.addListener(this);

    addAndMakeVisible(aenv4TimeSlider);
    aenv4TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv4TimeSlider.setRange(0, 127, 1);
    aenv4TimeSlider.addListener(this);
    addAndMakeVisible(aenv4TimeLabel);
    aenv4TimeLabel.setText("4", juce::dontSendNotification);
    aenv4TimeLabel.attachToComponent(&aenv4TimeSlider, true);

    addAndMakeVisible(drySlider);
    drySlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    drySlider.setRange(0, 127, 1);
    drySlider.addListener(this);
    addAndMakeVisible(dryLabel);
    dryLabel.setText("Dry Send", juce::dontSendNotification);
    dryLabel.attachToComponent(&drySlider, true);

    addAndMakeVisible(reverbSlider);
    reverbSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    reverbSlider.setRange(0, 127, 1);
    reverbSlider.addListener(this);
    addAndMakeVisible(reverbLabel);
    reverbLabel.setText("Reverb", juce::dontSendNotification);
    reverbLabel.attachToComponent(&reverbSlider, true);

    addAndMakeVisible(chorusSlider);
    chorusSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    chorusSlider.setRange(0, 127, 1);
    chorusSlider.addListener(this);
    addAndMakeVisible(chorusLabel);
    chorusLabel.setText("Chorus", juce::dontSendNotification);
    chorusLabel.attachToComponent(&chorusSlider, true);

    addAndMakeVisible(outputComboBox);
    outputComboBox.addListener(this);
    outputComboBox.setScrollWheelEnabled(true);
    outputComboBox.addItem("Main", 1);
    outputComboBox.addItem("Sub", 2);
    addAndMakeVisible(outputLabel);
    outputLabel.setText("Output", juce::dontSendNotification);
    outputLabel.attachToComponent(&outputComboBox, true);

}

EditToneTab::~EditToneTab()
{
}

void EditToneTab::addMenuEntriesFromArray(juce::ComboBox &m, const std::vector<std::string> &array)
{
    uint32_t idx = 1;

    for (auto e : array)
    {
        m.addItem(e, idx);
        idx++;
    }
}

void EditToneTab::updateValues()
{
    Patch* patch = (Patch*)audioProcessor.status.patch;
    Tone tone = patch->tones[toneCount];
    waveGroupComboBox.setSelectedItemIndex((tone.flags & 0x3) + 0, juce::dontSendNotification);
    waveformSlider.setValue((tone.waveNumber & 0xff) + 1, juce::dontSendNotification);
    toneSwitchToggle.setToggleState(((tone.flags >> 7) & 0x01) ? 1 : 0, juce::dontSendNotification);
    FXMSwitchToggle.setToggleState(((tone.fxmConfig >> 7) & 0x01) ? 1 : 0, juce::dontSendNotification);
    FXMDepthSlider.setValue(((tone.fxmConfig) & 0x0f) + 1, juce::dontSendNotification);
    velRangeLowSlider.setValue(((tone.velocityRangeLow) & 0x7f) + 0, juce::dontSendNotification);
    velRangeHighSlider.setValue(((tone.velocityRangeUp) & 0x7f) + 0, juce::dontSendNotification);

    volumeSwitchToggle.setToggleState(((tone.tvaEnvTime1 >> 7) & 0x01) ? 1 : 0, juce::dontSendNotification);
    holdSwitchToggle.setToggleState(((tone.tvaEnvLevel1 >> 7) & 0x01) ? 1 : 0, juce::dontSendNotification);

    modDestAComboBox.setSelectedItemIndex((tone.matrixModDestAB & 0xf) + 0, juce::dontSendNotification);
    modDestBComboBox.setSelectedItemIndex(((tone.matrixModDestAB & 0xf0) >> 4) + 0, juce::dontSendNotification);
    modDestCComboBox.setSelectedItemIndex((tone.matrixModDestCB & 0xf) + 0, juce::dontSendNotification);
    modDestDComboBox.setSelectedItemIndex(((tone.matrixModDestCB & 0xf0) >> 4) + 0, juce::dontSendNotification);
    modSensASlider.setValue(int8_t((tone.matrixModSensA)), juce::dontSendNotification);
    modSensBSlider.setValue(int8_t((tone.matrixModSensB)), juce::dontSendNotification);
    modSensCSlider.setValue(int8_t((tone.matrixModSensC)), juce::dontSendNotification);
    modSensDSlider.setValue(int8_t((tone.matrixModSensD)), juce::dontSendNotification);
    aftDestAComboBox.setSelectedItemIndex((tone.matrixAftDestAB & 0xf) + 0, juce::dontSendNotification);
    aftDestBComboBox.setSelectedItemIndex(((tone.matrixAftDestAB & 0xf0) >> 4) + 0, juce::dontSendNotification);
    aftDestCComboBox.setSelectedItemIndex((tone.matrixAftDestCD & 0xf) + 0, juce::dontSendNotification);
    aftDestDComboBox.setSelectedItemIndex(((tone.matrixAftDestCD & 0xf0) >> 4) + 0, juce::dontSendNotification);
    aftSensASlider.setValue(int8_t((tone.matrixAftSensA)), juce::dontSendNotification);
    aftSensBSlider.setValue(int8_t((tone.matrixAftSensB)), juce::dontSendNotification);
    aftSensCSlider.setValue(int8_t((tone.matrixAftSensC)), juce::dontSendNotification);
    aftSensDSlider.setValue(int8_t((tone.matrixAftSensD)), juce::dontSendNotification);
    expDestAComboBox.setSelectedItemIndex((tone.matrixExpDestAB & 0xf) + 0, juce::dontSendNotification);
    expDestBComboBox.setSelectedItemIndex(((tone.matrixExpDestAB & 0xf0) >> 4) + 0, juce::dontSendNotification);
    expDestCComboBox.setSelectedItemIndex((tone.matrixExpDestCD & 0xf) + 0, juce::dontSendNotification);
    expDestDComboBox.setSelectedItemIndex(((tone.matrixExpDestCD & 0xf0) >> 4) + 0, juce::dontSendNotification);
    expSensASlider.setValue(int8_t((tone.matrixExpSensA)), juce::dontSendNotification);
    expSensBSlider.setValue(int8_t((tone.matrixExpSensB)), juce::dontSendNotification);
    expSensCSlider.setValue(int8_t((tone.matrixExpSensC)), juce::dontSendNotification);
    expSensDSlider.setValue(int8_t((tone.matrixExpSensD)), juce::dontSendNotification);

    lfo1FormComboBox.setSelectedItemIndex((tone.lfo1Flags & 0x7) + 0, juce::dontSendNotification);
    lfo1OffsetComboBox.setSelectedItemIndex((tone.lfo1Flags & 0x38) >> 3, juce::dontSendNotification);
    lfo1SyncToggle.setToggleState(((tone.lfo1Flags & 0x40) >> 6) ? 1 : 0, juce::dontSendNotification);
    lfo1FadeToggle.setToggleState(((tone.lfo1Flags & 0x80) >> 7) ? 1 : 0, juce::dontSendNotification);
    lfo1RateSlider.setValue(((tone.lfo1Rate)), juce::dontSendNotification);
    lfo1DelaySlider.setValue(((tone.lfo1Delay)), juce::dontSendNotification);
    lfo1FadeTimeSlider.setValue(((tone.lfo1Fade)), juce::dontSendNotification);
    lfo1PitchDepthSlider.setValue(int8_t((tone.lfo1PitchDepth)), juce::dontSendNotification);
    lfo1TVFDepthSlider.setValue(int8_t((tone.lfo1TvfDepth)), juce::dontSendNotification);
    lfo1TVADepthSlider.setValue(int8_t((tone.lfo1TvaDepth)), juce::dontSendNotification);

    lfo2FormComboBox.setSelectedItemIndex((tone.lfo2Flags & 0x7) + 0, juce::dontSendNotification);
    lfo2OffsetComboBox.setSelectedItemIndex((tone.lfo2Flags & 0x38) >> 3, juce::dontSendNotification);
    lfo2SyncToggle.setToggleState(((tone.lfo2Flags & 0x40) >> 6) ? 1 : 0, juce::dontSendNotification);
    lfo2FadeToggle.setToggleState(((tone.lfo2Flags & 0x80) >> 7) ? 1 : 0, juce::dontSendNotification);
    lfo2RateSlider.setValue(((tone.lfo2Rate)), juce::dontSendNotification);
    lfo2DelaySlider.setValue(((tone.lfo2Delay)), juce::dontSendNotification);
    lfo2FadeTimeSlider.setValue(((tone.lfo2Fade)), juce::dontSendNotification);
    lfo2PitchDepthSlider.setValue(int8_t((tone.lfo2PitchDepth)), juce::dontSendNotification);
    lfo2TVFDepthSlider.setValue(int8_t((tone.lfo2TvfDepth)), juce::dontSendNotification);
    lfo2TVADepthSlider.setValue(int8_t((tone.lfo2TvaDepth)), juce::dontSendNotification);

    pitchCoarseSlider.setValue(int8_t((tone.pitchCoarse)), juce::dontSendNotification);
    pitchFineSlider.setValue(int8_t((tone.pitchFine)), juce::dontSendNotification);
    pitchRandomComboBox.setSelectedItemIndex((tone.tvaPanningKFRandomPitch & 0xf), juce::dontSendNotification);
    pitchKFComboBox.setSelectedItemIndex((tone.tvpTimeKFKeyfollow & 0xf), juce::dontSendNotification);
    penvLevSensSlider.setValue(int8_t((tone.tvpVelocity)), juce::dontSendNotification);
    penvTime1SensComboBox.setSelectedItemIndex((tone.tvpT1T4Velocity & 0xf), juce::dontSendNotification);
    penvTime4SensComboBox.setSelectedItemIndex((tone.tvpT1T4Velocity & 0xf0) >> 4, juce::dontSendNotification);
    penvTimeKFSensComboBox.setSelectedItemIndex((tone.tvpTimeKFKeyfollow & 0xf0) >> 4, juce::dontSendNotification);
    penvDepthSlider.setValue(int8_t((tone.tvpEnvDepth)), juce::dontSendNotification);
    penv1TimeSlider.setValue(int8_t((tone.tvpEnvTime1)), juce::dontSendNotification);
    penv1LevelSlider.setValue(int8_t((tone.tvpEnvLevel1)), juce::dontSendNotification);
    penv2TimeSlider.setValue(int8_t((tone.tvpEnvTime2)), juce::dontSendNotification);
    penv2LevelSlider.setValue(int8_t((tone.tvpEnvLevel2)), juce::dontSendNotification);
    penv3TimeSlider.setValue(int8_t((tone.tvpEnvTime3)), juce::dontSendNotification);
    penv3LevelSlider.setValue(int8_t((tone.tvpEnvLevel3)), juce::dontSendNotification);
    penv4TimeSlider.setValue(int8_t((tone.tvpEnvTime4)), juce::dontSendNotification);
    penv4LevelSlider.setValue(int8_t((tone.tvpEnvLevel4)), juce::dontSendNotification);

    filterModeComboBox.setSelectedItemIndex((tone.tvfVeloCurveLpfHpf & 0x18) >> 3, juce::dontSendNotification);
    filterCutoffSlider.setValue(int8_t((tone.tvfCutoff)), juce::dontSendNotification);
    filterResoSlider.setValue(int8_t((tone.tvfResonance)), juce::dontSendNotification);
    filterResoModeComboBox.setSelectedItemIndex((tone.tvfResonance & 0x80) >> 7, juce::dontSendNotification);
    filterKFComboBox.setSelectedItemIndex((tone.tvfTimeKFKeyfollow & 0xf), juce::dontSendNotification);
    fenvVelCurveComboBox.setSelectedItemIndex((tone.tvfVeloCurveLpfHpf & 0x7), juce::dontSendNotification);
    fenvLevSensSlider.setValue(int8_t((tone.tvfVelocity)), juce::dontSendNotification);
    fenvTime1SensComboBox.setSelectedItemIndex((tone.tvfT1T4Velocity & 0xf), juce::dontSendNotification);
    fenvTime4SensComboBox.setSelectedItemIndex((tone.tvfT1T4Velocity & 0xf0) >> 4, juce::dontSendNotification);
    fenvTimeKFSensComboBox.setSelectedItemIndex((tone.tvfTimeKFKeyfollow & 0xf0) >> 4, juce::dontSendNotification);
    fenvDepthSlider.setValue(int8_t((tone.tvfEnvDepth)), juce::dontSendNotification);
    fenv1TimeSlider.setValue(int8_t((tone.tvfEnvTime1)), juce::dontSendNotification);
    fenv1LevelSlider.setValue(int8_t((tone.tvfEnvLevel1)), juce::dontSendNotification);
    fenv2TimeSlider.setValue(int8_t((tone.tvfEnvTime2)), juce::dontSendNotification);
    fenv2LevelSlider.setValue(int8_t((tone.tvfEnvLevel2)), juce::dontSendNotification);
    fenv3TimeSlider.setValue(int8_t((tone.tvfEnvTime3)), juce::dontSendNotification);
    fenv3LevelSlider.setValue(int8_t((tone.tvfEnvLevel3)), juce::dontSendNotification);
    fenv4TimeSlider.setValue(int8_t((tone.tvfEnvTime4)), juce::dontSendNotification);
    fenv4LevelSlider.setValue(int8_t((tone.tvfEnvLevel4)), juce::dontSendNotification);

    levelSlider.setValue(int8_t((tone.tvaLevel)), juce::dontSendNotification);
    levelKFComboBox.setSelectedItemIndex((tone.tvaTimeKFDelayTimeKeyfollow & 0xf), juce::dontSendNotification);
    panSlider.setValue(int8_t(tone.tvaPan - 64), juce::dontSendNotification);
    panKFComboBox.setSelectedItemIndex((tone.tvaPanningKFRandomPitch & 0xf0) >> 4, juce::dontSendNotification);
    toneDelayComboBox.setSelectedItemIndex((tone.tvaDelayModeVeloCurve & 0x18) >> 3, juce::dontSendNotification);
    toneDelayTimeSlider.setValue(int8_t((tone.tvaDelayTime)), juce::dontSendNotification);

    aenvVelCurveComboBox.setSelectedItemIndex((tone.tvaDelayModeVeloCurve & 0x7), juce::dontSendNotification);
    aenvLevSensSlider.setValue(int8_t((tone.tvaVelocity)), juce::dontSendNotification);
    aenvTime1SensComboBox.setSelectedItemIndex((tone.tvaT1T4Velocity & 0x0f), juce::dontSendNotification);
    aenvTime4SensComboBox.setSelectedItemIndex((tone.tvaT1T4Velocity & 0xf0) >> 4, juce::dontSendNotification);
    aenvTimeKFSensComboBox.setSelectedItemIndex((tone.tvaTimeKFDelayTimeKeyfollow & 0xf0) >> 4, juce::dontSendNotification);
    aenv1TimeSlider.setValue(int8_t((tone.tvaEnvTime1 & 0x7f)), juce::dontSendNotification);
    aenv1LevelSlider.setValue(int8_t((tone.tvaEnvLevel1 & 0x7f)), juce::dontSendNotification);
    aenv2TimeSlider.setValue(int8_t((tone.tvaEnvTime2)), juce::dontSendNotification);
    aenv2LevelSlider.setValue(int8_t((tone.tvaEnvLevel2)), juce::dontSendNotification);
    aenv3TimeSlider.setValue(int8_t((tone.tvaEnvTime3)), juce::dontSendNotification);
    aenv3LevelSlider.setValue(int8_t((tone.tvaEnvLevel3)), juce::dontSendNotification);
    aenv4TimeSlider.setValue(int8_t((tone.tvaEnvTime4)), juce::dontSendNotification);

    drySlider.setValue(int8_t((tone.drySend)), juce::dontSendNotification);
    reverbSlider.setValue(int8_t((tone.reverbSend)), juce::dontSendNotification);
    chorusSlider.setValue(int8_t((tone.chorusSend)), juce::dontSendNotification);

}

void EditToneTab::visibilityChanged()
{
    updateValues();
}

void EditToneTab::resized()
{
    const auto top = 10;
    const auto sliderLeft1 = 100;
    const auto width = getWidth() / 3 - sliderLeft1 - 10;
    const auto halfWidth = width / 2;
    const auto sliderLeft2 = sliderLeft1 + getWidth() / 3 + 10;
    const auto sliderLeft3 = sliderLeft2 + getWidth() / 3 - 10;
    const auto height = 24;
    const auto vMargin = 24;

    toneSwitchToggle      .setBounds(sliderLeft1 - 90, top + height * 0 + vMargin * 0, width, height);

    waveGroupComboBox     .setBounds(sliderLeft1, top + height * 1 + vMargin * 1, width, height);
    waveformSlider        .setBounds(sliderLeft1, top + height * 2 + vMargin * 1, width, height);

    velRangeLowSlider     .setBounds(sliderLeft1, top + height * 3 + vMargin * 2, halfWidth, height);
    velRangeHighSlider    .setBounds(sliderLeft1 + halfWidth, top + height * 3 + vMargin * 2, halfWidth, height);

    volumeSwitchToggle    .setBounds(sliderLeft1 - 90, top + height * 4 + vMargin * 3, width * 0.75f, height);
    holdSwitchToggle      .setBounds(sliderLeft1 + 30, top + height * 4 + vMargin * 3, width * 0.75f, height);

    lfo1FormComboBox      .setBounds(sliderLeft1, top + height * 5 + vMargin * 4, width, height);
    lfo1OffsetComboBox    .setBounds(sliderLeft1, top + height * 6 + vMargin * 4, width, height);
    lfo1RateSlider        .setBounds(sliderLeft1, top + height * 7 + vMargin * 4, width, height);
    lfo1DelaySlider       .setBounds(sliderLeft1, top + height * 8 + vMargin * 4, halfWidth, height);
    lfo1SyncToggle        .setBounds(sliderLeft1 + halfWidth, top + height * 8 + vMargin * 4, halfWidth, height);
    lfo1FadeTimeSlider    .setBounds(sliderLeft1, top + height * 9 + vMargin * 4, halfWidth, height);
    lfo1FadeToggle        .setBounds(sliderLeft1 + halfWidth, top + height * 9 + vMargin * 4, halfWidth, height);
    lfo1PitchDepthSlider  .setBounds(sliderLeft1, top + height * 10 + vMargin * 4, width, height);
    lfo1TVFDepthSlider    .setBounds(sliderLeft1, top + height * 11 + vMargin * 4, width, height);
    lfo1TVADepthSlider    .setBounds(sliderLeft1, top + height * 12 + vMargin * 4, width, height);

    lfo2FormComboBox      .setBounds(sliderLeft1, top + height * 13 + vMargin * 5, width, height);
    lfo2OffsetComboBox    .setBounds(sliderLeft1, top + height * 14 + vMargin * 5, width, height);
    lfo2RateSlider        .setBounds(sliderLeft1, top + height * 15 + vMargin * 5, width, height);
    lfo2DelaySlider       .setBounds(sliderLeft1, top + height * 16 + vMargin * 5, halfWidth, height);
    lfo2SyncToggle        .setBounds(sliderLeft1 + halfWidth, top + height * 16 + vMargin * 5, halfWidth, height);
    lfo2FadeTimeSlider    .setBounds(sliderLeft1, top + height * 17 + vMargin * 5, halfWidth, height);
    lfo2FadeToggle        .setBounds(sliderLeft1 + halfWidth, top + height * 17 + vMargin * 5, halfWidth, height);
    lfo2PitchDepthSlider  .setBounds(sliderLeft1, top + height * 18 + vMargin * 5, width, height);
    lfo2TVFDepthSlider    .setBounds(sliderLeft1, top + height * 19 + vMargin * 5, width, height);
    lfo2TVADepthSlider    .setBounds(sliderLeft1, top + height * 20 + vMargin * 5, width, height);

    modDestAComboBox      .setBounds(sliderLeft1 - 50, top + height * 21 + vMargin * 6, halfWidth + 25, height);
    modSensASlider        .setBounds(sliderLeft1 + halfWidth - 25, top + height * 21 + vMargin * 6, halfWidth + 25, height);
    modDestBComboBox      .setBounds(sliderLeft1 - 50, top + height * 22 + vMargin * 6, halfWidth + 25, height);
    modSensBSlider        .setBounds(sliderLeft1 + halfWidth - 25, top + height * 22 + vMargin * 6, halfWidth + 25, height);
    modDestCComboBox      .setBounds(sliderLeft1 - 50, top + height * 23 + vMargin * 6, halfWidth + 25, height);
    modSensCSlider        .setBounds(sliderLeft1 + halfWidth - 25, top + height * 23 + vMargin * 6, halfWidth + 25, height);
    modDestDComboBox      .setBounds(sliderLeft1 - 50, top + height * 24 + vMargin * 6, halfWidth + 25, height);
    modSensDSlider        .setBounds(sliderLeft1 + halfWidth - 25, top + height * 24 + vMargin * 6, halfWidth + 25, height);

    aftDestAComboBox      .setBounds(sliderLeft2 - 50, top + height * 21 + vMargin * 6, halfWidth + 25, height);
    aftSensASlider        .setBounds(sliderLeft2 + halfWidth - 25, top + height * 21 + vMargin * 6, halfWidth + 25, height);
    aftDestBComboBox      .setBounds(sliderLeft2 - 50, top + height * 22 + vMargin * 6, halfWidth + 25, height);
    aftSensBSlider        .setBounds(sliderLeft2 + halfWidth - 25, top + height * 22 + vMargin * 6, halfWidth + 25, height);
    aftDestCComboBox      .setBounds(sliderLeft2 - 50, top + height * 23 + vMargin * 6, halfWidth + 25, height);
    aftSensCSlider        .setBounds(sliderLeft2 + halfWidth - 25, top + height * 23 + vMargin * 6, halfWidth + 25, height);
    aftDestDComboBox      .setBounds(sliderLeft2 - 50, top + height * 24 + vMargin * 6, halfWidth + 25, height);
    aftSensDSlider        .setBounds(sliderLeft2 + halfWidth - 25, top + height * 24 + vMargin * 6, halfWidth + 25, height);

    expDestAComboBox      .setBounds(sliderLeft3 - 50, top + height * 21 + vMargin * 6, halfWidth + 25, height);
    expSensASlider        .setBounds(sliderLeft3 + halfWidth - 25, top + height * 21 + vMargin * 6, halfWidth + 25, height);
    expDestBComboBox      .setBounds(sliderLeft3 - 50, top + height * 22 + vMargin * 6, halfWidth + 25, height);
    expSensBSlider        .setBounds(sliderLeft3 + halfWidth - 25, top + height * 22 + vMargin * 6, halfWidth + 25, height);
    expDestCComboBox      .setBounds(sliderLeft3 - 50, top + height * 23 + vMargin * 6, halfWidth + 25, height);
    expSensCSlider        .setBounds(sliderLeft3 + halfWidth - 25, top + height * 23 + vMargin * 6, halfWidth + 25, height);
    expDestDComboBox      .setBounds(sliderLeft3 - 50, top + height * 24 + vMargin * 6, halfWidth + 25, height);
    expSensDSlider        .setBounds(sliderLeft3 + halfWidth - 25, top + height * 24 + vMargin * 6, halfWidth + 25, height);

    FXMSwitchToggle       .setBounds(sliderLeft2 - 90, top + height * 0 + vMargin * 0, halfWidth, height);
    FXMDepthSlider        .setBounds(sliderLeft2 + halfWidth, top + height * 0 + vMargin * 0, halfWidth, height);
    pitchCoarseSlider     .setBounds(sliderLeft2, top + height * 1 + vMargin * 0, width, height);
    pitchFineSlider       .setBounds(sliderLeft2, top + height * 2 + vMargin * 0, width, height);
    pitchRandomComboBox   .setBounds(sliderLeft2, top + height * 3 + vMargin * 0, halfWidth, height);
    pitchKFComboBox       .setBounds(sliderLeft2 + halfWidth, top + height * 3 + vMargin * 0, halfWidth, height);
    penvLevSensSlider     .setBounds(sliderLeft2, top + height * 4 + vMargin * 0, width, height);
    penvTime1SensComboBox .setBounds(sliderLeft2, top + height * 5 + vMargin * 0, halfWidth, height);
    penvTime4SensComboBox .setBounds(sliderLeft2 + halfWidth, top + height * 5 + vMargin * 0, halfWidth, height);
    penvTimeKFSensComboBox.setBounds(sliderLeft2, top + height * 6 + vMargin * 0, width, height);
    penvDepthSlider       .setBounds(sliderLeft2, top + height * 7 + vMargin * 0, width, height);
    penv1TimeSlider       .setBounds(sliderLeft2, top + height * 8 + vMargin * 0, halfWidth, height);
    penv1LevelSlider      .setBounds(sliderLeft2 + halfWidth, top + height * 8 + vMargin * 0, halfWidth, height);
    penv2TimeSlider       .setBounds(sliderLeft2, top + height * 9 + vMargin * 0, halfWidth, height);
    penv2LevelSlider      .setBounds(sliderLeft2 + halfWidth, top + height * 9 + vMargin * 0, halfWidth, height);
    penv3TimeSlider       .setBounds(sliderLeft2, top + height * 10 + vMargin * 0, halfWidth, height);
    penv3LevelSlider      .setBounds(sliderLeft2 + halfWidth, top + height * 10 + vMargin * 0, halfWidth, height);
    penv4TimeSlider       .setBounds(sliderLeft2, top + height * 11 + vMargin * 0, halfWidth, height);
    penv4LevelSlider      .setBounds(sliderLeft2 + halfWidth, top + height * 11 + vMargin * 0, halfWidth, height);

    levelSlider           .setBounds(sliderLeft2, top + height * 12 + vMargin * 1, width, height);
    panSlider             .setBounds(sliderLeft2, top + height * 13 + vMargin * 1, width, height);
    levelKFComboBox       .setBounds(sliderLeft2, top + height * 14 + vMargin * 1, halfWidth, height);
    panKFComboBox         .setBounds(sliderLeft2 + halfWidth, top + height * 14 + vMargin * 1, halfWidth, height);
    toneDelayComboBox     .setBounds(sliderLeft2, top + height * 15 + vMargin * 1, width, height);
    toneDelayTimeSlider   .setBounds(sliderLeft2, top + height * 16 + vMargin * 1, width, height);
    aenvVelCurveComboBox  .setBounds(sliderLeft2, top + height * 17 + vMargin * 1, width, height);
    aenvLevSensSlider     .setBounds(sliderLeft2, top + height * 18 + vMargin * 1, width, height);
    aenvTime1SensComboBox .setBounds(sliderLeft2, top + height * 19 + vMargin * 1, halfWidth, height);
    aenvTime4SensComboBox .setBounds(sliderLeft2 + halfWidth, top + height * 19 + vMargin * 1, halfWidth, height);
    aenvTimeKFSensComboBox.setBounds(sliderLeft2, top + height * 20 + vMargin * 1, width, height);
    aenv1TimeSlider       .setBounds(sliderLeft2, top + height * 21 + vMargin * 1, halfWidth, height);
    aenv1LevelSlider      .setBounds(sliderLeft2 + halfWidth, top + height * 21 + vMargin * 1, halfWidth, height);
    aenv2TimeSlider       .setBounds(sliderLeft2, top + height * 22 + vMargin * 1, halfWidth, height);
    aenv2LevelSlider      .setBounds(sliderLeft2 + halfWidth, top + height * 22 + vMargin * 1, halfWidth, height);
    aenv3TimeSlider       .setBounds(sliderLeft2, top + height * 23 + vMargin * 1, halfWidth, height);
    aenv3LevelSlider      .setBounds(sliderLeft2 + halfWidth, top + height * 23 + vMargin * 1, halfWidth, height);
    aenv4TimeSlider       .setBounds(sliderLeft2, top + height * 24 + vMargin * 1, halfWidth, height);

    filterModeComboBox    .setBounds(sliderLeft3, top + height * 0 + vMargin * 0, width, height);
    filterCutoffSlider    .setBounds(sliderLeft3, top + height * 1 + vMargin * 0, width, height);
    filterResoSlider      .setBounds(sliderLeft3, top + height * 2 + vMargin * 0, halfWidth, height);
    filterResoModeComboBox.setBounds(sliderLeft3 + halfWidth, top + height * 2 + vMargin * 0, halfWidth, height);
    filterKFComboBox      .setBounds(sliderLeft3, top + height * 3 + vMargin * 0, halfWidth, height);
    fenvVelCurveComboBox  .setBounds(sliderLeft3 + halfWidth, top + height * 3 + vMargin * 0, halfWidth, height);
    fenvLevSensSlider     .setBounds(sliderLeft3, top + height * 4 + vMargin * 0, width, height);
    fenvTime1SensComboBox .setBounds(sliderLeft3, top + height * 5 + vMargin * 0, halfWidth, height);
    fenvTime4SensComboBox .setBounds(sliderLeft3 + halfWidth, top + height * 5 + vMargin * 0, halfWidth, height);
    fenvTimeKFSensComboBox.setBounds(sliderLeft3, top + height * 6 + vMargin * 0, width, height);
    fenvDepthSlider       .setBounds(sliderLeft3, top + height * 7 + vMargin * 0, width, height);
    fenv1TimeSlider       .setBounds(sliderLeft3, top + height * 8 + vMargin * 0, halfWidth, height);
    fenv1LevelSlider      .setBounds(sliderLeft3 + halfWidth, top + height * 8 + vMargin * 0, halfWidth, height);
    fenv2TimeSlider       .setBounds(sliderLeft3, top + height * 9 + vMargin * 0, halfWidth, height);
    fenv2LevelSlider      .setBounds(sliderLeft3 + halfWidth, top + height * 9 + vMargin * 0, halfWidth, height);
    fenv3TimeSlider       .setBounds(sliderLeft3, top + height * 10 + vMargin * 0, halfWidth, height);
    fenv3LevelSlider      .setBounds(sliderLeft3 + halfWidth, top + height * 10 + vMargin * 0, halfWidth, height);
    fenv4TimeSlider       .setBounds(sliderLeft3, top + height * 11 + vMargin * 0, halfWidth, height);
    fenv4LevelSlider      .setBounds(sliderLeft3 + halfWidth, top + height * 11 + vMargin * 0, halfWidth, height);

    drySlider             .setBounds(sliderLeft3, top + height * 12 + vMargin * 1, width, height);
    reverbSlider          .setBounds(sliderLeft3, top + height * 13 + vMargin * 1, width, height);
    chorusSlider          .setBounds(sliderLeft3, top + height * 14 + vMargin * 1, width, height);
    outputComboBox        .setBounds(sliderLeft3, top + height * 15 + vMargin * 1, width, height);
}

void EditToneTab::sliderValueChanged(juce::Slider* slider)
{
    sendSysexPatchToneChange();
}

void EditToneTab::buttonClicked(juce::Button* button)
{
    sendSysexPatchToneChange();
}

void EditToneTab::buttonStateChanged(juce::Button* button)
{
}

void EditToneTab::comboBoxChanged(juce::ComboBox* button)
{
    sendSysexPatchToneChange();
}

void EditToneTab::sendSysexPatchToneChange1Byte(uint8_t address, uint8_t value)
{
    uint8_t data[5];
    data[0] = 0x00;              // address MSB
    data[1] = 0x08;              // address
    data[2] = 0x28 + toneCount;  // address
    data[3] = address & 127;     // address LSB
    data[4] = value;             // data

    uint32_t checksum = 0;

    for (size_t i = 0; i < 5; i++) {
        checksum += data[i];
        if (checksum >= 128) {
            checksum -= 128;
        }
    }

    uint8_t buf[12];
    buf[0] = 0xf0;
    buf[1] = 0x41;
    buf[2] = 0x10; // unit number
    buf[3] = 0x46;
    buf[4] = 0x12; // command

    checksum = 128 - checksum;

    for (size_t i = 0; i < 5; i++) {
        buf[i + 5] = data[i];
    }

    buf[10] = checksum;
    buf[11] = 0xf7;

    audioProcessor.mcuLock.enter();
    audioProcessor.mcu->postMidiSC55(buf, 12);
    audioProcessor.mcuLock.exit();
}

void EditToneTab::sendSysexPatchToneChange2Byte(uint8_t address, uint8_t value)
{
    uint8_t data[6];
    data[0] = 0x00;                 // address MSB
    data[1] = 0x08;                 // address
    data[2] = 0x28 + toneCount;     // address
    data[3] = address & 127;        // address LSB
    data[4] = (value & 0xf0) >> 4;  // data
    data[5] = value & 0x0f;         // data

    uint32_t checksum = 0;

    for (size_t i = 0; i < 6; i++) {
        checksum += data[i];
        if (checksum >= 128) {
            checksum -= 128;
        }
    }

    uint8_t buf[13];
    buf[0] = 0xf0;
    buf[1] = 0x41;
    buf[2] = 0x10; // unit number
    buf[3] = 0x46;
    buf[4] = 0x12; // command

    checksum = 128 - checksum;

    for (size_t i = 0; i < 6; i++) {
        buf[i + 5] = data[i];
    }

    buf[11] = checksum;
    buf[12] = 0xf7;

    audioProcessor.mcuLock.enter();
    audioProcessor.mcu->postMidiSC55(buf, 13);
    audioProcessor.mcuLock.exit();
}


void EditToneTab::sendSysexPatchToneChange()
{
    sendSysexPatchToneChange1Byte(0x00, (waveGroupComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange2Byte(0x01, (uint8_t(waveformSlider.getValue() - 1)));
    sendSysexPatchToneChange1Byte(0x03, (toneSwitchToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
    sendSysexPatchToneChange1Byte(0x04, (FXMSwitchToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
    sendSysexPatchToneChange1Byte(0x05, (uint8_t(FXMDepthSlider.getValue() - 1)));
    sendSysexPatchToneChange1Byte(0x06, (uint8_t(velRangeLowSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x07, (uint8_t(velRangeHighSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x08, (volumeSwitchToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
    sendSysexPatchToneChange1Byte(0x09, (holdSwitchToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
    sendSysexPatchToneChange1Byte(0x0a, (modDestAComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x0b, (uint8_t(modSensASlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x0c, (modDestBComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x0d, (uint8_t(modSensBSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x0e, (modDestCComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x0f, (uint8_t(modSensCSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x10, (modDestDComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x11, (uint8_t(modSensDSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x12, (aftDestAComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x13, (uint8_t(aftSensASlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x14, (aftDestBComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x15, (uint8_t(aftSensBSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x16, (aftDestCComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x17, (uint8_t(aftSensCSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x18, (aftDestDComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x19, (uint8_t(aftSensDSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x1a, (expDestAComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x1b, (uint8_t(expSensASlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x1c, (expDestBComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x1d, (uint8_t(expSensBSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x1e, (expDestCComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x1f, (uint8_t(expSensCSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x20, (expDestDComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x21, (uint8_t(expSensDSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x22, (lfo1FormComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x23, (lfo1OffsetComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x24, (lfo1SyncToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
    sendSysexPatchToneChange1Byte(0x25, (uint8_t(lfo1RateSlider.getValue())));
    sendSysexPatchToneChange2Byte(0x26, (uint8_t(lfo1DelaySlider.getValue())));
    sendSysexPatchToneChange1Byte(0x28, (lfo1FadeToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
    sendSysexPatchToneChange1Byte(0x29, (uint8_t(lfo1FadeTimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x2a, (uint8_t(lfo1PitchDepthSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x2b, (uint8_t(lfo1TVFDepthSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x2c, (uint8_t(lfo1TVADepthSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x2d, (lfo2FormComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x2e, (lfo2OffsetComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x2f, (lfo2SyncToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
    sendSysexPatchToneChange1Byte(0x30, (uint8_t(lfo2RateSlider.getValue())));
    sendSysexPatchToneChange2Byte(0x31, (uint8_t(lfo2DelaySlider.getValue())));
    sendSysexPatchToneChange1Byte(0x33, (lfo2FadeToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
    sendSysexPatchToneChange1Byte(0x34, (uint8_t(lfo2FadeTimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x35, (uint8_t(lfo2PitchDepthSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x36, (uint8_t(lfo2TVFDepthSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x37, (uint8_t(lfo2TVADepthSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x38, (uint8_t(pitchCoarseSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x39, (uint8_t(pitchFineSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x3a, (pitchRandomComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x3b, (pitchKFComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x3c, (uint8_t(penvLevSensSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x3d, (penvTime1SensComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x3e, (penvTime4SensComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x3f, (penvTimeKFSensComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x40, (uint8_t(penvDepthSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x41, (uint8_t(penv1TimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x42, (uint8_t(penv1LevelSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x43, (uint8_t(penv2TimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x44, (uint8_t(penv2LevelSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x45, (uint8_t(penv3TimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x46, (uint8_t(penv3LevelSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x47, (uint8_t(penv4TimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x48, (uint8_t(penv4LevelSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x49, (filterModeComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x4a, (uint8_t(filterCutoffSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x4b, (uint8_t(filterResoSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x4c, (filterResoModeComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x4d, (filterKFComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x4e, (fenvVelCurveComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x4f, (uint8_t(fenvLevSensSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x50, (fenvTime1SensComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x51, (fenvTime4SensComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x52, (fenvTimeKFSensComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x53, (uint8_t(fenvDepthSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x54, (uint8_t(fenv1TimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x55, (uint8_t(fenv1LevelSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x56, (uint8_t(fenv2TimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x57, (uint8_t(fenv2LevelSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x58, (uint8_t(fenv3TimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x59, (uint8_t(fenv3LevelSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x5a, (uint8_t(fenv4TimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x5b, (uint8_t(fenv4LevelSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x5c, (uint8_t(levelSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x5d, (levelKFComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange2Byte(0x5e, (uint8_t(panSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x60, (panKFComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x61, (toneDelayComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange2Byte(0x62, (uint8_t(toneDelayTimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x64, (aenvVelCurveComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x65, (uint8_t(aenvLevSensSlider.getValue() + 64)));
    sendSysexPatchToneChange1Byte(0x66, (aenvTime1SensComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x67, (aenvTime4SensComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x68, (aenvTimeKFSensComboBox.getSelectedItemIndex()));
    sendSysexPatchToneChange1Byte(0x69, (uint8_t(aenv1TimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x6a, (uint8_t(aenv1LevelSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x6b, (uint8_t(aenv2TimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x6c, (uint8_t(aenv2LevelSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x6d, (uint8_t(aenv3TimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x6e, (uint8_t(aenv3LevelSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x6f, (uint8_t(aenv4TimeSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x70, (uint8_t(drySlider.getValue())));
    sendSysexPatchToneChange1Byte(0x71, (uint8_t(reverbSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x72, (uint8_t(chorusSlider.getValue())));
    sendSysexPatchToneChange1Byte(0x73, (outputComboBox.getSelectedItemIndex()));

    Patch* patch = (Patch*)audioProcessor.status.patch;
    Tone* tone = &patch->tones[toneCount];

    tone->flags = uint8_t(waveGroupComboBox.getSelectedItemIndex() + (toneSwitchToggle.getToggleState() << 7));
    tone->waveNumber = uint8_t(waveformSlider.getValue() - 1);
    tone->fxmConfig = uint8_t(FXMDepthSlider.getValue() + (FXMSwitchToggle.getToggleState() << 7));
    tone->velocityRangeLow = uint8_t(velRangeLowSlider.getValue());
    tone->velocityRangeUp = uint8_t(velRangeHighSlider.getValue());
    tone->matrixModDestAB = uint8_t(modDestAComboBox.getSelectedItemIndex() + (modDestBComboBox.getSelectedItemIndex() << 4));
    tone->matrixModDestCB = uint8_t(modDestCComboBox.getSelectedItemIndex() + (modDestDComboBox.getSelectedItemIndex() << 4));
    tone->matrixModSensA = uint8_t(modSensASlider.getValue());
    tone->matrixModSensB = uint8_t(modSensBSlider.getValue());
    tone->matrixModSensC = uint8_t(modSensCSlider.getValue());
    tone->matrixModSensD = uint8_t(modSensDSlider.getValue());
    tone->matrixAftDestAB = uint8_t(aftDestAComboBox.getSelectedItemIndex() + (aftDestBComboBox.getSelectedItemIndex() << 4));
    tone->matrixAftDestCD = uint8_t(aftDestCComboBox.getSelectedItemIndex() + (aftDestDComboBox.getSelectedItemIndex() << 4));
    tone->matrixAftSensA = uint8_t(aftSensASlider.getValue());
    tone->matrixAftSensB = uint8_t(aftSensBSlider.getValue());
    tone->matrixAftSensC = uint8_t(aftSensCSlider.getValue());
    tone->matrixAftSensD = uint8_t(aftSensDSlider.getValue());
    tone->matrixExpDestAB = uint8_t(expDestAComboBox.getSelectedItemIndex() + (expDestBComboBox.getSelectedItemIndex() << 4));
    tone->matrixExpDestCD = uint8_t(expDestCComboBox.getSelectedItemIndex() + (expDestDComboBox.getSelectedItemIndex() << 4));
    tone->matrixExpSensA = uint8_t(expSensASlider.getValue());
    tone->matrixExpSensB = uint8_t(expSensBSlider.getValue());
    tone->matrixExpSensC = uint8_t(expSensCSlider.getValue());
    tone->matrixExpSensD = uint8_t(expSensDSlider.getValue());
    tone->lfo1Flags = uint8_t(lfo1FormComboBox.getSelectedItemIndex() + (lfo1OffsetComboBox.getSelectedItemIndex() << 3) + (lfo1SyncToggle.getToggleState() << 6) + (lfo1FadeToggle.getToggleState() << 7));
    tone->lfo1Rate = uint8_t(lfo1RateSlider.getValue());
    tone->lfo1Delay = uint8_t(lfo1DelaySlider.getValue());
    tone->lfo1Fade = uint8_t(lfo1FadeTimeSlider.getValue());
    tone->lfo1PitchDepth = uint8_t(lfo1PitchDepthSlider.getValue());
    tone->lfo1TvfDepth = uint8_t(lfo1TVFDepthSlider.getValue());
    tone->lfo1TvaDepth = uint8_t(lfo1TVADepthSlider.getValue());
    tone->lfo2Flags = uint8_t(lfo2FormComboBox.getSelectedItemIndex() + (lfo2OffsetComboBox.getSelectedItemIndex() << 3) + (lfo2SyncToggle.getToggleState() << 6) + (lfo2FadeToggle.getToggleState() << 7));
    tone->lfo2Rate = uint8_t(lfo2RateSlider.getValue());
    tone->lfo2Delay = uint8_t(lfo2DelaySlider.getValue());
    tone->lfo2Fade = uint8_t(lfo2FadeTimeSlider.getValue());
    tone->lfo2PitchDepth = uint8_t(lfo2PitchDepthSlider.getValue());
    tone->lfo2TvfDepth = uint8_t(lfo2TVFDepthSlider.getValue());
    tone->lfo2TvaDepth = uint8_t(lfo2TVADepthSlider.getValue());
    tone->pitchCoarse = uint8_t(pitchCoarseSlider.getValue());
    tone->pitchFine = uint8_t(pitchFineSlider.getValue());
    tone->tvaPanningKFRandomPitch = uint8_t(pitchRandomComboBox.getSelectedItemIndex() + (panKFComboBox.getSelectedItemIndex() << 4));
    tone->tvpTimeKFKeyfollow = uint8_t(pitchKFComboBox.getSelectedItemIndex() + (penvTimeKFSensComboBox.getSelectedItemIndex() << 4));
    tone->tvpT1T4Velocity = uint8_t(penvTime1SensComboBox.getSelectedItemIndex() + (penvTime4SensComboBox.getSelectedItemIndex() << 4));
    tone->tvpEnvDepth = uint8_t(penvDepthSlider.getValue());
    tone->tvpEnvTime1 = uint8_t(penv1TimeSlider.getValue());
    tone->tvpEnvLevel1 = uint8_t(penv1LevelSlider.getValue());
    tone->tvpEnvTime2 = uint8_t(penv2TimeSlider.getValue());
    tone->tvpEnvLevel2 = uint8_t(penv2LevelSlider.getValue());
    tone->tvpEnvTime3 = uint8_t(penv3TimeSlider.getValue());
    tone->tvpEnvLevel3 = uint8_t(penv3LevelSlider.getValue());
    tone->tvpEnvTime4 = uint8_t(penv4TimeSlider.getValue());
    tone->tvpEnvLevel4 = uint8_t(penv4LevelSlider.getValue());
    tone->tvfVeloCurveLpfHpf = uint8_t(fenvVelCurveComboBox.getSelectedItemIndex() + (filterModeComboBox.getSelectedItemIndex() << 3));
    tone->tvfCutoff = uint8_t(filterCutoffSlider.getValue());
    tone->tvfResonance = uint8_t(filterResoSlider.getValue() + (filterResoModeComboBox.getSelectedItemIndex() << 7));
    tone->tvfTimeKFKeyfollow = uint8_t(filterKFComboBox.getSelectedItemIndex() + (fenvTimeKFSensComboBox.getSelectedItemIndex() << 4));
    tone->tvfVelocity = uint8_t(fenvLevSensSlider.getValue());
    tone->tvfT1T4Velocity = uint8_t(fenvTime1SensComboBox.getSelectedItemIndex() + (fenvTime4SensComboBox.getSelectedItemIndex() << 4));
    tone->tvfEnvDepth = uint8_t(fenvDepthSlider.getValue());
    tone->tvfEnvTime1 = uint8_t(fenv1TimeSlider.getValue());
    tone->tvfEnvLevel1 = uint8_t(fenv1LevelSlider.getValue());
    tone->tvfEnvTime2 = uint8_t(fenv2TimeSlider.getValue());
    tone->tvfEnvLevel2 = uint8_t(fenv2LevelSlider.getValue());
    tone->tvfEnvTime3 = uint8_t(fenv3TimeSlider.getValue());
    tone->tvfEnvLevel3 = uint8_t(fenv3LevelSlider.getValue());
    tone->tvfEnvTime4 = uint8_t(fenv4TimeSlider.getValue());
    tone->tvfEnvLevel4 = uint8_t(fenv4LevelSlider.getValue());
    tone->tvaLevel = uint8_t(levelSlider.getValue());
    tone->tvaTimeKFDelayTimeKeyfollow = uint8_t(levelKFComboBox.getSelectedItemIndex() + (aenvTimeKFSensComboBox.getSelectedItemIndex() << 4));
    tone->tvaPan = uint8_t(panSlider.getValue() + 64);
    tone->tvaDelayModeVeloCurve = uint8_t(aenvVelCurveComboBox.getSelectedItemIndex() + (toneDelayComboBox.getSelectedItemIndex() << 3));
    tone->tvaDelayTime = uint8_t(toneDelayTimeSlider.getValue());
    tone->tvaVelocity = uint8_t(aenvLevSensSlider.getValue());
    tone->tvaT1T4Velocity = uint8_t(aenvTime1SensComboBox.getSelectedItemIndex() + (aenvTime4SensComboBox.getSelectedItemIndex() << 4));
    tone->tvaEnvTime1 = uint8_t(aenv1TimeSlider.getValue() + (volumeSwitchToggle.getToggleState() << 7));
    tone->tvaEnvLevel1 = uint8_t(aenv1LevelSlider.getValue() + (holdSwitchToggle.getToggleState() << 7));
    tone->tvaEnvTime2 = uint8_t(aenv2TimeSlider.getValue());
    tone->tvaEnvLevel2 = uint8_t(aenv2LevelSlider.getValue());
    tone->tvaEnvTime3 = uint8_t(aenv3TimeSlider.getValue());
    tone->tvaEnvLevel3 = uint8_t(aenv3LevelSlider.getValue());
    tone->tvaEnvTime4 = uint8_t(aenv4TimeSlider.getValue());
    tone->drySend = uint8_t(drySlider.getValue());
    tone->reverbSend = uint8_t(reverbSlider.getValue());
    tone->chorusSend = uint8_t(chorusSlider.getValue());
}
