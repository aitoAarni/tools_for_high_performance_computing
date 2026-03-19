#!/bin/bash

# run first chmod +x run_p2.sh before runnign the file
# you can run ./run_p2.sh > output.txt

echo "========== PROBLEM 2 DEMONSTRATION =========="

echo -e "\nCleaning up files to start from scratch...\n"
make clean

echo -e "\n Running 'make' for the first time:\n"
make

echo -e "\n Touching 'dep_2a' and 'dep_1b' to simulate a file update\n"
sleep 1 
touch dep_2a
touch dep_1b

echo -e "\n Running 'make' a second time:"
make
