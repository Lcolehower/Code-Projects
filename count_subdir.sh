#!/bin/bash

# Step 1: Determine which directory to search
if [ $# -gt 0 ]; then
    sdir="$1"
else
    sdir="."
fi

# Check if the directory exists
if [ ! -d "$sdir" ]; then
    echo "Error: $sdir is not a valid directory."
    exit 1
fi

# Step 2: Count subdirectories at depth 1
nsubdir=$(find "$sdir" -maxdepth 1 -type d | wc -l)

# Print the number of subdirectories
echo "Number of subdirectories in $sdir: $nsubdir"