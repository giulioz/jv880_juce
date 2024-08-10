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
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // g.setColour (juce::Colours::white);
    // g.setFont (juce::FontOptions (15.0f));
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

    uint8_t* bitmapResult = (uint8_t*)audioProcessor.mcu->lcd.LCD_Update();
    juce::Image image(juce::Image::PixelFormat::RGB, 820, 100, true);
    for (size_t y = 0; y < 100; y++)
      for (size_t x = 0; x < 820; x++)
        image.setPixelAt(x, y, juce::Colour::fromRGBA(
          bitmapResult[(x + y * 1024) * 4 + 0],
          bitmapResult[(x + y * 1024) * 4 + 1],
          bitmapResult[(x + y * 1024) * 4 + 2],
          255
        ));
    g.drawImageAt(image, 0, 0);
}

void Jv880_juceAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
