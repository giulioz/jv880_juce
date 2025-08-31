#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <algorithm>

class SliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    SliderLookAndFeel() {};

    void setBipolar(bool b) { bipolar = b; };

    void drawLinearSlider(juce::Graphics& g, int x, int y, int w, int h,
        float sliderPos, float /* minSliderPos */, float /* maxSliderPos */,
        const juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        g.setColour(slider.findColour(juce::Slider::trackColourId));

        if (bipolar)
        {
            const float midpoint = slider.isHorizontal() ? x + (w / 2.f) : y + (h / 2.f);

            g.fillRect(slider.isHorizontal() ? juce::Rectangle<float>(std::min(sliderPos, midpoint), (float)y + 0.5f, std::abs(midpoint - sliderPos), (float)h - 1.0f)
                : juce::Rectangle<float>((float)x + 0.5f, std::min(sliderPos, midpoint), (float)w - 1.0f, std::abs(midpoint - sliderPos)));
        }
        else
        {
            g.fillRect(slider.isHorizontal() ? juce::Rectangle<float>((float)x, (float)y + 0.5f, sliderPos - (float)x, (float)h - 1.0f)
                : juce::Rectangle<float>((float)x + 0.5f, sliderPos, (float)w - 1.0f, (float)y + ((float)h - sliderPos)));
        }

        drawLinearSliderOutline(g, x, y, w, h, style, slider);
    }

private:
    bool bipolar{ false };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SliderLookAndFeel)
};

class Slider : public juce::Slider
{
public:
    Slider(uint32_t _id, double min, double max, double interval, double _defval = 0, bool bipolar = false, bool vertical = false)
        : juce::Slider("Slider"), id(_id), defval(_defval)
    {
        setSliderStyle(vertical ? juce::Slider::SliderStyle::LinearBarVertical
            : juce::Slider::SliderStyle::LinearBar);
        setRange(min, max, interval);

        lookAndFeel.setBipolar(bipolar);

        setLookAndFeel(&lookAndFeel);
    };

    void mouseDown(const juce::MouseEvent& e) override
    {
        if (e.mods.isRightButtonDown())
        {
            setValue(defval);
        }
        else
        {
            juce::Slider::mouseDown(e);
        }
    }

    uint32_t getID() { return id; }

private:
    uint32_t id;
    double defval;
    SliderLookAndFeel lookAndFeel;
};