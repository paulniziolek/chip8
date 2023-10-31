#!/bin/bash
# build_chip8.sh
# A script to build the Chip8 directory using CMake and Make
set -e

mkdir -p build
cd build
# TODO: switch to release build w/ compiler flags & optimizations
cmake ..
make
cd ..
