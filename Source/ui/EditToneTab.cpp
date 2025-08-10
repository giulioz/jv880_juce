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
EditToneTab::EditToneTab(Jv880_juceAudioProcessor& p, uint8_t toneIn) : audioProcessor (p), toneCount(toneIn)
{
    addAndMakeVisible(waveGroupLabel);
    waveGroupLabel.setText ("Wave Group", juce::dontSendNotification);
    waveGroupLabel.attachToComponent (&waveGroupComboBox, true);
    addAndMakeVisible (waveGroupComboBox);
    waveGroupComboBox.addListener (this);
    waveGroupComboBox.addItem ("Internal", 1);
    waveGroupComboBox.addItem ("Expansion", 2);
    
    addAndMakeVisible (waveformSlider);
    waveformSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    waveformSlider.setRange (1, 255, 1);
    waveformSlider.addListener (this);
    addAndMakeVisible (waveformLabel);
    waveformLabel.setText ("Waveform", juce::dontSendNotification);
    waveformLabel.attachToComponent (&waveformSlider, true);
    
    addAndMakeVisible (toneSwitchToggle);
    toneSwitchToggle.addListener (this);
    toneSwitchToggle.setButtonText ("Tone Switch");
    
    addAndMakeVisible (FXMSwitchToggle);
    FXMSwitchToggle.addListener (this);
    FXMSwitchToggle.setButtonText ("FXM Switch");
    
    addAndMakeVisible (FXMDepthSlider);
    FXMDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    FXMDepthSlider.setRange (1, 16, 1);
    FXMDepthSlider.addListener (this);
    addAndMakeVisible (FXMDepthLabel);
    FXMDepthLabel.setText ("FXM Depth", juce::dontSendNotification);
    FXMDepthLabel.attachToComponent (&FXMDepthSlider, true);
    
    addAndMakeVisible (velRangeLowSlider);
    velRangeLowSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    velRangeLowSlider.setRange (0, 127, 1);
    velRangeLowSlider.addListener (this);
    addAndMakeVisible (velRangeLowLabel);
    velRangeLowLabel.setText ("Range Low", juce::dontSendNotification);
    velRangeLowLabel.attachToComponent (&velRangeLowSlider, true);
    
    addAndMakeVisible (velRangeHighSlider);
    velRangeHighSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    velRangeHighSlider.setRange (0, 127, 1);
    velRangeHighSlider.addListener (this);
    addAndMakeVisible (velRangeHighLabel);
    velRangeHighLabel.setText ("Range High", juce::dontSendNotification);
    velRangeHighLabel.attachToComponent (&velRangeHighSlider, true);
    
    addAndMakeVisible (volumeSwitchToggle);
    volumeSwitchToggle.addListener (this);
    volumeSwitchToggle.setButtonText ("Volume Switch");
    
    addAndMakeVisible (holdSwitchToggle);
    holdSwitchToggle.addListener (this);
    holdSwitchToggle.setButtonText ("Hold-1 Switch");
    
    addAndMakeVisible(modDestALabel);
    modDestALabel.setText ("Mod 1", juce::dontSendNotification);
    modDestALabel.attachToComponent (&modDestAComboBox, true);
    addAndMakeVisible (modDestAComboBox);
    modDestAComboBox.addListener (this);
    modDestAComboBox.addItem ("Off", 1);
    modDestAComboBox.addItem ("Pitch", 2);
    modDestAComboBox.addItem ("Cutoff", 3);
    modDestAComboBox.addItem ("Resonance", 4);
    modDestAComboBox.addItem ("Level", 5);
    modDestAComboBox.addItem ("Pitch LFO1", 6);
    modDestAComboBox.addItem ("Pitch LFO2", 7);
    modDestAComboBox.addItem ("TVF LFO1", 8);
    modDestAComboBox.addItem ("TVF LFO2", 9);
    modDestAComboBox.addItem ("TVA LFO1", 10);
    modDestAComboBox.addItem ("TVA LFO2", 11);
    modDestAComboBox.addItem ("LFO1 Rate", 12);
    modDestAComboBox.addItem ("LFO2 Rate", 13);
    addAndMakeVisible (modSensASlider);
    modSensASlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    modSensASlider.setRange (-63, 63, 1);
    modSensASlider.addListener (this);
    
    addAndMakeVisible(modDestBLabel);
    modDestBLabel.setText ("Mod 2", juce::dontSendNotification);
    modDestBLabel.attachToComponent (&modDestBComboBox, true);
    addAndMakeVisible (modDestBComboBox);
    modDestBComboBox.addListener (this);
    modDestBComboBox.addItem ("Off", 1);
    modDestBComboBox.addItem ("Pitch", 2);
    modDestBComboBox.addItem ("Cutoff", 3);
    modDestBComboBox.addItem ("Resonance", 4);
    modDestBComboBox.addItem ("Level", 5);
    modDestBComboBox.addItem ("Pitch LFO1", 6);
    modDestBComboBox.addItem ("Pitch LFO2", 7);
    modDestBComboBox.addItem ("TVF LFO1", 8);
    modDestBComboBox.addItem ("TVF LFO2", 9);
    modDestBComboBox.addItem ("TVA LFO1", 10);
    modDestBComboBox.addItem ("TVA LFO2", 11);
    modDestBComboBox.addItem ("LFO1 Rate", 12);
    modDestBComboBox.addItem ("LFO2 Rate", 13);
    addAndMakeVisible (modSensBSlider);
    modSensBSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    modSensBSlider.setRange (-63, 63, 1);
    modSensBSlider.addListener (this);
    
    addAndMakeVisible(modDestCLabel);
    modDestCLabel.setText ("Mod 3", juce::dontSendNotification);
    modDestCLabel.attachToComponent (&modDestCComboBox, true);
    addAndMakeVisible (modDestCComboBox);
    modDestCComboBox.addListener (this);
    modDestCComboBox.addItem ("Off", 1);
    modDestCComboBox.addItem ("Pitch", 2);
    modDestCComboBox.addItem ("Cutoff", 3);
    modDestCComboBox.addItem ("Resonance", 4);
    modDestCComboBox.addItem ("Level", 5);
    modDestCComboBox.addItem ("Pitch LFO1", 6);
    modDestCComboBox.addItem ("Pitch LFO2", 7);
    modDestCComboBox.addItem ("TVF LFO1", 8);
    modDestCComboBox.addItem ("TVF LFO2", 9);
    modDestCComboBox.addItem ("TVA LFO1", 10);
    modDestCComboBox.addItem ("TVA LFO2", 11);
    modDestCComboBox.addItem ("LFO1 Rate", 12);
    modDestCComboBox.addItem ("LFO2 Rate", 13);
    addAndMakeVisible (modSensCSlider);
    modSensCSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    modSensCSlider.setRange (-63, 63, 1);
    modSensCSlider.addListener (this);
    
    addAndMakeVisible(modDestDLabel);
    modDestDLabel.setText ("Mod 4", juce::dontSendNotification);
    modDestDLabel.attachToComponent (&modDestDComboBox, true);
    addAndMakeVisible (modDestDComboBox);
    modDestDComboBox.addListener (this);
    modDestDComboBox.addItem ("Off", 1);
    modDestDComboBox.addItem ("Pitch", 2);
    modDestDComboBox.addItem ("Cutoff", 3);
    modDestDComboBox.addItem ("Resonance", 4);
    modDestDComboBox.addItem ("Level", 5);
    modDestDComboBox.addItem ("Pitch LFO1", 6);
    modDestDComboBox.addItem ("Pitch LFO2", 7);
    modDestDComboBox.addItem ("TVF LFO1", 8);
    modDestDComboBox.addItem ("TVF LFO2", 9);
    modDestDComboBox.addItem ("TVA LFO1", 10);
    modDestDComboBox.addItem ("TVA LFO2", 11);
    modDestDComboBox.addItem ("LFO1 Rate", 12);
    modDestDComboBox.addItem ("LFO2 Rate", 13);
    addAndMakeVisible (modSensDSlider);
    modSensDSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    modSensDSlider.setRange (-63, 63, 1);
    modSensDSlider.addListener (this);
    
    addAndMakeVisible(aftDestALabel);
    aftDestALabel.setText ("Aft 1", juce::dontSendNotification);
    aftDestALabel.attachToComponent (&aftDestAComboBox, true);
    addAndMakeVisible (aftDestAComboBox);
    aftDestAComboBox.addListener (this);
    aftDestAComboBox.addItem ("Off", 1);
    aftDestAComboBox.addItem ("Pitch", 2);
    aftDestAComboBox.addItem ("Cutoff", 3);
    aftDestAComboBox.addItem ("Resonance", 4);
    aftDestAComboBox.addItem ("Level", 5);
    aftDestAComboBox.addItem ("Pitch LFO1", 6);
    aftDestAComboBox.addItem ("Pitch LFO2", 7);
    aftDestAComboBox.addItem ("TVF LFO1", 8);
    aftDestAComboBox.addItem ("TVF LFO2", 9);
    aftDestAComboBox.addItem ("TVA LFO1", 10);
    aftDestAComboBox.addItem ("TVA LFO2", 11);
    aftDestAComboBox.addItem ("LFO1 Rate", 12);
    aftDestAComboBox.addItem ("LFO2 Rate", 13);
    addAndMakeVisible (aftSensASlider);
    aftSensASlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aftSensASlider.setRange (-63, 63, 1);
    aftSensASlider.addListener (this);
    
    addAndMakeVisible(aftDestBLabel);
    aftDestBLabel.setText ("Aft 2", juce::dontSendNotification);
    aftDestBLabel.attachToComponent (&aftDestBComboBox, true);
    addAndMakeVisible (aftDestBComboBox);
    aftDestBComboBox.addListener (this);
    aftDestBComboBox.addItem ("Off", 1);
    aftDestBComboBox.addItem ("Pitch", 2);
    aftDestBComboBox.addItem ("Cutoff", 3);
    aftDestBComboBox.addItem ("Resonance", 4);
    aftDestBComboBox.addItem ("Level", 5);
    aftDestBComboBox.addItem ("Pitch LFO1", 6);
    aftDestBComboBox.addItem ("Pitch LFO2", 7);
    aftDestBComboBox.addItem ("TVF LFO1", 8);
    aftDestBComboBox.addItem ("TVF LFO2", 9);
    aftDestBComboBox.addItem ("TVA LFO1", 10);
    aftDestBComboBox.addItem ("TVA LFO2", 11);
    aftDestBComboBox.addItem ("LFO1 Rate", 12);
    aftDestBComboBox.addItem ("LFO2 Rate", 13);
    addAndMakeVisible (aftSensBSlider);
    aftSensBSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aftSensBSlider.setRange (-63, 63, 1);
    aftSensBSlider.addListener (this);
    
    addAndMakeVisible(aftDestCLabel);
    aftDestCLabel.setText ("Aft 3", juce::dontSendNotification);
    aftDestCLabel.attachToComponent (&aftDestCComboBox, true);
    addAndMakeVisible (aftDestCComboBox);
    aftDestCComboBox.addListener (this);
    aftDestCComboBox.addItem ("Off", 1);
    aftDestCComboBox.addItem ("Pitch", 2);
    aftDestCComboBox.addItem ("Cutoff", 3);
    aftDestCComboBox.addItem ("Resonance", 4);
    aftDestCComboBox.addItem ("Level", 5);
    aftDestCComboBox.addItem ("Pitch LFO1", 6);
    aftDestCComboBox.addItem ("Pitch LFO2", 7);
    aftDestCComboBox.addItem ("TVF LFO1", 8);
    aftDestCComboBox.addItem ("TVF LFO2", 9);
    aftDestCComboBox.addItem ("TVA LFO1", 10);
    aftDestCComboBox.addItem ("TVA LFO2", 11);
    aftDestCComboBox.addItem ("LFO1 Rate", 12);
    aftDestCComboBox.addItem ("LFO2 Rate", 13);
    addAndMakeVisible (aftSensCSlider);
    aftSensCSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aftSensCSlider.setRange (-63, 63, 1);
    aftSensCSlider.addListener (this);
    
    addAndMakeVisible(aftDestDLabel);
    aftDestDLabel.setText ("Aft 4", juce::dontSendNotification);
    aftDestDLabel.attachToComponent (&aftDestDComboBox, true);
    addAndMakeVisible (aftDestDComboBox);
    aftDestDComboBox.addListener (this);
    aftDestDComboBox.addItem ("Off", 1);
    aftDestDComboBox.addItem ("Pitch", 2);
    aftDestDComboBox.addItem ("Cutoff", 3);
    aftDestDComboBox.addItem ("Resonance", 4);
    aftDestDComboBox.addItem ("Level", 5);
    aftDestDComboBox.addItem ("Pitch LFO1", 6);
    aftDestDComboBox.addItem ("Pitch LFO2", 7);
    aftDestDComboBox.addItem ("TVF LFO1", 8);
    aftDestDComboBox.addItem ("TVF LFO2", 9);
    aftDestDComboBox.addItem ("TVA LFO1", 10);
    aftDestDComboBox.addItem ("TVA LFO2", 11);
    aftDestDComboBox.addItem ("LFO1 Rate", 12);
    aftDestDComboBox.addItem ("LFO2 Rate", 13);
    addAndMakeVisible (aftSensDSlider);
    aftSensDSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aftSensDSlider.setRange (-63, 63, 1);
    aftSensDSlider.addListener (this);
    
    addAndMakeVisible(expDestALabel);
    expDestALabel.setText ("Exp 1", juce::dontSendNotification);
    expDestALabel.attachToComponent (&expDestAComboBox, true);
    addAndMakeVisible (expDestAComboBox);
    expDestAComboBox.addListener (this);
    expDestAComboBox.addItem ("Off", 1);
    expDestAComboBox.addItem ("Pitch", 2);
    expDestAComboBox.addItem ("Cutoff", 3);
    expDestAComboBox.addItem ("Resonance", 4);
    expDestAComboBox.addItem ("Level", 5);
    expDestAComboBox.addItem ("Pitch LFO1", 6);
    expDestAComboBox.addItem ("Pitch LFO2", 7);
    expDestAComboBox.addItem ("TVF LFO1", 8);
    expDestAComboBox.addItem ("TVF LFO2", 9);
    expDestAComboBox.addItem ("TVA LFO1", 10);
    expDestAComboBox.addItem ("TVA LFO2", 11);
    expDestAComboBox.addItem ("LFO1 Rate", 12);
    expDestAComboBox.addItem ("LFO2 Rate", 13);
    addAndMakeVisible (expSensASlider);
    expSensASlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    expSensASlider.setRange (-63, 63, 1);
    expSensASlider.addListener (this);
    
    addAndMakeVisible(expDestBLabel);
    expDestBLabel.setText ("Exp 2", juce::dontSendNotification);
    expDestBLabel.attachToComponent (&expDestBComboBox, true);
    addAndMakeVisible (expDestBComboBox);
    expDestBComboBox.addListener (this);
    expDestBComboBox.addItem ("Off", 1);
    expDestBComboBox.addItem ("Pitch", 2);
    expDestBComboBox.addItem ("Cutoff", 3);
    expDestBComboBox.addItem ("Resonance", 4);
    expDestBComboBox.addItem ("Level", 5);
    expDestBComboBox.addItem ("Pitch LFO1", 6);
    expDestBComboBox.addItem ("Pitch LFO2", 7);
    expDestBComboBox.addItem ("TVF LFO1", 8);
    expDestBComboBox.addItem ("TVF LFO2", 9);
    expDestBComboBox.addItem ("TVA LFO1", 10);
    expDestBComboBox.addItem ("TVA LFO2", 11);
    expDestBComboBox.addItem ("LFO1 Rate", 12);
    expDestBComboBox.addItem ("LFO2 Rate", 13);
    addAndMakeVisible (expSensBSlider);
    expSensBSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    expSensBSlider.setRange (-63, 63, 1);
    expSensBSlider.addListener (this);
    
    addAndMakeVisible(expDestCLabel);
    expDestCLabel.setText ("Exp 3", juce::dontSendNotification);
    expDestCLabel.attachToComponent (&expDestCComboBox, true);
    addAndMakeVisible (expDestCComboBox);
    expDestCComboBox.addListener (this);
    expDestCComboBox.addItem ("Off", 1);
    expDestCComboBox.addItem ("Pitch", 2);
    expDestCComboBox.addItem ("Cutoff", 3);
    expDestCComboBox.addItem ("Resonance", 4);
    expDestCComboBox.addItem ("Level", 5);
    expDestCComboBox.addItem ("Pitch LFO1", 6);
    expDestCComboBox.addItem ("Pitch LFO2", 7);
    expDestCComboBox.addItem ("TVF LFO1", 8);
    expDestCComboBox.addItem ("TVF LFO2", 9);
    expDestCComboBox.addItem ("TVA LFO1", 10);
    expDestCComboBox.addItem ("TVA LFO2", 11);
    expDestCComboBox.addItem ("LFO1 Rate", 12);
    expDestCComboBox.addItem ("LFO2 Rate", 13);
    addAndMakeVisible (expSensCSlider);
    expSensCSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    expSensCSlider.setRange (-63, 63, 1);
    expSensCSlider.addListener (this);
    
    addAndMakeVisible(expDestDLabel);
    expDestDLabel.setText ("Exp 4", juce::dontSendNotification);
    expDestDLabel.attachToComponent (&expDestDComboBox, true);
    addAndMakeVisible (expDestDComboBox);
    expDestDComboBox.addListener (this);
    expDestDComboBox.addItem ("Off", 1);
    expDestDComboBox.addItem ("Pitch", 2);
    expDestDComboBox.addItem ("Cutoff", 3);
    expDestDComboBox.addItem ("Resonance", 4);
    expDestDComboBox.addItem ("Level", 5);
    expDestDComboBox.addItem ("Pitch LFO1", 6);
    expDestDComboBox.addItem ("Pitch LFO2", 7);
    expDestDComboBox.addItem ("TVF LFO1", 8);
    expDestDComboBox.addItem ("TVF LFO2", 9);
    expDestDComboBox.addItem ("TVA LFO1", 10);
    expDestDComboBox.addItem ("TVA LFO2", 11);
    expDestDComboBox.addItem ("LFO1 Rate", 12);
    expDestDComboBox.addItem ("LFO2 Rate", 13);
    addAndMakeVisible (expSensDSlider);
    expSensDSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    expSensDSlider.setRange (-63, 63, 1);
    expSensDSlider.addListener (this);
    
    addAndMakeVisible(lfo1FormLabel);
    lfo1FormLabel.setText ("LFO 1", juce::dontSendNotification);
    lfo1FormLabel.attachToComponent (&lfo1FormComboBox, true);
    addAndMakeVisible (lfo1FormComboBox);
    lfo1FormComboBox.addListener (this);
    lfo1FormComboBox.addItem ("Tri", 1);
    lfo1FormComboBox.addItem ("Sin", 2);
    lfo1FormComboBox.addItem ("Saw", 3);
    lfo1FormComboBox.addItem ("Squ", 4);
    lfo1FormComboBox.addItem ("Rnd1", 5);
    lfo1FormComboBox.addItem ("Rnd2", 6);
    addAndMakeVisible (lfo1OffsetComboBox);
    lfo1OffsetComboBox.addListener (this);
    lfo1OffsetComboBox.addItem ("-100", 1);
    lfo1OffsetComboBox.addItem ("-50", 2);
    lfo1OffsetComboBox.addItem ("0", 3);
    lfo1OffsetComboBox.addItem ("50", 4);
    lfo1OffsetComboBox.addItem ("100", 5);
    addAndMakeVisible (lfo1SyncToggle);
    lfo1SyncToggle.addListener (this);
    lfo1SyncToggle.setButtonText ("Sync");
    addAndMakeVisible (lfo1RateSlider);
    lfo1RateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo1RateSlider.setRange (0, 127, 1);
    lfo1RateSlider.addListener (this);
    addAndMakeVisible (lfo1RateLabel);
    lfo1RateLabel.setText ("Rate", juce::dontSendNotification);
    lfo1RateLabel.attachToComponent (&lfo1RateSlider, true);
    addAndMakeVisible (lfo1DelaySlider);
    lfo1DelaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo1DelaySlider.setRange (0, 128, 1);
    lfo1DelaySlider.addListener (this);
    addAndMakeVisible (lfo1DelayLabel);
    lfo1DelayLabel.setText ("Delay", juce::dontSendNotification);
    lfo1DelayLabel.attachToComponent (&lfo1DelaySlider, true);
    addAndMakeVisible (lfo1FadeToggle);
    lfo1FadeToggle.addListener (this);
    lfo1FadeToggle.setButtonText ("Fade");
    addAndMakeVisible (lfo1FadeTimeSlider);
    lfo1FadeTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo1FadeTimeSlider.setRange (0, 127, 1);
    lfo1FadeTimeSlider.addListener (this);
    addAndMakeVisible (lfo1FadeTimeLabel);
    lfo1FadeTimeLabel.setText ("Fade Time", juce::dontSendNotification);
    lfo1FadeTimeLabel.attachToComponent (&lfo1FadeTimeSlider, true);
    addAndMakeVisible (lfo1PitchDepthSlider);
    lfo1PitchDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo1PitchDepthSlider.setRange (-60, 60, 1);
    lfo1PitchDepthSlider.addListener (this);
    addAndMakeVisible (lfo1PitchDepthLabel);
    lfo1PitchDepthLabel.setText ("Pitch", juce::dontSendNotification);
    lfo1PitchDepthLabel.attachToComponent (&lfo1PitchDepthSlider, true);
    addAndMakeVisible (lfo1TVFDepthSlider);
    lfo1TVFDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo1TVFDepthSlider.setRange (-63, 63, 1);
    lfo1TVFDepthSlider.addListener (this);
    addAndMakeVisible (lfo1TVFDepthLabel);
    lfo1TVFDepthLabel.setText ("TVF", juce::dontSendNotification);
    lfo1TVFDepthLabel.attachToComponent (&lfo1TVFDepthSlider, true);
    addAndMakeVisible (lfo1TVADepthSlider);
    lfo1TVADepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo1TVADepthSlider.setRange (-63, 63, 1);
    lfo1TVADepthSlider.addListener (this);
    addAndMakeVisible (lfo1TVADepthLabel);
    lfo1TVADepthLabel.setText ("TVA", juce::dontSendNotification);
    lfo1TVADepthLabel.attachToComponent (&lfo1TVADepthSlider, true);
    
    addAndMakeVisible(lfo2FormLabel);
    lfo2FormLabel.setText ("LFO 2", juce::dontSendNotification);
    lfo2FormLabel.attachToComponent (&lfo2FormComboBox, true);
    addAndMakeVisible (lfo2FormComboBox);
    lfo2FormComboBox.addListener (this);
    lfo2FormComboBox.addItem ("Tri", 1);
    lfo2FormComboBox.addItem ("Sin", 2);
    lfo2FormComboBox.addItem ("Saw", 3);
    lfo2FormComboBox.addItem ("Squ", 4);
    lfo2FormComboBox.addItem ("Rnd1", 5);
    lfo2FormComboBox.addItem ("Rnd2", 6);
    addAndMakeVisible (lfo2OffsetComboBox);
    lfo2OffsetComboBox.addListener (this);
    lfo2OffsetComboBox.addItem ("-100", 1);
    lfo2OffsetComboBox.addItem ("-50", 2);
    lfo2OffsetComboBox.addItem ("0", 3);
    lfo2OffsetComboBox.addItem ("50", 4);
    lfo2OffsetComboBox.addItem ("100", 5);
    addAndMakeVisible (lfo2SyncToggle);
    lfo2SyncToggle.addListener (this);
    lfo2SyncToggle.setButtonText ("Sync");
    addAndMakeVisible (lfo2RateSlider);
    lfo2RateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo2RateSlider.setRange (0, 127, 1);
    lfo2RateSlider.addListener (this);
    addAndMakeVisible (lfo2RateLabel);
    lfo2RateLabel.setText ("Rate", juce::dontSendNotification);
    lfo2RateLabel.attachToComponent (&lfo2RateSlider, true);
    addAndMakeVisible (lfo2DelaySlider);
    lfo2DelaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo2DelaySlider.setRange (0, 128, 1);
    lfo2DelaySlider.addListener (this);
    addAndMakeVisible (lfo2DelayLabel);
    lfo2DelayLabel.setText ("Delay", juce::dontSendNotification);
    lfo2DelayLabel.attachToComponent (&lfo2DelaySlider, true);
    addAndMakeVisible (lfo2FadeToggle);
    lfo2FadeToggle.addListener (this);
    lfo2FadeToggle.setButtonText ("Fade");
    addAndMakeVisible (lfo2FadeTimeSlider);
    lfo2FadeTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo2FadeTimeSlider.setRange (0, 127, 1);
    lfo2FadeTimeSlider.addListener (this);
    addAndMakeVisible (lfo2FadeTimeLabel);
    lfo2FadeTimeLabel.setText ("Fade Time", juce::dontSendNotification);
    lfo2FadeTimeLabel.attachToComponent (&lfo2FadeTimeSlider, true);
    addAndMakeVisible (lfo2PitchDepthSlider);
    lfo2PitchDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo2PitchDepthSlider.setRange (-60, 60, 1);
    lfo2PitchDepthSlider.addListener (this);
    addAndMakeVisible (lfo2PitchDepthLabel);
    lfo2PitchDepthLabel.setText ("Pitch", juce::dontSendNotification);
    lfo2PitchDepthLabel.attachToComponent (&lfo2PitchDepthSlider, true);
    addAndMakeVisible (lfo2TVFDepthSlider);
    lfo2TVFDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo2TVFDepthSlider.setRange (-63, 63, 1);
    lfo2TVFDepthSlider.addListener (this);
    addAndMakeVisible (lfo2TVFDepthLabel);
    lfo2TVFDepthLabel.setText ("TVF", juce::dontSendNotification);
    lfo2TVFDepthLabel.attachToComponent (&lfo2TVFDepthSlider, true);
    addAndMakeVisible (lfo2TVADepthSlider);
    lfo2TVADepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    lfo2TVADepthSlider.setRange (-63, 63, 1);
    lfo2TVADepthSlider.addListener (this);
    addAndMakeVisible (lfo2TVADepthLabel);
    lfo2TVADepthLabel.setText ("TVA", juce::dontSendNotification);
    lfo2TVADepthLabel.attachToComponent (&lfo2TVADepthSlider, true);
    
    addAndMakeVisible (pitchCoarseSlider);
    pitchCoarseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    pitchCoarseSlider.setRange (-48, 48, 1);
    pitchCoarseSlider.addListener (this);
    addAndMakeVisible (pitchCoarseLabel);
    pitchCoarseLabel.setText ("Coarse", juce::dontSendNotification);
    pitchCoarseLabel.attachToComponent (&pitchCoarseSlider, true);
    
    addAndMakeVisible (pitchFineSlider);
    pitchFineSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    pitchFineSlider.setRange (-50, 50, 1);
    pitchFineSlider.addListener (this);
    addAndMakeVisible (pitchFineLabel);
    pitchFineLabel.setText ("Fine", juce::dontSendNotification);
    pitchFineLabel.attachToComponent (&pitchFineSlider, true);
    
    addAndMakeVisible (pitchRandomComboBox);
    pitchRandomComboBox.addListener (this);
    pitchRandomComboBox.addItem ("0", 1);
    pitchRandomComboBox.addItem ("5", 2);
    pitchRandomComboBox.addItem ("10", 3);
    pitchRandomComboBox.addItem ("20", 4);
    pitchRandomComboBox.addItem ("30", 5);
    pitchRandomComboBox.addItem ("40", 6);
    pitchRandomComboBox.addItem ("50", 7);
    pitchRandomComboBox.addItem ("70", 8);
    pitchRandomComboBox.addItem ("100", 9);
    pitchRandomComboBox.addItem ("200", 10);
    pitchRandomComboBox.addItem ("300", 11);
    pitchRandomComboBox.addItem ("400", 12);
    pitchRandomComboBox.addItem ("500", 13);
    pitchRandomComboBox.addItem ("600", 14);
    pitchRandomComboBox.addItem ("800", 15);
    pitchRandomComboBox.addItem ("1200", 16);
    addAndMakeVisible (pitchRandomLabel);
    pitchRandomLabel.setText ("Random / KF", juce::dontSendNotification);
    pitchRandomLabel.attachToComponent (&pitchRandomComboBox, true);
    
    addAndMakeVisible (pitchKFComboBox);
    pitchKFComboBox.addListener (this);
    pitchKFComboBox.addItem ("-100", 1);
    pitchKFComboBox.addItem ("-70", 2);
    pitchKFComboBox.addItem ("-50", 3);
    pitchKFComboBox.addItem ("-30", 4);
    pitchKFComboBox.addItem ("-10", 5);
    pitchKFComboBox.addItem ("0", 6);
    pitchKFComboBox.addItem ("10", 7);
    pitchKFComboBox.addItem ("20", 8);
    pitchKFComboBox.addItem ("30", 9);
    pitchKFComboBox.addItem ("40", 10);
    pitchKFComboBox.addItem ("50", 11);
    pitchKFComboBox.addItem ("70", 12);
    pitchKFComboBox.addItem ("100", 13);
    pitchKFComboBox.addItem ("120", 14);
    pitchKFComboBox.addItem ("150", 15);
    pitchKFComboBox.addItem ("200", 16);
    
    addAndMakeVisible(penvLevSensSlider);
    penvLevSensSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penvLevSensSlider.setRange (-12, 12, 1);
    penvLevSensSlider.addListener (this);
    addAndMakeVisible (penvLevSensLabel);
    penvLevSensLabel.setText ("Pitch Sens", juce::dontSendNotification);
    penvLevSensLabel.attachToComponent (&penvLevSensSlider, true);
    
    addAndMakeVisible (penvTime1SensComboBox);
    penvTime1SensComboBox.addListener (this);
    penvTime1SensComboBox.addItem ("-100", 1);
    penvTime1SensComboBox.addItem ("-70", 2);
    penvTime1SensComboBox.addItem ("-50", 3);
    penvTime1SensComboBox.addItem ("-40", 4);
    penvTime1SensComboBox.addItem ("-30", 5);
    penvTime1SensComboBox.addItem ("-20", 6);
    penvTime1SensComboBox.addItem ("-10", 7);
    penvTime1SensComboBox.addItem ("0", 8);
    penvTime1SensComboBox.addItem ("10", 9);
    penvTime1SensComboBox.addItem ("20", 10);
    penvTime1SensComboBox.addItem ("30", 11);
    penvTime1SensComboBox.addItem ("40", 12);
    penvTime1SensComboBox.addItem ("50", 13);
    penvTime1SensComboBox.addItem ("70", 14);
    penvTime1SensComboBox.addItem ("100", 15);
    addAndMakeVisible (penvTime1SensLabel);
    penvTime1SensLabel.setText ("Time Sens", juce::dontSendNotification);
    penvTime1SensLabel.attachToComponent (&penvTime1SensComboBox, true);
    
    addAndMakeVisible (penvTime4SensComboBox);
    penvTime4SensComboBox.addListener (this);
    penvTime4SensComboBox.addItem ("-100", 1);
    penvTime4SensComboBox.addItem ("-70", 2);
    penvTime4SensComboBox.addItem ("-50", 3);
    penvTime4SensComboBox.addItem ("-40", 4);
    penvTime4SensComboBox.addItem ("-30", 5);
    penvTime4SensComboBox.addItem ("-20", 6);
    penvTime4SensComboBox.addItem ("-10", 7);
    penvTime4SensComboBox.addItem ("0", 8);
    penvTime4SensComboBox.addItem ("10", 9);
    penvTime4SensComboBox.addItem ("20", 10);
    penvTime4SensComboBox.addItem ("30", 11);
    penvTime4SensComboBox.addItem ("40", 12);
    penvTime4SensComboBox.addItem ("50", 13);
    penvTime4SensComboBox.addItem ("70", 14);
    penvTime4SensComboBox.addItem ("100", 15);
    
    addAndMakeVisible (penvTimeKFSensComboBox);
    penvTimeKFSensComboBox.addListener (this);
    penvTimeKFSensComboBox.addItem ("-100", 1);
    penvTimeKFSensComboBox.addItem ("-70", 2);
    penvTimeKFSensComboBox.addItem ("-50", 3);
    penvTimeKFSensComboBox.addItem ("-40", 4);
    penvTimeKFSensComboBox.addItem ("-30", 5);
    penvTimeKFSensComboBox.addItem ("-20", 6);
    penvTimeKFSensComboBox.addItem ("-10", 7);
    penvTimeKFSensComboBox.addItem ("0", 8);
    penvTimeKFSensComboBox.addItem ("10", 9);
    penvTimeKFSensComboBox.addItem ("20", 10);
    penvTimeKFSensComboBox.addItem ("30", 11);
    penvTimeKFSensComboBox.addItem ("40", 12);
    penvTimeKFSensComboBox.addItem ("50", 13);
    penvTimeKFSensComboBox.addItem ("70", 14);
    penvTimeKFSensComboBox.addItem ("100", 15);
    addAndMakeVisible (penvTimeKFSensLabel);
    penvTimeKFSensLabel.setText ("Time KF", juce::dontSendNotification);
    penvTimeKFSensLabel.attachToComponent (&penvTimeKFSensComboBox, true);
    
    addAndMakeVisible(penvDepthSlider);
    penvDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penvDepthSlider.setRange (-12, 12, 1);
    penvDepthSlider.addListener (this);
    addAndMakeVisible (penvDepthLabel);
    penvDepthLabel.setText ("Pitch Depth", juce::dontSendNotification);
    penvDepthLabel.attachToComponent (&penvDepthSlider, true);
    
    addAndMakeVisible(penv1TimeSlider);
    penv1TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv1TimeSlider.setRange (0, 127, 1);
    penv1TimeSlider.addListener (this);
    addAndMakeVisible (penv1TimeLabel);
    penv1TimeLabel.setText ("Time/Level 1", juce::dontSendNotification);
    penv1TimeLabel.attachToComponent (&penv1TimeSlider, true);
    addAndMakeVisible(penv1LevelSlider);
    penv1LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv1LevelSlider.setRange (-63, 63, 1);
    penv1LevelSlider.addListener (this);
    
    addAndMakeVisible(penv2TimeSlider);
    penv2TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv2TimeSlider.setRange (0, 127, 1);
    penv2TimeSlider.addListener (this);
    addAndMakeVisible (penv2TimeLabel);
    penv2TimeLabel.setText ("Time/Level 2", juce::dontSendNotification);
    penv2TimeLabel.attachToComponent (&penv2TimeSlider, true);
    addAndMakeVisible(penv2LevelSlider);
    penv2LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv2LevelSlider.setRange (-63, 63, 1);
    penv2LevelSlider.addListener (this);
    
    addAndMakeVisible(penv3TimeSlider);
    penv3TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv3TimeSlider.setRange (0, 127, 1);
    penv3TimeSlider.addListener (this);
    addAndMakeVisible (penv3TimeLabel);
    penv3TimeLabel.setText ("Time/Level 3", juce::dontSendNotification);
    penv3TimeLabel.attachToComponent (&penv3TimeSlider, true);
    addAndMakeVisible(penv3LevelSlider);
    penv3LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv3LevelSlider.setRange (-63, 63, 1);
    penv3LevelSlider.addListener (this);
    
    addAndMakeVisible(penv4TimeSlider);
    penv4TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv4TimeSlider.setRange (0, 127, 1);
    penv4TimeSlider.addListener (this);
    addAndMakeVisible (penv4TimeLabel);
    penv4TimeLabel.setText ("Time/Level 4", juce::dontSendNotification);
    penv4TimeLabel.attachToComponent (&penv4TimeSlider, true);
    addAndMakeVisible(penv4LevelSlider);
    penv4LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    penv4LevelSlider.setRange (-63, 63, 1);
    penv4LevelSlider.addListener (this);
    
    addAndMakeVisible (filterModeComboBox);
    filterModeComboBox.addListener (this);
    filterModeComboBox.addItem ("OFF", 1);
    filterModeComboBox.addItem ("LPF", 2);
    filterModeComboBox.addItem ("HPF", 3);
    addAndMakeVisible (filterModeLabel);
    filterModeLabel.setText ("Filter", juce::dontSendNotification);
    filterModeLabel.attachToComponent (&filterModeComboBox, true);
    
    addAndMakeVisible(filterCutoffSlider);
    filterCutoffSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    filterCutoffSlider.setRange (0, 127, 1);
    filterCutoffSlider.addListener (this);
    addAndMakeVisible (filterCutoffLabel);
    filterCutoffLabel.setText ("Cutoff", juce::dontSendNotification);
    filterCutoffLabel.attachToComponent (&filterCutoffSlider, true);
    
    addAndMakeVisible(filterResoSlider);
    filterResoSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    filterResoSlider.setRange (0, 127, 1);
    filterResoSlider.addListener (this);
    addAndMakeVisible (filterResoLabel);
    filterResoLabel.setText ("Reson", juce::dontSendNotification);
    filterResoLabel.attachToComponent (&filterResoSlider, true);
    
    addAndMakeVisible (filterResoModeComboBox);
    filterResoModeComboBox.addListener (this);
    filterResoModeComboBox.addItem ("SOFT", 1);
    filterResoModeComboBox.addItem ("HARD", 2);
    addAndMakeVisible (filterResoModeLabel);
    filterResoModeLabel.setText ("Reso Mode", juce::dontSendNotification);
    filterResoModeLabel.attachToComponent (&filterResoModeComboBox, true);
    
    addAndMakeVisible (filterKFComboBox);
    filterKFComboBox.addListener (this);
    filterKFComboBox.addItem ("-100", 1);
    filterKFComboBox.addItem ("-70", 2);
    filterKFComboBox.addItem ("-50", 3);
    filterKFComboBox.addItem ("-30", 4);
    filterKFComboBox.addItem ("-10", 5);
    filterKFComboBox.addItem ("0", 6);
    filterKFComboBox.addItem ("10", 7);
    filterKFComboBox.addItem ("20", 8);
    filterKFComboBox.addItem ("30", 9);
    filterKFComboBox.addItem ("40", 10);
    filterKFComboBox.addItem ("50", 11);
    filterKFComboBox.addItem ("70", 12);
    filterKFComboBox.addItem ("100", 13);
    filterKFComboBox.addItem ("120", 14);
    filterKFComboBox.addItem ("150", 15);
    filterKFComboBox.addItem ("200", 16);
    addAndMakeVisible (filterKFLabel);
    filterKFLabel.setText ("KF / Curve", juce::dontSendNotification);
    filterKFLabel.attachToComponent (&filterKFComboBox, true);
    
    addAndMakeVisible (fenvVelCurveComboBox);
    fenvVelCurveComboBox.addListener (this);
    fenvVelCurveComboBox.addItem ("1", 1);
    fenvVelCurveComboBox.addItem ("2", 2);
    fenvVelCurveComboBox.addItem ("3", 3);
    fenvVelCurveComboBox.addItem ("4", 4);
    fenvVelCurveComboBox.addItem ("5", 5);
    fenvVelCurveComboBox.addItem ("6", 6);
    fenvVelCurveComboBox.addItem ("7", 7);
    
    addAndMakeVisible(fenvLevSensSlider);
    fenvLevSensSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenvLevSensSlider.setRange (-63, 63, 1);
    fenvLevSensSlider.addListener (this);
    addAndMakeVisible (fenvLevSensLabel);
    fenvLevSensLabel.setText ("TVF Sens", juce::dontSendNotification);
    fenvLevSensLabel.attachToComponent (&fenvLevSensSlider, true);
    
    addAndMakeVisible (fenvTime1SensComboBox);
    fenvTime1SensComboBox.addListener (this);
    fenvTime1SensComboBox.addItem ("-100", 1);
    fenvTime1SensComboBox.addItem ("-70", 2);
    fenvTime1SensComboBox.addItem ("-50", 3);
    fenvTime1SensComboBox.addItem ("-40", 4);
    fenvTime1SensComboBox.addItem ("-30", 5);
    fenvTime1SensComboBox.addItem ("-20", 6);
    fenvTime1SensComboBox.addItem ("-10", 7);
    fenvTime1SensComboBox.addItem ("0", 8);
    fenvTime1SensComboBox.addItem ("10", 9);
    fenvTime1SensComboBox.addItem ("20", 10);
    fenvTime1SensComboBox.addItem ("30", 11);
    fenvTime1SensComboBox.addItem ("40", 12);
    fenvTime1SensComboBox.addItem ("50", 13);
    fenvTime1SensComboBox.addItem ("70", 14);
    fenvTime1SensComboBox.addItem ("100", 15);
    addAndMakeVisible (fenvTime1SensLabel);
    fenvTime1SensLabel.setText ("Time Sens", juce::dontSendNotification);
    fenvTime1SensLabel.attachToComponent (&fenvTime1SensComboBox, true);
    
    addAndMakeVisible (fenvTime4SensComboBox);
    fenvTime4SensComboBox.addListener (this);
    fenvTime4SensComboBox.addItem ("-100", 1);
    fenvTime4SensComboBox.addItem ("-70", 2);
    fenvTime4SensComboBox.addItem ("-50", 3);
    fenvTime4SensComboBox.addItem ("-40", 4);
    fenvTime4SensComboBox.addItem ("-30", 5);
    fenvTime4SensComboBox.addItem ("-20", 6);
    fenvTime4SensComboBox.addItem ("-10", 7);
    fenvTime4SensComboBox.addItem ("0", 8);
    fenvTime4SensComboBox.addItem ("10", 9);
    fenvTime4SensComboBox.addItem ("20", 10);
    fenvTime4SensComboBox.addItem ("30", 11);
    fenvTime4SensComboBox.addItem ("40", 12);
    fenvTime4SensComboBox.addItem ("50", 13);
    fenvTime4SensComboBox.addItem ("70", 14);
    fenvTime4SensComboBox.addItem ("100", 15);
    
    addAndMakeVisible (fenvTimeKFSensComboBox);
    fenvTimeKFSensComboBox.addListener (this);
    fenvTimeKFSensComboBox.addItem ("-100", 1);
    fenvTimeKFSensComboBox.addItem ("-70", 2);
    fenvTimeKFSensComboBox.addItem ("-50", 3);
    fenvTimeKFSensComboBox.addItem ("-40", 4);
    fenvTimeKFSensComboBox.addItem ("-30", 5);
    fenvTimeKFSensComboBox.addItem ("-20", 6);
    fenvTimeKFSensComboBox.addItem ("-10", 7);
    fenvTimeKFSensComboBox.addItem ("0", 8);
    fenvTimeKFSensComboBox.addItem ("10", 9);
    fenvTimeKFSensComboBox.addItem ("20", 10);
    fenvTimeKFSensComboBox.addItem ("30", 11);
    fenvTimeKFSensComboBox.addItem ("40", 12);
    fenvTimeKFSensComboBox.addItem ("50", 13);
    fenvTimeKFSensComboBox.addItem ("70", 14);
    fenvTimeKFSensComboBox.addItem ("100", 15);
    addAndMakeVisible (fenvTimeKFSensLabel);
    fenvTimeKFSensLabel.setText ("Time KF", juce::dontSendNotification);
    fenvTimeKFSensLabel.attachToComponent (&fenvTimeKFSensComboBox, true);
    
    addAndMakeVisible(fenvDepthSlider);
    fenvDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenvDepthSlider.setRange (-63, 63, 1);
    fenvDepthSlider.addListener (this);
    addAndMakeVisible (fenvDepthLabel);
    fenvDepthLabel.setText ("TVF Depth", juce::dontSendNotification);
    fenvDepthLabel.attachToComponent (&fenvDepthSlider, true);
    
    addAndMakeVisible(fenv1TimeSlider);
    fenv1TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv1TimeSlider.setRange (0, 127, 1);
    fenv1TimeSlider.addListener (this);
    addAndMakeVisible (fenv1TimeLabel);
    fenv1TimeLabel.setText ("Time/Level 1", juce::dontSendNotification);
    fenv1TimeLabel.attachToComponent (&fenv1TimeSlider, true);
    addAndMakeVisible(fenv1LevelSlider);
    fenv1LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv1LevelSlider.setRange (0, 127, 1);
    fenv1LevelSlider.addListener (this);
    
    addAndMakeVisible(fenv2TimeSlider);
    fenv2TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv2TimeSlider.setRange (0, 127, 1);
    fenv2TimeSlider.addListener (this);
    addAndMakeVisible (fenv2TimeLabel);
    fenv2TimeLabel.setText ("Time/Level 2", juce::dontSendNotification);
    fenv2TimeLabel.attachToComponent (&fenv2TimeSlider, true);
    addAndMakeVisible(fenv2LevelSlider);
    fenv2LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv2LevelSlider.setRange (0, 127, 1);
    fenv2LevelSlider.addListener (this);
    
    addAndMakeVisible(fenv3TimeSlider);
    fenv3TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv3TimeSlider.setRange (0, 127, 1);
    fenv3TimeSlider.addListener (this);
    addAndMakeVisible (fenv3TimeLabel);
    fenv3TimeLabel.setText ("Time/Level 3", juce::dontSendNotification);
    fenv3TimeLabel.attachToComponent (&fenv3TimeSlider, true);
    addAndMakeVisible(fenv3LevelSlider);
    fenv3LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv3LevelSlider.setRange (0, 127, 1);
    fenv3LevelSlider.addListener (this);
    
    addAndMakeVisible(fenv4TimeSlider);
    fenv4TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv4TimeSlider.setRange (0, 127, 1);
    fenv4TimeSlider.addListener (this);
    addAndMakeVisible (fenv4TimeLabel);
    fenv4TimeLabel.setText ("Time/Level 4", juce::dontSendNotification);
    fenv4TimeLabel.attachToComponent (&fenv4TimeSlider, true);
    addAndMakeVisible(fenv4LevelSlider);
    fenv4LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    fenv4LevelSlider.setRange (0, 127, 1);
    fenv4LevelSlider.addListener (this);
    
    addAndMakeVisible(levelSlider);
    levelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    levelSlider.setRange (0, 127, 1);
    levelSlider.addListener (this);
    addAndMakeVisible (levelLabel);
    levelLabel.setText ("Level", juce::dontSendNotification);
    levelLabel.attachToComponent (&levelSlider, true);
    
    addAndMakeVisible (levelKFComboBox);
    levelKFComboBox.addListener (this);
    levelKFComboBox.addItem ("-100", 1);
    levelKFComboBox.addItem ("-70", 2);
    levelKFComboBox.addItem ("-50", 3);
    levelKFComboBox.addItem ("-40", 4);
    levelKFComboBox.addItem ("-30", 5);
    levelKFComboBox.addItem ("-20", 6);
    levelKFComboBox.addItem ("-10", 7);
    levelKFComboBox.addItem ("0", 8);
    levelKFComboBox.addItem ("10", 9);
    levelKFComboBox.addItem ("20", 10);
    levelKFComboBox.addItem ("30", 11);
    levelKFComboBox.addItem ("40", 12);
    levelKFComboBox.addItem ("50", 13);
    levelKFComboBox.addItem ("70", 14);
    levelKFComboBox.addItem ("100", 15);
    addAndMakeVisible (levelKFLabel);
    levelKFLabel.setText ("Level/Pan KF", juce::dontSendNotification);
    levelKFLabel.attachToComponent (&levelKFComboBox, true);
    
    addAndMakeVisible(panSlider);
    panSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    panSlider.setRange (-64, 64, 1);
    panSlider.addListener (this);
    addAndMakeVisible (panLabel);
    panLabel.setText ("Pan", juce::dontSendNotification);
    panLabel.attachToComponent (&panSlider, true);
    
    addAndMakeVisible (panKFComboBox);
    panKFComboBox.addListener (this);
    panKFComboBox.addItem ("-100", 1);
    panKFComboBox.addItem ("-70", 2);
    panKFComboBox.addItem ("-50", 3);
    panKFComboBox.addItem ("-40", 4);
    panKFComboBox.addItem ("-30", 5);
    panKFComboBox.addItem ("-20", 6);
    panKFComboBox.addItem ("-10", 7);
    panKFComboBox.addItem ("0", 8);
    panKFComboBox.addItem ("10", 9);
    panKFComboBox.addItem ("20", 10);
    panKFComboBox.addItem ("30", 11);
    panKFComboBox.addItem ("40", 12);
    panKFComboBox.addItem ("50", 13);
    panKFComboBox.addItem ("70", 14);
    panKFComboBox.addItem ("100", 15);
    
    addAndMakeVisible (toneDelayComboBox);
    toneDelayComboBox.addListener (this);
    toneDelayComboBox.addItem ("NORMAL", 1);
    toneDelayComboBox.addItem ("HOLD", 2);
    toneDelayComboBox.addItem ("PLAY-MATE", 3);
    addAndMakeVisible (toneDelayLabel);
    toneDelayLabel.setText ("Delay Mode", juce::dontSendNotification);
    toneDelayLabel.attachToComponent (&toneDelayComboBox, true);
    
    addAndMakeVisible(toneDelayTimeSlider);
    toneDelayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    toneDelayTimeSlider.setRange (-64, 64, 1);
    toneDelayTimeSlider.addListener (this);
    addAndMakeVisible (toneDelayTimeLabel);
    toneDelayTimeLabel.setText ("Delay Time", juce::dontSendNotification);
    toneDelayTimeLabel.attachToComponent (&toneDelayTimeSlider, true);
    
    addAndMakeVisible (aenvVelCurveComboBox);
    aenvVelCurveComboBox.addListener (this);
    aenvVelCurveComboBox.addItem ("1", 1);
    aenvVelCurveComboBox.addItem ("2", 2);
    aenvVelCurveComboBox.addItem ("3", 3);
    aenvVelCurveComboBox.addItem ("4", 4);
    aenvVelCurveComboBox.addItem ("5", 5);
    aenvVelCurveComboBox.addItem ("6", 6);
    aenvVelCurveComboBox.addItem ("7", 7);
    addAndMakeVisible (aenvVelCurveLabel);
    aenvVelCurveLabel.setText ("Curve", juce::dontSendNotification);
    aenvVelCurveLabel.attachToComponent (&aenvVelCurveComboBox, true);
    
    addAndMakeVisible(aenvLevSensSlider);
    aenvLevSensSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenvLevSensSlider.setRange (-63, 63, 1);
    aenvLevSensSlider.addListener (this);
    addAndMakeVisible (aenvLevSensLabel);
    aenvLevSensLabel.setText ("TVF Sens", juce::dontSendNotification);
    aenvLevSensLabel.attachToComponent (&aenvLevSensSlider, true);
    
    addAndMakeVisible (aenvTime1SensComboBox);
    aenvTime1SensComboBox.addListener (this);
    aenvTime1SensComboBox.addItem ("-100", 1);
    aenvTime1SensComboBox.addItem ("-70", 2);
    aenvTime1SensComboBox.addItem ("-50", 3);
    aenvTime1SensComboBox.addItem ("-40", 4);
    aenvTime1SensComboBox.addItem ("-30", 5);
    aenvTime1SensComboBox.addItem ("-20", 6);
    aenvTime1SensComboBox.addItem ("-10", 7);
    aenvTime1SensComboBox.addItem ("0", 8);
    aenvTime1SensComboBox.addItem ("10", 9);
    aenvTime1SensComboBox.addItem ("20", 10);
    aenvTime1SensComboBox.addItem ("30", 11);
    aenvTime1SensComboBox.addItem ("40", 12);
    aenvTime1SensComboBox.addItem ("50", 13);
    aenvTime1SensComboBox.addItem ("70", 14);
    aenvTime1SensComboBox.addItem ("100", 15);
    addAndMakeVisible (aenvTime1SensLabel);
    aenvTime1SensLabel.setText ("Time Sens", juce::dontSendNotification);
    aenvTime1SensLabel.attachToComponent (&aenvTime1SensComboBox, true);
    
    addAndMakeVisible (aenvTime4SensComboBox);
    aenvTime4SensComboBox.addListener (this);
    aenvTime4SensComboBox.addItem ("-100", 1);
    aenvTime4SensComboBox.addItem ("-70", 2);
    aenvTime4SensComboBox.addItem ("-50", 3);
    aenvTime4SensComboBox.addItem ("-40", 4);
    aenvTime4SensComboBox.addItem ("-30", 5);
    aenvTime4SensComboBox.addItem ("-20", 6);
    aenvTime4SensComboBox.addItem ("-10", 7);
    aenvTime4SensComboBox.addItem ("0", 8);
    aenvTime4SensComboBox.addItem ("10", 9);
    aenvTime4SensComboBox.addItem ("20", 10);
    aenvTime4SensComboBox.addItem ("30", 11);
    aenvTime4SensComboBox.addItem ("40", 12);
    aenvTime4SensComboBox.addItem ("50", 13);
    aenvTime4SensComboBox.addItem ("70", 14);
    aenvTime4SensComboBox.addItem ("100", 15);
    
    addAndMakeVisible (aenvTimeKFSensComboBox);
    aenvTimeKFSensComboBox.addListener (this);
    aenvTimeKFSensComboBox.addItem ("-100", 1);
    aenvTimeKFSensComboBox.addItem ("-70", 2);
    aenvTimeKFSensComboBox.addItem ("-50", 3);
    aenvTimeKFSensComboBox.addItem ("-40", 4);
    aenvTimeKFSensComboBox.addItem ("-30", 5);
    aenvTimeKFSensComboBox.addItem ("-20", 6);
    aenvTimeKFSensComboBox.addItem ("-10", 7);
    aenvTimeKFSensComboBox.addItem ("0", 8);
    aenvTimeKFSensComboBox.addItem ("10", 9);
    aenvTimeKFSensComboBox.addItem ("20", 10);
    aenvTimeKFSensComboBox.addItem ("30", 11);
    aenvTimeKFSensComboBox.addItem ("40", 12);
    aenvTimeKFSensComboBox.addItem ("50", 13);
    aenvTimeKFSensComboBox.addItem ("70", 14);
    aenvTimeKFSensComboBox.addItem ("100", 15);
    addAndMakeVisible (aenvTimeKFSensLabel);
    aenvTimeKFSensLabel.setText ("Time KF", juce::dontSendNotification);
    aenvTimeKFSensLabel.attachToComponent (&aenvTimeKFSensComboBox, true);
    
    addAndMakeVisible(aenv1TimeSlider);
    aenv1TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv1TimeSlider.setRange (0, 127, 1);
    aenv1TimeSlider.addListener (this);
    addAndMakeVisible (aenv1TimeLabel);
    aenv1TimeLabel.setText ("Time/Level 1", juce::dontSendNotification);
    aenv1TimeLabel.attachToComponent (&aenv1TimeSlider, true);
    addAndMakeVisible(aenv1LevelSlider);
    aenv1LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv1LevelSlider.setRange (0, 127, 1);
    aenv1LevelSlider.addListener (this);
    
    addAndMakeVisible(aenv2TimeSlider);
    aenv2TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv2TimeSlider.setRange (0, 127, 1);
    aenv2TimeSlider.addListener (this);
    addAndMakeVisible (aenv2TimeLabel);
    aenv2TimeLabel.setText ("Time/Level 2", juce::dontSendNotification);
    aenv2TimeLabel.attachToComponent (&aenv2TimeSlider, true);
    addAndMakeVisible(aenv2LevelSlider);
    aenv2LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv2LevelSlider.setRange (0, 127, 1);
    aenv2LevelSlider.addListener (this);
    
    addAndMakeVisible(aenv3TimeSlider);
    aenv3TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv3TimeSlider.setRange (0, 127, 1);
    aenv3TimeSlider.addListener (this);
    addAndMakeVisible (aenv3TimeLabel);
    aenv3TimeLabel.setText ("Time/Level 3", juce::dontSendNotification);
    aenv3TimeLabel.attachToComponent (&aenv3TimeSlider, true);
    addAndMakeVisible(aenv3LevelSlider);
    aenv3LevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv3LevelSlider.setRange (0, 127, 1);
    aenv3LevelSlider.addListener (this);
    
    addAndMakeVisible(aenv4TimeSlider);
    aenv4TimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    aenv4TimeSlider.setRange (0, 127, 1);
    aenv4TimeSlider.addListener (this);
    addAndMakeVisible (aenv4TimeLabel);
    aenv4TimeLabel.setText ("Time/Level 4", juce::dontSendNotification);
    aenv4TimeLabel.attachToComponent (&aenv4TimeSlider, true);
    
    addAndMakeVisible(drySlider);
    drySlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    drySlider.setRange (0, 127, 1);
    drySlider.addListener (this);
    addAndMakeVisible (dryLabel);
    dryLabel.setText ("Dry Send", juce::dontSendNotification);
    dryLabel.attachToComponent (&drySlider, true);
    
    addAndMakeVisible(reverbSlider);
    reverbSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    reverbSlider.setRange (0, 127, 1);
    reverbSlider.addListener (this);
    addAndMakeVisible (reverbLabel);
    reverbLabel.setText ("Reverb", juce::dontSendNotification);
    reverbLabel.attachToComponent (&reverbSlider, true);
    
    addAndMakeVisible(chorusSlider);
    chorusSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    chorusSlider.setRange (0, 127, 1);
    chorusSlider.addListener (this);
    addAndMakeVisible (chorusLabel);
    chorusLabel.setText ("Chorus", juce::dontSendNotification);
    chorusLabel.attachToComponent (&chorusSlider, true);
    
    addAndMakeVisible (outputComboBox);
    outputComboBox.addListener (this);
    outputComboBox.addItem ("MAIN", 1);
    outputComboBox.addItem ("SUB", 2);
    addAndMakeVisible (outputLabel);
    outputLabel.setText ("Output", juce::dontSendNotification);
    outputLabel.attachToComponent (&outputComboBox, true);
    
}

EditToneTab::~EditToneTab()
{
}

void EditToneTab::updateValues()
{
    Patch* patch = (Patch*) audioProcessor.status.patch;
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
    
    modDestAComboBox.setSelectedItemIndex((tone.unk_0x05 & 0xf) + 0, juce::dontSendNotification);
    modDestBComboBox.setSelectedItemIndex(((tone.unk_0x05 & 0xf0) >> 4) + 0, juce::dontSendNotification);
    modDestCComboBox.setSelectedItemIndex((tone.unk_0x06 & 0xf) + 0, juce::dontSendNotification);
    modDestDComboBox.setSelectedItemIndex(((tone.unk_0x06 & 0xf0) >> 4) + 0, juce::dontSendNotification);
    modSensASlider.setValue(int8_t((tone.unk_0x07)) - 0, juce::dontSendNotification);
    modSensBSlider.setValue(int8_t((tone.unk_0x08)) - 0, juce::dontSendNotification);
    modSensCSlider.setValue(int8_t((tone.unk_0x09)) - 0, juce::dontSendNotification);
    modSensDSlider.setValue(int8_t((tone.unk_0x0A)) - 0, juce::dontSendNotification);
    aftDestAComboBox.setSelectedItemIndex((tone.unk_0x0B & 0xf) + 0, juce::dontSendNotification);
    aftDestBComboBox.setSelectedItemIndex(((tone.unk_0x0B & 0xf0) >> 4) + 0, juce::dontSendNotification);
    aftDestCComboBox.setSelectedItemIndex((tone.unk_0x0C & 0xf) + 0, juce::dontSendNotification);
    aftDestDComboBox.setSelectedItemIndex(((tone.unk_0x0C & 0xf0) >> 4) + 0, juce::dontSendNotification);
    aftSensASlider.setValue(int8_t((tone.unk_0x0D)) - 0, juce::dontSendNotification);
    aftSensBSlider.setValue(int8_t((tone.unk_0x0E)) - 0, juce::dontSendNotification);
    aftSensCSlider.setValue(int8_t((tone.unk_0x0F)) - 0, juce::dontSendNotification);
    aftSensDSlider.setValue(int8_t((tone.unk_0x10)) - 0, juce::dontSendNotification);
    expDestAComboBox.setSelectedItemIndex((tone.unk_0x11 & 0xf) + 0, juce::dontSendNotification);
    expDestBComboBox.setSelectedItemIndex(((tone.unk_0x11 & 0xf0) >> 4) + 0, juce::dontSendNotification);
    expDestCComboBox.setSelectedItemIndex((tone.unk_0x12 & 0xf) + 0, juce::dontSendNotification);
    expDestDComboBox.setSelectedItemIndex(((tone.unk_0x12 & 0xf0) >> 4) + 0, juce::dontSendNotification);
    expSensASlider.setValue(int8_t((tone.unk_0x13)) - 0, juce::dontSendNotification);
    expSensBSlider.setValue(int8_t((tone.unk_0x14)) - 0, juce::dontSendNotification);
    expSensCSlider.setValue(int8_t((tone.unk_0x15)) - 0, juce::dontSendNotification);
    expSensDSlider.setValue(int8_t((tone.unk_0x16)) - 0, juce::dontSendNotification);
    
    lfo1FormComboBox.setSelectedItemIndex((tone.lfo1Flags & 0x7) + 0, juce::dontSendNotification);
    lfo1OffsetComboBox.setSelectedItemIndex((tone.lfo1Flags & 0x38) >> 3, juce::dontSendNotification);
    lfo1SyncToggle.setToggleState(((tone.lfo1Flags & 0x40) >> 6) ? 1 : 0, juce::dontSendNotification);
    lfo1FadeToggle.setToggleState(((tone.lfo1Flags & 0x80) >> 7) ? 1 : 0, juce::dontSendNotification);
    lfo1RateSlider.setValue(((tone.lfo1Rate)) - 0, juce::dontSendNotification);
    lfo1DelaySlider.setValue(((tone.lfo1Delay)) - 0, juce::dontSendNotification);
    lfo1FadeTimeSlider.setValue(((tone.lfo1Fade)) - 0, juce::dontSendNotification);
    lfo1PitchDepthSlider.setValue(int8_t((tone.lfo1PitchDepth)) - 0, juce::dontSendNotification);
    lfo1TVFDepthSlider.setValue(int8_t((tone.lfo1TvfDepth)) - 0, juce::dontSendNotification);
    lfo1TVADepthSlider.setValue(int8_t((tone.lfo1TvaDepth)) - 0, juce::dontSendNotification);
    
    lfo2FormComboBox.setSelectedItemIndex((tone.lfo2Flags & 0x7) + 0, juce::dontSendNotification);
    lfo2OffsetComboBox.setSelectedItemIndex((tone.lfo2Flags & 0x38) >> 3, juce::dontSendNotification);
    lfo2SyncToggle.setToggleState(((tone.lfo2Flags & 0x40) >> 6) ? 1 : 0, juce::dontSendNotification);
    lfo2FadeToggle.setToggleState(((tone.lfo2Flags & 0x80) >> 7) ? 1 : 0, juce::dontSendNotification);
    lfo2RateSlider.setValue(((tone.lfo2Rate)) - 0, juce::dontSendNotification);
    lfo2DelaySlider.setValue(((tone.lfo2Delay)) - 0, juce::dontSendNotification);
    lfo2FadeTimeSlider.setValue(((tone.lfo2Fade)) - 0, juce::dontSendNotification);
    lfo2PitchDepthSlider.setValue(int8_t((tone.lfo2PitchDepth)) - 0, juce::dontSendNotification);
    lfo2TVFDepthSlider.setValue(int8_t((tone.lfo2TvfDepth)) - 0, juce::dontSendNotification);
    lfo2TVADepthSlider.setValue(int8_t((tone.lfo2TvaDepth)) - 0, juce::dontSendNotification);
    
    pitchCoarseSlider.setValue(int8_t((tone.pitchCoarse)) - 0, juce::dontSendNotification);
    pitchFineSlider.setValue(int8_t((tone.pitchFine)) - 0, juce::dontSendNotification);
    pitchRandomComboBox.setSelectedItemIndex((tone.tvaPanningKFRandomPitch & 0xf), juce::dontSendNotification);
    pitchKFComboBox.setSelectedItemIndex((tone.tvpTimeKFKeyfollow & 0xf), juce::dontSendNotification);
    penvLevSensSlider.setValue(int8_t((tone.tvpVelocity)) - 0, juce::dontSendNotification);
    penvTime1SensComboBox.setSelectedItemIndex((tone.tvpT1T4Velocity & 0xf), juce::dontSendNotification);
    penvTime4SensComboBox.setSelectedItemIndex((tone.tvpT1T4Velocity & 0xf0) >> 4, juce::dontSendNotification);
    penvTimeKFSensComboBox.setSelectedItemIndex((tone.tvpTimeKFKeyfollow & 0xf0) >> 4, juce::dontSendNotification);
    penvDepthSlider.setValue(int8_t((tone.tvpEnvDepth)) - 0, juce::dontSendNotification);
    penv1TimeSlider.setValue(int8_t((tone.tvpEnvTime1)), juce::dontSendNotification);
    penv1LevelSlider.setValue(int8_t((tone.tvpEnvLevel1) - 0), juce::dontSendNotification);
    penv2TimeSlider.setValue(int8_t((tone.tvpEnvTime2)), juce::dontSendNotification);
    penv2LevelSlider.setValue(int8_t((tone.tvpEnvLevel2) - 0), juce::dontSendNotification);
    penv3TimeSlider.setValue(int8_t((tone.tvpEnvTime3)), juce::dontSendNotification);
    penv3LevelSlider.setValue(int8_t((tone.tvpEnvLevel3) - 0), juce::dontSendNotification);
    penv4TimeSlider.setValue(int8_t((tone.tvpEnvTime4)), juce::dontSendNotification);
    penv4LevelSlider.setValue(int8_t((tone.tvpEnvLevel4) - 0), juce::dontSendNotification);
    
    filterModeComboBox.setSelectedItemIndex((tone.tvfVeloCurveLpfHpf & 0x18) >> 3, juce::dontSendNotification);
    filterCutoffSlider.setValue(int8_t((tone.tvfCutoff)), juce::dontSendNotification);
    filterResoSlider.setValue(int8_t((tone.tvfResonance)), juce::dontSendNotification);
    filterResoModeComboBox.setSelectedItemIndex((tone.tvfResonance & 0x80) >> 7, juce::dontSendNotification);
    filterKFComboBox.setSelectedItemIndex((tone.tvfTimeKFKeyfollow & 0xf), juce::dontSendNotification);
    fenvVelCurveComboBox.setSelectedItemIndex((tone.tvfVeloCurveLpfHpf & 0x7), juce::dontSendNotification);
    fenvLevSensSlider.setValue(int8_t((tone.tvfVelocity)) - 0, juce::dontSendNotification);
    fenvTime1SensComboBox.setSelectedItemIndex((tone.tvfT1T4Velocity & 0xf), juce::dontSendNotification);
    fenvTime4SensComboBox.setSelectedItemIndex((tone.tvfT1T4Velocity & 0xf0) >> 4, juce::dontSendNotification);
    fenvTimeKFSensComboBox.setSelectedItemIndex((tone.tvfTimeKFKeyfollow & 0xf0) >> 4, juce::dontSendNotification);
    fenvDepthSlider.setValue(int8_t((tone.tvfEnvDepth)) - 0, juce::dontSendNotification);
    fenv1TimeSlider.setValue(int8_t((tone.tvfEnvTime1)), juce::dontSendNotification);
    fenv1LevelSlider.setValue(int8_t((tone.tvfEnvLevel1) - 0), juce::dontSendNotification);
    fenv2TimeSlider.setValue(int8_t((tone.tvfEnvTime2)), juce::dontSendNotification);
    fenv2LevelSlider.setValue(int8_t((tone.tvfEnvLevel2) - 0), juce::dontSendNotification);
    fenv3TimeSlider.setValue(int8_t((tone.tvfEnvTime3)), juce::dontSendNotification);
    fenv3LevelSlider.setValue(int8_t((tone.tvfEnvLevel3) - 0), juce::dontSendNotification);
    fenv4TimeSlider.setValue(int8_t((tone.tvfEnvTime4)), juce::dontSendNotification);
    fenv4LevelSlider.setValue(int8_t((tone.tvfEnvLevel4) - 0), juce::dontSendNotification);
    
    levelSlider.setValue(int8_t((tone.tvaLevel)), juce::dontSendNotification);
    levelKFComboBox.setSelectedItemIndex((tone.tvaTimeKFDelayTimeKeyfollow & 0xf), juce::dontSendNotification);
    panSlider.setValue(int8_t(tone.tvaPan - 64), juce::dontSendNotification);
    panKFComboBox.setSelectedItemIndex((tone.tvaPanningKFRandomPitch & 0xf0) >> 4, juce::dontSendNotification);
    toneDelayComboBox.setSelectedItemIndex((tone.tvaDelayModeVeloCurve & 0x18) >> 3, juce::dontSendNotification);
    toneDelayTimeSlider.setValue(int8_t((tone.unk_0x45)) - 0, juce::dontSendNotification);
    aenvVelCurveComboBox.setSelectedItemIndex((tone.tvaDelayModeVeloCurve & 0x7), juce::dontSendNotification);
    aenvLevSensSlider.setValue(int8_t((tone.tvaVelocity)) - 0, juce::dontSendNotification);
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
    auto top = 30;
    auto sliderLeft1 = 100;
    auto width = getWidth() / 3 - sliderLeft1 - 20;
    auto sliderLeft2 = sliderLeft1 + getWidth() / 3 + 10;
    auto sliderLeft3 = sliderLeft2 + getWidth() / 3 - 10;
    auto height = 20;
    auto groupMargin = 15;
    waveGroupComboBox.setBounds(sliderLeft1, top + height * -1 + groupMargin * 0, width, height);
    waveformSlider.setBounds(sliderLeft1, top + height * 0 + groupMargin * 0, width, height);
    toneSwitchToggle.setBounds(sliderLeft1 - 90, top + height * 1 + groupMargin * 0, width, height);
    FXMSwitchToggle.setBounds(sliderLeft1 + 30, top + height * 1 + groupMargin * 0, width, height);
    FXMDepthSlider.setBounds(sliderLeft1, top + height * 2 + groupMargin * 0, width, height);
    velRangeLowSlider.setBounds(sliderLeft1, top + height * 3 + groupMargin * 0, width, height);
    velRangeHighSlider.setBounds(sliderLeft1, top + height * 4 + groupMargin * 0, width, height);
    
    volumeSwitchToggle.setBounds(sliderLeft1 - 90, top + height * 5 + groupMargin * 1, width, height);
    holdSwitchToggle.setBounds(sliderLeft1 + 30, top + height * 5 + groupMargin * 1, width, height);
    modDestAComboBox.setBounds(sliderLeft1 - 60, top + height * 6 + groupMargin * 1, width / 2 + 30, height);
    modSensASlider.setBounds(sliderLeft1 + width / 2 - 30, top + height * 6 + groupMargin * 1, width / 2 + 30, height);
    modDestBComboBox.setBounds(sliderLeft1 - 60, top + height * 7 + groupMargin * 1, width / 2 + 30, height);
    modSensBSlider.setBounds(sliderLeft1 + width / 2 - 30, top + height * 7 + groupMargin * 1, width / 2 + 30, height);
    modDestCComboBox.setBounds(sliderLeft1 - 60, top + height * 8 + groupMargin * 1, width / 2 + 30, height);
    modSensCSlider.setBounds(sliderLeft1 + width / 2 - 30, top + height * 8 + groupMargin * 1, width / 2 + 30, height);
    modDestDComboBox.setBounds(sliderLeft1 - 60, top + height * 9 + groupMargin * 1, width / 2 + 30, height);
    modSensDSlider.setBounds(sliderLeft1 + width / 2 - 30, top + height * 9 + groupMargin * 1, width / 2 + 30, height);
    aftDestAComboBox.setBounds(sliderLeft1 - 60, top + height * 10 + groupMargin * 1, width / 2 + 30, height);
    aftSensASlider.setBounds(sliderLeft1 + width / 2 - 30, top + height * 10 + groupMargin * 1, width / 2 + 30, height);
    aftDestBComboBox.setBounds(sliderLeft1 - 60, top + height * 11 + groupMargin * 1, width / 2 + 30, height);
    aftSensBSlider.setBounds(sliderLeft1 + width / 2 - 30, top + height * 11 + groupMargin * 1, width / 2 + 30, height);
    aftDestCComboBox.setBounds(sliderLeft1 - 60, top + height * 12 + groupMargin * 1, width / 2 + 30, height);
    aftSensCSlider.setBounds(sliderLeft1 + width / 2 - 30, top + height * 12 + groupMargin * 1, width / 2 + 30, height);
    aftDestDComboBox.setBounds(sliderLeft1 - 60, top + height * 13 + groupMargin * 1, width / 2 + 30, height);
    aftSensDSlider.setBounds(sliderLeft1 + width / 2 - 30, top + height * 13 + groupMargin * 1, width / 2 + 30, height);
    expDestAComboBox.setBounds(sliderLeft1 - 60, top + height * 14 + groupMargin * 1, width / 2 + 30, height);
    expSensASlider.setBounds(sliderLeft1 + width / 2 - 30, top + height * 14 + groupMargin * 1, width / 2 + 30, height);
    expDestBComboBox.setBounds(sliderLeft1 - 60, top + height * 15 + groupMargin * 1, width / 2 + 30, height);
    expSensBSlider.setBounds(sliderLeft1 + width / 2 - 30, top + height * 15 + groupMargin * 1, width / 2 + 30, height);
    expDestCComboBox.setBounds(sliderLeft1 - 60, top + height * 16 + groupMargin * 1, width / 2 + 30, height);
    expSensCSlider.setBounds(sliderLeft1 + width / 2 - 30, top + height * 16 + groupMargin * 1, width / 2 + 30, height);
    expDestDComboBox.setBounds(sliderLeft1 - 60, top + height * 17 + groupMargin * 1, width / 2 + 30, height);
    expSensDSlider.setBounds(sliderLeft1 + width / 2 - 30, top + height * 17 + groupMargin * 1, width / 2 + 30, height);
    
    lfo1FormComboBox.setBounds(sliderLeft1, top + height * 18 + groupMargin * 2, width / 2, height);
    lfo1OffsetComboBox.setBounds(sliderLeft1 + width / 2, top + height * 18 + groupMargin * 2, width / 2, height);
    lfo1SyncToggle.setBounds(sliderLeft1, top + height * 19 + groupMargin * 2, width / 2, height);
    lfo1FadeToggle.setBounds(sliderLeft1 + width / 2, top + height * 19 + groupMargin * 2, width / 2, height);
    lfo1RateSlider.setBounds(sliderLeft1, top + height * 20 + groupMargin * 2, width, height);
    lfo1DelaySlider.setBounds(sliderLeft1, top + height * 21 + groupMargin * 2, width, height);
    lfo1FadeTimeSlider.setBounds(sliderLeft1, top + height * 22 + groupMargin * 2, width, height);
    lfo1PitchDepthSlider.setBounds(sliderLeft1, top + height * 23 + groupMargin * 2, width, height);
    lfo1TVFDepthSlider.setBounds(sliderLeft1, top + height * 24 + groupMargin * 2, width, height);
    lfo1TVADepthSlider.setBounds(sliderLeft1, top + height * 25 + groupMargin * 2, width, height);
    lfo2FormComboBox.setBounds(sliderLeft1, top + height * 26 + groupMargin * 3, width / 2, height);
    lfo2OffsetComboBox.setBounds(sliderLeft1 + width / 2, top + height * 26 + groupMargin * 3, width / 2, height);
    lfo2SyncToggle.setBounds(sliderLeft1, top + height * 27 + groupMargin * 3, width / 2, height);
    lfo2FadeToggle.setBounds(sliderLeft1 + width / 2, top + height * 27 + groupMargin * 3, width / 2, height);
    lfo2RateSlider.setBounds(sliderLeft1, top + height * 28 + groupMargin * 3, width, height);
    lfo2DelaySlider.setBounds(sliderLeft1, top + height * 29 + groupMargin * 3, width, height);
    lfo2FadeTimeSlider.setBounds(sliderLeft1, top + height * 30 + groupMargin * 3, width, height);
    lfo2PitchDepthSlider.setBounds(sliderLeft1, top + height * 31 + groupMargin * 3, width, height);
    lfo2TVFDepthSlider.setBounds(sliderLeft1, top + height * 32 + groupMargin * 3, width, height);
    lfo2TVADepthSlider.setBounds(sliderLeft1, top + height * 33 + groupMargin * 3, width, height);
    
    pitchCoarseSlider.setBounds(sliderLeft2, top + height * -1 + groupMargin * 0, width, height);
    pitchFineSlider.setBounds(sliderLeft2, top + height * 0 + groupMargin * 0, width, height);
    pitchRandomComboBox.setBounds(sliderLeft2, top + height * 1 + groupMargin * 0, width / 2, height);
    pitchKFComboBox.setBounds(sliderLeft2 + width / 2, top + height * 1 + groupMargin * 0, width / 2, height);
    penvLevSensSlider.setBounds(sliderLeft2, top + height * 2 + groupMargin * 0, width, height);
    penvTime1SensComboBox.setBounds(sliderLeft2, top + height * 3 + groupMargin * 0, width / 2, height);
    penvTime4SensComboBox.setBounds(sliderLeft2 + width / 2, top + height * 3 + groupMargin * 0, width / 2, height);
    penvTimeKFSensComboBox.setBounds(sliderLeft2, top + height * 4 + groupMargin * 0, width, height);
    penvDepthSlider.setBounds(sliderLeft2, top + height * 5 + groupMargin * 0, width, height);
    penv1TimeSlider.setBounds(sliderLeft2, top + height * 6 + groupMargin * 0, width / 2, height);
    penv1LevelSlider.setBounds(sliderLeft2 + width / 2, top + height * 6 + groupMargin * 0, width / 2, height);
    penv2TimeSlider.setBounds(sliderLeft2, top + height * 7 + groupMargin * 0, width / 2, height);
    penv2LevelSlider.setBounds(sliderLeft2 + width / 2, top + height * 7 + groupMargin * 0, width / 2, height);
    penv3TimeSlider.setBounds(sliderLeft2, top + height * 8 + groupMargin * 0, width / 2, height);
    penv3LevelSlider.setBounds(sliderLeft2 + width / 2, top + height * 8 + groupMargin * 0, width / 2, height);
    penv4TimeSlider.setBounds(sliderLeft2, top + height * 9 + groupMargin * 0, width / 2, height);
    penv4LevelSlider.setBounds(sliderLeft2 + width / 2, top + height * 9 + groupMargin * 0, width / 2, height);
    
    filterModeComboBox.setBounds(sliderLeft2, top + height * 10 + groupMargin * 1, width, height);
    filterCutoffSlider.setBounds(sliderLeft2, top + height * 11 + groupMargin * 1, width, height);
    filterResoSlider.setBounds(sliderLeft2, top + height * 12 + groupMargin * 1, width / 2, height);
    filterKFComboBox.setBounds(sliderLeft2, top + height * 13 + groupMargin * 1, width / 2, height);
    fenvVelCurveComboBox.setBounds(sliderLeft2 + width / 2, top + height * 13 + groupMargin * 1, width / 2, height);
    fenvLevSensSlider.setBounds(sliderLeft2, top + height * 14 + groupMargin * 1, width, height);
    fenvTime1SensComboBox.setBounds(sliderLeft2, top + height * 15 + groupMargin * 1, width / 2, height);
    fenvTime4SensComboBox.setBounds(sliderLeft2 + width / 2, top + height * 15 + groupMargin * 1, width / 2, height);
    fenvTimeKFSensComboBox.setBounds(sliderLeft2, top + height * 16 + groupMargin * 1, width, height);
    fenvDepthSlider.setBounds(sliderLeft2, top + height * 17 + groupMargin * 1, width, height);
    fenv1TimeSlider.setBounds(sliderLeft2, top + height * 18 + groupMargin * 1, width / 2, height);
    fenv1LevelSlider.setBounds(sliderLeft2 + width / 2, top + height * 18 + groupMargin * 1, width / 2, height);
    fenv2TimeSlider.setBounds(sliderLeft2, top + height * 19 + groupMargin * 1, width / 2, height);
    fenv2LevelSlider.setBounds(sliderLeft2 + width / 2, top + height * 19 + groupMargin * 1, width / 2, height);
    fenv3TimeSlider.setBounds(sliderLeft2, top + height * 20 + groupMargin * 1, width / 2, height);
    fenv3LevelSlider.setBounds(sliderLeft2 + width / 2, top + height * 20 + groupMargin * 1, width / 2, height);
    fenv4TimeSlider.setBounds(sliderLeft2, top + height * 21 + groupMargin * 1, width / 2, height);
    fenv4LevelSlider.setBounds(sliderLeft2 + width / 2, top + height * 21 + groupMargin * 1, width / 2, height);
    
    levelSlider.setBounds(sliderLeft2, top + height * 22 + groupMargin * 2, width, height);
    panSlider.setBounds(sliderLeft2, top + height * 23 + groupMargin * 2, width, height);
    levelKFComboBox.setBounds(sliderLeft2, top + height * 24 + groupMargin * 2, width / 2, height);
    panKFComboBox.setBounds(sliderLeft2 + width / 2, top + height * 24 + groupMargin * 2, width / 2, height);
    toneDelayComboBox.setBounds(sliderLeft2, top + height * 25 + groupMargin * 2, width, height);
    toneDelayTimeSlider.setBounds(sliderLeft2, top + height * 26 + groupMargin * 2, width, height);
    aenvVelCurveComboBox.setBounds(sliderLeft2, top + height * 27 + groupMargin * 2, width, height);
    aenvLevSensSlider.setBounds(sliderLeft2, top + height * 28 + groupMargin * 2, width, height);
    aenvTime1SensComboBox.setBounds(sliderLeft2, top + height * 29 + groupMargin * 2, width / 2, height);
    aenvTime4SensComboBox.setBounds(sliderLeft2 + width / 2, top + height * 29 + groupMargin * 2, width / 2, height);
    aenvTimeKFSensComboBox.setBounds(sliderLeft2, top + height * 30 + groupMargin * 2, width, height);
    aenv1TimeSlider.setBounds(sliderLeft2, top + height * 31 + groupMargin * 2, width / 2, height);
    aenv1LevelSlider.setBounds(sliderLeft2 + width / 2, top + height * 31 + groupMargin * 2, width / 2, height);
    aenv2TimeSlider.setBounds(sliderLeft2, top + height * 32 + groupMargin * 2, width / 2, height);
    aenv2LevelSlider.setBounds(sliderLeft2 + width / 2, top + height * 32 + groupMargin * 2, width / 2, height);
    aenv3TimeSlider.setBounds(sliderLeft2, top + height * 33 + groupMargin * 2, width / 2, height);
    aenv3LevelSlider.setBounds(sliderLeft2 + width / 2, top + height * 33 + groupMargin * 2, width / 2, height);
    aenv4TimeSlider.setBounds(sliderLeft2, top + height * 34 + groupMargin * 2, width / 2, height);
    
    drySlider.setBounds(sliderLeft3, top + height * 0 + groupMargin * 0, width, height);
    reverbSlider.setBounds(sliderLeft3, top + height * 1 + groupMargin * 0, width, height);
    chorusSlider.setBounds(sliderLeft3, top + height * 2 + groupMargin * 0, width, height);
    outputComboBox.setBounds(sliderLeft3, top + height * 3 + groupMargin * 0, width, height);

}

void EditToneTab::sliderValueChanged (juce::Slider* slider)
{
    sendSysexPatchToneChange();
}

void EditToneTab::buttonClicked (juce::Button* button)
{
    sendSysexPatchToneChange();
}

void EditToneTab::buttonStateChanged (juce::Button* button)
{
}

void EditToneTab::comboBoxChanged (juce::ComboBox* button)
{
    sendSysexPatchToneChange();
}

void EditToneTab::sendSysexPatchToneChange1(uint32_t address, uint8_t value)
{
      uint8_t data[5];
      data[0] = 0x00; // address MSB
      data[1] = 0x08; // address
      data[2] = 0x28 + toneCount;  // address
      data[3] = address & 127;  // address LSB
      data[4] = value;                 // data
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

void EditToneTab::sendSysexPatchToneChange2(uint32_t address, uint8_t value)
{
      uint8_t data[6];
      data[0] = 0x00; // address MSB
      data[1] = 0x08; // address
      data[2] = 0x28 + toneCount;  // address
      data[3] = address & 127;  // address LSB
      data[4] = (value & 0xf0) >> 4;                 // data
      data[5] = value & 0x0f;                 // data
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
        sendSysexPatchToneChange2(1,(uint8_t(waveformSlider.getValue() - 1)));
        sendSysexPatchToneChange1(5,(uint8_t(FXMDepthSlider.getValue() - 1)));
        sendSysexPatchToneChange1(6,(uint8_t(velRangeLowSlider.getValue())));
        sendSysexPatchToneChange1(7,(uint8_t(velRangeHighSlider.getValue())));
        sendSysexPatchToneChange1(11,(uint8_t(modSensASlider.getValue() + 64)));
        sendSysexPatchToneChange1(13,(uint8_t(modSensBSlider.getValue() + 64)));
        sendSysexPatchToneChange1(15,(uint8_t(modSensCSlider.getValue() + 64)));
        sendSysexPatchToneChange1(17,(uint8_t(modSensDSlider.getValue() + 64)));
        sendSysexPatchToneChange1(19,(uint8_t(aftSensASlider.getValue() + 64)));
        sendSysexPatchToneChange1(21,(uint8_t(aftSensBSlider.getValue() + 64)));
        sendSysexPatchToneChange1(23,(uint8_t(aftSensCSlider.getValue() + 64)));
        sendSysexPatchToneChange1(25,(uint8_t(aftSensDSlider.getValue() + 64)));
        sendSysexPatchToneChange1(27,(uint8_t(expSensASlider.getValue() + 64)));
        sendSysexPatchToneChange1(29,(uint8_t(expSensBSlider.getValue() + 64)));
        sendSysexPatchToneChange1(31,(uint8_t(expSensCSlider.getValue() + 64)));
        sendSysexPatchToneChange1(33,(uint8_t(expSensDSlider.getValue() + 64)));
        sendSysexPatchToneChange1(37,(uint8_t(lfo1RateSlider.getValue())));
        sendSysexPatchToneChange2(38,(uint8_t(lfo1DelaySlider.getValue())));
        sendSysexPatchToneChange1(41,(uint8_t(lfo1FadeTimeSlider.getValue())));
        sendSysexPatchToneChange1(42,(uint8_t(lfo1PitchDepthSlider.getValue() + 64)));
        sendSysexPatchToneChange1(43,(uint8_t(lfo1TVFDepthSlider.getValue() + 64)));
        sendSysexPatchToneChange1(44,(uint8_t(lfo1TVADepthSlider.getValue() + 64)));
        sendSysexPatchToneChange1(48,(uint8_t(lfo2RateSlider.getValue())));
        sendSysexPatchToneChange2(49,(uint8_t(lfo2DelaySlider.getValue())));
        sendSysexPatchToneChange1(52,(uint8_t(lfo2FadeTimeSlider.getValue())));
        sendSysexPatchToneChange1(53,(uint8_t(lfo2PitchDepthSlider.getValue() + 64)));
        sendSysexPatchToneChange1(54,(uint8_t(lfo2TVFDepthSlider.getValue() + 64)));
        sendSysexPatchToneChange1(55,(uint8_t(lfo2TVADepthSlider.getValue() + 64)));
        sendSysexPatchToneChange1(56,(uint8_t(pitchCoarseSlider.getValue() + 64)));
        sendSysexPatchToneChange1(57,(uint8_t(pitchFineSlider.getValue() + 64)));
        sendSysexPatchToneChange1(60,(uint8_t(penvLevSensSlider.getValue() + 64)));
        sendSysexPatchToneChange1(64,(uint8_t(penvDepthSlider.getValue() + 64)));
        sendSysexPatchToneChange1(65,(uint8_t(penv1TimeSlider.getValue())));
        sendSysexPatchToneChange1(66,(uint8_t(penv1LevelSlider.getValue() + 64)));
        sendSysexPatchToneChange1(67,(uint8_t(penv2TimeSlider.getValue())));
        sendSysexPatchToneChange1(68,(uint8_t(penv2LevelSlider.getValue() + 64)));
        sendSysexPatchToneChange1(69,(uint8_t(penv3TimeSlider.getValue())));
        sendSysexPatchToneChange1(70,(uint8_t(penv3LevelSlider.getValue() + 64)));
        sendSysexPatchToneChange1(71,(uint8_t(penv4TimeSlider.getValue())));
        sendSysexPatchToneChange1(72,(uint8_t(penv4LevelSlider.getValue() + 64)));
        sendSysexPatchToneChange1(74,(uint8_t(filterCutoffSlider.getValue())));
        sendSysexPatchToneChange1(75,(uint8_t(filterResoSlider.getValue())));
        sendSysexPatchToneChange1(79,(uint8_t(fenvLevSensSlider.getValue() + 64)));
        sendSysexPatchToneChange1(83,(uint8_t(fenvDepthSlider.getValue() + 64)));
        sendSysexPatchToneChange1(84,(uint8_t(fenv1TimeSlider.getValue())));
        sendSysexPatchToneChange1(85,(uint8_t(fenv1LevelSlider.getValue() + 64)));
        sendSysexPatchToneChange1(86,(uint8_t(fenv2TimeSlider.getValue())));
        sendSysexPatchToneChange1(87,(uint8_t(fenv2LevelSlider.getValue() + 64)));
        sendSysexPatchToneChange1(88,(uint8_t(fenv3TimeSlider.getValue())));
        sendSysexPatchToneChange1(89,(uint8_t(fenv3LevelSlider.getValue() + 64)));
        sendSysexPatchToneChange1(90,(uint8_t(fenv4TimeSlider.getValue())));
        sendSysexPatchToneChange1(91,(uint8_t(fenv4LevelSlider.getValue() + 64)));
        sendSysexPatchToneChange1(92,(uint8_t(levelSlider.getValue())));
        sendSysexPatchToneChange2(94,(uint8_t(panSlider.getValue() + 64)));
        sendSysexPatchToneChange2(98,(uint8_t(toneDelayTimeSlider.getValue())));
        sendSysexPatchToneChange1(101,(uint8_t(aenvLevSensSlider.getValue() + 64)));
        sendSysexPatchToneChange1(105,(uint8_t(aenv1TimeSlider.getValue())));
        sendSysexPatchToneChange1(106,(uint8_t(aenv1LevelSlider.getValue())));
        sendSysexPatchToneChange1(107,(uint8_t(aenv2TimeSlider.getValue())));
        sendSysexPatchToneChange1(108,(uint8_t(aenv2LevelSlider.getValue())));
        sendSysexPatchToneChange1(109,(uint8_t(aenv3TimeSlider.getValue())));
        sendSysexPatchToneChange1(110,(uint8_t(aenv3LevelSlider.getValue())));
        sendSysexPatchToneChange1(111,(uint8_t(aenv4TimeSlider.getValue())));
        sendSysexPatchToneChange1(112,(uint8_t(drySlider.getValue())));
        sendSysexPatchToneChange1(113,(uint8_t(reverbSlider.getValue())));
        sendSysexPatchToneChange1(114,(uint8_t(chorusSlider.getValue())));
        sendSysexPatchToneChange1(3,(toneSwitchToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
        sendSysexPatchToneChange1(4,(FXMSwitchToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
        sendSysexPatchToneChange1(8,(volumeSwitchToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
        sendSysexPatchToneChange1(9,(holdSwitchToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
        sendSysexPatchToneChange1(36,(lfo1SyncToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
        sendSysexPatchToneChange1(40,(lfo1FadeToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
        sendSysexPatchToneChange1(47,(lfo2SyncToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
        sendSysexPatchToneChange1(51,(lfo2FadeToggle.getToggleStateValue() == 1 ? 0x01 : 0x00));
        sendSysexPatchToneChange1(0,(waveGroupComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(10,(modDestAComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(12,(modDestBComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(14,(modDestCComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(16,(modDestDComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(18,(aftDestAComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(20,(aftDestBComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(22,(aftDestCComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(24,(aftDestDComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(26,(expDestAComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(28,(expDestBComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(30,(expDestCComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(32,(expDestDComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(34,(lfo1FormComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(35,(lfo1OffsetComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(45,(lfo2FormComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(46,(lfo2OffsetComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(58,(pitchRandomComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(59,(pitchKFComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(61,(penvTime1SensComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(62,(penvTime4SensComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(63,(penvTimeKFSensComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(73,(filterModeComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(76,(filterResoModeComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(77,(filterKFComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(78,(fenvVelCurveComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(80,(fenvTime1SensComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(81,(fenvTime4SensComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(82,(fenvTimeKFSensComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(93,(levelKFComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(96,(panKFComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(97,(toneDelayComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(100,(aenvVelCurveComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(102,(aenvTime1SensComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(103,(aenvTime4SensComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(104,(aenvTimeKFSensComboBox.getSelectedItemIndex() - 0));
        sendSysexPatchToneChange1(115,(outputComboBox.getSelectedItemIndex() - 0));
    Patch* patch = (Patch*) audioProcessor.status.patch;
    Tone* tone = &patch->tones[toneCount];
    
    tone->flags = uint8_t(waveGroupComboBox.getSelectedItemIndex() + (toneSwitchToggle.getToggleState() << 7));
    tone->waveNumber = uint8_t(waveformSlider.getValue() - 1);
    tone->fxmConfig = uint8_t(FXMDepthSlider.getValue() + (FXMSwitchToggle.getToggleState() << 7));
    tone->velocityRangeLow = uint8_t(velRangeLowSlider.getValue());
    tone->velocityRangeUp = uint8_t(velRangeHighSlider.getValue());
    tone->unk_0x05 = uint8_t(modDestAComboBox.getSelectedItemIndex() + (modDestBComboBox.getSelectedItemIndex() << 4));
    tone->unk_0x06 = uint8_t(modDestCComboBox.getSelectedItemIndex() + (modDestDComboBox.getSelectedItemIndex() << 4));
    tone->unk_0x07 = uint8_t(modSensASlider.getValue());
    tone->unk_0x08 = uint8_t(modSensBSlider.getValue());
    tone->unk_0x09 = uint8_t(modSensCSlider.getValue());
    tone->unk_0x0A = uint8_t(modSensDSlider.getValue());
    tone->unk_0x0B = uint8_t(aftDestAComboBox.getSelectedItemIndex() + (aftDestBComboBox.getSelectedItemIndex() << 4));
    tone->unk_0x0C = uint8_t(aftDestCComboBox.getSelectedItemIndex() + (aftDestDComboBox.getSelectedItemIndex() << 4));
    tone->unk_0x0D = uint8_t(aftSensASlider.getValue());
    tone->unk_0x0E = uint8_t(aftSensBSlider.getValue());
    tone->unk_0x0F = uint8_t(aftSensCSlider.getValue());
    tone->unk_0x10 = uint8_t(aftSensDSlider.getValue());
    tone->unk_0x11 = uint8_t(expDestAComboBox.getSelectedItemIndex() + (expDestBComboBox.getSelectedItemIndex() << 4));
    tone->unk_0x12 = uint8_t(expDestCComboBox.getSelectedItemIndex() + (expDestDComboBox.getSelectedItemIndex() << 4));
    tone->unk_0x13 = uint8_t(expSensASlider.getValue());
    tone->unk_0x14 = uint8_t(expSensBSlider.getValue());
    tone->unk_0x15 = uint8_t(expSensCSlider.getValue());
    tone->unk_0x16 = uint8_t(expSensDSlider.getValue());
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
    tone->unk_0x45 = uint8_t(toneDelayTimeSlider.getValue());
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
