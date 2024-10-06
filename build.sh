#!/bin/bash
# Build script for ActiveThreshold

# Compile all examples
arduino-cli compile --fqbn arduino:avr:uno examples/ActiveThresholdExample/ActiveThresholdExample.ino

# Add other necessary build steps if required

echo "Build complete."
