/*
  ==============================================================================

    SettingsTab.cpp
    Created: 18 Aug 2024 1:05:04pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SettingsTab.h"

//==============================================================================
SettingsTab::SettingsTab()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SettingsTab::~SettingsTab()
{
}

void SettingsTab::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("SettingsTab", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void SettingsTab::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
