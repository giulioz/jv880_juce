/*
  ==============================================================================

    EditCommonTab.cpp
    Created: 20 Aug 2024 2:33:58pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EditCommonTab.h"

//==============================================================================
EditCommonTab::EditCommonTab(VirtualJVProcessor& p) : processor (p)
{
    addAndMakeVisible(patchNameEditor);
    patchNameEditor.addListener(this);
    patchNameEditor.setInputRestrictions(MAX_PATCH_NAME_CHARS,
                                         " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-*/#!,.");
    addAndMakeVisible(patchNameLabel);
    patchNameLabel.attachToComponent(&patchNameEditor, true);

    addAndMakeVisible(velocitySwitchToggle);
    velocitySwitchToggle.addListener(this);

    addAndMakeVisible(reverbTypeLabel);
    reverbTypeLabel.attachToComponent(&reverbTypeComboBox, true);

    addAndMakeVisible(reverbTypeComboBox);
    reverbTypeComboBox.addListener(this);
    reverbTypeComboBox.addItem("Room 1", 1);
    reverbTypeComboBox.addItem("Room 2", 2);
    reverbTypeComboBox.addItem("Stage 1", 3);
    reverbTypeComboBox.addItem("Stage 2", 4);
    reverbTypeComboBox.addItem("Hall 1", 5);
    reverbTypeComboBox.addItem("Hall 2", 6);
    reverbTypeComboBox.addItem("Delay", 7);
    reverbTypeComboBox.addItem("Pan Delay", 8);

    addAndMakeVisible(reverbLevelSlider);
    reverbLevelSlider.addListener(this);

    addAndMakeVisible(reverbLevelLabel);
    reverbLevelLabel.attachToComponent(&reverbLevelSlider, true);

    addAndMakeVisible(reverbTimeSlider);
    reverbTimeSlider.addListener(this);

    addAndMakeVisible(reverbTimeLabel);
    reverbTimeLabel.attachToComponent(&reverbTimeSlider, true);

    addAndMakeVisible(delayFeedbackSlider);
    delayFeedbackSlider.addListener(this);

    addAndMakeVisible(delayFeedbackLabel);
    delayFeedbackLabel.attachToComponent(&delayFeedbackSlider, true);

    addAndMakeVisible(chorusTypeLabel);
    chorusTypeLabel.attachToComponent(&chorusTypeComboBox, true);

    addAndMakeVisible(chorusTypeComboBox);
    chorusTypeComboBox.addListener(this);
    chorusTypeComboBox.addItem("Type 1", 1);
    chorusTypeComboBox.addItem("Type 2", 2);
    chorusTypeComboBox.addItem("Type 3", 3);

    addAndMakeVisible(chorusLevelSlider);
    chorusLevelSlider.addListener(this);

    addAndMakeVisible(chorusLevelLabel);
    chorusLevelLabel.attachToComponent(&chorusLevelSlider, true);

    addAndMakeVisible(chorusDepthSlider);
    chorusDepthSlider.addListener(this);

    addAndMakeVisible(chorusDepthLabel);
    chorusDepthLabel.attachToComponent(&chorusDepthSlider, true);

    addAndMakeVisible(chorusRateSlider);
    chorusRateSlider.addListener(this);

    addAndMakeVisible(chorusRateLabel);
    chorusRateLabel.attachToComponent(&chorusRateSlider, true);

    addAndMakeVisible(chorusFeedbackSlider);
    chorusFeedbackSlider.addListener(this);

    addAndMakeVisible(chorusFeedbackLabel);
    chorusFeedbackLabel.attachToComponent(&chorusFeedbackSlider, true);

    addAndMakeVisible(chorusOutputLabel);
    chorusOutputLabel.attachToComponent(&chorusOutputComboBox, true);

    addAndMakeVisible(chorusOutputComboBox);
    chorusOutputComboBox.addListener(this);
    chorusOutputComboBox.addItem("Mix", 1);
    chorusOutputComboBox.addItem("Reverb", 2);

    addAndMakeVisible(analogFeelSlider);
    analogFeelSlider.addListener(this);

    addAndMakeVisible(analogFeelLabel);
    analogFeelLabel.attachToComponent(&analogFeelSlider, true);

    addAndMakeVisible(levelSlider);
    levelSlider.addListener(this);

    addAndMakeVisible(levelLabel);
    levelLabel.attachToComponent(&levelSlider, true);

    addAndMakeVisible(panSlider);
    panSlider.addListener(this);

    addAndMakeVisible(panLabel);
    panLabel.attachToComponent(&panSlider, true);

    addAndMakeVisible(bendRangeDownSlider);
    bendRangeDownSlider.addListener(this);

    addAndMakeVisible(bendRangeLabel);
    bendRangeLabel.attachToComponent(&bendRangeDownSlider, true);

    addAndMakeVisible(bendRangeUpSlider);
    bendRangeUpSlider.addListener(this);

    addAndMakeVisible(keyAssignLabel);
    keyAssignLabel.attachToComponent(&keyAssignComboBox, true);

    addAndMakeVisible(keyAssignComboBox);
    keyAssignComboBox.addListener(this);
    keyAssignComboBox.addItem("Poly", 1);
    keyAssignComboBox.addItem("Solo", 2);

    addAndMakeVisible(soloLegatoToggle);
    soloLegatoToggle.addListener(this);

    addAndMakeVisible(portamentoToggle);
    portamentoToggle.addListener(this);

    addAndMakeVisible(portamentoModeLabel);
    portamentoModeLabel.attachToComponent(&portamentoModeComboBox, true);

    addAndMakeVisible(portamentoModeComboBox);
    portamentoModeComboBox.addListener(this);
    portamentoModeComboBox.addItem("Legato", 1);
    portamentoModeComboBox.addItem("Normal", 2);

    addAndMakeVisible(portamentoTypeLabel);
    portamentoTypeLabel.attachToComponent(&portamentoTypeComboBox, true);

    addAndMakeVisible(portamentoTypeComboBox);
    portamentoTypeComboBox.addListener(this);
    portamentoTypeComboBox.addItem("Time", 1);
    portamentoTypeComboBox.addItem("Rate", 2);

    addAndMakeVisible(portamentoTimeSlider);
    portamentoTimeSlider.addListener(this);

    addAndMakeVisible(portamentoTimeLabel);
    portamentoTimeLabel.attachToComponent(&portamentoTimeSlider, true);
}

EditCommonTab::~EditCommonTab()
{
}

void EditCommonTab::updateValues()
{
    Patch* patch = (Patch*) processor.status.patch;

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

void EditCommonTab::sliderValueChanged(juce::Slider* slider)
{
    uint32_t id = 0xFFFFFFF;

    if (auto i = dynamic_cast<Slider*>(slider))
    {
        id = i->getID();
    }

    Patch* patch = (Patch*)processor.status.patch;

    switch (id)
    {
    case ReverbLevel:
        sendSysexPatchCommonParamChange(0x0e, uint8_t(reverbLevelSlider.getValue()));
        patch->reverbLevel = uint8_t(reverbLevelSlider.getValue());
        break;
    case ReverbTime:
        sendSysexPatchCommonParamChange(0x0f, uint8_t(reverbTimeSlider.getValue()));
        patch->reverbTime = uint8_t(reverbTimeSlider.getValue());
        break;
    case DelayFeedback:
        sendSysexPatchCommonParamChange(0x10, uint8_t(delayFeedbackSlider.getValue()));
        patch->reverbFeedback = uint8_t(delayFeedbackSlider.getValue());
        break;
    case ChorusLevel:
        sendSysexPatchCommonParamChange(0x12, uint8_t(chorusLevelSlider.getValue()));
        patch->chorusLevel = uint8_t(chorusLevelSlider.getValue()
                                     + (chorusOutputComboBox.getSelectedItemIndex() << 7));
        break;
    case ChorusDepth:
        sendSysexPatchCommonParamChange(0x13, uint8_t(chorusDepthSlider.getValue()));
        patch->chorusDepth = uint8_t(chorusDepthSlider.getValue());
        break;
    case ChorusRate:
        sendSysexPatchCommonParamChange(0x14, uint8_t(chorusRateSlider.getValue()));
        patch->chorusRate = uint8_t(chorusRateSlider.getValue());
        break;
    case ChorusFeedback:
        sendSysexPatchCommonParamChange(0x15, uint8_t(chorusFeedbackSlider.getValue()));
        patch->chorusFeedback = uint8_t(chorusFeedbackSlider.getValue());
        break;
    case AnalogFeel:
        sendSysexPatchCommonParamChange(0x17, uint8_t(analogFeelSlider.getValue()));
        patch->analogFeel = uint8_t(analogFeelSlider.getValue());
        break;
    case Level:
        sendSysexPatchCommonParamChange(0x18, uint8_t(levelSlider.getValue()));
        patch->level = uint8_t(levelSlider.getValue());
        break;
    case Pan:
        sendSysexPatchCommonParamChange(0x19, uint8_t(panSlider.getValue()));
        patch->pan = uint8_t(panSlider.getValue());
        break;
    case BendRangeDown:
        sendSysexPatchCommonParamChange(0x1a, uint8_t(bendRangeDownSlider.getValue()));
        patch->bendRange = uint8_t(bendRangeDownSlider.getValue() + 64);
        break;
    case BendRangeUp:
        sendSysexPatchCommonParamChange(0x1b, uint8_t(bendRangeUpSlider.getValue()));
        patch->flags = uint8_t(bendRangeUpSlider.getValue()
                               + (portamentoModeComboBox.getSelectedItemIndex() << 4)
                               + (soloLegatoToggle.getToggleState() << 5)
                               + (portamentoToggle.getToggleState() << 6)
                               + (keyAssignComboBox.getSelectedItemIndex() << 7));
        break;
    case PortamentoTime:
        sendSysexPatchCommonParamChange(0x21, uint8_t(portamentoTimeSlider.getValue()));
        patch->portamentoTime = uint8_t(portamentoTimeSlider.getValue()
                                        + (portamentoTypeComboBox.getSelectedItemIndex() << 7));
        break;
    default:
        break;
    }
}

void EditCommonTab::buttonClicked(juce::Button* button)
{
    uint32_t id = 0xFFFFFFF;

    if (auto i = dynamic_cast<Button*>(button))
    {
        id = i->getID();
    }

    Patch* patch = (Patch*)processor.status.patch;

    switch (id)
    {
    case VelocitySwitch:
        sendSysexPatchCommonParamChange(0x0c, uint8_t(velocitySwitchToggle.getToggleStateValue() == 1));
        patch->recChorConfig = uint8_t(reverbTypeComboBox.getSelectedItemIndex()
                                       + (chorusTypeComboBox.getSelectedItemIndex() << 4)
                                       + (velocitySwitchToggle.getToggleState() << 7));
        break;
    case SoloLegato:
        sendSysexPatchCommonParamChange(0x1d, uint8_t(soloLegatoToggle.getToggleStateValue() == 1));
        patch->flags = uint8_t(bendRangeUpSlider.getValue()
                               + (portamentoModeComboBox.getSelectedItemIndex() << 4)
                               + (soloLegatoToggle.getToggleState() << 5)
                               + (portamentoToggle.getToggleState() << 6)
                               + (keyAssignComboBox.getSelectedItemIndex() << 7));
        break;
    case Portamento:
        sendSysexPatchCommonParamChange(0x1e, uint8_t(portamentoToggle.getToggleStateValue() == 1));
        patch->flags = uint8_t(bendRangeUpSlider.getValue()
                               + (portamentoModeComboBox.getSelectedItemIndex() << 4)
                               + (soloLegatoToggle.getToggleState() << 5)
                               + (portamentoToggle.getToggleState() << 6)
                               + (keyAssignComboBox.getSelectedItemIndex() << 7));
        break;
    default:
        break;
    }
}

void EditCommonTab::comboBoxChanged(juce::ComboBox* comboBox)
{
    uint32_t id = 0xFFFFFFF;

    if (auto i = dynamic_cast<Menu*>(comboBox))
    {
        id = i->getID();
    }

    Patch* patch = (Patch*) processor.status.patch;

    switch (id)
    {
    case ReverbType:
        sendSysexPatchCommonParamChange(0x0d, uint8_t(reverbTypeComboBox.getSelectedItemIndex()));
        patch->recChorConfig = uint8_t(reverbTypeComboBox.getSelectedItemIndex()
                                       + (chorusTypeComboBox.getSelectedItemIndex() << 4)
                                       + (velocitySwitchToggle.getToggleState() << 7));
        break;
    case ChorusType:
        sendSysexPatchCommonParamChange(0x11, uint8_t(chorusTypeComboBox.getSelectedItemIndex()));
        patch->recChorConfig = uint8_t(reverbTypeComboBox.getSelectedItemIndex()
                                       + (chorusTypeComboBox.getSelectedItemIndex() << 4)
                                       + (velocitySwitchToggle.getToggleState() << 7));
        break;
    case ChorusOutput:
        sendSysexPatchCommonParamChange(0x16, uint8_t(chorusOutputComboBox.getSelectedItemIndex()));
        patch->chorusLevel = uint8_t(chorusLevelSlider.getValue()
                                     + (chorusOutputComboBox.getSelectedItemIndex() << 7));
        break;
    case KeyAssign:
        sendSysexPatchCommonParamChange(0x1c, uint8_t(keyAssignComboBox.getSelectedItemIndex()));
        patch->flags = uint8_t(bendRangeUpSlider.getValue()
                               + (portamentoModeComboBox.getSelectedItemIndex() << 4)
                               + (soloLegatoToggle.getToggleState() << 5)
                               + (portamentoToggle.getToggleState() << 6)
                               + (keyAssignComboBox.getSelectedItemIndex() << 7));
        break;
    case PortamentoMode:
        sendSysexPatchCommonParamChange(0x1f, uint8_t(portamentoModeComboBox.getSelectedItemIndex()));
        patch->flags = uint8_t(bendRangeUpSlider.getValue()
                               + (portamentoModeComboBox.getSelectedItemIndex() << 4)
                               + (soloLegatoToggle.getToggleState() << 5)
                               + (portamentoToggle.getToggleState() << 6)
                               + (keyAssignComboBox.getSelectedItemIndex() << 7));
        break;
    case PortamentoType:
        sendSysexPatchCommonParamChange(0x20, uint8_t(portamentoTypeComboBox.getSelectedItemIndex()));
        patch->portamentoTime = uint8_t(portamentoTimeSlider.getValue()
                                        + (portamentoTypeComboBox.getSelectedItemIndex() << 7));
        break;
    default:
        break;
    }
}

void EditCommonTab::textEditorTextChanged (juce::TextEditor& textEditor)
{
    if (&textEditor == &patchNameEditor)
        sendSysexPatchNameChange();
}

void EditCommonTab::sendSysexPatchNameChange()
{
    auto patch = (Patch*) processor.status.patch;

    uint8_t buf[24];

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
        buf[i + 9]     = patchNameEditor.getText()[i];
        patch->name[i] = patchNameEditor.getText()[i];
    }

    if (patchNameEditor.getText().length() < MAX_PATCH_NAME_CHARS)
    {
        for (int i = patchNameEditor.getText().length(); i < MAX_PATCH_NAME_CHARS; i++)
        {
            buf[i + 9]     = 0x20;
            patch->name[i] = 0x20;
        }
    }

    uint32_t checksum = 0;

    for (size_t i = 5; i < 21; i++)
    {
        checksum += buf[i];

        if (checksum >= 128)
            checksum -= 128;
    }

    checksum = 128 - checksum;

    buf[22] = (uint8_t)checksum;
    buf[23] = 0xf7;

    processor.mcuLock.enter();
    processor.mcu->postMidiSC55(buf, 24);
    processor.mcuLock.exit();
}

void EditCommonTab::sendSysexPatchCommonParamChange(const uint8_t address, const uint8_t value)
{
    uint8_t buf[12];

    buf[0] = 0xf0;
    buf[1] = 0x41;
    buf[2] = 0x10; // unit number
    buf[3] = 0x46;
    buf[4] = 0x12; // command
    buf[5] = 0x00;
    buf[6] = 0x08;
    buf[7] = 0x20;
    buf[8] = address;
    buf[9] = value;

    uint32_t checksum = 0;

    for (size_t i = 5; i < 10; i++)
    {
        checksum += buf[i];

        if (checksum >= 128)
           checksum -= 128;
    }

    checksum = 128 - checksum;

    buf[10] = (uint8_t)checksum;
    buf[11] = 0xf7;

    processor.mcuLock.enter();
    processor.mcu->postMidiSC55(buf, 12);
    processor.mcuLock.exit();
}