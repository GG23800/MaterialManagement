# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/gg/Data/Github/perso/MaterialManagement

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/gg/Data/Github/perso/MaterialManagement

# Include any dependencies generated for this target.
include CMakeFiles/MaterialManagement.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MaterialManagement.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MaterialManagement.dir/flags.make

CMakeFiles/MaterialManagement.dir/src/material.cpp.o: CMakeFiles/MaterialManagement.dir/flags.make
CMakeFiles/MaterialManagement.dir/src/material.cpp.o: src/material.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/gg/Data/Github/perso/MaterialManagement/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MaterialManagement.dir/src/material.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MaterialManagement.dir/src/material.cpp.o -c /media/gg/Data/Github/perso/MaterialManagement/src/material.cpp

CMakeFiles/MaterialManagement.dir/src/material.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MaterialManagement.dir/src/material.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/gg/Data/Github/perso/MaterialManagement/src/material.cpp > CMakeFiles/MaterialManagement.dir/src/material.cpp.i

CMakeFiles/MaterialManagement.dir/src/material.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MaterialManagement.dir/src/material.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/gg/Data/Github/perso/MaterialManagement/src/material.cpp -o CMakeFiles/MaterialManagement.dir/src/material.cpp.s

CMakeFiles/MaterialManagement.dir/src/material.cpp.o.requires:

.PHONY : CMakeFiles/MaterialManagement.dir/src/material.cpp.o.requires

CMakeFiles/MaterialManagement.dir/src/material.cpp.o.provides: CMakeFiles/MaterialManagement.dir/src/material.cpp.o.requires
	$(MAKE) -f CMakeFiles/MaterialManagement.dir/build.make CMakeFiles/MaterialManagement.dir/src/material.cpp.o.provides.build
.PHONY : CMakeFiles/MaterialManagement.dir/src/material.cpp.o.provides

CMakeFiles/MaterialManagement.dir/src/material.cpp.o.provides.build: CMakeFiles/MaterialManagement.dir/src/material.cpp.o


# Object files for target MaterialManagement
MaterialManagement_OBJECTS = \
"CMakeFiles/MaterialManagement.dir/src/material.cpp.o"

# External object files for target MaterialManagement
MaterialManagement_EXTERNAL_OBJECTS =

src/libMaterialManagement.so: CMakeFiles/MaterialManagement.dir/src/material.cpp.o
src/libMaterialManagement.so: CMakeFiles/MaterialManagement.dir/build.make
src/libMaterialManagement.so: CMakeFiles/MaterialManagement.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/gg/Data/Github/perso/MaterialManagement/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library src/libMaterialManagement.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MaterialManagement.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MaterialManagement.dir/build: src/libMaterialManagement.so

.PHONY : CMakeFiles/MaterialManagement.dir/build

CMakeFiles/MaterialManagement.dir/requires: CMakeFiles/MaterialManagement.dir/src/material.cpp.o.requires

.PHONY : CMakeFiles/MaterialManagement.dir/requires

CMakeFiles/MaterialManagement.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MaterialManagement.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MaterialManagement.dir/clean

CMakeFiles/MaterialManagement.dir/depend:
	cd /media/gg/Data/Github/perso/MaterialManagement && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/gg/Data/Github/perso/MaterialManagement /media/gg/Data/Github/perso/MaterialManagement /media/gg/Data/Github/perso/MaterialManagement /media/gg/Data/Github/perso/MaterialManagement /media/gg/Data/Github/perso/MaterialManagement/CMakeFiles/MaterialManagement.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MaterialManagement.dir/depend
