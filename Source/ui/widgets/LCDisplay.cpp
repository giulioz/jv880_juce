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
LCDisplay::LCDisplay(VirtualJVProcessor &p) : redrawTimer(this), processor(p)
{
  redrawTimer.startTimerHz(25);

  if (processor.loaded)
  {
      lcdColor = (Color)processor.status.selectedLCDColor;
      setLCDColor(lcdColor);
  }
}

LCDisplay::~LCDisplay()
{
    processor.status.selectedLCDColor = (uint8_t)lcdColor;
}

void LCDisplay::paint(juce::Graphics &g)
{
  uint8_t *bitmapResult = (uint8_t *)processor.mcu->lcd.LCD_Update();

  if (!bitmapResult)
  {
    return;
  }

  for (size_t i = 0; i < 1024 * 1024; i++)
  {
    bitmapResult[i * 4 + 3] = 0xff;
  }

  juce::Image image = {juce::Image::PixelFormat::ARGB, 820, 100, false};
  juce::Image::BitmapData pixelMap(image, juce::Image::BitmapData::readWrite);

  for (int y = 0; y < pixelMap.height; y++)
  {
    memcpy(pixelMap.getLinePointer(y), bitmapResult + (y * 1024 * 4), (size_t)pixelMap.lineStride);
  }

  g.drawImageAt(image, 0, 0);
}

void LCDisplay::setLCDColor(const Color color)
{
    switch (color)
    {
    case Color::Green:
    default:
        processor.mcu->lcd.lcd_bg = 0xff03be51;
        processor.mcu->lcd.lcd_col1 = 0xff2b4000;
        processor.mcu->lcd.lcd_col2 = 0xff04b430;
        break;
    case Color::Amber:
        processor.mcu->lcd.lcd_bg = 0xffbe9f03;
        processor.mcu->lcd.lcd_col1 = 0xff581600;
        processor.mcu->lcd.lcd_col2 = 0xffb98c04;
        break;
    case Color::Red:
        processor.mcu->lcd.lcd_bg = 0xff600000;
        processor.mcu->lcd.lcd_col1 = 0xfffa2b4f;
        processor.mcu->lcd.lcd_col2 = 0xff6a0508;
        break;
    case Color::Blue:
        processor.mcu->lcd.lcd_bg = 0xff135dfe;
        processor.mcu->lcd.lcd_col1 = 0xffdddddd;
        processor.mcu->lcd.lcd_col2 = 0xff3776fe;
        break;
    case Color::White:
        processor.mcu->lcd.lcd_bg = 0xffebfbfb;
        processor.mcu->lcd.lcd_col1 = 0xff191919;
        processor.mcu->lcd.lcd_col2 = 0xffdbebeb;
        break;
    case Color::Black:
        processor.mcu->lcd.lcd_bg = 0xff000000;
        processor.mcu->lcd.lcd_col1 = 0xffffffff;
        processor.mcu->lcd.lcd_col2 = 0xff292929;
        break;
    };

    lcdColor = color;
}

void LCDisplay::mouseDown(const juce::MouseEvent& e)
{
    if (e.mods.isPopupMenu())
    {
        auto addItem = [this](juce::PopupMenu &menu, const std::string text, Color color)
            {
                menu.addItem(text, true, (lcdColor == color), [this, color]() { setLCDColor(color); });
            };

        auto menu = juce::PopupMenu();

        addItem(menu, "Green", Color::Green);
        addItem(menu, "Amber", Color::Amber);
        addItem(menu, "Red", Color::Red);
        addItem(menu, "Blue", Color::Blue);
        addItem(menu, "White", Color::White);
        addItem(menu, "Black", Color::Black);

        auto o = juce::PopupMenu::Options();

        o = o.withMousePosition().withPreferredPopupDirection(
            juce::PopupMenu::Options::PopupDirection::downwards);

        menu.showMenuAsync(o);
    }
}