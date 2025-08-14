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
    addAndMakeVisible(patchNameEditor);
    patchNameEditor.addListener(this);
    patchNameEditor.setInputRestrictions(MAX_PATCH_NAME_CHARS,
                                         " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-*/#!,.");
    addAndMakeVisible(patchNameLabel);
    patchNameLabel.setText("Patch Name", juce::dontSendNotification);
    patchNameLabel.attachToComponent(&patchNameEditor, true);

    addAndMakeVisible(velocitySwitchToggle);
    velocitySwitchToggle.addListener(this);
    velocitySwitchToggle.setButtonText ("Velocity Switch");

    addAndMakeVisible(reverbTypeLabel);
    reverbTypeLabel.setText("Reverb", juce::dontSendNotification);
    reverbTypeLabel.attachToComponent(&reverbTypeComboBox, true);
    addAndMakeVisible(reverbTypeComboBox);
    reverbTypeComboBox.addListener(this);
    reverbTypeComboBox.setScrollWheelEnabled (true);
    reverbTypeComboBox.addItem("Room 1", 1);
    reverbTypeComboBox.addItem("Room 2", 2);
    reverbTypeComboBox.addItem("Stage 1", 3);
    reverbTypeComboBox.addItem("Stage 2", 4);
    reverbTypeComboBox.addItem("Hall 1", 5);
    reverbTypeComboBox.addItem("Hall 2", 6);
    reverbTypeComboBox.addItem("Delay", 7);
    reverbTypeComboBox.addItem("Pan Delay", 8);

    addAndMakeVisible(reverbLevelSlider);
    reverbLevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    reverbLevelSlider.setRange (0, 127, 1);
    reverbLevelSlider.addListener(this);
    addAndMakeVisible(reverbLevelLabel);
    reverbLevelLabel.setText("Level", juce::dontSendNotification);
    reverbLevelLabel.attachToComponent(&reverbLevelSlider, true);

    addAndMakeVisible(reverbTimeSlider);
    reverbTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    reverbTimeSlider.setRange (0, 127, 1);
    reverbTimeSlider.addListener(this);
    addAndMakeVisible(reverbTimeLabel);
    reverbTimeLabel.setText("Time", juce::dontSendNotification);
    reverbTimeLabel.attachToComponent(&reverbTimeSlider, true);

    addAndMakeVisible(delayFeedbackSlider);
    delayFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    delayFeedbackSlider.setRange (0, 127, 1);
    delayFeedbackSlider.addListener(this);
    addAndMakeVisible(delayFeedbackLabel);
    delayFeedbackLabel.setText("Feedback", juce::dontSendNotification);
    delayFeedbackLabel.attachToComponent(&delayFeedbackSlider, true);

    addAndMakeVisible(chorusTypeLabel);
    chorusTypeLabel.setText("Chorus", juce::dontSendNotification);
    chorusTypeLabel.attachToComponent(&chorusTypeComboBox, true);
    addAndMakeVisible(chorusTypeComboBox);
    chorusTypeComboBox.addListener(this);
    chorusTypeComboBox.setScrollWheelEnabled (true);
    chorusTypeComboBox.addItem("Type 1", 1);
    chorusTypeComboBox.addItem("Type 2", 2);
    chorusTypeComboBox.addItem("Type 3", 3);
    
    addAndMakeVisible(chorusLevelSlider);
    chorusLevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    chorusLevelSlider.setRange (0, 127, 1);
    chorusLevelSlider.addListener(this);
    addAndMakeVisible(chorusLevelLabel);
    chorusLevelLabel.setText("Level", juce::dontSendNotification);
    chorusLevelLabel.attachToComponent(&chorusLevelSlider, true);
    
    addAndMakeVisible(chorusDepthSlider);
    chorusDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    chorusDepthSlider.setRange (0, 127, 1);
    chorusDepthSlider.addListener(this);
    addAndMakeVisible(chorusDepthLabel);
    chorusDepthLabel.setText("Depth", juce::dontSendNotification);
    chorusDepthLabel.attachToComponent(&chorusDepthSlider, true);
    
    addAndMakeVisible(chorusRateSlider);
    chorusRateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    chorusRateSlider.setRange (0, 127, 1);
    chorusRateSlider.addListener(this);
    addAndMakeVisible(chorusRateSlider);
    chorusRateLabel.setText("Rate", juce::dontSendNotification);
    chorusRateLabel.attachToComponent(&chorusRateSlider, true);
    
    addAndMakeVisible(chorusFeedbackSlider);
    chorusFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    chorusFeedbackSlider.setRange (0, 127, 1);
    chorusFeedbackSlider.addListener(this);
    addAndMakeVisible(chorusFeedbackLabel);
    chorusFeedbackLabel.setText("Feedback", juce::dontSendNotification);
    chorusFeedbackLabel.attachToComponent(&chorusFeedbackSlider, true);

    addAndMakeVisible(chorusOutputLabel);
    chorusOutputLabel.setText("Output", juce::dontSendNotification);
    chorusOutputLabel.attachToComponent(&chorusOutputComboBox, true);
    addAndMakeVisible(chorusOutputComboBox);
    chorusOutputComboBox.addListener(this);
    chorusOutputComboBox.setScrollWheelEnabled (true);
    chorusOutputComboBox.addItem("Mix", 1);
    chorusOutputComboBox.addItem("Reverb", 2);
    
    addAndMakeVisible(analogFeelSlider);
    analogFeelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    analogFeelSlider.setRange (0, 127, 1);
    analogFeelSlider.addListener(this);
    addAndMakeVisible(analogFeelLabel);
    analogFeelLabel.setText("Analog Feel", juce::dontSendNotification);
    analogFeelLabel.attachToComponent(&analogFeelSlider, true);
    
    addAndMakeVisible(levelSlider);
    levelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    levelSlider.setRange (0, 127, 1);
    levelSlider.addListener(this);
    addAndMakeVisible(levelLabel);
    levelLabel.setText("Level", juce::dontSendNotification);
    levelLabel.attachToComponent(&levelSlider, true);
    
    addAndMakeVisible(panSlider);
    panSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    panSlider.setRange (0, 127, 1);
    panSlider.addListener(this);
    addAndMakeVisible(panLabel);
    panLabel.setText("Pan", juce::dontSendNotification);
    panLabel.attachToComponent(&panSlider, true);
    
    addAndMakeVisible(bendRangeDownSlider);
    bendRangeDownSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    bendRangeDownSlider.setRange (-48, 0, 1);
    bendRangeDownSlider.addListener(this);

    addAndMakeVisible(bendRangeLabel);
    bendRangeLabel.setText("Bend Range", juce::dontSendNotification);
    bendRangeLabel.attachToComponent(&bendRangeDownSlider, true);
    
    addAndMakeVisible(bendRangeUpSlider);
    bendRangeUpSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    bendRangeUpSlider.setRange (0, 12, 1);
    bendRangeUpSlider.addListener(this);

    addAndMakeVisible(keyAssignLabel);
    keyAssignLabel.setText("Key Assign", juce::dontSendNotification);
    keyAssignLabel.attachToComponent(&keyAssignComboBox, true);
    addAndMakeVisible(keyAssignComboBox);
    keyAssignComboBox.addListener(this);
    keyAssignComboBox.setScrollWheelEnabled (true);
    keyAssignComboBox.addItem("Poly", 1);
    keyAssignComboBox.addItem("Solo", 2);

    addAndMakeVisible(soloLegatoToggle);
    soloLegatoToggle.addListener(this);
    soloLegatoToggle.setButtonText ("Legato");

    addAndMakeVisible(portamentoToggle);
    portamentoToggle.addListener(this);
    portamentoToggle.setButtonText ("Portamento");

    addAndMakeVisible(portamentoModeLabel);
    portamentoModeLabel.setText("Mode", juce::dontSendNotification);
    portamentoModeLabel.attachToComponent(&portamentoModeComboBox, true);
    addAndMakeVisible(portamentoModeComboBox);
    portamentoModeComboBox.addListener(this);
    portamentoModeComboBox.setScrollWheelEnabled (true);
    portamentoModeComboBox.addItem("Legato", 1);
    portamentoModeComboBox.addItem("Normal", 2);

    addAndMakeVisible(portamentoTypeLabel);
    portamentoTypeLabel.setText("Type", juce::dontSendNotification);
    portamentoTypeLabel.attachToComponent(&portamentoTypeComboBox, true);
    addAndMakeVisible(portamentoTypeComboBox);
    portamentoTypeComboBox.addListener(this);
    portamentoTypeComboBox.setScrollWheelEnabled (true);
    portamentoTypeComboBox.addItem("Time", 1);
    portamentoTypeComboBox.addItem("Rate", 2);
    
    addAndMakeVisible(portamentoTimeSlider);
    portamentoTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    portamentoTimeSlider.setRange (0, 127, 1);
    portamentoTimeSlider.addListener(this);
    addAndMakeVisible(portamentoTimeLabel);
    portamentoTimeLabel.setText("Time", juce::dontSendNotification);
    portamentoTimeLabel.attachToComponent(&portamentoTimeSlider, true);
}

EditCommonTab::~EditCommonTab()
{
}

void EditCommonTab::updateValues()
{
    Patch* patch = (Patch*) audioProcessor.status.patch;

    patchNameEditor         .setText(juce::String(patch->name, 0xc), juce::dontSendNotification);
    velocitySwitchToggle    .setToggleState((patch->recChorConfig & 0x80) != 0, juce::dontSendNotification);
    reverbTypeComboBox      .setSelectedItemIndex(patch->recChorConfig & 0x7, juce::dontSendNotification);
    reverbLevelSlider       .setValue(patch->reverbLevel, juce::dontSendNotification);
    reverbTimeSlider        .setValue(patch->reverbTime, juce::dontSendNotification);
    delayFeedbackSlider     .setValue(patch->reverbFeedback, juce::dontSendNotification);
    chorusTypeComboBox      .setSelectedItemIndex((patch->recChorConfig >> 4) & 0x3, juce::dontSendNotification);
    chorusLevelSlider       .setValue(patch->chorusLevel & 0x7f, juce::dontSendNotification);
    chorusDepthSlider       .setValue(patch->chorusDepth, juce::dontSendNotification);
    chorusRateSlider        .setValue(patch->chorusRate, juce::dontSendNotification);
    chorusFeedbackSlider    .setValue(patch->chorusFeedback, juce::dontSendNotification);
    chorusOutputComboBox    .setSelectedItemIndex((patch->chorusLevel & 0x80) != 0, juce::dontSendNotification);
    analogFeelSlider        .setValue(patch->analogFeel, juce::dontSendNotification);
    levelSlider             .setValue(patch->level, juce::dontSendNotification);
    panSlider               .setValue(patch->pan, juce::dontSendNotification);
    bendRangeDownSlider     .setValue(((patch->bendRange) & 0x3f) - 64, juce::dontSendNotification);
    bendRangeUpSlider       .setValue(patch->flags & 0xf, juce::dontSendNotification);
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
    const auto top = 30;
    const auto sliderLeft1 = 120;
    const auto width = getWidth() / 2 - sliderLeft1 - 10;
    const auto halfWidth = width / 2;
    const auto sliderLeft2 = getWidth() / 2 + sliderLeft1 + 0;
    const auto height = 24;
    const auto vMargin = 24;

    patchNameEditor        .setBounds(sliderLeft1, top + height * 0 + vMargin * 0, halfWidth, height);
    velocitySwitchToggle   .setBounds(sliderLeft1 + halfWidth, top + height * 0 + vMargin * 0, halfWidth, height);

    reverbTypeComboBox     .setBounds(sliderLeft1, top + height * 1 + vMargin * 1, width, height);
    reverbLevelSlider      .setBounds(sliderLeft1, top + height * 2 + vMargin * 1, width, height);
    reverbTimeSlider       .setBounds(sliderLeft1, top + height * 3 + vMargin * 1, width, height);
    delayFeedbackSlider    .setBounds(sliderLeft1, top + height * 4 + vMargin * 1, width, height);
    
    chorusTypeComboBox     .setBounds(sliderLeft1, top + height * 5 + vMargin * 2, width, height);
    chorusLevelSlider      .setBounds(sliderLeft1, top + height * 6 + vMargin * 2, width, height);
    chorusDepthSlider      .setBounds(sliderLeft1, top + height * 7 + vMargin * 2, width, height);
    chorusRateSlider       .setBounds(sliderLeft1, top + height * 8 + vMargin * 2, width, height);
    chorusFeedbackSlider   .setBounds(sliderLeft1, top + height * 9 + vMargin * 2, width, height);
    chorusOutputComboBox   .setBounds(sliderLeft1, top + height * 10 + vMargin * 2, width, height);
    
    levelSlider            .setBounds(sliderLeft2, top + height * 0 + vMargin * 0, width, height);
    panSlider              .setBounds(sliderLeft2, top + height * 1 + vMargin * 0, width, height);

    analogFeelSlider       .setBounds(sliderLeft2, top + height * 2 + vMargin * 1, width, height);

    bendRangeDownSlider    .setBounds(sliderLeft2, top + height * 3 + vMargin * 2, halfWidth, height);
    bendRangeUpSlider      .setBounds(sliderLeft2 + halfWidth, top + height * 3 + vMargin * 2, halfWidth, height);

    keyAssignComboBox      .setBounds(sliderLeft2, top + height * 4 + vMargin * 3, halfWidth, height);
    soloLegatoToggle       .setBounds(sliderLeft2 + halfWidth, top + height * 4 + vMargin * 3, halfWidth, height);

    portamentoToggle       .setBounds(sliderLeft2, top + height * 5 + vMargin * 4, width, height);
    portamentoModeComboBox .setBounds(sliderLeft2, top + height * 6 + vMargin * 4, width, height);
    portamentoTypeComboBox .setBounds(sliderLeft2, top + height * 7 + vMargin * 4, width, height);
    portamentoTimeSlider   .setBounds(sliderLeft2, top + height * 8 + vMargin * 4, width, height);
}

void EditCommonTab::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &reverbLevelSlider)
        sendSysexPatchCommonChange();
    else if (slider == &reverbTimeSlider)
        sendSysexPatchCommonChange();
    else if (slider == &delayFeedbackSlider)
        sendSysexPatchCommonChange();
    else if (slider == &chorusLevelSlider)
        sendSysexPatchCommonChange();
    else if (slider == &chorusDepthSlider)
        sendSysexPatchCommonChange();
    else if (slider == &chorusRateSlider)
        sendSysexPatchCommonChange();
    else if (slider == &chorusFeedbackSlider)
        sendSysexPatchCommonChange();
    else if (slider == &analogFeelSlider)
        sendSysexPatchCommonChange();
    else if (slider == &levelSlider)
        sendSysexPatchCommonChange();
    else if (slider == &panSlider)
        sendSysexPatchCommonChange();
    else if (slider == &bendRangeDownSlider)
        sendSysexPatchCommonChange();
    else if (slider == &bendRangeUpSlider)
        sendSysexPatchCommonChange();
    else if (slider == &portamentoTimeSlider)
        sendSysexPatchCommonChange();
}

void EditCommonTab::buttonClicked (juce::Button* button)
{
    if (button == &velocitySwitchToggle)
        sendSysexPatchCommonChange();
    else if (button == &soloLegatoToggle)
        sendSysexPatchCommonChange();
    else if (button == &portamentoToggle)
        sendSysexPatchCommonChange();
}

void EditCommonTab::buttonStateChanged (juce::Button* button)
{
}

void EditCommonTab::comboBoxChanged (juce::ComboBox* comboBox)
{
    if (comboBox == &reverbTypeComboBox)
        sendSysexPatchCommonChange();
    else if (comboBox == &chorusTypeComboBox)
        sendSysexPatchCommonChange();
    else if (comboBox == &chorusOutputComboBox)
        sendSysexPatchCommonChange();
    else if (comboBox == &keyAssignComboBox)
        sendSysexPatchCommonChange();
    else if (comboBox == &portamentoModeComboBox)
        sendSysexPatchCommonChange();
    else if (comboBox == &portamentoTypeComboBox)
        sendSysexPatchCommonChange();
}

void EditCommonTab::textEditorTextChanged (juce::TextEditor& textEditor)
{
    if (&textEditor == &patchNameEditor)
        sendSysexPatchCommonChange();
}

void EditCommonTab::sendSysexPatchCommonChange()
{
    Patch* patch = (Patch*) audioProcessor.status.patch;
    
    uint8_t buf[45];

    buf[0] = 0xf0;
    buf[1] = 0x41;
    buf[2] = 0x10; // unit number
    buf[3] = 0x46;
    buf[4] = 0x12; // command
    buf[5] = 0x00;
    buf[6] = 0x08;
    buf[7] = 0x20;
    buf[8] = 0x00;

    for (int i = 0; i < juce::jmin(MAX_PATCH_NAME_CHARS, patchNameEditor.getText().length()); i++)
    {
        buf[i + 9] = patchNameEditor.getText()[i];
    }

    if (patchNameEditor.getText().length() < MAX_PATCH_NAME_CHARS)
    {
        for (int i = patchNameEditor.getText().length(); i < MAX_PATCH_NAME_CHARS; i++)
        {
            buf[i + 9] = 0x20;
        }
    }

    buf[21] = velocitySwitchToggle.getToggleStateValue() == 1 ? 1U : 0U;
    buf[22] = reverbTypeComboBox.getSelectedItemIndex();
    buf[23] = uint8_t(reverbLevelSlider.getValue());
    buf[24] = uint8_t(reverbTimeSlider.getValue());
    buf[25] = uint8_t(delayFeedbackSlider.getValue());
    buf[26] = chorusTypeComboBox.getSelectedItemIndex();
    buf[27] = uint8_t(chorusLevelSlider.getValue());
    buf[28] = uint8_t(chorusDepthSlider.getValue());
    buf[29] = uint8_t(chorusRateSlider.getValue());
    buf[30] = uint8_t(chorusFeedbackSlider.getValue());
    buf[31] = chorusOutputComboBox.getSelectedItemIndex();
    buf[32] = uint8_t(analogFeelSlider.getValue());
    buf[33] = uint8_t(levelSlider.getValue());
    buf[34] = uint8_t(panSlider.getValue());
    buf[35] = uint8_t(bendRangeDownSlider.getValue() + 64);
    buf[36] = uint8_t(bendRangeUpSlider.getValue());
    buf[37] = keyAssignComboBox.getSelectedItemIndex();
    buf[38] = soloLegatoToggle.getToggleStateValue() == 1 ? 1U : 0U;
    buf[39] = portamentoToggle.getToggleStateValue() == 1 ? 1U : 0U;
    buf[40] = portamentoModeComboBox.getSelectedItemIndex();
    buf[41] = portamentoTypeComboBox.getSelectedItemIndex();
    buf[42] = uint8_t(portamentoTimeSlider.getValue());
    
    uint32_t checksum = 0;
    
    for (size_t i = 5; i < 43; i++)
    {
        checksum += buf[i];

        if (checksum >= 128)
            checksum -= 128;
    }
    
    checksum = 128 - checksum;
    
    buf[43] = checksum;
    buf[44] = 0xf7;

    audioProcessor.mcuLock.enter();
    audioProcessor.mcu->postMidiSC55(buf, 45);
    audioProcessor.mcuLock.exit();
    
    for (int i = 0; i < juce::jmin(MAX_PATCH_NAME_CHARS, patchNameEditor.getText().length()); i++)
    {
        patch->name[i] = patchNameEditor.getText()[i];
    }

    if (patchNameEditor.getText().length() < MAX_PATCH_NAME_CHARS)
    {
        for (int i = patchNameEditor.getText().length(); i < MAX_PATCH_NAME_CHARS; i++)
        {
            patch->name[i] = 0x20;
        }
    }

    patch->recChorConfig = uint8_t(reverbTypeComboBox.getSelectedItemIndex()
                                   + (chorusTypeComboBox.getSelectedItemIndex() << 4)
                                   + (velocitySwitchToggle.getToggleState() << 7));
    patch->reverbLevel = uint8_t(reverbLevelSlider.getValue());
    patch->reverbTime = uint8_t(reverbTimeSlider.getValue());
    patch->reverbFeedback = uint8_t(delayFeedbackSlider.getValue());
    patch->chorusLevel = uint8_t(chorusLevelSlider.getValue()
                                 + (chorusOutputComboBox.getSelectedItemIndex() << 7));
    patch->chorusDepth = uint8_t(chorusDepthSlider.getValue());
    patch->chorusRate = uint8_t(chorusRateSlider.getValue());
    patch->chorusFeedback = uint8_t(chorusFeedbackSlider.getValue());
    patch->analogFeel = uint8_t(analogFeelSlider.getValue());
    patch->level = uint8_t(levelSlider.getValue());
    patch->pan = uint8_t(panSlider.getValue());
    patch->bendRange = uint8_t(bendRangeDownSlider.getValue() + 64);
    patch->flags = uint8_t(bendRangeUpSlider.getValue()
                           + (portamentoModeComboBox.getSelectedItemIndex() << 4)
                           + (soloLegatoToggle.getToggleState() << 5)
                           + (portamentoToggle.getToggleState() << 6)
                           + (keyAssignComboBox.getSelectedItemIndex() << 7));
    patch->portamentoTime = uint8_t(portamentoTimeSlider.getValue()
                                    + (portamentoTypeComboBox.getSelectedItemIndex() << 7));
}
