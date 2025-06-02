#!/bin/bash

# compile compression
make -C src/compress

# compile compression
if [ $? -ne 0 ]; then
    echo "Build failed. Exiting."
    exit 1
fi

# run compression
./src/compress/compressor > "./compress_output"

# author: Mateo Jakšić
