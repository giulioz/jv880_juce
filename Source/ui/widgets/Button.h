#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Button final : public juce::ToggleButton
{
public:
    Button(uint32_t _id, const juce::String &_name) : juce::ToggleButton(_name), id(_id) {};

    uint32_t getID() { return id; }

private:
    uint32_t id;
};