#!/bin/bash

# Kompajliraj projekt
make -C src/compress

# Provjeri je li kompajlacija uspjela
if [ $? -ne 0 ]; then
    echo "Build failed. Exiting."
    exit 1
fi

# Pokreni program
./src/compress/compressor
