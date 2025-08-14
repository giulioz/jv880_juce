/*
  ==============================================================================

    PatchBrowser.h
    Created: 18 Aug 2024 1:01:38pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once

#include "../PluginProcessor.h"
#include <JuceHeader.h>
#include "../rom.h"

static const char *groupNames[] = {
    "880 Factory",
    "500 Factory",
    "Exp 01 Pop",
    "Exp 02 Orchestral",
    "Exp 03 Piano",
    "Exp 04 Vintage Synth",
    "Exp 05 World",
    "Exp 06 Dance",
    "Exp 07 Super Sound Set",
    "Exp 08 60s/70s Keyboards",
    "Exp 09 Session",
    "Exp 10 Bass & Drum",
    "Exp 11 Techno",
    "Exp 12 Hip-Hop",
    "Exp 13 Vocal",
    "Exp 14 Asia",
    "Exp 15 Special FX",
    "Exp 16 Orchestral II",
    "Exp 17 Country",
    "Exp 18 Latin",
    "Exp 19 House",
    "Exp Custom"
};

const int columns = 6;
const int rowPerColumn = 43;

//==============================================================================
/*
 */
class PatchBrowser : public juce::Component {
public:
  PatchBrowser(Jv880_juceAudioProcessor &);
  ~PatchBrowser() override;

  void resized() override;

private:
  Jv880_juceAudioProcessor &audioProcessor;

  class CategoriesListModel : public juce::ListBoxModel,
                              public juce::ChangeBroadcaster {
    int getNumRows() override { return NUM_EXPS + 1; }

    void paintListBoxItem(int rowNumber, juce::Graphics &g, int width,
                          int height, bool rowIsSelected) override {
      g.fillAll(rowIsSelected ? juce::Colour(0xff42A2C8)
                              : juce::Colour(0xff263238));

      g.setColour(rowIsSelected ? juce::Colours::black : juce::Colours::white);

      if (rowNumber < NUM_EXPS + 1)
        g.drawFittedText(groupNames[rowNumber], {5, 0, width, height - 2},
                         juce::Justification::left, 1);

      g.setColour(juce::Colours::white.withAlpha(0.4f));
      g.drawRect(0, height - 1, width, 2);
      g.drawRect(width - 2, 0, width, height);
    }

    void selectedRowsChanged(int lastRowSelected) override {
      sendChangeMessage();
    }
  };
  CategoriesListModel categoriesListModel;
  juce::ListBox categoriesListBox;

  class PatchesListModel : public juce::ListBoxModel,
                           public juce::ChangeListener {
  public:
    PatchesListModel(int startI, int endI, PatchBrowser *parent,
                     juce::ListBox *categoriesListBox,
                     CategoriesListModel *categoriesListModel)
        : startI(startI), endI(endI), categoriesListBox(categoriesListBox),
          categoriesListModel(categoriesListModel), parent(parent) {
      categoriesListModel->addChangeListener(this);
    }

    ~PatchesListModel() override {
      categoriesListModel->removeChangeListener(this);
    }

    int getNumRows() override {
      if (!parent->audioProcessor.loaded || !(romInfos[std::max(groupI, 1) + romCountRequired].loaded)) {
        return 0;
      }

      return std::min(
          endI - startI,
          (int)parent->audioProcessor.patchInfoPerGroup[groupI].size() -
              startI);
    }

    void paintListBoxItem(int rowNumber, juce::Graphics &g, int width,
                          int height, bool rowIsSelected) override {
      g.fillAll(rowIsSelected ? juce::Colour(0xff42A2C8)
                              : juce::Colour(0xff263238));

      g.setColour(rowIsSelected ? juce::Colours::black : juce::Colours::white);

      if (!parent->audioProcessor.loaded) {
        return;
      }

      int length =
          parent->audioProcessor.patchInfoPerGroup[groupI][rowNumber + startI]
              ->nameLength;
      const char *strPtr = (const char *)parent->audioProcessor
                               .patchInfoPerGroup[groupI][rowNumber + startI]
                               ->name;
      juce::String str = juce::String(strPtr, length);
      g.drawFittedText(str, {5, 0, width, height - 2},
                       juce::Justification::left, 1);

      g.setColour(juce::Colours::white.withAlpha(0.4f));
      g.drawRect(0, height - 1, width, 1);
    }

    void changeListenerCallback(juce::ChangeBroadcaster *source) override {
      if (source == categoriesListModel) {
        groupI = categoriesListBox->getSelectedRow();
        owner->updateContent();
        owner->deselectAllRows();
        owner->repaint();
      }
    }

    void selectedRowsChanged(int lastRowSelected) override {
      if (!parent->audioProcessor.loaded) {
        return;
      }

      for (size_t i = 0; i < columns; i++) {
        if (lastRowSelected != -1 && parent->patchesListBoxes[i] != owner)
          parent->patchesListBoxes[i]->deselectAllRows();
      }

      int selected = owner->getSelectedRow() + startI;
      if (selected >= 0 &&
          selected < parent->audioProcessor.patchInfoPerGroup[groupI].size())
        parent->audioProcessor.setCurrentProgram(
            parent->audioProcessor.patchInfoPerGroup[groupI][selected]
                ->iInList);
    }

    int groupI = 0;
    int startI;
    int endI;
    juce::ListBox *owner = nullptr;
    juce::ListBox *categoriesListBox;
    CategoriesListModel *categoriesListModel;
    PatchBrowser *parent;
  };
  PatchesListModel *patchesListModels[columns];
  juce::ListBox *patchesListBoxes[columns];

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatchBrowser)
};
