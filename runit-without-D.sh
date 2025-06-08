#!/bin/bash
set -e

# Compile all sources into b.out
g++ -std=c++17 -Wall -Wextra *.cpp -o b.out

# Back up and filter out Drama-genre movies (lines starting with "D,")
cp data4movies.txt data4movies.bak
grep -v '^D,' data4movies.bak > data4movies.txt

# Run and capture output
./b.out > output-no-D.txt 2>&1

# Restore original movies file
mv data4movies.bak data4movies.txt

# Clean up
rm -f b.out

echo "Generated output-no-D.txt"
