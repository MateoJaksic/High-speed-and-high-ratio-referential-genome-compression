#!/bin/bash

# parsing command line to get arguments using flags
while getopts r:t:o: opt; do
  case $opt in
    r) REFERENCE="$OPTARG" ;;
    t) TARGET="$OPTARG" ;;
    o) OUTPUT="$OPTARG" ;;
    *) echo "Error: Please enter: ./run_compress.sh -r reference_genome -t target_genome -o output_file" >&2; exit 1 ;;
  esac
done

# check if all required arguments are provided
[ -z "$REFERENCE" ] || [ -z "$TARGET" ] || [ -z "$OUTPUT" ] && {
  echo "Error: Please enter: ./run_compress.sh -r reference_genome -t target_genome -o output_file" >&2
  exit 1
}

# checking if reference genome file exists
if [ ! -f "$REFERENCE" ]; then
    echo "Error: Reference genome file doesn't exist."
    exit 1
fi

# checking if target genome file exists
if [ ! -f "$TARGET" ]; then
    echo "Error: Target genome file doesn't exist."
    exit 1
fi

# compile compression
make -C src/compress || { echo "Error: Build failed. Exiting."; exit 1; }

# run compression
./src/compress/compressor "$REFERENCE" "$TARGET" > "$OUTPUT"

# author: Mateo Jakšić
