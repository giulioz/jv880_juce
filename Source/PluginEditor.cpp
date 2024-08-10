/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Jv880_juceAudioProcessorEditor::Jv880_juceAudioProcessorEditor (Jv880_juceAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), redrawTimer (this)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (820, 100);

    redrawTimer.startTimerHz(60/2);
}

Jv880_juceAudioProcessorEditor::~Jv880_juceAudioProcessorEditor()
{
}

//==============================================================================
void Jv880_juceAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    uint8_t* bitmapResult = (uint8_t*)audioProcessor.mcu->lcd.LCD_Update();
    juce::Image image = { juce::Image::PixelFormat::ARGB, 820, 100, false};
    juce::Image::BitmapData pixelMap(image, juce::Image::BitmapData::readWrite);
    for (int y = 0; y < pixelMap.height; y++)
        memcpy(pixelMap.getLinePointer(y), bitmapResult + (y * 1024 * 4), (size_t)pixelMap.lineStride);
    g.drawImageAt(image, 0, 0, true);
}

void Jv880_juceAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
