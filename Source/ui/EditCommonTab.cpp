/*
  ==============================================================================

    EditCommonTab.cpp
    Created: 20 Aug 2024 2:33:58pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EditCommonTab.h"
#include "../dataStructures.h"

//==============================================================================
EditCommonTab::EditCommonTab(Jv880_juceAudioProcessor& p) : audioProcessor (p)
{
    addAndMakeVisible (patchNameEditor);
    addAndMakeVisible (patchNameLabel);
    patchNameLabel.setText ("Patch Name", juce::dontSendNotification);
    patchNameLabel.attachToComponent (&patchNameEditor, true);

    addAndMakeVisible (velocitySwitchToggle);
    velocitySwitchToggle.addListener (this);
    velocitySwitchToggle.setButtonText ("Velocity Switch");

    addAndMakeVisible(reverbTypeLabel);
    reverbTypeLabel.setText ("Reverb Type", juce::dontSendNotification);
    reverbTypeLabel.attachToComponent (&reverbTypeComboBox, true);
    addAndMakeVisible (reverbTypeComboBox);
    reverbTypeComboBox.addListener (this);
    reverbTypeComboBox.addItem ("Room 1", 1);
    reverbTypeComboBox.addItem ("Room 2", 2);
    reverbTypeComboBox.addItem ("Stage 1", 3);
    reverbTypeComboBox.addItem ("Stage 2", 4);
    reverbTypeComboBox.addItem ("Hall 1", 5);
    reverbTypeComboBox.addItem ("Hall 2", 6);
    reverbTypeComboBox.addItem ("Delay", 7);
    reverbTypeComboBox.addItem ("Pan-Delay", 8);

    addAndMakeVisible (reverbLevelSlider);
    reverbLevelSlider.setRange (0, 127);
    reverbLevelSlider.addListener (this);
    addAndMakeVisible (reverbLevelLabel);
    reverbLevelLabel.setText ("Reverb Level", juce::dontSendNotification);
    reverbLevelLabel.attachToComponent (&reverbLevelSlider, true);

    addAndMakeVisible (reverbTimeSlider);
    reverbTimeSlider.setRange (0, 127);
    reverbTimeSlider.addListener (this);
    addAndMakeVisible (reverbTimeLabel);
    reverbTimeLabel.setText ("Reverb Time", juce::dontSendNotification);
    reverbTimeLabel.attachToComponent (&reverbTimeSlider, true);

    addAndMakeVisible (delayFeedbackSlider);
    delayFeedbackSlider.setRange (0, 127);
    delayFeedbackSlider.addListener (this);
    addAndMakeVisible (delayFeedbackLabel);
    delayFeedbackLabel.setText ("Delay Feedback", juce::dontSendNotification);
    delayFeedbackLabel.attachToComponent (&delayFeedbackSlider, true);

    addAndMakeVisible(chorusTypeLabel);
    chorusTypeLabel.setText ("Chorus Type", juce::dontSendNotification);
    chorusTypeLabel.attachToComponent (&chorusTypeComboBox, true);
    addAndMakeVisible(chorusTypeComboBox);
    chorusTypeComboBox.addListener (this);
    chorusTypeComboBox.addItem ("Chorus 1", 1);
    chorusTypeComboBox.addItem ("Chorus 2", 2);
    chorusTypeComboBox.addItem ("Chorus 3", 3);
    
    addAndMakeVisible(chorusLevelSlider);
    chorusLevelSlider.setRange (0, 127);
    chorusLevelSlider.addListener (this);
    addAndMakeVisible(chorusLevelLabel);
    chorusLevelLabel.setText ("Chorus Level", juce::dontSendNotification);
    chorusLevelLabel.attachToComponent (&chorusLevelSlider, true);
    
    addAndMakeVisible(chorusDepthSlider);
    chorusDepthSlider.setRange (0, 127);
    chorusDepthSlider.addListener (this);
    addAndMakeVisible(chorusDepthLabel);
    chorusDepthLabel.setText ("Chorus Depth", juce::dontSendNotification);
    chorusDepthLabel.attachToComponent (&chorusDepthSlider, true);
    
    addAndMakeVisible(chorusFeedbackSlider);
    chorusFeedbackSlider.setRange (0, 127);
    chorusFeedbackSlider.addListener (this);
    addAndMakeVisible(chorusFeedbackLabel);
    chorusFeedbackLabel.setText ("Chorus Feedback", juce::dontSendNotification);
    chorusFeedbackLabel.attachToComponent (&chorusFeedbackSlider, true);

    addAndMakeVisible(chorusOutputLabel);
    chorusOutputLabel.setText ("Chorus Output", juce::dontSendNotification);
    chorusOutputLabel.attachToComponent (&chorusOutputComboBox, true);
    addAndMakeVisible(chorusOutputComboBox);
    chorusOutputComboBox.addListener (this);
    chorusOutputComboBox.addItem ("MIX", 1);
    chorusOutputComboBox.addItem ("REV", 2);
    
    addAndMakeVisible(analogFeelSlider);
    analogFeelSlider.setRange (0, 127);
    analogFeelSlider.addListener (this);
    addAndMakeVisible(analogFeelLabel);
    analogFeelLabel.setText ("Analog Feel", juce::dontSendNotification);
    analogFeelLabel.attachToComponent (&analogFeelSlider, true);
    
    addAndMakeVisible(levelSlider);
    levelSlider.setRange (0, 127);
    levelSlider.addListener (this);
    addAndMakeVisible(levelLabel);
    levelLabel.setText ("Level", juce::dontSendNotification);
    levelLabel.attachToComponent (&levelSlider, true);
    
    addAndMakeVisible(panSlider);
    panSlider.setRange (0, 127);
    panSlider.addListener (this);
    addAndMakeVisible(panLabel);
    panLabel.setText ("Pan", juce::dontSendNotification);
    panLabel.attachToComponent (&panSlider, true);
    
    addAndMakeVisible(bendRangeDownSlider);
    bendRangeDownSlider.setRange (16, 64);
    bendRangeDownSlider.addListener (this);
    addAndMakeVisible(bendRangeDownLabel);
    bendRangeDownLabel.setText ("Bend Range Down", juce::dontSendNotification);
    bendRangeDownLabel.attachToComponent (&bendRangeDownSlider, true);
    
    addAndMakeVisible(bendRangeUpSlider);
    bendRangeUpSlider.setRange (0, 12);
    bendRangeUpSlider.addListener (this);
    addAndMakeVisible(bendRangeUpLabel);
    bendRangeUpLabel.setText ("Bend Range Up", juce::dontSendNotification);
    bendRangeUpLabel.attachToComponent (&bendRangeUpSlider, true);

    addAndMakeVisible(keyAssignLabel);
    keyAssignLabel.setText ("Key Assign", juce::dontSendNotification);
    keyAssignLabel.attachToComponent (&keyAssignComboBox, true);
    addAndMakeVisible(keyAssignComboBox);
    keyAssignComboBox.addListener (this);
    keyAssignComboBox.addItem ("POLY", 1);
    keyAssignComboBox.addItem ("SOLO", 2);

    addAndMakeVisible (soloLegatoToggle);
    soloLegatoToggle.addListener (this);
    soloLegatoToggle.setButtonText ("Solo Legato");

    addAndMakeVisible (portamentoToggle);
    portamentoToggle.addListener (this);
    portamentoToggle.setButtonText ("Portamento");

    addAndMakeVisible(portamentoModeLabel);
    portamentoModeLabel.setText ("Portamento Mode", juce::dontSendNotification);
    portamentoModeLabel.attachToComponent (&portamentoModeComboBox, true);
    addAndMakeVisible(portamentoModeComboBox);
    portamentoModeComboBox.addListener (this);
    portamentoModeComboBox.addItem ("LEGATO", 1);
    portamentoModeComboBox.addItem ("NORMAL", 2);

    addAndMakeVisible(portamentoTypeLabel);
    portamentoTypeLabel.setText ("Portamento Type", juce::dontSendNotification);
    portamentoTypeLabel.attachToComponent (&portamentoTypeComboBox, true);
    addAndMakeVisible(portamentoTypeComboBox);
    portamentoTypeComboBox.addListener (this);
    portamentoTypeComboBox.addItem ("TIME", 1);
    portamentoTypeComboBox.addItem ("RATE", 2);
    
    addAndMakeVisible(portamentoTimeSlider);
    portamentoTimeSlider.setRange (0, 127);
    portamentoTimeSlider.addListener (this);
    addAndMakeVisible(portamentoTimeLabel);
    portamentoTimeLabel.setText ("Portamento Time", juce::dontSendNotification);
    portamentoTimeLabel.attachToComponent (&portamentoTimeSlider, true);
}

EditCommonTab::~EditCommonTab()
{
}

void EditCommonTab::updateValues()
{
    Patch* patch = (Patch*) audioProcessor.status.patch;

    patchNameEditor         .setText(juce::String(patch->name, 0xc), juce::dontSendNotification);
    velocitySwitchToggle    .setToggleState((patch->recChorConfig & 0x80) != 0, juce::dontSendNotification);
    reverbTypeComboBox      .setSelectedItemIndex(patch->recChorConfig & 0xf, juce::dontSendNotification);
    reverbLevelSlider       .setValue(patch->reverbLevel, juce::dontSendNotification);
    reverbTimeSlider        .setValue(patch->reverbTime, juce::dontSendNotification);
    delayFeedbackSlider     .setValue(patch->reverbFeedback, juce::dontSendNotification);
    chorusTypeComboBox      .setSelectedItemIndex((patch->recChorConfig >> 4) & 0x3, juce::dontSendNotification);
    chorusLevelSlider       .setValue(patch->chorusLevel & 0x7f, juce::dontSendNotification);
    chorusDepthSlider       .setValue(patch->chorusDepth, juce::dontSendNotification);
    chorusFeedbackSlider    .setValue(patch->chorusFeedback, juce::dontSendNotification);
    chorusOutputComboBox    .setSelectedItemIndex((patch->chorusLevel & 0x80) != 0, juce::dontSendNotification);
    analogFeelSlider        .setValue(patch->analogFeel, juce::dontSendNotification);
    levelSlider             .setValue(patch->level, juce::dontSendNotification);
    panSlider               .setValue(patch->pan, juce::dontSendNotification);
    bendRangeDownSlider     .setValue((patch->bendRange << 4)  & 0xf, juce::dontSendNotification);
    bendRangeUpSlider       .setValue(patch->bendRange & 0xf, juce::dontSendNotification);
    keyAssignComboBox       .setSelectedItemIndex((patch->flags & 0x80) != 0, juce::dontSendNotification);
    soloLegatoToggle        .setToggleState((patch->flags & 0x20) != 0, juce::dontSendNotification);
    portamentoToggle        .setToggleState((patch->flags & 0x40) != 0, juce::dontSendNotification);
    portamentoModeComboBox  .setSelectedItemIndex((patch->flags & 0x10) != 0, juce::dontSendNotification);
    portamentoTypeComboBox  .setSelectedItemIndex((patch->portamentoTime & 0x80) != 0, juce::dontSendNotification);
    portamentoTimeSlider    .setValue(patch->portamentoTime & 0x7f, juce::dontSendNotification);
}

void EditCommonTab::visibilityChanged()
{
    updateValues();
}

void EditCommonTab::resized()
{
    auto top = 30;
    auto sliderLeft1 = 120;
    auto width = getWidth() / 2 - sliderLeft1 - 20;
    auto sliderLeft2 = getWidth() / 2 + sliderLeft1 + 10;
    auto height = 32;
    auto groupMargin = 24;

    patchNameEditor        .setBounds(sliderLeft1, top + height * 0 + groupMargin * 0, width, height);
    velocitySwitchToggle   .setBounds(sliderLeft1, top + height * 1 + groupMargin * 0, width, height);

    reverbTypeComboBox     .setBounds(sliderLeft1, top + height * 2 + groupMargin * 1, width, height);
    reverbLevelSlider      .setBounds(sliderLeft1, top + height * 3 + groupMargin * 1, width, height);
    reverbTimeSlider       .setBounds(sliderLeft1, top + height * 4 + groupMargin * 1, width, height);
    delayFeedbackSlider    .setBounds(sliderLeft1, top + height * 5 + groupMargin * 1, width, height);
    
    chorusTypeComboBox     .setBounds(sliderLeft1, top + height * 6 + groupMargin * 2, width, height);
    chorusLevelSlider      .setBounds(sliderLeft1, top + height * 7 + groupMargin * 2, width, height);
    chorusDepthSlider      .setBounds(sliderLeft1, top + height * 8 + groupMargin * 2, width, height);
    chorusFeedbackSlider   .setBounds(sliderLeft1, top + height * 9 + groupMargin * 2, width, height);
    chorusOutputComboBox   .setBounds(sliderLeft1, top + height * 10 + groupMargin * 2, width, height);
    
    analogFeelSlider       .setBounds(sliderLeft2, top + height * 0 + groupMargin * 0, width, height);
    levelSlider            .setBounds(sliderLeft2, top + height * 1 + groupMargin * 0, width, height);
    panSlider              .setBounds(sliderLeft2, top + height * 2 + groupMargin * 0, width, height);
    
    bendRangeDownSlider    .setBounds(sliderLeft2, top + height * 3 + groupMargin * 1, width, height);
    bendRangeUpSlider      .setBounds(sliderLeft2, top + height * 4 + groupMargin * 1, width, height);
    keyAssignComboBox      .setBounds(sliderLeft2, top + height * 5 + groupMargin * 1, width, height);
    soloLegatoToggle       .setBounds(sliderLeft2, top + height * 6 + groupMargin * 1, width, height);
    portamentoToggle       .setBounds(sliderLeft2, top + height * 7 + groupMargin * 1, width, height);
    portamentoModeComboBox .setBounds(sliderLeft2, top + height * 8 + groupMargin * 1, width, height);
    portamentoTypeComboBox .setBounds(sliderLeft2, top + height * 9 + groupMargin * 1, width, height);
    portamentoTimeSlider   .setBounds(sliderLeft2, top + height * 10 + groupMargin * 1, width, height);
}

void EditCommonTab::sliderValueChanged (juce::Slider* slider)
{
    // if (slider == &masterTuneSlider) {
    //   uint32_t address = 0x01;
    //   uint8_t value = (uint8_t) masterTuneSlider.getValue();
    //   audioProcessor.sendSysexParamChange(address, value);
    // }
}

void EditCommonTab::buttonClicked (juce::Button* button)
{
    // if (button == &reverbToggle) {
    //   uint32_t address = 0x04;
    //   uint8_t value = reverbToggle.getToggleState() ? 1 : 0;
    //   audioProcessor.sendSysexParamChange(address, value);
    // }
    // if (button == &chorusToggle) {
    //   uint32_t address = 0x05;
    //   uint8_t value = chorusToggle.getToggleState() ? 1 : 0;
    //   audioProcessor.sendSysexParamChange(address, value);
    // }
}

void EditCommonTab::buttonStateChanged (juce::Button* button)
{
}

void EditCommonTab::comboBoxChanged (juce::ComboBox* button)
{
}
