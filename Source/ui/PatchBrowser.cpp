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
    : processor(p), categoriesListModel(), categoriesListBox("Categories", &categoriesListModel)
{
  categoriesListBox.setRowHeight(34);
  addAndMakeVisible(categoriesListBox);

  for (int i = 0; i < columns; i++)
  {
    patchesListModels[i] =
        new PatchesListModel(rowPerColumn * i, rowPerColumn * (i + 1), this,
                             &categoriesListBox, &categoriesListModel);
    patchesListBoxes[i] = new juce::ListBox("Patches", patchesListModels[i]);
    patchesListModels[i]->owner = patchesListBoxes[i];

    patchesListBoxes[i]->setRowHeight(17);
    addAndMakeVisible(*patchesListBoxes[i]);
  }

  if (processor.loaded)
  {
    if (processor.status.selectedRom < 0)
    {
      processor.status.selectedRom = 0;
    }

    categoriesListBox.selectRow(processor.status.selectedRom);

    /* this doesn't seem to work for some reason
    const auto col = processor.status.selectedPatch / rowPerColumn;
    const auto row = processor.status.selectedPatch % rowPerColumn;

    patchesListBoxes[col]->selectRow(row);
    */
  }
}

PatchBrowser::~PatchBrowser()
{
  processor.status.selectedRom = categoriesListBox.getSelectedRow();

  for (int i = 0; i < columns; i++)
  {
    if (patchesListBoxes[i]->getSelectedRow() > -1)
    {
      processor.status.selectedPatch = (i * rowPerColumn) + patchesListBoxes[i]->getSelectedRow();
    }

    delete patchesListModels[i];
    delete patchesListBoxes[i];
  }
}

void PatchBrowser::resized()
{
  categoriesListBox.setBounds(0, 0, 180, getHeight());

  for (int i = 0; i < columns; i++)
  {
    patchesListBoxes[i]->setBounds(180 + (getWidth() - 180) / columns * i,
                                   0,
                                   (getWidth() - 180) / columns,
                                   getHeight());
  }
}
