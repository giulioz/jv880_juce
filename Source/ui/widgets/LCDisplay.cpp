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
      setLCDColor((Color)processor.status.selectedLCDColor);
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
        processor.mcu->lcd.lcd_bg = 0x03be51;
        processor.mcu->lcd.lcd_col1 = 0x204000;
        processor.mcu->lcd.lcd_col2 = 0x08aa45;
        break;
    case Color::Amber:
        processor.mcu->lcd.lcd_bg = 0xbe9f03;
        processor.mcu->lcd.lcd_col1 = 0x502000;
        processor.mcu->lcd.lcd_col2 = 0xac8c02;
        break;
    case Color::Red:
        processor.mcu->lcd.lcd_bg = 0x600000;
        processor.mcu->lcd.lcd_col1 = 0xff3040;
        processor.mcu->lcd.lcd_col2 = 0x88090f;
        break;
    case Color::Blue:
        processor.mcu->lcd.lcd_bg = 0x1860ff;
        processor.mcu->lcd.lcd_col1 = 0xdcdcdc;
        processor.mcu->lcd.lcd_col2 = 0x557ef8;
        break;
    case Color::WhiteBlack:
        processor.mcu->lcd.lcd_bg = 0xe8f8f8;
        processor.mcu->lcd.lcd_col1 = 0x181818;
        processor.mcu->lcd.lcd_col2 = 0xcacaca;
        break;
    case Color::WhiteBlue:
        processor.mcu->lcd.lcd_bg = 0xe8f8f8;
        processor.mcu->lcd.lcd_col1 = 0x2040ff;
        processor.mcu->lcd.lcd_col2 = 0xd3d5ec;
        break;
    case Color::BlackWhite:
        processor.mcu->lcd.lcd_bg = 0x000000;
        processor.mcu->lcd.lcd_col1 = 0xdcdcdc;
        processor.mcu->lcd.lcd_col2 = 0x4a4a4a;
        break;
    case Color::BlackAmber:
        processor.mcu->lcd.lcd_bg = 0x000000;
        processor.mcu->lcd.lcd_col1 = 0xc0b400;
        processor.mcu->lcd.lcd_col2 = 0x403b00;
        break;
    case Color::BlackRed:
        processor.mcu->lcd.lcd_bg = 0x000000;
        processor.mcu->lcd.lcd_col1 = 0xff3040;
        processor.mcu->lcd.lcd_col2 = 0x58090f;
        break;
    case Color::BlackGreen:
        processor.mcu->lcd.lcd_bg = 0x000000;
        processor.mcu->lcd.lcd_col1 = 0x00c040;
        processor.mcu->lcd.lcd_col2 = 0x00400f;
        break;
    case Color::BlackBlue:
        processor.mcu->lcd.lcd_bg = 0x000000;
        processor.mcu->lcd.lcd_col1 = 0x4080ff;
        processor.mcu->lcd.lcd_col2 = 0x0b1f47;
        break;
    case Color::BlackVFD:
        processor.mcu->lcd.lcd_bg = 0x000000;
        processor.mcu->lcd.lcd_col1 = 0xc0ffff;
        processor.mcu->lcd.lcd_col2 = 0x484848;
        break;
    };

    lcdColor = color;
    processor.status.selectedLCDColor = (uint8_t)lcdColor;
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
        addItem(menu, "White-Black", Color::WhiteBlack);
        addItem(menu, "White-Blue", Color::WhiteBlue);
        addItem(menu, "Black-White", Color::BlackWhite);
        addItem(menu, "Black-Amber", Color::BlackAmber);
        addItem(menu, "Black-Red", Color::BlackRed);
        addItem(menu, "Black-Green", Color::BlackGreen);
        addItem(menu, "Black-Blue", Color::BlackBlue);
        addItem(menu, "VFD", Color::BlackVFD);

        auto o = juce::PopupMenu::Options();

        o = o.withMousePosition().withPreferredPopupDirection(
            juce::PopupMenu::Options::PopupDirection::downwards);

        menu.showMenuAsync(o);
    }
}