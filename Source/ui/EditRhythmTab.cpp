/*
  ==============================================================================

    EditRhythmTab.cpp
    Created: 20 Aug 2024 2:34:06pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#include <algorithm>
#include <JuceHeader.h>

#include "EditRhythmTab.h"

#include "../dataStructures.h"
#include "../PluginEditor.h"

//==============================================================================
EditRhythmTab::EditRhythmTab
(VirtualJVProcessor& p, VirtualJVEditor* e)
    : processor(p), editor(e)
{
    toneCount = 0;

    const std::array<std::string, 12> noteNames{ "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "Bb", "B" };

    addAndMakeVisible(selectKeyComboBox);
    selectKeyComboBox.addListener(this);

    for (uint8_t i = 36; i <= 96; i++)
    {
        if (i % 12 == 0 and i > 36)
        {
            selectKeyComboBox.getRootMenu()->addColumnBreak();
        }

        selectKeyComboBox.addItem(noteNames[i % 12] + std::to_string((i / 12) - 1) + " (" + std::to_string(i) + ")", i);
    }

    selectKeyComboBox.setSelectedItemIndex(0);

    addAndMakeVisible(toneLabel);
    toneLabel.attachToComponent(&selectKeyComboBox, true);

    addAndMakeVisible(waveGroupLabel);
    waveGroupLabel.attachToComponent(&waveGroupComboBox, true);

    addAndMakeVisible(waveGroupComboBox);
    waveGroupComboBox.addListener(this);
    waveGroupComboBox.addItem("Internal", 1);
    waveGroupComboBox.addItem("Expansion", 2);
    waveGroupComboBox.setSelectedItemIndex(0);

    addAndMakeVisible(waveformComboBox);
    waveformComboBox.addListener(this);

    addAndMakeVisible(waveformLabel);
    waveformLabel.attachToComponent(&waveformComboBox, true);

    addAndMakeVisible(toneSwitchToggle);
    toneSwitchToggle.addListener(this);

    addAndMakeVisible(muteGroupSlider);
    muteGroupSlider.addListener(this);
    muteGroupSlider.textFromValueFunction = [this](double value)
        {
            return value == 0 ? "Off" : std::to_string((int)value);
        };

    addAndMakeVisible(muteLabel);
    muteLabel.attachToComponent(&muteGroupSlider, true);

    addAndMakeVisible(envModeComboBox);
    envModeComboBox.addListener(this);
    envModeComboBox.addItem("Oneshot", 1);
    envModeComboBox.addItem("Sustain", 2);

    addAndMakeVisible(envModeLabel);
    envModeLabel.attachToComponent(&envModeComboBox, true);

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

    addAndMakeVisible(bendRangeSlider);
    bendRangeSlider.addListener(this);

    addAndMakeVisible(bendRangeLabel);
    bendRangeLabel.attachToComponent(&bendRangeSlider, true);

    addAndMakeVisible(penvLevSensSlider);
    penvLevSensSlider.addListener(this);

    addAndMakeVisible(penvLevSensLabel);
    penvLevSensLabel.attachToComponent(&penvLevSensSlider, true);

    addAndMakeVisible(penvTimeSensComboBox);
    penvTimeSensComboBox.addListener(this);
    addMenuEntriesFromArray(penvTimeSensComboBox, np100);

    addAndMakeVisible(penvTimeSensLabel);
    penvTimeSensLabel.attachToComponent(&penvTimeSensComboBox, true);

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

    addAndMakeVisible(fenvLevSensSlider);
    fenvLevSensSlider.addListener(this);

    addAndMakeVisible(fenvLevSensLabel);
    fenvLevSensLabel.attachToComponent(&fenvLevSensSlider, true);

    addAndMakeVisible(fenvTimeSensComboBox);
    fenvTimeSensComboBox.addListener(this);
    addMenuEntriesFromArray(fenvTimeSensComboBox, np100);

    addAndMakeVisible(fenvTimeSensLabel);
    fenvTimeSensLabel.attachToComponent(&fenvTimeSensComboBox, true);

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

    addAndMakeVisible(aenvLevSensSlider);
    aenvLevSensSlider.addListener(this);

    addAndMakeVisible(aenvLevSensLabel);
    aenvLevSensLabel.attachToComponent(&aenvLevSensSlider, true);

    addAndMakeVisible(aenvTimeSensComboBox);
    aenvTimeSensComboBox.addListener(this);
    addMenuEntriesFromArray(aenvTimeSensComboBox, np100);

    addAndMakeVisible(aenvTimeSensLabel);
    aenvTimeSensLabel.attachToComponent(&aenvTimeSensComboBox, true);

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

EditRhythmTab::~EditRhythmTab()
{
}

void EditRhythmTab::addMenuEntriesFromArray(Menu& m, const std::vector<std::string>& array)
{
    uint32_t idx = 1;

    for (auto e : array)
    {
        m.addItem(e, idx);
        idx++;
    }
}

void EditRhythmTab::updateWaveformComboBox(Menu& wfMenu)
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

        wfMenu.addItem(std::string{ std::to_string(i + 1) + ": " + names[i] }, i + 1);
    }

    if (priorSelection > -1)
    {
        const int newSelection = std::clamp(priorSelection, 0, wfMenu.getNumItems() - 1);

        wfMenu.setSelectedItemIndex(newSelection);
    }
}

void EditRhythmTab::updateValues()
{
    Rhythm* rhythm = (Rhythm*)processor.status.drums;
    RhythmTone tone = rhythm->tones[toneCount];

    toneSwitchToggle.setToggleState(((tone.flags >> 7) & 0x01) ? 1 : 0, juce::dontSendNotification);

    waveGroupComboBox.setSelectedItemIndex(tone.flags & 0x3, juce::dontSendNotification);
    waveformComboBox.setSelectedItemIndex(tone.waveNumber & 0xff, juce::dontSendNotification);

    updateWaveformComboBox(waveformComboBox);

    muteGroupSlider.setValue(int8_t(tone.muteGroup & 0x1f), juce::dontSendNotification);
    envModeComboBox.setSelectedItemIndex(((tone.muteGroup) >> 5) & 0x01, juce::dontSendNotification);

    pitchCoarseSlider.setValue(int8_t(tone.pitchCoarse) - 64, juce::dontSendNotification);
    pitchFineSlider.setValue(int8_t(tone.pitchFine), juce::dontSendNotification);
    pitchRandomComboBox.setSelectedItemIndex(tone.pitchRandom, juce::dontSendNotification);
    bendRangeSlider.setValue(tone.bendRange >> 4, juce::dontSendNotification);
    penvLevSensSlider.setValue(int8_t(tone.tvpVelocity), juce::dontSendNotification);
    penvTimeSensComboBox.setSelectedItemIndex(tone.bendRange & 0x0f, juce::dontSendNotification);
    penvDepthSlider.setValue(int8_t(tone.tvpEnvDepth), juce::dontSendNotification);
    penv1TimeSlider.setValue(int8_t(tone.tvpEnvTime1), juce::dontSendNotification);
    penv1LevelSlider.setValue(int8_t(tone.tvpEnvLevel1), juce::dontSendNotification);
    penv2TimeSlider.setValue(int8_t(tone.tvpEnvTime2), juce::dontSendNotification);
    penv2LevelSlider.setValue(int8_t(tone.tvpEnvLevel2), juce::dontSendNotification);
    penv3TimeSlider.setValue(int8_t(tone.tvpEnvTime3), juce::dontSendNotification);
    penv3LevelSlider.setValue(int8_t(tone.tvpEnvLevel3), juce::dontSendNotification);
    penv4TimeSlider.setValue(int8_t(tone.tvpEnvTime4), juce::dontSendNotification);
    penv4LevelSlider.setValue(int8_t(tone.tvpEnvLevel4), juce::dontSendNotification);

    filterModeComboBox.setSelectedItemIndex((tone.tvfTimeVelLpfHpf & 0x30) >> 4, juce::dontSendNotification);
    filterCutoffSlider.setValue(int8_t(tone.tvfCutoff), juce::dontSendNotification);
    filterResoSlider.setValue(int8_t(tone.tvfResonance), juce::dontSendNotification);
    filterResoModeComboBox.setSelectedItemIndex((tone.tvfResonance & 0x80) >> 7, juce::dontSendNotification);
    fenvLevSensSlider.setValue(int8_t(tone.tvfVelocity), juce::dontSendNotification);
    fenvTimeSensComboBox.setSelectedItemIndex((tone.tvfTimeVelLpfHpf & 0xf), juce::dontSendNotification);
    fenvDepthSlider.setValue(int8_t(tone.tvfEnvDepth), juce::dontSendNotification);
    fenv1TimeSlider.setValue(int8_t(tone.tvfEnvTime1), juce::dontSendNotification);
    fenv1LevelSlider.setValue(int8_t(tone.tvfEnvLevel1), juce::dontSendNotification);
    fenv2TimeSlider.setValue(int8_t(tone.tvfEnvTime2), juce::dontSendNotification);
    fenv2LevelSlider.setValue(int8_t(tone.tvfEnvLevel2), juce::dontSendNotification);
    fenv3TimeSlider.setValue(int8_t(tone.tvfEnvTime3), juce::dontSendNotification);
    fenv3LevelSlider.setValue(int8_t(tone.tvfEnvLevel3), juce::dontSendNotification);
    fenv4TimeSlider.setValue(int8_t(tone.tvfEnvTime4), juce::dontSendNotification);
    fenv4LevelSlider.setValue(int8_t(tone.tvfEnvLevel4), juce::dontSendNotification);

    levelSlider.setValue(int8_t(tone.tvaLevel), juce::dontSendNotification);
    panSlider.setValue(int8_t(tone.tvaPan - 64), juce::dontSendNotification);

    aenvLevSensSlider.setValue(int8_t(tone.tvaVelocity), juce::dontSendNotification);
    aenvTimeSensComboBox.setSelectedItemIndex((tone.tvaTimeVelocity & 0x0f), juce::dontSendNotification);
    aenv1TimeSlider.setValue(int8_t(tone.tvaEnvTime1 & 0x7f), juce::dontSendNotification);
    aenv1LevelSlider.setValue(int8_t(tone.tvaEnvLevel1 & 0x7f), juce::dontSendNotification);
    aenv2TimeSlider.setValue(int8_t(tone.tvaEnvTime2), juce::dontSendNotification);
    aenv2LevelSlider.setValue(int8_t(tone.tvaEnvLevel2), juce::dontSendNotification);
    aenv3TimeSlider.setValue(int8_t(tone.tvaEnvTime3), juce::dontSendNotification);
    aenv3LevelSlider.setValue(int8_t(tone.tvaEnvLevel3), juce::dontSendNotification);
    aenv4TimeSlider.setValue(int8_t(tone.tvaEnvTime4), juce::dontSendNotification);

    drySlider.setValue(int8_t(tone.drySend), juce::dontSendNotification);
    reverbSlider.setValue(int8_t(tone.reverbSend), juce::dontSendNotification);
    chorusSlider.setValue(int8_t(tone.chorusSend), juce::dontSendNotification);
}

void EditRhythmTab::resized()
{
    const auto top = 10;
    const auto sliderLeft1 = 100;
    const auto width = getWidth() / 3 - sliderLeft1 - 10;
    const auto halfWidth = width / 2;
    const auto thirdWidth = width / 3;
    const auto sliderLeft2 = sliderLeft1 + getWidth() / 3 + 2;
    const auto sliderLeft3 = sliderLeft2 + getWidth() / 3;
    const auto height = 24;
    const auto vMargin = 24;

    toneSwitchToggle.setBounds(sliderLeft1 - 90, top + height * 0 + vMargin * 0, width, height);
    selectKeyComboBox.setBounds(sliderLeft1 + thirdWidth, top + height * 0 + vMargin * 0, thirdWidth * 2, height);

    waveGroupComboBox.setBounds(sliderLeft1, top + height * 1 + vMargin * 1, width, height);
    waveformComboBox.setBounds(sliderLeft1, top + height * 2 + vMargin * 1, width, height);

    bendRangeSlider.setBounds(sliderLeft2, top + height * 0 + vMargin * 0, width, height);
    pitchCoarseSlider.setBounds(sliderLeft2, top + height * 1 + vMargin * 0, width, height);
    pitchFineSlider.setBounds(sliderLeft2, top + height * 2 + vMargin * 0, width, height);
    pitchRandomComboBox.setBounds(sliderLeft2, top + height * 3 + vMargin * 0, width, height);
    penvLevSensSlider.setBounds(sliderLeft2, top + height * 4 + vMargin * 0, width, height);
    penvTimeSensComboBox.setBounds(sliderLeft2, top + height * 5 + vMargin * 0, width, height);

    penvDepthSlider.setBounds(sliderLeft2, top + height * 6 + vMargin * 0, width, height);
    penv1TimeSlider.setBounds(sliderLeft2, top + height * 7 + vMargin * 0, halfWidth, height);
    penv1LevelSlider.setBounds(sliderLeft2 + halfWidth, top + height * 7 + vMargin * 0, halfWidth, height);
    penv2TimeSlider.setBounds(sliderLeft2, top + height * 8 + vMargin * 0, halfWidth, height);
    penv2LevelSlider.setBounds(sliderLeft2 + halfWidth, top + height * 8 + vMargin * 0, halfWidth, height);
    penv3TimeSlider.setBounds(sliderLeft2, top + height * 9 + vMargin * 0, halfWidth, height);
    penv3LevelSlider.setBounds(sliderLeft2 + halfWidth, top + height * 9 + vMargin * 0, halfWidth, height);
    penv4TimeSlider.setBounds(sliderLeft2, top + height * 10 + vMargin * 0, halfWidth, height);
    penv4LevelSlider.setBounds(sliderLeft2 + halfWidth, top + height * 10 + vMargin * 0, halfWidth, height);

    muteGroupSlider.setBounds(sliderLeft1, top + height * 3 + vMargin * 2, width, height);
    envModeComboBox.setBounds(sliderLeft1, top + height * 4 + vMargin * 2, width, height);
    levelSlider.setBounds(sliderLeft1, top + height * 5 + vMargin * 2, width, height);
    panSlider.setBounds(sliderLeft1, top + height * 6 + vMargin * 2, width, height);
    aenvLevSensSlider.setBounds(sliderLeft1, top + height * 7 + vMargin * 2, width, height);
    aenvTimeSensComboBox.setBounds(sliderLeft1, top + height * 8 + vMargin * 2, width, height);
    aenv1TimeSlider.setBounds(sliderLeft1, top + height * 9 + vMargin * 2, halfWidth, height);
    aenv1LevelSlider.setBounds(sliderLeft1 + halfWidth, top + height * 9 + vMargin * 2, halfWidth, height);
    aenv2TimeSlider.setBounds(sliderLeft1, top + height * 10 + vMargin * 2, halfWidth, height);
    aenv2LevelSlider.setBounds(sliderLeft1 + halfWidth, top + height * 10 + vMargin * 2, halfWidth, height);
    aenv3TimeSlider.setBounds(sliderLeft1, top + height * 11 + vMargin * 2, halfWidth, height);
    aenv3LevelSlider.setBounds(sliderLeft1 + halfWidth, top + height * 11 + vMargin * 2, halfWidth, height);
    aenv4TimeSlider.setBounds(sliderLeft1, top + height * 12 + vMargin * 2, halfWidth, height);

    filterModeComboBox.setBounds(sliderLeft3, top + height * 0 + vMargin * 0, width, height);
    filterCutoffSlider.setBounds(sliderLeft3, top + height * 1 + vMargin * 0, width, height);
    filterResoSlider.setBounds(sliderLeft3, top + height * 2 + vMargin * 0, halfWidth, height);
    filterResoModeComboBox.setBounds(sliderLeft3 + halfWidth, top + height * 2 + vMargin * 0, halfWidth, height);
    fenvLevSensSlider.setBounds(sliderLeft3, top + height * 3 + vMargin * 0, width, height);
    fenvTimeSensComboBox.setBounds(sliderLeft3, top + height * 4 + vMargin * 0, width, height);
    fenvDepthSlider.setBounds(sliderLeft3, top + height * 5 + vMargin * 0, width, height);
    fenv1TimeSlider.setBounds(sliderLeft3, top + height * 6 + vMargin * 0, halfWidth, height);
    fenv1LevelSlider.setBounds(sliderLeft3 + halfWidth, top + height * 6 + vMargin * 0, halfWidth, height);
    fenv2TimeSlider.setBounds(sliderLeft3, top + height * 7 + vMargin * 0, halfWidth, height);
    fenv2LevelSlider.setBounds(sliderLeft3 + halfWidth, top + height * 7 + vMargin * 0, halfWidth, height);
    fenv3TimeSlider.setBounds(sliderLeft3, top + height * 8 + vMargin * 0, halfWidth, height);
    fenv3LevelSlider.setBounds(sliderLeft3 + halfWidth, top + height * 8 + vMargin * 0, halfWidth, height);
    fenv4TimeSlider.setBounds(sliderLeft3, top + height * 9 + vMargin * 0, halfWidth, height);
    fenv4LevelSlider.setBounds(sliderLeft3 + halfWidth, top + height * 9 + vMargin * 0, halfWidth, height);

    drySlider.setBounds(sliderLeft3, top + height * 10 + vMargin * 1, width, height);
    reverbSlider.setBounds(sliderLeft3, top + height * 11 + vMargin * 1, width, height);
    chorusSlider.setBounds(sliderLeft3, top + height * 12 + vMargin * 1, width, height);
    outputComboBox.setBounds(sliderLeft3, top + height * 13 + vMargin * 1, width, height);
}

void EditRhythmTab::sliderValueChanged(juce::Slider* slider)
{
    uint32_t id = 0xFFFFFFF;

    if (auto i = dynamic_cast<Slider*>(slider))
    {
        id = i->getID();
    }

    Rhythm* rhythm = (Rhythm*)processor.status.drums;
    RhythmTone* tone = &rhythm->tones[toneCount];

    switch (id)
    {
    case Waveform:
        sendSysexPatchRhythmChange2Byte(0x01, uint8_t(waveformComboBox.getSelectedItemIndex()));
        tone->waveNumber = uint8_t(waveformComboBox.getSelectedItemIndex());
        break;
    case MuteGroup:
        sendSysexPatchRhythmChange1Byte(0x05, uint8_t(muteGroupSlider.getValue()));
        tone->muteGroup = uint8_t((uint8_t(muteGroupSlider.getValue()) << 0) + (envModeComboBox.getSelectedItemIndex() << 5));
        break;
    case PitchCoarse:
        sendSysexPatchRhythmChange1Byte(0x04, uint8_t(pitchCoarseSlider.getValue() + 64));
        tone->pitchCoarse = uint8_t(pitchCoarseSlider.getValue() + 64);
        break;
    case PitchFine:
        sendSysexPatchRhythmChange1Byte(0x07, uint8_t(pitchFineSlider.getValue() + 64));
        tone->pitchFine = uint8_t(pitchFineSlider.getValue());
        break;
    case BendRange:
        sendSysexPatchRhythmChange1Byte(0x09, uint8_t(bendRangeSlider.getValue()));
        tone->bendRange = uint8_t(penvTimeSensComboBox.getSelectedItemIndex() + (uint8_t(bendRangeSlider.getValue()) << 4));
        break;
    case PitchEnvLevelSense:
        sendSysexPatchRhythmChange1Byte(0x0a, uint8_t(penvLevSensSlider.getValue() + 64));
        tone->tvpVelocity = uint8_t(penvLevSensSlider.getValue());
        break;
    case PitchEnvDepth:
        sendSysexPatchRhythmChange1Byte(0x0c, uint8_t(penvDepthSlider.getValue() + 64));
        tone->tvpEnvDepth = uint8_t(penvDepthSlider.getValue());
        break;
    case PitchEnvTime1:
        sendSysexPatchRhythmChange1Byte(0x0d, uint8_t(penv1TimeSlider.getValue()));
        tone->tvpEnvTime1 = uint8_t(penv1TimeSlider.getValue());
        break;
    case PitchEnvLevel1:
        sendSysexPatchRhythmChange1Byte(0x0e, uint8_t(penv1LevelSlider.getValue() + 64));
        tone->tvpEnvLevel1 = uint8_t(penv1LevelSlider.getValue());
        break;
    case PitchEnvTime2:
        sendSysexPatchRhythmChange1Byte(0x0f, uint8_t(penv2TimeSlider.getValue()));
        tone->tvpEnvTime2 = uint8_t(penv2TimeSlider.getValue());
        break;
    case PitchEnvLevel2:
        sendSysexPatchRhythmChange1Byte(0x10, uint8_t(penv2LevelSlider.getValue() + 64));
        tone->tvpEnvLevel2 = uint8_t(penv2LevelSlider.getValue());
        break;
    case PitchEnvTime3:
        sendSysexPatchRhythmChange1Byte(0x11, uint8_t(penv3TimeSlider.getValue()));
        tone->tvpEnvTime3 = uint8_t(penv3TimeSlider.getValue());
        break;
    case PitchEnvLevel3:
        sendSysexPatchRhythmChange1Byte(0x12, uint8_t(penv3LevelSlider.getValue() + 64));
        tone->tvpEnvLevel3 = uint8_t(penv3LevelSlider.getValue());
        break;
    case PitchEnvTime4:
        sendSysexPatchRhythmChange1Byte(0x13, uint8_t(penv4TimeSlider.getValue()));
        tone->tvpEnvTime4 = uint8_t(penv4TimeSlider.getValue());
        break;
    case PitchEnvLevel4:
        sendSysexPatchRhythmChange1Byte(0x14, uint8_t(penv4LevelSlider.getValue() + 64));
        tone->tvpEnvLevel4 = uint8_t(penv4LevelSlider.getValue());
        break;
    case FilterCutoff:
        sendSysexPatchRhythmChange1Byte(0x16, uint8_t(filterCutoffSlider.getValue()));
        tone->tvfCutoff = uint8_t(filterCutoffSlider.getValue());
        break;
    case FilterReso:
        sendSysexPatchRhythmChange1Byte(0x17, uint8_t(filterResoSlider.getValue()));
        tone->tvfResonance = uint8_t(filterResoSlider.getValue() + (filterResoModeComboBox.getSelectedItemIndex() << 7));
        break;
    case FilterEnvLevelSense:
        sendSysexPatchRhythmChange1Byte(0x19, uint8_t(fenvLevSensSlider.getValue() + 64));
        tone->tvfVelocity = uint8_t(fenvLevSensSlider.getValue());
        break;
    case FilterEnvDepth:
        sendSysexPatchRhythmChange1Byte(0x1b, uint8_t(fenvDepthSlider.getValue() + 64));
        tone->tvfEnvDepth = uint8_t(fenvDepthSlider.getValue());
        break;
    case FilterEnvTime1:
        sendSysexPatchRhythmChange1Byte(0x1c, uint8_t(fenv1TimeSlider.getValue()));
        tone->tvfEnvTime1 = uint8_t(fenv1TimeSlider.getValue());
        break;
    case FilterEnvLevel1:
        sendSysexPatchRhythmChange1Byte(0x1d, uint8_t(fenv1LevelSlider.getValue()));
        tone->tvfEnvLevel1 = uint8_t(fenv1LevelSlider.getValue());
        break;
    case FilterEnvTime2:
        sendSysexPatchRhythmChange1Byte(0x1e, uint8_t(fenv2TimeSlider.getValue()));
        tone->tvfEnvTime2 = uint8_t(fenv2TimeSlider.getValue());
        break;
    case FilterEnvLevel2:
        sendSysexPatchRhythmChange1Byte(0x1f, uint8_t(fenv2LevelSlider.getValue()));
        tone->tvfEnvLevel2 = uint8_t(fenv2LevelSlider.getValue());
        break;
    case FilterEnvTime3:
        sendSysexPatchRhythmChange1Byte(0x20, uint8_t(fenv3TimeSlider.getValue()));
        tone->tvfEnvTime3 = uint8_t(fenv3TimeSlider.getValue());
        break;
    case FilterEnvLevel3:
        sendSysexPatchRhythmChange1Byte(0x21, uint8_t(fenv3LevelSlider.getValue()));
        tone->tvfEnvLevel3 = uint8_t(fenv3LevelSlider.getValue());
        break;
    case FilterEnvTime4:
        sendSysexPatchRhythmChange1Byte(0x22, uint8_t(fenv4TimeSlider.getValue()));
        tone->tvfEnvTime4 = uint8_t(fenv4TimeSlider.getValue());
        break;
    case FilterEnvLevel4:
        sendSysexPatchRhythmChange1Byte(0x23, uint8_t(fenv4LevelSlider.getValue()));
        tone->tvfEnvLevel4 = uint8_t(fenv4LevelSlider.getValue());
        break;
    case Level:
        sendSysexPatchRhythmChange1Byte(0x24, uint8_t(levelSlider.getValue()));
        tone->tvaLevel = uint8_t(levelSlider.getValue());
        break;
    case Pan:
        sendSysexPatchRhythmChange2Byte(0x25, uint8_t(panSlider.getValue() + 64));
        tone->tvaPan = uint8_t(panSlider.getValue() + 64);
        break;
    case AmpEnvLevelSense:
        sendSysexPatchRhythmChange1Byte(0x27, uint8_t(aenvLevSensSlider.getValue() + 64));
        tone->tvaVelocity = uint8_t(aenvLevSensSlider.getValue());
        break;
    case AmpEnvTime1:
        sendSysexPatchRhythmChange1Byte(0x29, uint8_t(aenv1TimeSlider.getValue()));
        tone->tvaEnvTime1 = uint8_t(aenv1TimeSlider.getValue());
        break;
    case AmpEnvLevel1:
        sendSysexPatchRhythmChange1Byte(0x2a, uint8_t(aenv1LevelSlider.getValue()));
        tone->tvaEnvLevel1 = uint8_t(aenv1LevelSlider.getValue());
        break;
    case AmpEnvTime2:
        sendSysexPatchRhythmChange1Byte(0x2b, uint8_t(aenv2TimeSlider.getValue()));
        tone->tvaEnvTime2 = uint8_t(aenv2TimeSlider.getValue());
        break;
    case AmpEnvLevel2:
        sendSysexPatchRhythmChange1Byte(0x2c, uint8_t(aenv2LevelSlider.getValue()));
        tone->tvaEnvLevel2 = uint8_t(aenv2LevelSlider.getValue());
        break;
    case AmpEnvTime3:
        sendSysexPatchRhythmChange1Byte(0x2d, uint8_t(aenv3TimeSlider.getValue()));
        tone->tvaEnvTime3 = uint8_t(aenv3TimeSlider.getValue());
        break;
    case AmpEnvLevel3:
        sendSysexPatchRhythmChange1Byte(0x2e, uint8_t(aenv3LevelSlider.getValue()));
        tone->tvaEnvLevel3 = uint8_t(aenv3LevelSlider.getValue());
        break;
    case AmpEnvTime4:
        sendSysexPatchRhythmChange1Byte(0x2f, uint8_t(aenv4TimeSlider.getValue()));
        tone->tvaEnvTime4 = uint8_t(aenv4TimeSlider.getValue());
        break;
    case DrySend:
        sendSysexPatchRhythmChange1Byte(0x30, uint8_t(drySlider.getValue()));
        tone->drySend = uint8_t(drySlider.getValue());
        break;
    case ReverbSend:
        sendSysexPatchRhythmChange1Byte(0x31, uint8_t(reverbSlider.getValue()));
        tone->reverbSend = uint8_t(reverbSlider.getValue());
        break;
    case ChorusSend:
        sendSysexPatchRhythmChange1Byte(0x32, uint8_t(chorusSlider.getValue()));
        tone->chorusSend = uint8_t(chorusSlider.getValue());
        break;
    default:
        break;
    }
}

void EditRhythmTab::buttonClicked(juce::Button* button)
{
    uint32_t id = 0xFFFFFFF;

    if (auto i = dynamic_cast<Button*>(button))
    {
        id = i->getID();
    }

    Rhythm* rhythm = (Rhythm*)processor.status.drums;
    RhythmTone* tone = &rhythm->tones[toneCount];

    switch (id)
    {
    case ToneSwitch:
        sendSysexPatchRhythmChange1Byte(0x03, toneSwitchToggle.getToggleStateValue() == 1 ? 0x01 : 0x00);
        tone->flags = uint8_t(waveGroupComboBox.getSelectedItemIndex() + (toneSwitchToggle.getToggleState() << 7));
        break;
    default:
        break;
    }
}

void EditRhythmTab::comboBoxChanged(juce::ComboBox* comboBox)
{
    uint32_t id = 0xFFFFFFF;

    if (auto i = dynamic_cast<Menu*>(comboBox))
    {
        id = i->getID();
    }

    Rhythm* rhythm = (Rhythm*)processor.status.drums;
    RhythmTone* tone = &rhythm->tones[toneCount];

    switch (id)
    {
    case SelectKey:
        toneCount = uint8_t(selectKeyComboBox.getSelectedItemIndex());
        updateValues();
        break;
    case WaveGroup:
        updateWaveformComboBox(waveformComboBox);
        sendSysexPatchRhythmChange1Byte(0x00, uint8_t(waveGroupComboBox.getSelectedItemIndex()));
        tone->flags = uint8_t(waveGroupComboBox.getSelectedItemIndex() + (toneSwitchToggle.getToggleState() << 7));
        break;
    case Waveform:
        sendSysexPatchRhythmChange2Byte(0x01, uint8_t(waveformComboBox.getSelectedItemIndex()));
        tone->waveNumber = uint8_t(waveformComboBox.getSelectedItemIndex());
        break;
    case EnvMode:
        sendSysexPatchRhythmChange1Byte(0x06, uint8_t(envModeComboBox.getSelectedItemIndex()));
        tone->muteGroup = uint8_t((uint8_t(muteGroupSlider.getValue()) << 0) + (envModeComboBox.getSelectedItemIndex() << 5));
        break;
    case PitchRandom:
        sendSysexPatchRhythmChange1Byte(0x08, uint8_t(pitchRandomComboBox.getSelectedItemIndex()));
        tone->pitchRandom = uint8_t(pitchRandomComboBox.getSelectedItemIndex());
        break;
    case PitchEnvTimeSense:
        sendSysexPatchRhythmChange1Byte(0x0b, uint8_t(penvTimeSensComboBox.getSelectedItemIndex()));
        tone->bendRange = uint8_t(penvTimeSensComboBox.getSelectedItemIndex() + (uint8_t(bendRangeSlider.getValue()) << 4));
        break;
    case FilterMode:
        sendSysexPatchRhythmChange1Byte(0x15, uint8_t(filterModeComboBox.getSelectedItemIndex()));
        tone->tvfTimeVelLpfHpf = uint8_t(fenvTimeSensComboBox.getSelectedItemIndex() + (filterModeComboBox.getSelectedItemIndex() << 4));
        break;
    case FilterResoMode:
        sendSysexPatchRhythmChange1Byte(0x18, uint8_t(filterResoModeComboBox.getSelectedItemIndex()));
        tone->tvfResonance = uint8_t(filterResoSlider.getValue() + (filterResoModeComboBox.getSelectedItemIndex() << 7));
        break;
    case FilterEnvTimeSense:
        sendSysexPatchRhythmChange1Byte(0x1a, uint8_t(fenvTimeSensComboBox.getSelectedItemIndex()));
        tone->tvfTimeVelLpfHpf = uint8_t(fenvTimeSensComboBox.getSelectedItemIndex() + (filterModeComboBox.getSelectedItemIndex() << 4));
        break;
    case AmpEnvTimeSense:
        sendSysexPatchRhythmChange1Byte(0x28, uint8_t(aenvTimeSensComboBox.getSelectedItemIndex()));
        tone->tvaTimeVelocity = uint8_t(aenvTimeSensComboBox.getSelectedItemIndex());
        break;
    case Output:
        sendSysexPatchRhythmChange1Byte(0x33, uint8_t(outputComboBox.getSelectedItemIndex()));
        break;
    default:
        break;
    }
}

void EditRhythmTab::sendSysexPatchRhythmChange1Byte(uint8_t address, uint8_t value)
{
    uint8_t data[5];
    data[0] = 0x00;              // address MSB
    data[1] = 0x07;              // address
    data[2] = 0x40 + toneCount;  // address
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

void EditRhythmTab::sendSysexPatchRhythmChange2Byte(uint8_t address, uint8_t value)
{
    uint8_t data[6];
    data[0] = 0x00;                 // address MSB
    data[1] = 0x07;                 // address
    data[2] = 0x40 + toneCount;     // address
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

