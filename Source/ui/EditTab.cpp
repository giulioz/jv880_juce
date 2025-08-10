/*
  ==============================================================================

    EditTab.cpp
    Created: 18 Aug 2024 1:04:53pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EditTab.h"

//==============================================================================
EditTab::EditTab(Jv880_juceAudioProcessor& p) :
  audioProcessor (p),
  tabs (juce::TabbedButtonBar::TabsAtTop),
  editCommon (p),
  editTone1 (p, 0),
  editTone2 (p, 1),
  editTone3 (p, 2),
  editTone4 (p, 3)
{
    addAndMakeVisible(tabs);
    setSize(820, 1000);

    tabs.addTab("Common", getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId), &editCommon, false);
    tabs.addTab("Tone 1", getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId), &editTone1, false);
    tabs.addTab("Tone 2", getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId), &editTone2, false);
    tabs.addTab("Tone 3", getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId), &editTone3, false);
    tabs.addTab("Tone 4", getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId), &editTone4, false);
}

EditTab::~EditTab()
{
}


void EditTab::resized()
{
    tabs.setBounds(getLocalBounds());
}
