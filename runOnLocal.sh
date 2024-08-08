#!/bin/bash
DIST_DIR=./dist

echo -e "\nCleaning previous build..."
make clean

echo -e "\nCreating new build..."
make

echo -e "\nRunning executable..."
cd ./dist
./executable
