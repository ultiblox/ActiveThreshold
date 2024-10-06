#!/bin/bash
# Increment version script for ActiveThreshold

# Extract the current version from library.properties
current_version=$(grep "^version=" library.properties | cut -d'=' -f2)

# Increment the patch version (e.g., 1.0.0 -> 1.0.1)
IFS='.' read -r major minor patch <<< "$current_version"
new_patch=$((patch + 1))
new_version="$major.$minor.$new_patch"

# Update the version in library.properties
sed -i "s/^version=.*/version=$new_version/" library.properties

echo "Version incremented to $new_version."
