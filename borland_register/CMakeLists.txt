﻿# CMakeList.txt : CMake project for borland_register, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (borland_register STATIC "borland_register.cpp" "borland_register.h")

# TODO: Add tests and install targets if needed.
