#!/bin/bash

# parsing command line to get arguments using flags
while getopts t:d:o: opt; do
  case $opt in
    t) TARGET="$OPTARG" ;;
    d) DECOMPRESSED="$OPTARG" ;;
    o) OUTPUT="$OPTARG" ;;
    *) echo "Error: Please enter: ./run_evaluate.sh -t target_genome -d decompressed_genome -o output_file" >&2; exit 1 ;;
  esac
done

# check if all required arguments are provided
[ -z "$TARGET" ] || [ -z "$DECOMPRESSED" ] || [ -z "$OUTPUT" ] && {
  echo "Error: Please enter: ./run_evaluate.sh -t target_genome -d decompressed_genome -o output_file" >&2
  exit 1
}

# checking if reference genome file exists
if [ ! -f "$TARGET" ]; then
    echo "Error: Target genome file doesn't exist."
    exit 1
fi

# checking if target genome file exists
if [ ! -f "$DECOMPRESSED" ]; then
    echo "Error: Decompressed genome file doesn't exist."
    exit 1
fi

# compile evaluation
make -C src/evaluate || { echo "Error: Build failed. Exiting."; exit 1; }

# run evaluation
./src/evaluate/evaluator "$TARGET" "$DECOMPRESSED" > "$OUTPUT"

# author: Mateo Jakšić
