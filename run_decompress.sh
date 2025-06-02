#!/bin/bash

# compile decompression
make -C src/decompress

# compile decompression
if [ $? -ne 0 ]; then
    echo "Build failed. Exiting."
    exit 1
fi

# run decompression
./src/decompress/decompressor > "./decompress_output"

# author: Mateo Jakšić
