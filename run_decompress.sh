#!/bin/bash

# parsing command line to get arguments using flags
while getopts r:c:o: opt; do
  case $opt in
    r) REFERENCE="$OPTARG" ;;
    c) COMPRESSED="$OPTARG" ;;
    o) OUTPUT="$OPTARG" ;;
    *) echo "Error: Please enter: ./run_decompress.sh -r reference_genome -c compressed_file -o output_file" >&2; exit 1 ;;
  esac
done

# check if all required arguments are provided
[ -z "$REFERENCE" ] || [ -z "$COMPRESSED" ] || [ -z "$OUTPUT" ] && {
  echo "Error: Please enter: ./run_decompress.sh -r reference_genome -c compressed_file -o output_file" >&2
  exit 1
}

# checking if reference genome file exists
if [ ! -f "$REFERENCE" ]; then
    echo "Error: Reference genome file doesn't exist."
    exit 1
fi

# checking if compressed genome file exists
if [ ! -f "$COMPRESSED" ]; then
    echo "Error: Compressed genome file doesn't exist."
    exit 1
fi

# compile decompression
make -C src/decompress || { echo "Error: Build failed. Exiting."; exit 1; }

# run decompression
{ time ./src/decompress/decompressor "$REFERENCE" "$COMPRESSED" > "$OUTPUT"; } 2>&1

# author: Mateo Jakšić
