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
        toneSelect = 300U,
        waveGroup = 301U,
        waveform = 302U,
        toneSwitch = 303U,
        mute = 304U,
        envMode = 305U,
        bendRange = 306U,

        pitchCoarse = 310U,
        pitchFine = 311U,
        pitchRandom = 312U,
        DelayFeedback = 313U,
        penvLevSens = 314U,
        penvTimeSens = 315U,
        penvDepth = 316U,

        penv1Time = 320U,
        penv1Level = 321U,
        penv2Time = 322U,
        penv2Level = 323U,
        penv3Time = 324U,
        penv3Level = 325U,
        penv4Time = 326U,
        penv4Level = 327U,

        filterMode = 330U,
        filterCutoff = 331U,
        filterReso = 332U,
        filterResoMode = 333U,
        fenvLevSens = 334U,
        fenvTimeSens = 335U,
        fenvDepth = 336U,

        fenv1Time = 340U,
        fenv1Level = 341U,
        fenv2Time = 342U,
        fenv2Level = 343U,
        fenv3Time = 344U,
        fenv3Level = 345U,
        fenv4Time = 346U,
        fenv4Level = 347U,

        level = 350U,
        pan = 351U,
        aenvLevSens = 352U,
        aenvTimeSens = 353U,

        aenv1Time = 360U,
        aenv1Level = 361U,
        aenv2Time = 362U,
        aenv2Level = 363U,
        aenv3Time = 364U,
        aenv3Level = 365U,
        aenv4Time = 366U,

        dry = 370U,
        reverb = 371U,
        chorus = 372U,
        output = 373U
    };

    void addMenuEntriesFromArray(Menu& menu, const std::vector<std::string>& array);
    void updateWaveformComboBox(Menu& wfMenu);

    VirtualJVProcessor& processor;
    VirtualJVEditor* editor;
    Menu selectKeyComboBox{ toneSelect };
    juce::Label toneLabel;
    uint8_t toneCount;

    Menu waveGroupComboBox{ waveGroup };
    juce::Label waveGroupLabel;
    Menu waveformComboBox{ waveform };
    juce::Label waveformLabel;
    Button toneSwitchToggle{ toneSwitch , "Enable" };
    juce::Label toneSwitchLabel;

    Slider muteSlider{ mute, 0, 31, 1 };
    juce::Label muteLabel;
    Menu envModeComboBox{ envMode };
    juce::Label envModeLabel;
    Slider bendRangeSlider{ bendRange, 0, 12, 1 };
    juce::Label bendRangeLabel;

    Slider pitchCoarseSlider{ pitchCoarse, -48, 48, 1 };
    juce::Label pitchCoarseLabel;
    Slider pitchFineSlider{ pitchFine, -50, 50, 1 };
    juce::Label pitchFineLabel;
    Menu pitchRandomComboBox{ pitchRandom };
    juce::Label pitchRandomLabel;
    Slider penvLevSensSlider{ penvLevSens, -12, 12, 1 };
    juce::Label penvLevSensLabel;
    Menu penvTimeSensComboBox{ penvTimeSens };
    juce::Label penvTimeSensLabel;
    Slider penvDepthSlider{ penvDepth, -12, 12, 1 };
    juce::Label penvDepthLabel;
    Slider penv1TimeSlider{ penv1Time, 0, 127, 1 };
    juce::Label penv1TimeLabel;
    Slider penv1LevelSlider{ penv1Level, -63, 63, 1 };
    juce::Label penv1LevelLabel;
    Slider penv2TimeSlider{ penv2Time, 0, 127, 1 };
    juce::Label penv2TimeLabel;
    Slider penv2LevelSlider{ penv2Level, -63, 63, 1 };
    juce::Label penv2LevelLabel;
    Slider penv3TimeSlider{ penv3Time, 0, 127, 1 };
    juce::Label penv3TimeLabel;
    Slider penv3LevelSlider{ penv3Level, -63, 63, 1 };
    juce::Label penv3LevelLabel;
    Slider penv4TimeSlider{ penv4Time, 0, 127, 1 };
    juce::Label penv4TimeLabel;
    Slider penv4LevelSlider{ penv4Level, -63, 63, 1 };
    juce::Label penv4LevelLabel;

    Menu filterModeComboBox{ filterMode };
    juce::Label filterModeLabel;
    Slider filterCutoffSlider{ filterCutoff, 0, 127, 1 };
    juce::Label filterCutoffLabel;
    Slider filterResoSlider{ filterReso, 0, 127, 1 };
    juce::Label filterResoLabel;
    Menu filterResoModeComboBox{ filterReso };
    Slider fenvLevSensSlider{ fenvLevSens, -63, 63, 1 };
    juce::Label fenvLevSensLabel;
    Menu fenvTimeSensComboBox{ fenvTimeSens };
    juce::Label fenvTimeSensLabel;
    Slider fenvDepthSlider{ fenvDepth, 0, 127, 1 };
    juce::Label fenvDepthLabel;
    Slider fenv1TimeSlider{ fenv1Time, 0, 127, 1 };
    juce::Label fenv1TimeLabel;
    Slider fenv1LevelSlider{ fenv1Level, 0, 127, 1 };
    juce::Label fenv1LevelLabel;
    Slider fenv2TimeSlider{ fenv2Time, 0, 127, 1 };
    juce::Label fenv2TimeLabel;
    Slider fenv2LevelSlider{ fenv2Level, 0, 127, 1 };
    juce::Label fenv2LevelLabel;
    Slider fenv3TimeSlider{ fenv3Time, 0, 127, 1 };
    juce::Label fenv3TimeLabel;
    Slider fenv3LevelSlider{ fenv3Level, 0, 127, 1 };
    juce::Label fenv3LevelLabel;
    Slider fenv4TimeSlider{ fenv4Time, 0, 127, 1 };
    juce::Label fenv4TimeLabel;
    Slider fenv4LevelSlider{ fenv4Level, 0, 127, 1 };
    juce::Label fenv4LevelLabel;

    Slider levelSlider{ level, 0, 127, 1 };
    juce::Label levelLabel;
    Slider panSlider{ pan, -64, 64, 1 };
    juce::Label panLabel;
    Slider aenvLevSensSlider{ aenvLevSens, -63, 63, 1 };
    juce::Label aenvLevSensLabel;
    Menu aenvTimeSensComboBox{ aenvTimeSens };
    juce::Label aenvTimeSensLabel;
    Slider aenv1TimeSlider{ aenv1Time, 0, 127, 1 };
    juce::Label aenv1TimeLabel;
    Slider aenv1LevelSlider{ aenv1Level, 0, 127, 1 };
    juce::Label aenv1LevelLabel;
    Slider aenv2TimeSlider{ aenv2Time, 0, 127, 1 };
    juce::Label aenv2TimeLabel;
    Slider aenv2LevelSlider{ aenv2Level, 0, 127, 1 };
    juce::Label aenv2LevelLabel;
    Slider aenv3TimeSlider{ aenv3Time, 0, 127, 1 };
    juce::Label aenv3TimeLabel;
    Slider aenv3LevelSlider{ aenv3Level, 0, 127, 1 };
    juce::Label aenv3LevelLabel;
    Slider aenv4TimeSlider{ aenv4Time, 0, 127, 1 };
    juce::Label aenv4TimeLabel;

    Slider drySlider{ dry, 0, 127, 1 };
    juce::Label dryLabel;
    Slider reverbSlider{ reverb, 0, 127, 1 };
    juce::Label reverbLabel;
    Slider chorusSlider{ chorus, 0, 127, 1 };
    juce::Label chorusLabel;
    Menu outputComboBox{ output };
    juce::Label outputLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditRhythmTab)
};

