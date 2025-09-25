#!/bin/bash
# Split a log file into N parts

# Usage: ./split-log.sh <input_file> <parts>

INPUT_FILE=$1
PARTS=$2

# Validation
if [[ -z "$INPUT_FILE" || -z "$PARTS" ]]; then
  echo "Usage: $0 <input_file> <parts>"
  exit 1
fi

if [[ ! -f "$INPUT_FILE" ]]; then
  echo "Error: file '$INPUT_FILE' not found."
  exit 1
fi

# Count total lines
TOTAL_LINES=$(wc -l < "$INPUT_FILE")
CHUNK_SIZE=$(( (TOTAL_LINES + PARTS - 1) / PARTS ))  # ceiling division

# Split file
FILENAME=$(basename -- "$INPUT_FILE")
EXT="${FILENAME##*.}"
BASENAME="${FILENAME%.*}"

split -l $CHUNK_SIZE -d --additional-suffix=".$EXT" "$INPUT_FILE" "${BASENAME}_part"

# Rename output to have _part1, _part2, ...
i=1
for f in ${BASENAME}_part*."$EXT"; do
  echo "Renaming $f to ${BASENAME}_part${i}.${EXT}"
  mv "$f" "${BASENAME}_part${i}.${EXT}"
  i=$((i+1))
done

echo "✅ File split into $PARTS parts successfully."
