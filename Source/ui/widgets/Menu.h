#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Menu final : public juce::ComboBox
{
public:
    Menu(uint32_t _id, int _defval = 0) : juce::ComboBox("Menu"), id(_id), defval(_defval)
    {
        setScrollWheelEnabled(true);
    };

    void mouseDown(const juce::MouseEvent& e) override
    {
        if (e.mods.isRightButtonDown())
        {
            setSelectedItemIndex(defval);
        }
        else
        {
            juce::ComboBox::mouseDown(e);
        }
    }

    uint32_t getID() { return id; }

private:
    uint32_t id;
    int defval;
};