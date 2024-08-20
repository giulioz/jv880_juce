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
  editTone (p)
{
    addAndMakeVisible(tabs);
    setSize(820, 800);

    tabs.addTab("Common", getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId), &editCommon, false);
    tabs.addTab("Tone", getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId), &editTone, false);
}

EditTab::~EditTab()
{
}


void EditTab::resized()
{
    tabs.setBounds(getLocalBounds());
}
