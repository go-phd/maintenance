# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/sf_project/maintenance/code/maintenance

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/sf_project/maintenance/code/maintenance/build

# Include any dependencies generated for this target.
include apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/depend.make

# Include the progress variables for this target.
include apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/progress.make

# Include the compile flags for this target's objects.
include apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/flags.make

apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/src/alifpga_hw_optimize.cpp.o: apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/flags.make
apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/src/alifpga_hw_optimize.cpp.o: ../apps/bin/alifpga_hw_optimize/src/alifpga_hw_optimize.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/sf_project/maintenance/code/maintenance/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/src/alifpga_hw_optimize.cpp.o"
	cd /media/sf_project/maintenance/code/maintenance/build/apps/bin/alifpga_hw_optimize && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alifpga_hw_optimize.dir/src/alifpga_hw_optimize.cpp.o -c /media/sf_project/maintenance/code/maintenance/apps/bin/alifpga_hw_optimize/src/alifpga_hw_optimize.cpp

apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/src/alifpga_hw_optimize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alifpga_hw_optimize.dir/src/alifpga_hw_optimize.cpp.i"
	cd /media/sf_project/maintenance/code/maintenance/build/apps/bin/alifpga_hw_optimize && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/sf_project/maintenance/code/maintenance/apps/bin/alifpga_hw_optimize/src/alifpga_hw_optimize.cpp > CMakeFiles/alifpga_hw_optimize.dir/src/alifpga_hw_optimize.cpp.i

apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/src/alifpga_hw_optimize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alifpga_hw_optimize.dir/src/alifpga_hw_optimize.cpp.s"
	cd /media/sf_project/maintenance/code/maintenance/build/apps/bin/alifpga_hw_optimize && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/sf_project/maintenance/code/maintenance/apps/bin/alifpga_hw_optimize/src/alifpga_hw_optimize.cpp -o CMakeFiles/alifpga_hw_optimize.dir/src/alifpga_hw_optimize.cpp.s

# Object files for target alifpga_hw_optimize
alifpga_hw_optimize_OBJECTS = \
"CMakeFiles/alifpga_hw_optimize.dir/src/alifpga_hw_optimize.cpp.o"

# External object files for target alifpga_hw_optimize
alifpga_hw_optimize_EXTERNAL_OBJECTS =

apps/bin/alifpga_hw_optimize/alifpga_hw_optimize: apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/src/alifpga_hw_optimize.cpp.o
apps/bin/alifpga_hw_optimize/alifpga_hw_optimize: apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/build.make
apps/bin/alifpga_hw_optimize/alifpga_hw_optimize: libs/maintenance/libcsd_maintenance.so
apps/bin/alifpga_hw_optimize/alifpga_hw_optimize: apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/sf_project/maintenance/code/maintenance/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable alifpga_hw_optimize"
	cd /media/sf_project/maintenance/code/maintenance/build/apps/bin/alifpga_hw_optimize && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alifpga_hw_optimize.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/build: apps/bin/alifpga_hw_optimize/alifpga_hw_optimize

.PHONY : apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/build

apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/clean:
	cd /media/sf_project/maintenance/code/maintenance/build/apps/bin/alifpga_hw_optimize && $(CMAKE_COMMAND) -P CMakeFiles/alifpga_hw_optimize.dir/cmake_clean.cmake
.PHONY : apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/clean

apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/depend:
	cd /media/sf_project/maintenance/code/maintenance/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/sf_project/maintenance/code/maintenance /media/sf_project/maintenance/code/maintenance/apps/bin/alifpga_hw_optimize /media/sf_project/maintenance/code/maintenance/build /media/sf_project/maintenance/code/maintenance/build/apps/bin/alifpga_hw_optimize /media/sf_project/maintenance/code/maintenance/build/apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : apps/bin/alifpga_hw_optimize/CMakeFiles/alifpga_hw_optimize.dir/depend

