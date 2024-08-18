/*
  ==============================================================================

    JV880LCD.cpp
    Created: 18 Aug 2024 12:13:42am
    Author:  Giulio Zausa

  ==============================================================================
*/

#include <JuceHeader.h>
#include "JV880LCD.h"

//==============================================================================
JV880LCD::JV880LCD(Jv880_juceAudioProcessor& p) : audioProcessor (p), redrawTimer(this)
{
    redrawTimer.startTimerHz(60/3);
}

JV880LCD::~JV880LCD()
{
}

void JV880LCD::paint (juce::Graphics& g)
{
    uint8_t* bitmapResult = (uint8_t*)audioProcessor.mcu->lcd.LCD_Update();
    for (size_t i = 0; i < 1024 * 1024; i++)
        bitmapResult[i * 4 + 3] = 0xff;
    juce::Image image = { juce::Image::PixelFormat::ARGB, 820, 100, false};
    juce::Image::BitmapData pixelMap(image, juce::Image::BitmapData::readWrite);
    for (int y = 0; y < pixelMap.height; y++)
        memcpy(pixelMap.getLinePointer(y), bitmapResult + (y * 1024 * 4), (size_t)pixelMap.lineStride);
    g.drawImageAt(image, 0, 0);
}

void JV880LCD::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
