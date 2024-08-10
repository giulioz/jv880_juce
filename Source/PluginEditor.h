/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Jv880_juceAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Jv880_juceAudioProcessorEditor (Jv880_juceAudioProcessor&);
    ~Jv880_juceAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Jv880_juceAudioProcessor& audioProcessor;

    class RedrawTimer : public juce::Timer
    {
    public:
        RedrawTimer(Jv880_juceAudioProcessorEditor* editor) : editor(editor) {}
        void timerCallback() override
        {
            editor->repaint();
        }
    private:
      Jv880_juceAudioProcessorEditor* editor;
    };

    RedrawTimer redrawTimer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Jv880_juceAudioProcessorEditor)
};
