#!/bin/bash
set -e

# 1) Clean and recompile
make clean
make

echo "Running without Drama genre..."

# 2) Back up the original movies file
cp data4movies.txt data4movies.orig

# 3) Filter out lines that start with "D," and overwrite data4movies.txt
grep -v '^D,' data4movies.orig > data4movies.txt

# 4) Run the program
./a.out

# 5) Restore the original movies file
mv data4movies.orig data4movies.txt
