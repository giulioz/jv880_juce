#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class TextEdit final : public juce::TextEditor
{
public:
    TextEdit(uint32_t _id) : juce::TextEditor(), id(_id) {};

    uint32_t getID() { return id; }

private:
    uint32_t id;
};