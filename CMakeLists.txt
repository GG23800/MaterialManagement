# Minimal version of cmake used
cmake_minimum_required (VERSION 3.0)

# The project
project (MaterialManagement)

# Set directories
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/src)

# Include directories
include_directories(src)
include_directories(ThirdParty)

# Compilation flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3")

set(SRC
    src/material.cpp
    )

set(HEADER
    src/material.hpp
    )

add_library(MaterialManagement SHARED ${SRC} ${HEADER})
set_target_properties( MaterialManagement PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/src" )

# Test subproject
add_subdirectory(test)
