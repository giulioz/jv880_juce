/*
  ==============================================================================

    PatchBrowser.h
    Created: 18 Aug 2024 1:01:38pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

static const char* groupNames[] = {
    "JV-880 Factory",
    "RD-500 Factory",
    "JD-990 Factory",
    "SR-JV80: 01 Pop",
    "SR-JV80: 02 Orchestral",
    "SR-JV80: 03 Piano",
    "SR-JV80: 04 Vintage Synth",
    "SR-JV80: 05 World",
    "SR-JV80: 06 Dance",
    "SR-JV80: 07 Super Sound Set",
    "SR-JV80: 08 Keyboards of the 60s and 70s",
    "SR-JV80: 09 Session",
    "SR-JV80: 10 Bass & Drum",
    "SR-JV80: 11 Techno",
    "SR-JV80: 12 HipHop",
    "SR-JV80: 13 Vocal",
    "SR-JV80: 14 Asia",
    "SR-JV80: 15 Special FX",
    "SR-JV80: 16 Orchestral II",
    "SR-JV80: 17 Country",
    "SR-JV80: 18 Latin",
    "SR-JV80: 19 House",
};

const int columns = 6;
const int rowPerColumn = 43;

//==============================================================================
/*
*/
class PatchBrowser  : public juce::Component
{
public:
    PatchBrowser(Jv880_juceAudioProcessor&);
    ~PatchBrowser() override;

    void resized() override;

private:
    Jv880_juceAudioProcessor& audioProcessor;

    class CategoriesListModel : public juce::ListBoxModel, public juce::ChangeBroadcaster {
      int getNumRows() override {
        return 20;
      }

      void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override {
        g.fillAll (rowIsSelected ? juce::Colour (0xff42A2C8)
                                 : juce::Colour (0xff263238));

        g.setColour (rowIsSelected ? juce::Colours::black : juce::Colours::white);

        if (rowNumber < 20)
            g.drawFittedText (groupNames[rowNumber], { 5, 0, width, height - 2 }, juce::Justification::left, 1);

        g.setColour (juce::Colours::white.withAlpha (0.4f));
        g.drawRect (0, height - 1, width, 2);
        g.drawRect (width - 2, 0, width, height);
      }

      void selectedRowsChanged(int lastRowSelected) override {
        sendChangeMessage();
      }
    };
    CategoriesListModel categoriesListModel;
    juce::ListBox categoriesListBox;

    class PatchesListModel : public juce::ListBoxModel, public juce::ChangeListener {
    public:
      PatchesListModel(int startI, int endI, PatchBrowser* parent, juce::ListBox* categoriesListBox, CategoriesListModel* categoriesListModel)
        : startI(startI), endI(endI), categoriesListBox(categoriesListBox), categoriesListModel(categoriesListModel), parent(parent) {
        categoriesListModel->addChangeListener(this);
      }

      int getNumRows() override {
        return std::min(endI - startI, (int)parent->audioProcessor.patchInfoPerGroup[groupI].size() - startI);
      }

      void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override {
        g.fillAll (rowIsSelected ? juce::Colour (0xff42A2C8)
                                 : juce::Colour (0xff263238));

        g.setColour (rowIsSelected ? juce::Colours::black : juce::Colours::white);

        int length = parent->audioProcessor.patchInfoPerGroup[groupI][rowNumber + startI]->nameLength;
        const char* strPtr = (const char*)parent->audioProcessor.patchInfoPerGroup[groupI][rowNumber + startI]->name;
        juce::String str = juce::String(strPtr, length);
        g.drawFittedText (str, { 5, 0, width, height - 2 }, juce::Justification::left, 1);

        g.setColour (juce::Colours::white.withAlpha (0.4f));
        g.drawRect (0, height - 1, width, 1);
      }

      void changeListenerCallback(juce::ChangeBroadcaster* source) override {
        if (source == categoriesListModel) {
          groupI = categoriesListBox->getSelectedRow();
          owner->updateContent();
          owner->deselectAllRows();
        }
      }

      void selectedRowsChanged(int lastRowSelected) override {
        for (size_t i = 0; i < columns; i++) {
          if (lastRowSelected != -1 && parent->patchesListBoxes[i] != owner)
            parent->patchesListBoxes[i]->deselectAllRows();
        }
        
        int selected = owner->getSelectedRow() + startI;
        if (selected >= 0 && selected < parent->audioProcessor.patchInfoPerGroup[groupI].size())
          parent->audioProcessor.setCurrentProgram(parent->audioProcessor.patchInfoPerGroup[groupI][selected]->iInList);
      }

      int groupI = 0;
      int startI;
      int endI;
      juce::ListBox* owner = nullptr;
      juce::ListBox* categoriesListBox;
      CategoriesListModel* categoriesListModel;
      PatchBrowser* parent;
    };
    PatchesListModel *patchesListModels[columns];
    juce::ListBox *patchesListBoxes[columns];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PatchBrowser)
};
