/*
  ==============================================================================

    EditToneTab.cpp
    Created: 20 Aug 2024 2:34:06pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#include <JuceHeader.h>
#include <algorithm>

#include "EditToneTab.h"

#include "../PluginEditor.h"
#include "../dataStructures.h"

//==============================================================================
EditToneTab::EditToneTab
    ( VirtualJVProcessor &p, VirtualJVEditor *e, uint8_t toneIn)
    : processor(p), editor(e), toneCount(toneIn)
{
    addAndMakeVisible(waveGroupComboBox);
    waveGroupComboBox.addListener(this);
    waveGroupComboBox.addItem("Internal", 1);
    waveGroupComboBox.addItem("Expansion", 2);
    waveGroupComboBox.setSelectedItemIndex(0);

    addAndMakeVisible(waveGroupLabel);
    waveGroupLabel.attachToComponent(&waveGroupComboBox, true);

    addAndMakeVisible(waveformComboBox);
    waveformComboBox.addListener(this);

    addAndMakeVisible(waveformLabel);
    waveformLabel.attachToComponent(&waveformComboBox, true);

    addAndMakeVisible(toneSwitchToggle);
    toneSwitchToggle.addListener(this);

    addAndMakeVisible(FXMSwitchToggle);
    FXMSwitchToggle.addListener(this);

    addAndMakeVisible(FXMDepthSlider);
    FXMDepthSlider.addListener(this);

    addAndMakeVisible(FXMDepthLabel);
    FXMDepthLabel.attachToComponent(&FXMDepthSlider, true);

    addAndMakeVisible(velRangeLowSlider);
    velRangeLowSlider.addListener(this);

    addAndMakeVisible(velRangeLabel);
    velRangeLabel.attachToComponent(&velRangeLowSlider, true);

    addAndMakeVisible(velRangeHighSlider);
    velRangeHighSlider.addListener(this);

    addAndMakeVisible(volumeSwitchToggle);
    volumeSwitchToggle.addListener(this);

    addAndMakeVisible(holdSwitchToggle);
    holdSwitchToggle.addListener(this);

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
    modDestALabel.attachToComponent(&modDestAComboBox, true);

    addAndMakeVisible(modDestAComboBox);
    modDestAComboBox.addListener(this);
    addMenuEntriesFromArray(modDestAComboBox, modSources);

    addAndMakeVisible(modSensASlider);
    modSensASlider.addListener(this);

    addAndMakeVisible(modDestBLabel);
    modDestBLabel.attachToComponent(&modDestBComboBox, true);

    addAndMakeVisible(modDestBComboBox);
    modDestBComboBox.addListener(this);
    addMenuEntriesFromArray(modDestBComboBox, modSources);

    addAndMakeVisible(modSensBSlider);
    modSensBSlider.addListener(this);

    addAndMakeVisible(modDestCLabel);
    modDestCLabel.attachToComponent(&modDestCComboBox, true);

    addAndMakeVisible(modDestCComboBox);
    modDestCComboBox.addListener(this);
    addMenuEntriesFromArray(modDestCComboBox, modSources);

    addAndMakeVisible(modSensCSlider);
    modSensCSlider.addListener(this);

    addAndMakeVisible(modDestDLabel);
    modDestDLabel.attachToComponent(&modDestDComboBox, true);

    addAndMakeVisible(modDestDComboBox);
    modDestDComboBox.addListener(this);
    addMenuEntriesFromArray(modDestDComboBox, modSources);

    addAndMakeVisible(modSensDSlider);
    modSensDSlider.addListener(this);

    addAndMakeVisible(aftDestALabel);
    aftDestALabel.attachToComponent(&aftDestAComboBox, true);

    addAndMakeVisible(aftDestAComboBox);
    aftDestAComboBox.addListener(this);;
    addMenuEntriesFromArray(aftDestAComboBox, modSources);

    addAndMakeVisible(aftSensASlider);
    aftSensASlider.addListener(this);

    addAndMakeVisible(aftDestBLabel);
    aftDestBLabel.attachToComponent(&aftDestBComboBox, true);

    addAndMakeVisible(aftDestBComboBox);
    aftDestBComboBox.addListener(this);
    addMenuEntriesFromArray(aftDestBComboBox, modSources);

    addAndMakeVisible(aftSensBSlider);
    aftSensBSlider.addListener(this);

    addAndMakeVisible(aftDestCLabel);
    aftDestCLabel.attachToComponent(&aftDestCComboBox, true);

    addAndMakeVisible(aftDestCComboBox);
    aftDestCComboBox.addListener(this);
    addMenuEntriesFromArray(aftDestCComboBox, modSources);

    addAndMakeVisible(aftSensCSlider);
    aftSensCSlider.addListener(this);

    addAndMakeVisible(aftDestDLabel);
    aftDestDLabel.attachToComponent(&aftDestDComboBox, true);

    addAndMakeVisible(aftDestDComboBox);
    aftDestDComboBox.addListener(this);
    addMenuEntriesFromArray(aftDestDComboBox, modSources);

    addAndMakeVisible(aftSensDSlider);
    aftSensDSlider.addListener(this);

    addAndMakeVisible(expDestALabel);
    expDestALabel.attachToComponent(&expDestAComboBox, true);

    addAndMakeVisible(expDestAComboBox);
    expDestAComboBox.addListener(this);
    addMenuEntriesFromArray(expDestAComboBox, modSources);

    addAndMakeVisible(expSensASlider);
    expSensASlider.addListener(this);

    addAndMakeVisible(expDestBLabel);
    expDestBLabel.attachToComponent(&expDestBComboBox, true);

    addAndMakeVisible(expDestBComboBox);
    expDestBComboBox.addListener(this);
    addMenuEntriesFromArray(expDestBComboBox, modSources);

    addAndMakeVisible(expSensBSlider);
    expSensBSlider.addListener(this);

    addAndMakeVisible(expDestCLabel);
    expDestCLabel.attachToComponent(&expDestCComboBox, true);

    addAndMakeVisible(expDestCComboBox);
    expDestCComboBox.addListener(this);
    addMenuEntriesFromArray(expDestCComboBox, modSources);

    addAndMakeVisible(expSensCSlider);
    expSensCSlider.addListener(this);

    addAndMakeVisible(expDestDLabel);
    expDestDLabel.attachToComponent(&expDestDComboBox, true);

    addAndMakeVisible(expDestDComboBox);
    expDestDComboBox.addListener(this);
    addMenuEntriesFromArray(expDestDComboBox, modSources);

    addAndMakeVisible(expSensDSlider);
    expSensDSlider.addListener(this);

    const std::vector<std::string> lfoWaves{"Triangle", "Sine", "Sawtooth", "Square", "Random 1", "Random 2"};

    const std::vector<std::string> lfoOffsets{"-100", "-50", "0", "+50", "+100"};

    addAndMakeVisible(lfo1FormLabel);
    lfo1FormLabel.attachToComponent(&lfo1FormComboBox, true);

    addAndMakeVisible(lfo1FormComboBox);
    lfo1FormComboBox.addListener(this);
    addMenuEntriesFromArray(lfo1FormComboBox, lfoWaves);

    addAndMakeVisible(lfo1OffsetLabel);
    lfo1OffsetLabel.attachToComponent(&lfo1OffsetComboBox, true);

    addAndMakeVisible(lfo1OffsetComboBox);
    lfo1OffsetComboBox.addListener(this);
    addMenuEntriesFromArray(lfo1OffsetComboBox, lfoOffsets);

    addAndMakeVisible(lfo1SyncToggle);
    lfo1SyncToggle.addListener(this);

    addAndMakeVisible(lfo1RateSlider);
    lfo1RateSlider.addListener(this);

    addAndMakeVisible(lfo1RateLabel);
    lfo1RateLabel.attachToComponent(&lfo1RateSlider, true);

    addAndMakeVisible(lfo1DelaySlider);
    lfo1DelaySlider.addListener(this);
    lfo1DelaySlider.textFromValueFunction = [this](double value)
        {
            return value == 128 ? "Key Off" : std::to_string((uint8_t)value);
        };

    addAndMakeVisible(lfo1DelayLabel);
    lfo1DelayLabel.attachToComponent(&lfo1DelaySlider, true);

    addAndMakeVisible(lfo1FadeToggle);
    lfo1FadeToggle.addListener(this);

    addAndMakeVisible(lfo1FadeTimeSlider);
    lfo1FadeTimeSlider.addListener(this);

    addAndMakeVisible(lfo1FadeTimeLabel);
    lfo1FadeTimeLabel.attachToComponent(&lfo1FadeTimeSlider, true);

    addAndMakeVisible(lfo1PitchDepthSlider);
    lfo1PitchDepthSlider.addListener(this);

    addAndMakeVisible(lfo1PitchDepthLabel);
    lfo1PitchDepthLabel.attachToComponent(&lfo1PitchDepthSlider, true);

    addAndMakeVisible(lfo1TVFDepthSlider);
    lfo1TVFDepthSlider.addListener(this);

    addAndMakeVisible(lfo1TVFDepthLabel);
    lfo1TVFDepthLabel.attachToComponent(&lfo1TVFDepthSlider, true);

    addAndMakeVisible(lfo1TVADepthSlider);
    lfo1TVADepthSlider.addListener(this);

    addAndMakeVisible(lfo1TVADepthLabel);
    lfo1TVADepthLabel.attachToComponent(&lfo1TVADepthSlider, true);

    addAndMakeVisible(lfo2FormLabel);
    lfo2FormLabel.attachToComponent(&lfo2FormComboBox, true);

    addAndMakeVisible(lfo2FormComboBox);
    lfo2FormComboBox.addListener(this);
    addMenuEntriesFromArray(lfo2FormComboBox, lfoWaves);

    addAndMakeVisible(lfo2OffsetLabel);
    lfo2OffsetLabel.attachToComponent(&lfo2OffsetComboBox, true);

    addAndMakeVisible(lfo2OffsetComboBox);
    lfo2OffsetComboBox.addListener(this);
    addMenuEntriesFromArray(lfo2OffsetComboBox, lfoOffsets);

    addAndMakeVisible(lfo2SyncToggle);
    lfo2SyncToggle.addListener(this);

    addAndMakeVisible(lfo2RateSlider);
    lfo2RateSlider.addListener(this);

    addAndMakeVisible(lfo2RateLabel);
    lfo2RateLabel.attachToComponent(&lfo2RateSlider, true);

    addAndMakeVisible(lfo2DelaySlider);
    lfo2DelaySlider.addListener(this);
    lfo2DelaySlider.textFromValueFunction = [this](double value)
        {
            return value == 128 ? "Key Off" : std::to_string((uint8_t)value);
        };

    addAndMakeVisible(lfo2DelayLabel);
    lfo2DelayLabel.attachToComponent(&lfo2DelaySlider, true);

    addAndMakeVisible(lfo2FadeToggle);
    lfo2FadeToggle.addListener(this);

    addAndMakeVisible(lfo2FadeTimeSlider);
    lfo2FadeTimeSlider.addListener(this);

    addAndMakeVisible(lfo2FadeTimeLabel);
    lfo2FadeTimeLabel.attachToComponent(&lfo2FadeTimeSlider, true);

    addAndMakeVisible(lfo2PitchDepthSlider);
    lfo2PitchDepthSlider.addListener(this);

    addAndMakeVisible(lfo2PitchDepthLabel);
    lfo2PitchDepthLabel.attachToComponent(&lfo2PitchDepthSlider, true);

    addAndMakeVisible(lfo2TVFDepthSlider);
    lfo2TVFDepthSlider.addListener(this);

    addAndMakeVisible(lfo2TVFDepthLabel);
    lfo2TVFDepthLabel.attachToComponent(&lfo2TVFDepthSlider, true);

    addAndMakeVisible(lfo2TVADepthSlider);
    lfo2TVADepthSlider.addListener(this);

    addAndMakeVisible(lfo2TVADepthLabel);
    lfo2TVADepthLabel.attachToComponent(&lfo2TVADepthSlider, true);

    addAndMakeVisible(pitchCoarseSlider);
    pitchCoarseSlider.addListener(this);

    addAndMakeVisible(pitchCoarseLabel);
    pitchCoarseLabel.attachToComponent(&pitchCoarseSlider, true);

    addAndMakeVisible(pitchFineSlider);
    pitchFineSlider.addListener(this);

    addAndMakeVisible(pitchFineLabel);
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
    addMenuEntriesFromArray(pitchRandomComboBox, pitchRandoms);

    addAndMakeVisible(pitchRandomLabel);
    pitchRandomLabel.attachToComponent(&pitchRandomComboBox, true);

    addAndMakeVisible(pitchKFComboBox);
    pitchKFComboBox.addListener(this);
    addMenuEntriesFromArray(pitchKFComboBox, keyFollows);

    addAndMakeVisible(penvLevSensSlider);
    penvLevSensSlider.addListener(this);

    addAndMakeVisible(penvLevSensLabel);
    penvLevSensLabel.attachToComponent(&penvLevSensSlider, true);

    addAndMakeVisible(penvTime1SensComboBox);
    penvTime1SensComboBox.addListener(this);
    addMenuEntriesFromArray(penvTime1SensComboBox, np100);

    addAndMakeVisible(penvTime1SensLabel);
    penvTime1SensLabel.attachToComponent(&penvTime1SensComboBox, true);

    addAndMakeVisible(penvTime4SensComboBox);
    penvTime4SensComboBox.addListener(this);
    addMenuEntriesFromArray(penvTime4SensComboBox, np100);

    addAndMakeVisible(penvTimeKFSensComboBox);
    penvTimeKFSensComboBox.addListener(this);
    addMenuEntriesFromArray(penvTimeKFSensComboBox, np100);

    addAndMakeVisible(penvTimeKFSensLabel);
    penvTimeKFSensLabel.attachToComponent(&penvTimeKFSensComboBox, true);

    addAndMakeVisible(penvDepthSlider);
    penvDepthSlider.addListener(this);

    addAndMakeVisible(penvDepthLabel);
    penvDepthLabel.attachToComponent(&penvDepthSlider, true);

    addAndMakeVisible(penv1TimeSlider);
    penv1TimeSlider.addListener(this);

    addAndMakeVisible(penv1TimeLabel);
    penv1TimeLabel.attachToComponent(&penv1TimeSlider, true);

    addAndMakeVisible(penv1LevelSlider);
    penv1LevelSlider.addListener(this);

    addAndMakeVisible(penv2TimeSlider);
    penv2TimeSlider.addListener(this);

    addAndMakeVisible(penv2TimeLabel);
    penv2TimeLabel.attachToComponent(&penv2TimeSlider, true);

    addAndMakeVisible(penv2LevelSlider);
    penv2LevelSlider.addListener(this);

    addAndMakeVisible(penv3TimeSlider);
    penv3TimeSlider.addListener(this);

    addAndMakeVisible(penv3TimeLabel);
    penv3TimeLabel.attachToComponent(&penv3TimeSlider, true);

    addAndMakeVisible(penv3LevelSlider);
    penv3LevelSlider.addListener(this);

    addAndMakeVisible(penv4TimeSlider);
    penv4TimeSlider.addListener(this);

    addAndMakeVisible(penv4TimeLabel);
    penv4TimeLabel.attachToComponent(&penv4TimeSlider, true);

    addAndMakeVisible(penv4LevelSlider);
    penv4LevelSlider.addListener(this);

    addAndMakeVisible(filterModeComboBox);
    filterModeComboBox.addListener(this);
    filterModeComboBox.addItem("Off", 1);
    filterModeComboBox.addItem("Lowpass", 2);
    filterModeComboBox.addItem("Highpass", 3);

    addAndMakeVisible(filterModeLabel);
    filterModeLabel.attachToComponent(&filterModeComboBox, true);

    addAndMakeVisible(filterCutoffSlider);
    filterCutoffSlider.addListener(this);

    addAndMakeVisible(filterCutoffLabel);
    filterCutoffLabel.attachToComponent(&filterCutoffSlider, true);

    addAndMakeVisible(filterResoSlider);
    filterResoSlider.addListener(this);

    addAndMakeVisible(filterResoLabel);
    filterResoLabel.attachToComponent(&filterResoSlider, true);

    addAndMakeVisible(filterResoModeComboBox);
    filterResoModeComboBox.addListener(this);
    filterResoModeComboBox.addItem("Soft", 1);
    filterResoModeComboBox.addItem("Hard", 2);

    addAndMakeVisible(filterKFComboBox);
    filterKFComboBox.addListener(this);
    addMenuEntriesFromArray(filterKFComboBox, keyFollows);

    addAndMakeVisible(filterKFLabel);
    filterKFLabel.attachToComponent(&filterKFComboBox, true);

    std::vector<std::string> velCurves{ "1", "2", "3", "4", "5", "6", "7" };

    addAndMakeVisible(fenvVelCurveComboBox);
    fenvVelCurveComboBox.addListener(this);
    addMenuEntriesFromArray(fenvVelCurveComboBox, velCurves);

    addAndMakeVisible(fenvLevSensSlider);
    fenvLevSensSlider.addListener(this);

    addAndMakeVisible(fenvLevSensLabel);
    fenvLevSensLabel.attachToComponent(&fenvLevSensSlider, true);

    addAndMakeVisible(fenvTime1SensComboBox);
    fenvTime1SensComboBox.addListener(this);
    addMenuEntriesFromArray(fenvTime1SensComboBox, np100);

    addAndMakeVisible(fenvTime1SensLabel);
    fenvTime1SensLabel.attachToComponent(&fenvTime1SensComboBox, true);

    addAndMakeVisible(fenvTime4SensComboBox);
    fenvTime4SensComboBox.addListener(this);
    addMenuEntriesFromArray(fenvTime4SensComboBox, np100);

    addAndMakeVisible(fenvTimeKFSensComboBox);
    fenvTimeKFSensComboBox.addListener(this);
    addMenuEntriesFromArray(fenvTimeKFSensComboBox, np100);

    addAndMakeVisible(fenvTimeKFSensLabel);
    fenvTimeKFSensLabel.attachToComponent(&fenvTimeKFSensComboBox, true);

    addAndMakeVisible(fenvDepthSlider);
    fenvDepthSlider.addListener(this);

    addAndMakeVisible(fenvDepthLabel);
    fenvDepthLabel.attachToComponent(&fenvDepthSlider, true);

    addAndMakeVisible(fenv1TimeSlider);
    fenv1TimeSlider.addListener(this);

    addAndMakeVisible(fenv1TimeLabel);
    fenv1TimeLabel.attachToComponent(&fenv1TimeSlider, true);

    addAndMakeVisible(fenv1LevelSlider);
    fenv1LevelSlider.addListener(this);

    addAndMakeVisible(fenv2TimeSlider);
    fenv2TimeSlider.addListener(this);

    addAndMakeVisible(fenv2TimeLabel);
    fenv2TimeLabel.attachToComponent(&fenv2TimeSlider, true);

    addAndMakeVisible(fenv2LevelSlider);
    fenv2LevelSlider.addListener(this);

    addAndMakeVisible(fenv3TimeSlider);
    fenv3TimeSlider.addListener(this);

    addAndMakeVisible(fenv3TimeLabel);
    fenv3TimeLabel.attachToComponent(&fenv3TimeSlider, true);

    addAndMakeVisible(fenv3LevelSlider);
    fenv3LevelSlider.addListener(this);

    addAndMakeVisible(fenv4TimeSlider);
    fenv4TimeSlider.addListener(this);

    addAndMakeVisible(fenv4TimeLabel);
    fenv4TimeLabel.attachToComponent(&fenv4TimeSlider, true);

    addAndMakeVisible(fenv4LevelSlider);
    fenv4LevelSlider.addListener(this);

    addAndMakeVisible(levelSlider);
    levelSlider.addListener(this);

    addAndMakeVisible(levelLabel);
    levelLabel.attachToComponent(&levelSlider, true);

    addAndMakeVisible(levelKFComboBox);
    levelKFComboBox.addListener(this);
    addMenuEntriesFromArray(levelKFComboBox, np100);

    addAndMakeVisible(levelKFLabel);
    levelKFLabel.attachToComponent(&levelKFComboBox, true);

    addAndMakeVisible(panSlider);
    panSlider.addListener(this);
    panSlider.textFromValueFunction = [this](double value)
        {
            return value == 64 ? "Random"
                               : value == 0 ? "C"
                                            : value < 0 ? "L" + std::to_string((int)abs(value))
                                                        : "R" + std::to_string((int)value);
        };

    addAndMakeVisible(panLabel);
    panLabel.attachToComponent(&panSlider, true);

    addAndMakeVisible(panKFComboBox);
    panKFComboBox.addListener(this);
    addMenuEntriesFromArray(panKFComboBox, np100);

    addAndMakeVisible(toneDelayComboBox);
    toneDelayComboBox.addListener(this);
    toneDelayComboBox.addItem("Normal", 1);
    toneDelayComboBox.addItem("Hold", 2);
    toneDelayComboBox.addItem("Playmate", 3);

    addAndMakeVisible(toneDelayLabel);
    toneDelayLabel.attachToComponent(&toneDelayComboBox, true);

    addAndMakeVisible(toneDelayTimeSlider);
    toneDelayTimeSlider.addListener(this);
    toneDelayTimeSlider.textFromValueFunction = [this](double value)
    {
        return value == 128 ? "Key Off" : std::to_string((uint8_t)value);
    };

    addAndMakeVisible(toneDelayTimeLabel);
    toneDelayTimeLabel.attachToComponent(&toneDelayTimeSlider, true);

    addAndMakeVisible(aenvVelCurveComboBox);
    aenvVelCurveComboBox.addListener(this);
    addMenuEntriesFromArray(aenvVelCurveComboBox, velCurves);

    addAndMakeVisible(aenvVelCurveLabel);
    aenvVelCurveLabel.attachToComponent(&aenvVelCurveComboBox, true);

    addAndMakeVisible(aenvLevSensSlider);
    aenvLevSensSlider.addListener(this);

    addAndMakeVisible(aenvLevSensLabel);
    aenvLevSensLabel.attachToComponent(&aenvLevSensSlider, true);

    addAndMakeVisible(aenvTime1SensComboBox);
    aenvTime1SensComboBox.addListener(this);
    addMenuEntriesFromArray(aenvTime1SensComboBox, np100);

    addAndMakeVisible(aenvTime1SensLabel);
    aenvTime1SensLabel.attachToComponent(&aenvTime1SensComboBox, true);

    addAndMakeVisible(aenvTime4SensComboBox);
    aenvTime4SensComboBox.addListener(this);
    addMenuEntriesFromArray(aenvTime4SensComboBox, np100);

    addAndMakeVisible(aenvTimeKFSensComboBox);
    aenvTimeKFSensComboBox.addListener(this);
    addMenuEntriesFromArray(aenvTimeKFSensComboBox, np100);

    addAndMakeVisible(aenvTimeKFSensLabel);
    aenvTimeKFSensLabel.attachToComponent(&aenvTimeKFSensComboBox, true);

    addAndMakeVisible(aenv1TimeSlider);
    aenv1TimeSlider.addListener(this);

    addAndMakeVisible(aenv1TimeLabel);
    aenv1TimeLabel.attachToComponent(&aenv1TimeSlider, true);

    addAndMakeVisible(aenv1LevelSlider);
    aenv1LevelSlider.addListener(this);

    addAndMakeVisible(aenv2TimeSlider);
    aenv2TimeSlider.addListener(this);

    addAndMakeVisible(aenv2TimeLabel);
    aenv2TimeLabel.attachToComponent(&aenv2TimeSlider, true);

    addAndMakeVisible(aenv2LevelSlider);
    aenv2LevelSlider.addListener(this);

    addAndMakeVisible(aenv3TimeSlider);
    aenv3TimeSlider.addListener(this);

    addAndMakeVisible(aenv3TimeLabel);
    aenv3TimeLabel.attachToComponent(&aenv3TimeSlider, true);

    addAndMakeVisible(aenv3LevelSlider);
    aenv3LevelSlider.addListener(this);

    addAndMakeVisible(aenv4TimeSlider);
    aenv4TimeSlider.addListener(this);

    addAndMakeVisible(aenv4TimeLabel);
    aenv4TimeLabel.attachToComponent(&aenv4TimeSlider, true);

    addAndMakeVisible(drySlider);
    drySlider.addListener(this);

    addAndMakeVisible(dryLabel);
    dryLabel.attachToComponent(&drySlider, true);

    addAndMakeVisible(reverbSlider);
    reverbSlider.addListener(this);

    addAndMakeVisible(reverbLabel);
    reverbLabel.attachToComponent(&reverbSlider, true);

    addAndMakeVisible(chorusSlider);
    chorusSlider.addListener(this);

    addAndMakeVisible(chorusLabel);
    chorusLabel.attachToComponent(&chorusSlider, true);

    addAndMakeVisible(outputComboBox);
    outputComboBox.addListener(this);
    outputComboBox.addItem("Main", 1);
    outputComboBox.addItem("Sub", 2);

    addAndMakeVisible(outputLabel);
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

void EditToneTab::updateWaveformComboBox(juce::ComboBox &wfMenu)
{
    const int priorSelection = wfMenu.getSelectedItemIndex();

    wfMenu.clear(juce::dontSendNotification);

    if (!editor)
        return;

    const auto romIdx = waveGroupComboBox.getSelectedItemIndex() == 0 ? 2U : editor->getSelectedRomIdx();
    auto names = processor.readMultisampleNames(romIdx);

    for (int i = 0; i < names.size(); i++)
    {
        if (i % 32 == 0 && i > 0)
        {
            wfMenu.getRootMenu()->addColumnBreak();
        }

        wfMenu.addItem(std::string{std::to_string(i + 1) + ": " + names[i]}, i + 1);
    }

    if (priorSelection > -1)
    {
        const int newSelection = std::clamp(priorSelection, 0, wfMenu.getNumItems() - 1);

        wfMenu.setSelectedItemIndex(newSelection);
    }
}

void EditToneTab::updateValues()
{
    Patch* patch = (Patch*)processor.status.patch;
    Tone tone = patch->tones[toneCount];
    waveGroupComboBox.setSelectedItemIndex((tone.flags & 0x3), juce::dontSendNotification);
    waveformComboBox.setSelectedItemIndex((tone.waveNumber & 0xff), juce::dontSendNotification);
    toneSwitchToggle.setToggleState(((tone.flags >> 7) & 0x01) ? 1 : 0, juce::dontSendNotification);
    FXMSwitchToggle.setToggleState(((tone.fxmConfig >> 7) & 0x01) ? 1 : 0, juce::dontSendNotification);
    FXMDepthSlider.setValue(((tone.fxmConfig) & 0x0f) + 1, juce::dontSendNotification);
    velRangeLowSlider.setValue(((tone.velocityRangeLow) & 0x7f), juce::dontSendNotification);
    velRangeHighSlider.setValue(((tone.velocityRangeUp) & 0x7f), juce::dontSendNotification);

    updateWaveformComboBox(waveformComboBox);

    volumeSwitchToggle.setToggleState(((tone.tvaDelayModeVeloCurve >> 7) & 0x01) ? 1 : 0, juce::dontSendNotification);
    holdSwitchToggle.setToggleState(((tone.tvaDelayModeVeloCurve >> 6) & 0x01) ? 1 : 0, juce::dontSendNotification);

    modDestAComboBox.setSelectedItemIndex((tone.matrixModDestAB & 0xf), juce::dontSendNotification);
    modDestBComboBox.setSelectedItemIndex(((tone.matrixModDestAB & 0xf0) >> 4), juce::dontSendNotification);
    modDestCComboBox.setSelectedItemIndex((tone.matrixModDestCD & 0xf), juce::dontSendNotification);
    modDestDComboBox.setSelectedItemIndex(((tone.matrixModDestCD & 0xf0) >> 4), juce::dontSendNotification);
    modSensASlider.setValue(int8_t((tone.matrixModSensA)), juce::dontSendNotification);
    modSensBSlider.setValue(int8_t((tone.matrixModSensB)), juce::dontSendNotification);
    modSensCSlider.setValue(int8_t((tone.matrixModSensC)), juce::dontSendNotification);
    modSensDSlider.setValue(int8_t((tone.matrixModSensD)), juce::dontSendNotification);
    aftDestAComboBox.setSelectedItemIndex((tone.matrixAftDestAB & 0xf), juce::dontSendNotification);
    aftDestBComboBox.setSelectedItemIndex(((tone.matrixAftDestAB & 0xf0) >> 4), juce::dontSendNotification);
    aftDestCComboBox.setSelectedItemIndex((tone.matrixAftDestCD & 0xf), juce::dontSendNotification);
    aftDestDComboBox.setSelectedItemIndex(((tone.matrixAftDestCD & 0xf0) >> 4), juce::dontSendNotification);
    aftSensASlider.setValue(int8_t((tone.matrixAftSensA)), juce::dontSendNotification);
    aftSensBSlider.setValue(int8_t((tone.matrixAftSensB)), juce::dontSendNotification);
    aftSensCSlider.setValue(int8_t((tone.matrixAftSensC)), juce::dontSendNotification);
    aftSensDSlider.setValue(int8_t((tone.matrixAftSensD)), juce::dontSendNotification);
    expDestAComboBox.setSelectedItemIndex((tone.matrixExpDestAB & 0xf), juce::dontSendNotification);
    expDestBComboBox.setSelectedItemIndex(((tone.matrixExpDestAB & 0xf0) >> 4), juce::dontSendNotification);
    expDestCComboBox.setSelectedItemIndex((tone.matrixExpDestCD & 0xf), juce::dontSendNotification);
    expDestDComboBox.setSelectedItemIndex(((tone.matrixExpDestCD & 0xf0) >> 4), juce::dontSendNotification);
    expSensASlider.setValue(int8_t((tone.matrixExpSensA)), juce::dontSendNotification);
    expSensBSlider.setValue(int8_t((tone.matrixExpSensB)), juce::dontSendNotification);
    expSensCSlider.setValue(int8_t((tone.matrixExpSensC)), juce::dontSendNotification);
    expSensDSlider.setValue(int8_t((tone.matrixExpSensD)), juce::dontSendNotification);

    lfo1FormComboBox.setSelectedItemIndex((tone.lfo1Flags & 0x7), juce::dontSendNotification);
    lfo1OffsetComboBox.setSelectedItemIndex((tone.lfo1Flags & 0x38) >> 3, juce::dontSendNotification);
    lfo1SyncToggle.setToggleState(((tone.lfo1Flags & 0x40) >> 6) ? 1 : 0, juce::dontSendNotification);
    lfo1FadeToggle.setToggleState(((tone.lfo1Flags & 0x80) >> 7) ? 1 : 0, juce::dontSendNotification);
    lfo1RateSlider.setValue(((tone.lfo1Rate)), juce::dontSendNotification);
    lfo1DelaySlider.setValue(((tone.lfo1Delay)), juce::dontSendNotification);
    lfo1FadeTimeSlider.setValue(((tone.lfo1Fade)), juce::dontSendNotification);
    lfo1PitchDepthSlider.setValue(int8_t((tone.lfo1PitchDepth)), juce::dontSendNotification);
    lfo1TVFDepthSlider.setValue(int8_t((tone.lfo1TvfDepth)), juce::dontSendNotification);
    lfo1TVADepthSlider.setValue(int8_t((tone.lfo1TvaDepth)), juce::dontSendNotification);

    lfo2FormComboBox.setSelectedItemIndex((tone.lfo2Flags & 0x7), juce::dontSendNotification);
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
    pitchRandomComboBox.setSelectedItemIndex((tone.tvaPanKFpitchRandom & 0xf), juce::dontSendNotification);
    pitchKFComboBox.setSelectedItemIndex((tone.tvpKFtvaTimeKF & 0xf), juce::dontSendNotification);
    penvLevSensSlider.setValue(int8_t((tone.tvpVelocity)), juce::dontSendNotification);
    penvTime1SensComboBox.setSelectedItemIndex((tone.tvpT1T4Velocity & 0xf), juce::dontSendNotification);
    penvTime4SensComboBox.setSelectedItemIndex((tone.tvpT1T4Velocity & 0xf0) >> 4, juce::dontSendNotification);
    penvTimeKFSensComboBox.setSelectedItemIndex((tone.tvpKFtvaTimeKF & 0xf0) >> 4, juce::dontSendNotification);
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
    panKFComboBox.setSelectedItemIndex((tone.tvaPanKFpitchRandom & 0xf0) >> 4, juce::dontSendNotification);
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

void EditToneTab::resized()
{
    const auto top = 10;
    const auto sliderLeft1 = 100;
    const auto width = getWidth() / 3 - sliderLeft1 - 10;
    const auto halfWidth = width / 2;
    const auto sliderLeft2 = sliderLeft1 + getWidth() / 3 + 2;
    const auto sliderLeft3 = sliderLeft2 + getWidth() / 3;
    const auto height = 24;
    const auto vMargin = 24;

    toneSwitchToggle      .setBounds(sliderLeft1 - 90, top + height * 0 + vMargin * 0, width, height);

    waveGroupComboBox     .setBounds(sliderLeft1, top + height * 1 + vMargin * 1, width, height);
    waveformComboBox      .setBounds(sliderLeft1, top + height * 2 + vMargin * 1, width, height);

    velRangeLowSlider     .setBounds(sliderLeft1, top + height * 3 + vMargin * 2, halfWidth, height);
    velRangeHighSlider    .setBounds(sliderLeft1 + halfWidth, top + height * 3 + vMargin * 2, halfWidth, height);

    volumeSwitchToggle    .setBounds(sliderLeft1 - 90, top + height * 4 + vMargin * 3, int(width * 0.75f), height);
    holdSwitchToggle      .setBounds(sliderLeft1 + 30, top + height * 4 + vMargin * 3, int(width * 0.75f), height);

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
    uint32_t id = 0xFFFFFFF;

    if (auto i = dynamic_cast<Slider*>(slider))
    {
        id = i->getID();
    }

    Patch* patch = (Patch*)processor.status.patch;
    Tone* tone = &patch->tones[toneCount];

    switch (id)
    {
    case FXMDepth:
        sendSysexPatchToneChange1Byte(0x05, uint8_t(FXMDepthSlider.getValue() - 1));
        tone->fxmConfig = uint8_t((uint8_t(FXMDepthSlider.getValue() - 1) << 0) + (FXMSwitchToggle.getToggleState() << 7));
        break;
    case VelRangeLow:
        sendSysexPatchToneChange1Byte(0x06, uint8_t(velRangeLowSlider.getValue()));
        tone->velocityRangeLow = uint8_t(velRangeLowSlider.getValue());
        break;
    case VelRangeHigh:
        sendSysexPatchToneChange1Byte(0x07, uint8_t(velRangeHighSlider.getValue()));
        tone->velocityRangeUp = uint8_t(velRangeHighSlider.getValue());
        break;
    case MW1Depth:
        sendSysexPatchToneChange1Byte(0x0b, uint8_t(modSensASlider.getValue() + 64));
        tone->matrixModSensA = uint8_t(modSensASlider.getValue());
        break;
    case MW2Depth:
        sendSysexPatchToneChange1Byte(0x0d, uint8_t(modSensBSlider.getValue() + 64));
        tone->matrixModSensB = uint8_t(modSensBSlider.getValue());
        break;
    case MW3Depth:
        sendSysexPatchToneChange1Byte(0x0f, uint8_t(modSensCSlider.getValue() + 64));
        tone->matrixModSensC = uint8_t(modSensCSlider.getValue());
        break;
    case MW4Depth:
        sendSysexPatchToneChange1Byte(0x11, uint8_t(modSensDSlider.getValue() + 64));
        tone->matrixModSensD = uint8_t(modSensDSlider.getValue());
        break;
    case AT1Depth:
        sendSysexPatchToneChange1Byte(0x13, uint8_t(aftSensASlider.getValue() + 64));
        tone->matrixAftSensA = uint8_t(aftSensASlider.getValue());
        break;
    case AT2Depth:
        sendSysexPatchToneChange1Byte(0x15, uint8_t(aftSensBSlider.getValue() + 64));
        tone->matrixAftSensB = uint8_t(aftSensBSlider.getValue());
        break;
    case AT3Depth:
        sendSysexPatchToneChange1Byte(0x17, uint8_t(aftSensCSlider.getValue() + 64));
        tone->matrixAftSensC = uint8_t(aftSensCSlider.getValue());
        break;
    case AT4Depth:
        sendSysexPatchToneChange1Byte(0x19, uint8_t(aftSensDSlider.getValue() + 64));
        tone->matrixAftSensD = uint8_t(aftSensDSlider.getValue());
        break;
    case EXP1Depth:
        sendSysexPatchToneChange1Byte(0x1b, uint8_t(expSensASlider.getValue() + 64));
        tone->matrixExpSensA = uint8_t(expSensASlider.getValue());
        break;
    case EXP2Depth:
        sendSysexPatchToneChange1Byte(0x1d, uint8_t(expSensBSlider.getValue() + 64));
        tone->matrixExpSensB = uint8_t(expSensBSlider.getValue());
        break;
    case EXP3Depth:
        sendSysexPatchToneChange1Byte(0x1f, uint8_t(expSensCSlider.getValue() + 64));
        tone->matrixExpSensC = uint8_t(expSensCSlider.getValue());
        break;
    case EXP4Depth:
        sendSysexPatchToneChange1Byte(0x21, uint8_t(expSensDSlider.getValue() + 64));
        tone->matrixExpSensD = uint8_t(expSensDSlider.getValue());
        break;
    case LFO1Rate:
        sendSysexPatchToneChange1Byte(0x25, uint8_t(lfo1RateSlider.getValue()));
        tone->lfo1Rate = uint8_t(lfo1RateSlider.getValue());
        break;
    case LFO1Delay:
        sendSysexPatchToneChange2Byte(0x26, uint8_t(lfo1DelaySlider.getValue()));
        tone->lfo1Delay = uint8_t(lfo1DelaySlider.getValue());
        break;
    case LFO1FadeTime:
        sendSysexPatchToneChange1Byte(0x29, uint8_t(lfo1FadeTimeSlider.getValue()));
        tone->lfo1Fade = uint8_t(lfo1FadeTimeSlider.getValue());
        break;
    case LFO1ToPitch:
        sendSysexPatchToneChange1Byte(0x2a, uint8_t(lfo1PitchDepthSlider.getValue() + 64));
        tone->lfo1PitchDepth = uint8_t(lfo1PitchDepthSlider.getValue());
        break;
    case LFO1ToFilter:
        sendSysexPatchToneChange1Byte(0x2b, uint8_t(lfo1TVFDepthSlider.getValue() + 64));
        tone->lfo1TvfDepth = uint8_t(lfo1TVFDepthSlider.getValue());
        break;
    case LFO1ToAmp:
        sendSysexPatchToneChange1Byte(0x2c, uint8_t(lfo1TVADepthSlider.getValue() + 64));
        tone->lfo1TvaDepth = uint8_t(lfo1TVADepthSlider.getValue());
        break;
    case LFO2Rate:
        sendSysexPatchToneChange1Byte(0x30, uint8_t(lfo2RateSlider.getValue()));
        tone->lfo2Rate = uint8_t(lfo2RateSlider.getValue());
        break;
    case LFO2Delay:
        sendSysexPatchToneChange2Byte(0x31, uint8_t(lfo2DelaySlider.getValue()));
        tone->lfo2Delay = uint8_t(lfo2DelaySlider.getValue());
        break;
    case LFO2FadeTime:
        sendSysexPatchToneChange1Byte(0x34, uint8_t(lfo2FadeTimeSlider.getValue()));
        tone->lfo2Fade = uint8_t(lfo2FadeTimeSlider.getValue());
        break;
    case LFO2ToPitch:
        sendSysexPatchToneChange1Byte(0x35, uint8_t(lfo2PitchDepthSlider.getValue() + 64));
        tone->lfo2PitchDepth = uint8_t(lfo2PitchDepthSlider.getValue());
        break;
    case LFO2ToFilter:
        sendSysexPatchToneChange1Byte(0x36, uint8_t(lfo2TVFDepthSlider.getValue() + 64));
        tone->lfo2TvfDepth = uint8_t(lfo2TVFDepthSlider.getValue());
        break;
    case LFO2ToAmp:
        sendSysexPatchToneChange1Byte(0x37, uint8_t(lfo2TVADepthSlider.getValue() + 64));
        tone->lfo2TvaDepth = uint8_t(lfo2TVADepthSlider.getValue());
        break;
    case PitchCoarse:
        sendSysexPatchToneChange1Byte(0x38, uint8_t(pitchCoarseSlider.getValue() + 64));
        tone->pitchCoarse = uint8_t(pitchCoarseSlider.getValue());
        break;
    case PitchFine:
        sendSysexPatchToneChange1Byte(0x39, uint8_t(pitchFineSlider.getValue() + 64));
        tone->pitchFine = uint8_t(pitchFineSlider.getValue());
        break;
    case PitchEnvLevelSense:
        sendSysexPatchToneChange1Byte(0x3c, uint8_t(penvLevSensSlider.getValue() + 64));
        tone->tvpVelocity = uint8_t(penvLevSensSlider.getValue());
        break;
    case PitchEnvDepth:
        sendSysexPatchToneChange1Byte(0x40, uint8_t(penvDepthSlider.getValue() + 64));
        tone->tvpEnvDepth = uint8_t(penvDepthSlider.getValue());
        break;
    case PitchEnvTime1:
        sendSysexPatchToneChange1Byte(0x41, uint8_t(penv1TimeSlider.getValue()));
        tone->tvpEnvTime1 = uint8_t(penv1TimeSlider.getValue());
        break;
    case PitchEnvLevel1:
        sendSysexPatchToneChange1Byte(0x42, uint8_t(penv1LevelSlider.getValue() + 64));
        tone->tvpEnvLevel1 = uint8_t(penv1LevelSlider.getValue());
        break;
    case PitchEnvTime2:
        sendSysexPatchToneChange1Byte(0x43, uint8_t(penv2TimeSlider.getValue()));
        tone->tvpEnvTime2 = uint8_t(penv2TimeSlider.getValue());
        break;
    case PitchEnvLevel2:
        sendSysexPatchToneChange1Byte(0x44, uint8_t(penv2LevelSlider.getValue() + 64));
        tone->tvpEnvLevel2 = uint8_t(penv2LevelSlider.getValue());
        break;
    case PitchEnvTime3:
        sendSysexPatchToneChange1Byte(0x45, uint8_t(penv3TimeSlider.getValue()));
        tone->tvpEnvTime3 = uint8_t(penv3TimeSlider.getValue());
        break;
    case PitchEnvLevel3:
        sendSysexPatchToneChange1Byte(0x46, uint8_t(penv3LevelSlider.getValue() + 64));
        tone->tvpEnvLevel3 = uint8_t(penv3LevelSlider.getValue());
        break;
    case PitchEnvTime4:
        sendSysexPatchToneChange1Byte(0x47, uint8_t(penv4TimeSlider.getValue()));
        tone->tvpEnvTime4 = uint8_t(penv4TimeSlider.getValue());
        break;
    case PitchEnvLevel4:
        sendSysexPatchToneChange1Byte(0x48, uint8_t(penv4LevelSlider.getValue() + 64));
        tone->tvpEnvLevel4 = uint8_t(penv4LevelSlider.getValue());
        break;
    case FilterCutoff:
        sendSysexPatchToneChange1Byte(0x4a, uint8_t(filterCutoffSlider.getValue()));
        tone->tvfCutoff = uint8_t(filterCutoffSlider.getValue());
        break;
    case FilterReso:
        sendSysexPatchToneChange1Byte(0x4b, uint8_t(filterResoSlider.getValue()));
        tone->tvfResonance = uint8_t(filterResoSlider.getValue() + (filterResoModeComboBox.getSelectedItemIndex() << 7));
        break;
    case FilterEnvLevelSense:
        sendSysexPatchToneChange1Byte(0x4f, uint8_t(fenvLevSensSlider.getValue() + 64));
        tone->tvfVelocity = uint8_t(fenvLevSensSlider.getValue());
        break;
    case FilterEnvDepth:
        sendSysexPatchToneChange1Byte(0x53, uint8_t(fenvDepthSlider.getValue() + 64));
        tone->tvfEnvDepth = uint8_t(fenvDepthSlider.getValue());
        break;
    case FilterEnvTime1:
        sendSysexPatchToneChange1Byte(0x54, uint8_t(fenv1TimeSlider.getValue()));
        tone->tvfEnvTime1 = uint8_t(fenv1TimeSlider.getValue());
        break;
    case FilterEnvLevel1:
        sendSysexPatchToneChange1Byte(0x55, uint8_t(fenv1LevelSlider.getValue()));
        tone->tvfEnvLevel1 = uint8_t(fenv1LevelSlider.getValue());
        break;
    case FilterEnvTime2:
        sendSysexPatchToneChange1Byte(0x56, uint8_t(fenv2TimeSlider.getValue()));
        tone->tvfEnvTime2 = uint8_t(fenv2TimeSlider.getValue());
        break;
    case FilterEnvLevel2:
        sendSysexPatchToneChange1Byte(0x57, uint8_t(fenv2LevelSlider.getValue()));
        tone->tvfEnvLevel2 = uint8_t(fenv2LevelSlider.getValue());
        break;
    case FilterEnvTime3:
        sendSysexPatchToneChange1Byte(0x58, uint8_t(fenv3TimeSlider.getValue()));
        tone->tvfEnvTime3 = uint8_t(fenv3TimeSlider.getValue());
        break;
    case FilterEnvLevel3:
        sendSysexPatchToneChange1Byte(0x59, uint8_t(fenv3LevelSlider.getValue()));
        tone->tvfEnvLevel3 = uint8_t(fenv3LevelSlider.getValue());
        break;
    case FilterEnvTime4:
        sendSysexPatchToneChange1Byte(0x5a, uint8_t(fenv4TimeSlider.getValue()));
        tone->tvfEnvTime4 = uint8_t(fenv4TimeSlider.getValue());
        break;
    case FilterEnvLevel4:
        sendSysexPatchToneChange1Byte(0x5b, uint8_t(fenv4LevelSlider.getValue()));
        tone->tvfEnvLevel4 = uint8_t(fenv4LevelSlider.getValue());
        break;
    case Level:
        sendSysexPatchToneChange1Byte(0x5c, uint8_t(levelSlider.getValue()));
        tone->tvaLevel = uint8_t(levelSlider.getValue());
        break;
    case Pan:
        sendSysexPatchToneChange2Byte(0x5e, uint8_t(panSlider.getValue() + 64));
        tone->tvaPan = uint8_t(panSlider.getValue() + 64);
        break;
    case DelayTime:
        sendSysexPatchToneChange2Byte(0x62, uint8_t(toneDelayTimeSlider.getValue()));
        tone->tvaDelayTime = uint8_t(toneDelayTimeSlider.getValue());
        break;
    case AmpEnvLevelSense:
        sendSysexPatchToneChange1Byte(0x65, uint8_t(aenvLevSensSlider.getValue() + 64));
        tone->tvaVelocity = uint8_t(aenvLevSensSlider.getValue());
        break;
    case AmpEnvTime1:
        sendSysexPatchToneChange1Byte(0x69, uint8_t(aenv1TimeSlider.getValue()));
        tone->tvaEnvTime1 = uint8_t(aenv1TimeSlider.getValue());
        break;
    case AmpEnvLevel1:
        sendSysexPatchToneChange1Byte(0x6a, uint8_t(aenv1LevelSlider.getValue()));
        tone->tvaEnvLevel1 = uint8_t(aenv1LevelSlider.getValue());
        break;
    case AmpEnvTime2:
        sendSysexPatchToneChange1Byte(0x6b, uint8_t(aenv2TimeSlider.getValue()));
        tone->tvaEnvTime2 = uint8_t(aenv2TimeSlider.getValue());
        break;
    case AmpEnvLevel2:
        sendSysexPatchToneChange1Byte(0x6c, uint8_t(aenv2LevelSlider.getValue()));
        tone->tvaEnvLevel2 = uint8_t(aenv2LevelSlider.getValue());
        break;
    case AmpEnvTime3:
        sendSysexPatchToneChange1Byte(0x6d, uint8_t(aenv3TimeSlider.getValue()));
        tone->tvaEnvTime3 = uint8_t(aenv3TimeSlider.getValue());
        break;
    case AmpEnvLevel3:
        sendSysexPatchToneChange1Byte(0x6e, uint8_t(aenv3LevelSlider.getValue()));
        tone->tvaEnvLevel3 = uint8_t(aenv3LevelSlider.getValue());
        break;
    case AmpEnvTime4:
        sendSysexPatchToneChange1Byte(0x6f, uint8_t(aenv4TimeSlider.getValue()));
        tone->tvaEnvTime4 = uint8_t(aenv4TimeSlider.getValue());
        break;
    case DrySend:
        sendSysexPatchToneChange1Byte(0x70, uint8_t(drySlider.getValue()));
        tone->drySend = uint8_t(drySlider.getValue());
        break;
    case ReverbSend:
        sendSysexPatchToneChange1Byte(0x71, uint8_t(reverbSlider.getValue()));
        tone->reverbSend = uint8_t(reverbSlider.getValue());
        break;
    case ChorusSend:
        sendSysexPatchToneChange1Byte(0x72, uint8_t(chorusSlider.getValue()));
        tone->chorusSend = uint8_t(chorusSlider.getValue());
        break;
    }
}

void EditToneTab::buttonClicked(juce::Button* button)
{
    uint32_t id = 0xFFFFFFF;

    if (auto i = dynamic_cast<Button*>(button))
    {
        id = i->getID();
    }

    Patch* patch = (Patch*)processor.status.patch;
    Tone* tone = &patch->tones[toneCount];

    switch (id)
    {
    case ToneSwitch:
        sendSysexPatchToneChange1Byte(0x03, toneSwitchToggle.getToggleStateValue() == 1);
        tone->flags = uint8_t(waveGroupComboBox.getSelectedItemIndex() + (toneSwitchToggle.getToggleState() << 7));
        break;
    case FXMSwitch:
        sendSysexPatchToneChange1Byte(0x04, FXMSwitchToggle.getToggleStateValue() == 1);
        tone->fxmConfig = uint8_t((uint8_t(FXMDepthSlider.getValue() - 1) << 0) + (FXMSwitchToggle.getToggleState() << 7));
        break;
    case CC7Receive:
        sendSysexPatchToneChange1Byte(0x08, volumeSwitchToggle.getToggleStateValue() == 1);
        tone->tvaDelayModeVeloCurve = uint8_t(aenvVelCurveComboBox.getSelectedItemIndex() + (toneDelayComboBox.getSelectedItemIndex() << 3) + (holdSwitchToggle.getToggleState() << 6) + (volumeSwitchToggle.getToggleState() << 7));
        break;
    case SustainPedalReceive:
        sendSysexPatchToneChange1Byte(0x09, holdSwitchToggle.getToggleStateValue() == 1);
        tone->tvaDelayModeVeloCurve = uint8_t(aenvVelCurveComboBox.getSelectedItemIndex() + (toneDelayComboBox.getSelectedItemIndex() << 3) + (holdSwitchToggle.getToggleState() << 6) + (volumeSwitchToggle.getToggleState() << 7));
        break;
    case LFO1KeySync:
        sendSysexPatchToneChange1Byte(0x24, lfo1SyncToggle.getToggleStateValue() == 1);
        tone->lfo1Flags = uint8_t(lfo1FormComboBox.getSelectedItemIndex() + (lfo1OffsetComboBox.getSelectedItemIndex() << 3) + (lfo1SyncToggle.getToggleState() << 6) + (lfo1FadeToggle.getToggleState() << 7));
        break;
    case LFO1FadeOut:
        sendSysexPatchToneChange1Byte(0x28, lfo1FadeToggle.getToggleStateValue() == 1);
        tone->lfo1Flags = uint8_t(lfo1FormComboBox.getSelectedItemIndex() + (lfo1OffsetComboBox.getSelectedItemIndex() << 3) + (lfo1SyncToggle.getToggleState() << 6) + (lfo1FadeToggle.getToggleState() << 7));
        break;
    case LFO2KeySync:
        sendSysexPatchToneChange1Byte(0x2f, lfo2SyncToggle.getToggleStateValue() == 1);
        tone->lfo2Flags = uint8_t(lfo2FormComboBox.getSelectedItemIndex() + (lfo2OffsetComboBox.getSelectedItemIndex() << 3) + (lfo2SyncToggle.getToggleState() << 6) + (lfo2FadeToggle.getToggleState() << 7));
        break;
    case LFO2FadeOut:
        sendSysexPatchToneChange1Byte(0x33, lfo2FadeToggle.getToggleStateValue() == 1);
        tone->lfo2Flags = uint8_t(lfo2FormComboBox.getSelectedItemIndex() + (lfo2OffsetComboBox.getSelectedItemIndex() << 3) + (lfo2SyncToggle.getToggleState() << 6) + (lfo2FadeToggle.getToggleState() << 7));
        break;
    }
}

void EditToneTab::comboBoxChanged(juce::ComboBox* comboBox)
{
    uint32_t id = 0xFFFFFFF;

    if (auto i = dynamic_cast<Menu*>(comboBox))
    {
        id = i->getID();
    }

    Patch* patch = (Patch*)processor.status.patch;
    Tone* tone = &patch->tones[toneCount];

    switch (id)
    {
    case WaveGroup:
        sendSysexPatchToneChange1Byte(0x00, uint8_t(waveGroupComboBox.getSelectedItemIndex()));
        updateWaveformComboBox(waveformComboBox);
        tone->flags = uint8_t(waveGroupComboBox.getSelectedItemIndex() + (toneSwitchToggle.getToggleState() << 7));
        break;
    case Waveform:
        sendSysexPatchToneChange2Byte(0x01, uint8_t(waveformComboBox.getSelectedItemIndex()));
        tone->waveNumber = uint8_t(waveformComboBox.getSelectedItemIndex());
        break;
    case MW1Target:
        sendSysexPatchToneChange1Byte(0x0a, uint8_t(modDestAComboBox.getSelectedItemIndex()));
        tone->matrixModDestAB = uint8_t(modDestAComboBox.getSelectedItemIndex() + (modDestBComboBox.getSelectedItemIndex() << 4));
        break;
    case MW2Target:
        sendSysexPatchToneChange1Byte(0x0c, uint8_t(modDestBComboBox.getSelectedItemIndex()));
        tone->matrixModDestAB = uint8_t(modDestAComboBox.getSelectedItemIndex() + (modDestBComboBox.getSelectedItemIndex() << 4));
        break;
    case MW3Target:
        sendSysexPatchToneChange1Byte(0x0e, uint8_t(modDestCComboBox.getSelectedItemIndex()));
        tone->matrixModDestCD = uint8_t(modDestCComboBox.getSelectedItemIndex() + (modDestDComboBox.getSelectedItemIndex() << 4));
        break;
    case MW4Target:
        sendSysexPatchToneChange1Byte(0x10, uint8_t(modDestDComboBox.getSelectedItemIndex()));
        tone->matrixModDestCD = uint8_t(modDestCComboBox.getSelectedItemIndex() + (modDestDComboBox.getSelectedItemIndex() << 4));
        break;
    case AT1Target:
        sendSysexPatchToneChange1Byte(0x12, uint8_t(aftDestAComboBox.getSelectedItemIndex()));
        tone->matrixAftDestAB = uint8_t(aftDestAComboBox.getSelectedItemIndex() + (aftDestBComboBox.getSelectedItemIndex() << 4));
        break;
    case AT2Target:
        sendSysexPatchToneChange1Byte(0x14, uint8_t(aftDestBComboBox.getSelectedItemIndex()));
        tone->matrixAftDestAB = uint8_t(aftDestAComboBox.getSelectedItemIndex() + (aftDestBComboBox.getSelectedItemIndex() << 4));
        break;
    case AT3Target:
        sendSysexPatchToneChange1Byte(0x16, uint8_t(aftDestCComboBox.getSelectedItemIndex()));
        tone->matrixAftDestCD = uint8_t(aftDestCComboBox.getSelectedItemIndex() + (aftDestDComboBox.getSelectedItemIndex() << 4));
        break;
    case AT4Target:
        sendSysexPatchToneChange1Byte(0x18, uint8_t(aftDestDComboBox.getSelectedItemIndex()));
        tone->matrixAftDestCD = uint8_t(aftDestCComboBox.getSelectedItemIndex() + (aftDestDComboBox.getSelectedItemIndex() << 4));
        break;
    case EXP1Target:
        sendSysexPatchToneChange1Byte(0x1a, uint8_t(expDestAComboBox.getSelectedItemIndex()));
        tone->matrixExpDestAB = uint8_t(expDestAComboBox.getSelectedItemIndex() + (expDestBComboBox.getSelectedItemIndex() << 4));
        break;
    case EXP2Target:
        sendSysexPatchToneChange1Byte(0x1c, uint8_t(expDestBComboBox.getSelectedItemIndex()));
        tone->matrixExpDestAB = uint8_t(expDestAComboBox.getSelectedItemIndex() + (expDestBComboBox.getSelectedItemIndex() << 4));
        break;
    case EXP3Target:
        sendSysexPatchToneChange1Byte(0x1e, uint8_t(expDestCComboBox.getSelectedItemIndex()));
        tone->matrixExpDestCD = uint8_t(expDestCComboBox.getSelectedItemIndex() + (expDestDComboBox.getSelectedItemIndex() << 4));
        break;
    case EXP4Target:
        sendSysexPatchToneChange1Byte(0x20, uint8_t(expDestDComboBox.getSelectedItemIndex()));
        tone->matrixExpDestCD = uint8_t(expDestCComboBox.getSelectedItemIndex() + (expDestDComboBox.getSelectedItemIndex() << 4));
        break;
    case LFO1Waveform:
        sendSysexPatchToneChange1Byte(0x22, uint8_t(lfo1FormComboBox.getSelectedItemIndex()));
        tone->lfo1Flags = uint8_t(lfo1FormComboBox.getSelectedItemIndex() + (lfo1OffsetComboBox.getSelectedItemIndex() << 3) + (lfo1SyncToggle.getToggleState() << 6) + (lfo1FadeToggle.getToggleState() << 7));
        break;
    case LFO1Offset:
        sendSysexPatchToneChange1Byte(0x23, uint8_t(lfo1OffsetComboBox.getSelectedItemIndex()));
        tone->lfo1Flags = uint8_t(lfo1FormComboBox.getSelectedItemIndex() + (lfo1OffsetComboBox.getSelectedItemIndex() << 3) + (lfo1SyncToggle.getToggleState() << 6) + (lfo1FadeToggle.getToggleState() << 7));
        break;
    case LFO2Waveform:
        sendSysexPatchToneChange1Byte(0x2d, uint8_t(lfo2FormComboBox.getSelectedItemIndex()));
        tone->lfo2Flags = uint8_t(lfo2FormComboBox.getSelectedItemIndex() + (lfo2OffsetComboBox.getSelectedItemIndex() << 3) + (lfo2SyncToggle.getToggleState() << 6) + (lfo2FadeToggle.getToggleState() << 7));
        break;
    case LFO2Offset:
        sendSysexPatchToneChange1Byte(0x2e, uint8_t(lfo2OffsetComboBox.getSelectedItemIndex()));
        tone->lfo2Flags = uint8_t(lfo2FormComboBox.getSelectedItemIndex() + (lfo2OffsetComboBox.getSelectedItemIndex() << 3) + (lfo2SyncToggle.getToggleState() << 6) + (lfo2FadeToggle.getToggleState() << 7));
        break;
    case PitchRandom:
        sendSysexPatchToneChange1Byte(0x3a, uint8_t(pitchRandomComboBox.getSelectedItemIndex()));
        tone->tvaPanKFpitchRandom = uint8_t(pitchRandomComboBox.getSelectedItemIndex() + (panKFComboBox.getSelectedItemIndex() << 4));
        break;
    case PitchKeyfollow:
        sendSysexPatchToneChange1Byte(0x3b, uint8_t(pitchKFComboBox.getSelectedItemIndex()));
        tone->tvpKFtvaTimeKF = uint8_t(pitchKFComboBox.getSelectedItemIndex() + (penvTimeKFSensComboBox.getSelectedItemIndex() << 4));
        break;
    case PitchEnvTime1Sense:
        sendSysexPatchToneChange1Byte(0x3d, uint8_t(penvTime1SensComboBox.getSelectedItemIndex()));
        tone->tvpT1T4Velocity = uint8_t(penvTime1SensComboBox.getSelectedItemIndex() + (penvTime4SensComboBox.getSelectedItemIndex() << 4));
        break;
    case PitchEnvTime4Sense:
        sendSysexPatchToneChange1Byte(0x3e, uint8_t(penvTime4SensComboBox.getSelectedItemIndex()));
        tone->tvpT1T4Velocity = uint8_t(penvTime1SensComboBox.getSelectedItemIndex() + (penvTime4SensComboBox.getSelectedItemIndex() << 4));
        break;
    case PitchEnvTimeKeyfollow:
        sendSysexPatchToneChange1Byte(0x3f, uint8_t(penvTimeKFSensComboBox.getSelectedItemIndex()));
        tone->tvpKFtvaTimeKF = uint8_t(pitchKFComboBox.getSelectedItemIndex() + (penvTimeKFSensComboBox.getSelectedItemIndex() << 4));
        break;
    case FilterMode:
        sendSysexPatchToneChange1Byte(0x49, uint8_t(filterModeComboBox.getSelectedItemIndex()));
        tone->tvfVeloCurveLpfHpf = uint8_t(fenvVelCurveComboBox.getSelectedItemIndex() + (filterModeComboBox.getSelectedItemIndex() << 3));
        break;
    case FilterResoMode:
        sendSysexPatchToneChange1Byte(0x4c, uint8_t(filterResoModeComboBox.getSelectedItemIndex()));
        tone->tvfResonance = uint8_t(filterResoSlider.getValue() + (filterResoModeComboBox.getSelectedItemIndex() << 7));
        break;
    case FilterKeyfollow:
        sendSysexPatchToneChange1Byte(0x4d, uint8_t(filterKFComboBox.getSelectedItemIndex()));
        tone->tvfTimeKFKeyfollow = uint8_t(filterKFComboBox.getSelectedItemIndex() + (fenvTimeKFSensComboBox.getSelectedItemIndex() << 4));
        break;
    case FilterVelCurve:
        sendSysexPatchToneChange1Byte(0x4e, uint8_t(fenvVelCurveComboBox.getSelectedItemIndex()));
        tone->tvfVeloCurveLpfHpf = uint8_t(fenvVelCurveComboBox.getSelectedItemIndex() + (filterModeComboBox.getSelectedItemIndex() << 3));
        break;
    case FilterEnvTime1Sense:
        sendSysexPatchToneChange1Byte(0x50, uint8_t(fenvTime1SensComboBox.getSelectedItemIndex()));
        tone->tvfT1T4Velocity = uint8_t(fenvTime1SensComboBox.getSelectedItemIndex() + (fenvTime4SensComboBox.getSelectedItemIndex() << 4));
        break;
    case FilterEnvTime4Sense:
        sendSysexPatchToneChange1Byte(0x51, uint8_t(fenvTime4SensComboBox.getSelectedItemIndex()));
        tone->tvfT1T4Velocity = uint8_t(fenvTime1SensComboBox.getSelectedItemIndex() + (fenvTime4SensComboBox.getSelectedItemIndex() << 4));
        break;
    case FilterEnvTimeKeyfollow:
        sendSysexPatchToneChange1Byte(0x52, uint8_t(fenvTimeKFSensComboBox.getSelectedItemIndex()));
        tone->tvfTimeKFKeyfollow = uint8_t(filterKFComboBox.getSelectedItemIndex() + (fenvTimeKFSensComboBox.getSelectedItemIndex() << 4));
        break;
    case LevelKeyfollow:
        sendSysexPatchToneChange1Byte(0x5d, uint8_t(levelKFComboBox.getSelectedItemIndex()));
        tone->tvaTimeKFDelayTimeKeyfollow = uint8_t(levelKFComboBox.getSelectedItemIndex() + (aenvTimeKFSensComboBox.getSelectedItemIndex() << 4));
        break;
    case PanKeyfollow:
        sendSysexPatchToneChange1Byte(0x60, uint8_t(panKFComboBox.getSelectedItemIndex()));
        tone->tvaPanKFpitchRandom = uint8_t(pitchRandomComboBox.getSelectedItemIndex() + (panKFComboBox.getSelectedItemIndex() << 4));
        break;
    case DelayMode:
        sendSysexPatchToneChange1Byte(0x61, uint8_t(toneDelayComboBox.getSelectedItemIndex()));
        tone->tvaDelayModeVeloCurve = uint8_t(aenvVelCurveComboBox.getSelectedItemIndex() + (toneDelayComboBox.getSelectedItemIndex() << 3) + (holdSwitchToggle.getToggleState() << 6) + (volumeSwitchToggle.getToggleState() << 7));
        break;
    case AmpVelCurve:
        sendSysexPatchToneChange1Byte(0x64, uint8_t(aenvVelCurveComboBox.getSelectedItemIndex()));
        tone->tvaDelayModeVeloCurve = uint8_t(aenvVelCurveComboBox.getSelectedItemIndex() + (toneDelayComboBox.getSelectedItemIndex() << 3) + (holdSwitchToggle.getToggleState() << 6) + (volumeSwitchToggle.getToggleState() << 7));
        break;
    case AmpEnvTime1Sense:
        sendSysexPatchToneChange1Byte(0x66, uint8_t(aenvTime1SensComboBox.getSelectedItemIndex()));
        tone->tvaT1T4Velocity = uint8_t(aenvTime1SensComboBox.getSelectedItemIndex() + (aenvTime4SensComboBox.getSelectedItemIndex() << 4));
        break;
    case AmpEnvTime4Sense:
        sendSysexPatchToneChange1Byte(0x67, uint8_t(aenvTime4SensComboBox.getSelectedItemIndex()));
        tone->tvaT1T4Velocity = uint8_t(aenvTime1SensComboBox.getSelectedItemIndex() + (aenvTime4SensComboBox.getSelectedItemIndex() << 4));
        break;
    case AmpEnvTimeKeyfollow:
        sendSysexPatchToneChange1Byte(0x68, uint8_t(aenvTimeKFSensComboBox.getSelectedItemIndex()));
        tone->tvaTimeKFDelayTimeKeyfollow = uint8_t(levelKFComboBox.getSelectedItemIndex() + (aenvTimeKFSensComboBox.getSelectedItemIndex() << 4));
        break;
    case Output:
        sendSysexPatchToneChange1Byte(0x73, uint8_t(outputComboBox.getSelectedItemIndex()));
        break;
    }
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

        if (checksum > 128) {
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

    buf[10] = (uint8_t)checksum;
    buf[11] = 0xf7;

    processor.mcuLock.enter();
    processor.mcu->postMidiSC55(buf, 12);
    processor.mcuLock.exit();
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

        if (checksum > 128) {
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

    buf[11] = (uint8_t)checksum;
    buf[12] = 0xf7;

    processor.mcuLock.enter();
    processor.mcu->postMidiSC55(buf, 13);
    processor.mcuLock.exit();
}