cmake_minimum_required (VERSION 3.8)

project ("borland_register")

set(ASMJIT_STATIC 1)
add_subdirectory ("asmjit")
include_directories ("${PROJECT_SOURCE_DIR}/asmjit/src")

add_subdirectory ("borland_register")