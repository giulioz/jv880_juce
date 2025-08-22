/*
  ==============================================================================

    LCDisplay.h
    Created: 18 Aug 2024 12:13:42am
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../PluginProcessor.h"

//==============================================================================
/*
*/
class LCDisplay  : public juce::Component
{
public:
    LCDisplay(VirtualJVProcessor&);
    ~LCDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    class RedrawTimer : public juce::Timer
    {
    public:
        RedrawTimer(LCDisplay* parent) : parent(parent) {}
        void timerCallback() override
        {
            parent->repaint();
        }
    private:
      LCDisplay* parent;
    };

    RedrawTimer redrawTimer;

    VirtualJVProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LCDisplay)
};
