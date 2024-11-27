#!/bin/bash

# Set Arduino libraries folder (default for Linux)
ARDUINO_LIBRARIES_DIR="$HOME/Arduino/libraries"

# Check if Arduino libraries folder exists
if [ ! -d "$ARDUINO_LIBRARIES_DIR" ]; then
    echo "Error: Arduino libraries directory not found at $ARDUINO_LIBRARIES_DIR"
    exit 1
fi

# Define the library name dynamically
LIBRARY_NAME="ActiveThreshold"
TARGET_NAME="UltiBlox-$LIBRARY_NAME"

# Install the main library
if [ -d "$ARDUINO_LIBRARIES_DIR/$TARGET_NAME" ]; then
    echo "$TARGET_NAME already installed."
else
    cp -r "$(pwd)" "$ARDUINO_LIBRARIES_DIR/$TARGET_NAME"
    echo "$TARGET_NAME installed to $ARDUINO_LIBRARIES_DIR"
fi

# Process dependencies
DEPENDENCIES_FILE="./dependencies.txt"
if [ ! -f "$DEPENDENCIES_FILE" ]; then
    echo "No dependencies file found. Skipping dependency installation."
    exit 0
fi

while IFS=',' read -r DEP_NAME GIT_URL || [ -n "$DEP_NAME" ]; do
    DEP_NAME=$(echo "$DEP_NAME" | tr -d '\r' | sed 's/^[ \t]*//;s/[ \t]*$//')
    GIT_URL=$(echo "$GIT_URL" | tr -d '\r' | sed 's/^[ \t]*//;s/[ \t]*$//')

    if [ -z "$DEP_NAME" ]; then
        echo "Skipping empty or invalid line in dependencies.txt."
        continue
    fi

    DEP_PATH="$(dirname "$(pwd)")/$DEP_NAME"

    if [ ! -d "$DEP_PATH" ]; then
        echo "Error: Dependency $DEP_NAME is missing. Please run prepare-libraries.sh first."
        exit 1
    fi

    TARGET_NAME="UltiBlox-$DEP_NAME"
    if [ -d "$ARDUINO_LIBRARIES_DIR/$TARGET_NAME" ]; then
        echo "$TARGET_NAME already installed."
    else
        cp -r "$DEP_PATH" "$ARDUINO_LIBRARIES_DIR/$TARGET_NAME"
        echo "$TARGET_NAME installed to $ARDUINO_LIBRARIES_DIR"
    fi
done < "$DEPENDENCIES_FILE"

echo "$LIBRARY_NAME and its dependencies installed successfully."