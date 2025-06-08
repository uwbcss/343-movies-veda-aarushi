#!/bin/bash
set -e

# 1) Clean and compile
make clean
make

echo "Running without Return (R) commands..."

# 2) Back up the original commands file
cp data4commands.txt data4commands.orig

# 3) Filter out lines starting with "R " and overwrite data4commands.txt
grep -v '^R ' data4commands.orig > data4commands.txt

# 4) Run the program
./a.out

# 5) Restore the original commands file
mv data4commands.orig data4commands.txt
