# Minimal verions of cmake used
cmake_minimum_required (VERSION 3.0)

# The subproject
project (test_material_management)

# Include gtest library
# TODO develope tests

# Test sources
set (SRC_TEST
    test_class.cpp
    )

# Executable test
add_executable( material_test ${SRC_TEST} )
target_link_libraries( material_test MaterialManagement )
set_target_properties( material_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test" )
