﻿# CMakeList.txt : CMake project for Sudoku, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Sudoku "Main.cpp" "Main.h" "Sudoku.cpp" "Sudoku.h"  "Generate.cpp" "Generate.h")

# TODO: Add tests and install targets if needed.
