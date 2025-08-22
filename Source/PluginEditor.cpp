/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "rom.h"
#include <algorithm>

//==============================================================================
Jv880_juceAudioProcessorEditor::Jv880_juceAudioProcessorEditor(
    Jv880_juceAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p),
      lcd(p), tabs(juce::TabbedButtonBar::TabsAtTop), patchBrowser(p), editCommonTab(p),
      editTone1Tab(p, this, 0U), editTone2Tab(p, this, 1U), editTone3Tab(p, this, 2U), editTone4Tab(p, this, 3U),
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
  else
  {
      updateEditTabs();
  }
}

Jv880_juceAudioProcessorEditor::~Jv880_juceAudioProcessorEditor() {}

void Jv880_juceAudioProcessorEditor::updateEditTabs()
{
    editCommonTab.updateValues();
    editTone1Tab.updateValues();
    editTone2Tab.updateValues();
    editTone3Tab.updateValues();
    editTone4Tab.updateValues();
    settingsTab.updateValues();
}

uint8_t Jv880_juceAudioProcessorEditor::getSelectedRomIdx()
{
    auto idx = patchBrowser.categoriesListBox.getSelectedRow();

    if (idx <= 0)
    {
        return 2; // internal JV-880 ROM 2, contains multisample info table
    }
    else
    {
        return std::min(romCountRequired + idx, romCount - 1); // RD-500 expansion ROM and other SR-JV ROMs henceforth
    }
}

void Jv880_juceAudioProcessorEditor::resized() {
  lcd.setBounds(0, 0, 820, 100);
  tabs.setBounds(0, 100, 820, 800);
}
