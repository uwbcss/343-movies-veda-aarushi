#!/bin/bash
set -e

# Compile all sources into b.out
g++ -std=c++17 -Wall -Wextra *.cpp -o b.out

# Back up and filter out Borrow commands (lines starting with "B ")
cp data4commands.txt data4commands.bak
grep -v '^B ' data4commands.bak > data4commands.txt

# Run and capture output
./b.out > output-no-B.txt 2>&1

# Restore original commands file
mv data4commands.bak data4commands.txt

# Clean up
rm -f b.out

echo "Generated output-no-B.txt"
