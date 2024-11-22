#!/bin/bash

cmake -S . -B build  -DCMAKE_BUILD_TYPE=Debug
cmake --build build
tree build
valgrind --leak-check=yes "build/$1"