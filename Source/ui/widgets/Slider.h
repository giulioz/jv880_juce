#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Slider : public juce::Slider
{
public:
    Slider(uint32_t _id, double _min, double _max, double _interval)
        : juce::Slider("Slider"), id(_id), min(_min), max(_max), interval(_interval)
    {
        setSliderStyle(juce::Slider::SliderStyle::LinearBar);
        setRange(min, max, interval);
    };

    uint32_t getID() { return id; }

private:
    uint32_t id;
    double min, max, interval;
};