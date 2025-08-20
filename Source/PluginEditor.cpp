/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
Jv880_juceAudioProcessorEditor::Jv880_juceAudioProcessorEditor(
    Jv880_juceAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p),
      lcd(p), patchBrowser(p), tabs(juce::TabbedButtonBar::TabsAtTop), editCommonTab(p),
      editTone1Tab(p, 0), editTone2Tab(p, 1), editTone3Tab(p, 2), editTone4Tab(p, 3),
      settingsTab(p)
{
  addAndMakeVisible(lcd);
  addAndMakeVisible(tabs);

  setSize(820, 900);

  const auto bgColor = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId);

  tabs.addTab("Browse", bgColor, &patchBrowser, false);
  tabs.addTab("Common", bgColor, &editCommonTab, false);
  tabs.addTab("Tone 1", bgColor, &editTone1Tab, false);
  tabs.addTab("Tone 2", bgColor, &editTone2Tab, false);
  tabs.addTab("Tone 3", bgColor, &editTone3Tab, false);
  tabs.addTab("Tone 4", bgColor, &editTone4Tab, false);
  tabs.addTab("Settings", bgColor, &settingsTab, false);

  if (!audioProcessor.loaded) {
    juce::AlertWindow::showAsync(
        juce::MessageBoxOptions()
            .withIconType(juce::MessageBoxIconType::WarningIcon)
            .withTitle("Error")
            .withMessage("Cannot load ROMs. Please copy the ROM files to the "
                         "ROM folder and restart the plugin to continue.")
            .withButton("Open ROMs Folder")
            .withAssociatedComponent(this)
            .withParentComponent(this),
        [](int /* param */) {
          juce::File romsDir(juce::File::getSpecialLocation(
                                 juce::File::userApplicationDataDirectory)
                                 .getChildFile("JV880"));
          if (romsDir.exists()) {
            juce::Process::openDocument(romsDir.getFullPathName(), "");
          }
        });
  }
}

Jv880_juceAudioProcessorEditor::~Jv880_juceAudioProcessorEditor() {}

void Jv880_juceAudioProcessorEditor::resized() {
  lcd.setBounds(0, 0, 820, 100);
  tabs.setBounds(0, 100, 820, 800);
}
