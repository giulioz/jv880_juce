/*
  ==============================================================================

    LCDisplay.cpp
    Created: 18 Aug 2024 12:13:42am
    Author:  Giulio Zausa

  ==============================================================================
*/

#include "LCDisplay.h"
#include <JuceHeader.h>

//==============================================================================
LCDisplay::LCDisplay(VirtualJVProcessor &p)
    : redrawTimer(this), processor(p) {
  redrawTimer.startTimerHz(60 / 3);
}

LCDisplay::~LCDisplay() {}

void LCDisplay::paint(juce::Graphics &g) {
  uint8_t *bitmapResult = (uint8_t *)processor.mcu->lcd.LCD_Update();
  if (!bitmapResult)
    return;

  for (size_t i = 0; i < 1024 * 1024; i++)
    bitmapResult[i * 4 + 3] = 0xff;
  juce::Image image = {juce::Image::PixelFormat::ARGB, 820, 100, false};
  juce::Image::BitmapData pixelMap(image, juce::Image::BitmapData::readWrite);
  for (int y = 0; y < pixelMap.height; y++)
    memcpy(pixelMap.getLinePointer(y), bitmapResult + (y * 1024 * 4),
           (size_t)pixelMap.lineStride);
  g.drawImageAt(image, 0, 0);
}

void LCDisplay::resized() {
  // This method is where you should set the bounds of any child
  // components that your component contains..
}
