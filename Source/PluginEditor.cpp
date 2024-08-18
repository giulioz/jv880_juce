/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Jv880_juceAudioProcessorEditor::Jv880_juceAudioProcessorEditor (Jv880_juceAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
      lcd (p),
      tabs (juce::TabbedButtonBar::TabsAtTop),
      patchBrowser (p),
      editTab (),
      settingsTab ()
{
    addAndMakeVisible(lcd);
    addAndMakeVisible(tabs);
    setSize(820, 800);

    tabs.addTab("Browse", getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId), &patchBrowser, false);
    tabs.addTab("Edit", getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId), &editTab, false);
    tabs.addTab("Settings", getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId), &settingsTab, false);
}

Jv880_juceAudioProcessorEditor::~Jv880_juceAudioProcessorEditor()
{
}

void Jv880_juceAudioProcessorEditor::resized()
{
    lcd.setBounds(0, 0, 820, 100);
    tabs.setBounds(0, 100, 820, 700);
}
