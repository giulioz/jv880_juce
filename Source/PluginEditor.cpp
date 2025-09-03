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
VirtualJVEditor::VirtualJVEditor(VirtualJVProcessor &p)
    : AudioProcessorEditor(&p), processor(p),
      lcd(p), tabs(), patchBrowser(p), editCommonTab(p),
      editTone1Tab(p, this, 0U), editTone2Tab(p, this, 1U), editTone3Tab(p, this, 2U), editTone4Tab(p, this, 3U), editRhythmTab(p, this),
      settingsTab(p)
{
    addAndMakeVisible(lcd);
    addAndMakeVisible(tabs);

    tabs.tabChangedFunction =
        [this](int index)
        {
            processor.status.selectedTab = index;
        };

    setSize(820, 900);

    if (!processor.loaded)
    {
        auto msgBox = juce::MessageBoxOptions()
                      .withIconType(juce::MessageBoxIconType::WarningIcon)
                      .withTitle("Error")
                      .withMessage("Cannot load ROMs. Please copy the ROM files to the ROM folder and restart the plugin to continue.")
                      .withButton("Open ROM Folder")
                      .withAssociatedComponent(this)
                      .withParentComponent(this);

        juce::AlertWindow::showAsync
        (
            msgBox,   
            [](int /* param */)
                {
                    juce::File romsDir(juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory).getChildFile("JV880"));

                    if (romsDir.exists())
                    {
                        juce::Process::openDocument(romsDir.getFullPathName(), "");
                    }
                }
        );
    }
    else
    {
        showToneOrRhythmEditTabs(processor.status.isDrums);
        setSelectedTab(processor.status.selectedTab);
        updateEditTabs();
    }
}

VirtualJVEditor::~VirtualJVEditor()
{
    processor.status.selectedTab = tabs.getCurrentTabIndex();
}

void VirtualJVEditor::updateEditTabs()
{
    editCommonTab.updateValues();
    editTone1Tab.updateValues();
    editTone2Tab.updateValues();
    editTone3Tab.updateValues();
    editTone4Tab.updateValues();
    editRhythmTab.updateValues();
    settingsTab.updateValues();
}

void VirtualJVEditor::showToneOrRhythmEditTabs(const bool isRhythm)
{
    const auto bgColor = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId);
    auto selTab = processor.status.selectedTab;

    tabs.clearTabs();

    if (isRhythm)
    {
        tabs.addTab("Browse", bgColor, &patchBrowser, false);
        tabs.addTab("Settings", bgColor, &settingsTab, false);
        tabs.addTab("Common", bgColor, &editCommonTab, false);
        tabs.addTab("Rhythm Set", bgColor, &editRhythmTab, false);
    }
    else
    {
        tabs.addTab("Browse", bgColor, &patchBrowser, false);
        tabs.addTab("Settings", bgColor, &settingsTab, false);
        tabs.addTab("Common", bgColor, &editCommonTab, false);
        tabs.addTab("Tone 1", bgColor, &editTone1Tab, false);
        tabs.addTab("Tone 2", bgColor, &editTone2Tab, false);
        tabs.addTab("Tone 3", bgColor, &editTone3Tab, false);
        tabs.addTab("Tone 4", bgColor, &editTone4Tab, false);
    }

    // just in case...
    if (selTab > 3 && processor.status.isDrums)
    {
        selTab = 3;
        tabs.setCurrentTabIndex(selTab);
    }

    processor.status.selectedTab = selTab;

    editCommonTab.rhythmSetMode(isRhythm);
}

uint8_t VirtualJVEditor::getSelectedRomIdx()
{
    auto idx = patchBrowser.categoriesListBox.getSelectedRow();

    if (idx <= 0)
    {
        return 2; // internal ROM 2 of the 880, contains multisample info table
    }
    else
    {
        return std::min(romCountRequired + idx, romCount - 1); // RD expansion ROM and other SR-JV ROMs henceforth
    }
}

void VirtualJVEditor::resized()
{
    lcd.setBounds(0, 0, 820, 100);
    tabs.setBounds(0, 100, 820, 800);
}
