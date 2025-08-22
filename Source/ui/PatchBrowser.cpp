/*
  ==============================================================================

    PatchBrowser.cpp
    Created: 18 Aug 2024 1:01:38pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#include "PatchBrowser.h"
#include <JuceHeader.h>

//==============================================================================
PatchBrowser::PatchBrowser(VirtualJVProcessor &p)
    : processor(p), categoriesListModel(),
      categoriesListBox("Categories", &categoriesListModel) {
  categoriesListBox.setRowHeight(34);
  addAndMakeVisible(categoriesListBox);

  for (int i = 0; i < columns; i++) {
    patchesListModels[i] =
        new PatchesListModel(rowPerColumn * i, rowPerColumn * (i + 1), this,
                             &categoriesListBox, &categoriesListModel);
    patchesListBoxes[i] = new juce::ListBox("Patches", patchesListModels[i]);
    patchesListModels[i]->owner = patchesListBoxes[i];

    patchesListBoxes[i]->setRowHeight(17);
    addAndMakeVisible(*patchesListBoxes[i]);
  }
}

PatchBrowser::~PatchBrowser() {
  for (int i = 0; i < columns; i++) {
    delete patchesListModels[i];
    delete patchesListBoxes[i];
  }
}

void PatchBrowser::resized() {
  categoriesListBox.setBounds(0, 0, 180, getHeight());
  for (int i = 0; i < columns; i++) {
    patchesListBoxes[i]->setBounds(180 + (getWidth() - 180) / columns * i, 0,
                                   (getWidth() - 180) / columns, getHeight());
  }
}
