/*
  ==============================================================================

    LCDisplay.h
    Created: 18 Aug 2024 12:13:42am
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../PluginProcessor.h"

//==============================================================================
/*
*/
class LCDisplay  : public juce::Component
{
public:
    enum struct Color: uint8_t
    {
        Green = 0U,
        Amber = 1U,
        Red   = 2U,
        Blue  = 3U,
        White = 4U,
        Black = 5U,
    };

    LCDisplay(VirtualJVProcessor&);
    ~LCDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override {}
    void mouseDown(const juce::MouseEvent & /* event */) override;
    void setLCDColor(const Color color);

private:
    class RedrawTimer : public juce::Timer
    {
    public:
        RedrawTimer(LCDisplay* parent) : parent(parent) {}

        void timerCallback() override { parent->repaint(); }

    private:
      LCDisplay* parent;
    };

    RedrawTimer redrawTimer;
    Color lcdColor;

    VirtualJVProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LCDisplay)
};
