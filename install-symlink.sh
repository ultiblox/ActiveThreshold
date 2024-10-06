#!/bin/bash
# Create symlink for ActiveThreshold library in Arduino libraries folder

TARGET_DIR="$HOME/Arduino/libraries/ActiveThreshold"
SRC_DIR="$(pwd)"

# Check if symlink already exists
if [ -L "$TARGET_DIR" ]; then
    echo "Symlink already exists: $TARGET_DIR"
else
    # Remove existing directory if present
    if [ -d "$TARGET_DIR" ]; then
        rm -rf "$TARGET_DIR"
        echo "Removed existing directory at $TARGET_DIR"
    fi

    # Create the symlink
    ln -s "$SRC_DIR" "$TARGET_DIR"
    echo "Symlink created: $SRC_DIR -> $TARGET_DIR"
fi