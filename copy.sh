#!/bin/bash

# Paths
ROOT_DIR="$(pwd)"
BUILD_DIR="$ROOT_DIR/build"

# Check if build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    echo "Build directory does not exist. Creating..."
    mkdir -p "$BUILD_DIR"
fi

# Copy config.txt
if [ -f "$ROOT_DIR/config.txt" ]; then
    cp "$ROOT_DIR/config.txt" "$BUILD_DIR/"
    echo "Copied config.txt to build/"
else
    echo "Warning: config.txt not found in root folder!"
fi

# Copy fonts folder
if [ -d "$ROOT_DIR/fonts" ]; then
    cp -r "$ROOT_DIR/fonts" "$BUILD_DIR/"
    echo "Copied fonts/ folder to build/"
else
    echo "Warning: fonts/ folder not found in root folder!"
fi

echo "Done."
