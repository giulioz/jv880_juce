/*
  ==============================================================================

    JV880LCD.h
    Created: 18 Aug 2024 12:13:42am
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class JV880LCD  : public juce::Component
{
public:
    JV880LCD(Jv880_juceAudioProcessor&);
    ~JV880LCD() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    class RedrawTimer : public juce::Timer
    {
    public:
        RedrawTimer(JV880LCD* parent) : parent(parent) {}
        void timerCallback() override
        {
            parent->repaint();
        }
    private:
      JV880LCD* parent;
    };

    RedrawTimer redrawTimer;

    Jv880_juceAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JV880LCD)
};
