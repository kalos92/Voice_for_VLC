# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/kalos/Desktop/clion-2019.1.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/kalos/Desktop/clion-2019.1.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kalos/CLionProjects/Voice_for_VLC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release

# Utility rule file for NightlyUpdate.

# Include the progress variables for this target.
include json/CMakeFiles/NightlyUpdate.dir/progress.make

json/CMakeFiles/NightlyUpdate:
	cd /home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/json && /home/kalos/Desktop/clion-2019.1.2/bin/cmake/linux/bin/ctest -D NightlyUpdate

NightlyUpdate: json/CMakeFiles/NightlyUpdate
NightlyUpdate: json/CMakeFiles/NightlyUpdate.dir/build.make

.PHONY : NightlyUpdate

# Rule to build all files generated by this target.
json/CMakeFiles/NightlyUpdate.dir/build: NightlyUpdate

.PHONY : json/CMakeFiles/NightlyUpdate.dir/build

json/CMakeFiles/NightlyUpdate.dir/clean:
	cd /home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/json && $(CMAKE_COMMAND) -P CMakeFiles/NightlyUpdate.dir/cmake_clean.cmake
.PHONY : json/CMakeFiles/NightlyUpdate.dir/clean

json/CMakeFiles/NightlyUpdate.dir/depend:
	cd /home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kalos/CLionProjects/Voice_for_VLC /home/kalos/CLionProjects/Voice_for_VLC/json /home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release /home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/json /home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/json/CMakeFiles/NightlyUpdate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : json/CMakeFiles/NightlyUpdate.dir/depend

