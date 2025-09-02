#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class TabBar final : public juce::TabbedComponent
{
public:
    TabBar() : juce::TabbedComponent(juce::TabbedButtonBar::TabsAtTop)
    {
        tabChangedFunction = [](int) {};
    };

    void currentTabChanged(int newTabIndex, const juce::String& /* newTabName */) override
    {
        tabChangedFunction(newTabIndex);
    }

    std::function<void(int)> tabChangedFunction;
};