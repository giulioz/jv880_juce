#!/bin/bash

# Define the prep function
prep() {
    echo "Preparing $1..."
    sudo xattr -cr "$1"
    sudo xattr -r -d com.apple.quarantine "$1"
    sudo codesign --force --sign - "$1"
    echo "$1 has been signed and prepared!"
}

# Variables
REPO_URL="https://github.com/giulioz/jv880_juce/releases/download/latest"
TMP_DIR="/tmp/jv880_install"
mkdir -p "$TMP_DIR"

# ZIP files to download
FILES=(
    "jv880.component.macOS.zip"
    "jv880.vst3.macOS.zip"
    "jv880.app.macOS.zip"
)

# Extracted file names (all lowercase)
EXTRACTED_FILES=(
    "jv880.component"
    "jv880.vst3"
    "jv880.app"
)

# Corresponding installation destinations
DESTINATIONS=(
    "/Library/Audio/Plug-Ins/Components"
    "/Library/Audio/Plug-Ins/VST3"
    "/Applications"
)

# Download, extract, install, and prep
for i in "${!FILES[@]}"; do
    ZIP_FILE="${FILES[$i]}"
    EXTRACTED_FILE="${EXTRACTED_FILES[$i]}"
    DEST="${DESTINATIONS[$i]}"

    echo "Downloading $ZIP_FILE..."
    curl -L -o "$TMP_DIR/$ZIP_FILE" "$REPO_URL/$ZIP_FILE"

    if [ $? -ne 0 ]; then
        echo "Error downloading $ZIP_FILE!"
        continue
    fi

    echo "Extracting $ZIP_FILE..."
    echo "A" | unzip -q "$TMP_DIR/$ZIP_FILE" -d "$TMP_DIR"

    echo "Installing $EXTRACTED_FILE to $DEST"
    sudo mv "$TMP_DIR/$EXTRACTED_FILE" "$DEST/"
    prep "$DEST/$EXTRACTED_FILE"
done

echo "Installation complete!"

