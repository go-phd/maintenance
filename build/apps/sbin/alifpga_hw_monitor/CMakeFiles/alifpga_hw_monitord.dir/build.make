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
include apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/depend.make

# Include the progress variables for this target.
include apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/progress.make

# Include the compile flags for this target's objects.
include apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/flags.make

apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/src/alifpga_hw_monitor.cpp.o: apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/flags.make
apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/src/alifpga_hw_monitor.cpp.o: ../apps/sbin/alifpga_hw_monitor/src/alifpga_hw_monitor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/sf_project/maintenance/code/maintenance/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/src/alifpga_hw_monitor.cpp.o"
	cd /media/sf_project/maintenance/code/maintenance/build/apps/sbin/alifpga_hw_monitor && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alifpga_hw_monitord.dir/src/alifpga_hw_monitor.cpp.o -c /media/sf_project/maintenance/code/maintenance/apps/sbin/alifpga_hw_monitor/src/alifpga_hw_monitor.cpp

apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/src/alifpga_hw_monitor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alifpga_hw_monitord.dir/src/alifpga_hw_monitor.cpp.i"
	cd /media/sf_project/maintenance/code/maintenance/build/apps/sbin/alifpga_hw_monitor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/sf_project/maintenance/code/maintenance/apps/sbin/alifpga_hw_monitor/src/alifpga_hw_monitor.cpp > CMakeFiles/alifpga_hw_monitord.dir/src/alifpga_hw_monitor.cpp.i

apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/src/alifpga_hw_monitor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alifpga_hw_monitord.dir/src/alifpga_hw_monitor.cpp.s"
	cd /media/sf_project/maintenance/code/maintenance/build/apps/sbin/alifpga_hw_monitor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/sf_project/maintenance/code/maintenance/apps/sbin/alifpga_hw_monitor/src/alifpga_hw_monitor.cpp -o CMakeFiles/alifpga_hw_monitord.dir/src/alifpga_hw_monitor.cpp.s

# Object files for target alifpga_hw_monitord
alifpga_hw_monitord_OBJECTS = \
"CMakeFiles/alifpga_hw_monitord.dir/src/alifpga_hw_monitor.cpp.o"

# External object files for target alifpga_hw_monitord
alifpga_hw_monitord_EXTERNAL_OBJECTS =

apps/sbin/alifpga_hw_monitor/alifpga_hw_monitord: apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/src/alifpga_hw_monitor.cpp.o
apps/sbin/alifpga_hw_monitor/alifpga_hw_monitord: apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/build.make
apps/sbin/alifpga_hw_monitor/alifpga_hw_monitord: libs/maintenance/libcsd_maintenance.so
apps/sbin/alifpga_hw_monitor/alifpga_hw_monitord: apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/sf_project/maintenance/code/maintenance/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable alifpga_hw_monitord"
	cd /media/sf_project/maintenance/code/maintenance/build/apps/sbin/alifpga_hw_monitor && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alifpga_hw_monitord.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/build: apps/sbin/alifpga_hw_monitor/alifpga_hw_monitord

.PHONY : apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/build

apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/clean:
	cd /media/sf_project/maintenance/code/maintenance/build/apps/sbin/alifpga_hw_monitor && $(CMAKE_COMMAND) -P CMakeFiles/alifpga_hw_monitord.dir/cmake_clean.cmake
.PHONY : apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/clean

apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/depend:
	cd /media/sf_project/maintenance/code/maintenance/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/sf_project/maintenance/code/maintenance /media/sf_project/maintenance/code/maintenance/apps/sbin/alifpga_hw_monitor /media/sf_project/maintenance/code/maintenance/build /media/sf_project/maintenance/code/maintenance/build/apps/sbin/alifpga_hw_monitor /media/sf_project/maintenance/code/maintenance/build/apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : apps/sbin/alifpga_hw_monitor/CMakeFiles/alifpga_hw_monitord.dir/depend
