#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Menu final : public juce::ComboBox
{
public:
    Menu(uint32_t _id) : juce::ComboBox("Menu"), id(_id)
    {
        setScrollWheelEnabled(true);
    };

    uint32_t getID() { return id; }

private:
    uint32_t id;
};