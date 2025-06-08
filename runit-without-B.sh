#!/bin/bash

# Exit on error
set -e

# 1) Build
make clean
make

echo "Running without Borrow (B) commands..."

# 2) Back up and filter out Borrow lines
cp data4commands.txt data4commands.orig
grep -v '^B ' data4commands.orig > data4commands.txt

# 3) Run the program
./a.out

# 4) Restore the original commands file
mv data4commands.orig data4commands.txt
