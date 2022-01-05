# Minimal verions of cmake used
cmake_minimum_required (VERSION 3.0)

# The subproject
project (test_material_management)

# Include gtest library
find_package( GTest REQUIRED)
include_directories( ${GTEST_INCLUDE_DIR} )
enable_testing()
# TODO develope tests

# Test sources
set (SRC_TEST
    unit_test/test_material.cpp
    )

# Executable test
add_executable( material_test ${SRC_TEST} )
target_link_libraries( material_test MaterialManagement ${GTEST_LIBRARIES} pthread )
set_target_properties( material_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/unit_test" )
