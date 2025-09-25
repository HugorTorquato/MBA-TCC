#!/bin/bash

# This script counts the total number of lines in all .h, .cpp, and .py files
# located in the parent directory (..) and its subdirectories.
#
# Step-by-step explanation:
#
# 1. find .. -type f \( -name "*.h" -o -name "*.cpp" -o -name "*.py" \)
#    - 'find ..' starts searching from the parent directory.
#    - '-type f' restricts results to files (not directories).
#    - '\( ... \)' groups the following name patterns.
#    - '-name "*.h"' matches files ending with .h (C++ header files).
#    - '-o' means "or".
#    - '-name "*.cpp"' matches files ending with .cpp (C++ source files).
#    - '-name "*.py"' matches files ending with .py (Python files).
#
# 2. -exec cat {} +
#    - For each file found, 'cat' outputs its contents.
#    - '{}' is replaced by the found file paths.
#    - '+' means all files are passed to 'cat' in as few invocations as possible (efficient).
#
# 3. | wc -l
#    - The output of 'cat' (all file contents) is piped to 'wc -l'.
#    - 'wc -l' counts the total number of lines in the combined output.
#
# The final result is a single number: the total lines in all
# .h, .cpp, and .py files in the specified directory tree.
echo "Total lines (with empty):"
find .. -type f \( -name "*.h" -o -name "*.cpp" -o -name "*.py" \) -exec cat {} + | wc -l

# Count total lines (excluding empty)
echo "Total lines (no empty):"
find .. -type f \( -name "*.h" -o -name "*.cpp" -o -name "*.py" \) -exec cat {} + | grep -v '^[[:space:]]*$' | wc -l

echo ""
echo "File counts:"
for ext in h cpp py; do
  count=$(find .. -type f -name "*.$ext" | wc -l)
  echo ".$ext files: $count"
done

# Count total number of files
echo ""
echo "Total source files:"
find .. -type f \( -name "*.h" -o -name "*.cpp" -o -name "*.py" \) | wc -l