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

# Include any dependencies generated for this target.
include CMakeFiles/Voice_for_VLC.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Voice_for_VLC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Voice_for_VLC.dir/flags.make

CMakeFiles/Voice_for_VLC.dir/main.cpp.o: CMakeFiles/Voice_for_VLC.dir/flags.make
CMakeFiles/Voice_for_VLC.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Voice_for_VLC.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Voice_for_VLC.dir/main.cpp.o -c /home/kalos/CLionProjects/Voice_for_VLC/main.cpp

CMakeFiles/Voice_for_VLC.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Voice_for_VLC.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kalos/CLionProjects/Voice_for_VLC/main.cpp > CMakeFiles/Voice_for_VLC.dir/main.cpp.i

CMakeFiles/Voice_for_VLC.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Voice_for_VLC.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kalos/CLionProjects/Voice_for_VLC/main.cpp -o CMakeFiles/Voice_for_VLC.dir/main.cpp.s

CMakeFiles/Voice_for_VLC.dir/message.cpp.o: CMakeFiles/Voice_for_VLC.dir/flags.make
CMakeFiles/Voice_for_VLC.dir/message.cpp.o: ../message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Voice_for_VLC.dir/message.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Voice_for_VLC.dir/message.cpp.o -c /home/kalos/CLionProjects/Voice_for_VLC/message.cpp

CMakeFiles/Voice_for_VLC.dir/message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Voice_for_VLC.dir/message.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kalos/CLionProjects/Voice_for_VLC/message.cpp > CMakeFiles/Voice_for_VLC.dir/message.cpp.i

CMakeFiles/Voice_for_VLC.dir/message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Voice_for_VLC.dir/message.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kalos/CLionProjects/Voice_for_VLC/message.cpp -o CMakeFiles/Voice_for_VLC.dir/message.cpp.s

CMakeFiles/Voice_for_VLC.dir/synch_queue.cpp.o: CMakeFiles/Voice_for_VLC.dir/flags.make
CMakeFiles/Voice_for_VLC.dir/synch_queue.cpp.o: ../synch_queue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Voice_for_VLC.dir/synch_queue.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Voice_for_VLC.dir/synch_queue.cpp.o -c /home/kalos/CLionProjects/Voice_for_VLC/synch_queue.cpp

CMakeFiles/Voice_for_VLC.dir/synch_queue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Voice_for_VLC.dir/synch_queue.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kalos/CLionProjects/Voice_for_VLC/synch_queue.cpp > CMakeFiles/Voice_for_VLC.dir/synch_queue.cpp.i

CMakeFiles/Voice_for_VLC.dir/synch_queue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Voice_for_VLC.dir/synch_queue.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kalos/CLionProjects/Voice_for_VLC/synch_queue.cpp -o CMakeFiles/Voice_for_VLC.dir/synch_queue.cpp.s

CMakeFiles/Voice_for_VLC.dir/vlc_manager.cpp.o: CMakeFiles/Voice_for_VLC.dir/flags.make
CMakeFiles/Voice_for_VLC.dir/vlc_manager.cpp.o: ../vlc_manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Voice_for_VLC.dir/vlc_manager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Voice_for_VLC.dir/vlc_manager.cpp.o -c /home/kalos/CLionProjects/Voice_for_VLC/vlc_manager.cpp

CMakeFiles/Voice_for_VLC.dir/vlc_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Voice_for_VLC.dir/vlc_manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kalos/CLionProjects/Voice_for_VLC/vlc_manager.cpp > CMakeFiles/Voice_for_VLC.dir/vlc_manager.cpp.i

CMakeFiles/Voice_for_VLC.dir/vlc_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Voice_for_VLC.dir/vlc_manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kalos/CLionProjects/Voice_for_VLC/vlc_manager.cpp -o CMakeFiles/Voice_for_VLC.dir/vlc_manager.cpp.s

CMakeFiles/Voice_for_VLC.dir/NotRunningException.cpp.o: CMakeFiles/Voice_for_VLC.dir/flags.make
CMakeFiles/Voice_for_VLC.dir/NotRunningException.cpp.o: ../NotRunningException.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Voice_for_VLC.dir/NotRunningException.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Voice_for_VLC.dir/NotRunningException.cpp.o -c /home/kalos/CLionProjects/Voice_for_VLC/NotRunningException.cpp

CMakeFiles/Voice_for_VLC.dir/NotRunningException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Voice_for_VLC.dir/NotRunningException.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kalos/CLionProjects/Voice_for_VLC/NotRunningException.cpp > CMakeFiles/Voice_for_VLC.dir/NotRunningException.cpp.i

CMakeFiles/Voice_for_VLC.dir/NotRunningException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Voice_for_VLC.dir/NotRunningException.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kalos/CLionProjects/Voice_for_VLC/NotRunningException.cpp -o CMakeFiles/Voice_for_VLC.dir/NotRunningException.cpp.s

CMakeFiles/Voice_for_VLC.dir/media.cpp.o: CMakeFiles/Voice_for_VLC.dir/flags.make
CMakeFiles/Voice_for_VLC.dir/media.cpp.o: ../media.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Voice_for_VLC.dir/media.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Voice_for_VLC.dir/media.cpp.o -c /home/kalos/CLionProjects/Voice_for_VLC/media.cpp

CMakeFiles/Voice_for_VLC.dir/media.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Voice_for_VLC.dir/media.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kalos/CLionProjects/Voice_for_VLC/media.cpp > CMakeFiles/Voice_for_VLC.dir/media.cpp.i

CMakeFiles/Voice_for_VLC.dir/media.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Voice_for_VLC.dir/media.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kalos/CLionProjects/Voice_for_VLC/media.cpp -o CMakeFiles/Voice_for_VLC.dir/media.cpp.s

CMakeFiles/Voice_for_VLC.dir/NotFoundException.cpp.o: CMakeFiles/Voice_for_VLC.dir/flags.make
CMakeFiles/Voice_for_VLC.dir/NotFoundException.cpp.o: ../NotFoundException.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Voice_for_VLC.dir/NotFoundException.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Voice_for_VLC.dir/NotFoundException.cpp.o -c /home/kalos/CLionProjects/Voice_for_VLC/NotFoundException.cpp

CMakeFiles/Voice_for_VLC.dir/NotFoundException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Voice_for_VLC.dir/NotFoundException.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kalos/CLionProjects/Voice_for_VLC/NotFoundException.cpp > CMakeFiles/Voice_for_VLC.dir/NotFoundException.cpp.i

CMakeFiles/Voice_for_VLC.dir/NotFoundException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Voice_for_VLC.dir/NotFoundException.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kalos/CLionProjects/Voice_for_VLC/NotFoundException.cpp -o CMakeFiles/Voice_for_VLC.dir/NotFoundException.cpp.s

CMakeFiles/Voice_for_VLC.dir/rest_server.cpp.o: CMakeFiles/Voice_for_VLC.dir/flags.make
CMakeFiles/Voice_for_VLC.dir/rest_server.cpp.o: ../rest_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Voice_for_VLC.dir/rest_server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Voice_for_VLC.dir/rest_server.cpp.o -c /home/kalos/CLionProjects/Voice_for_VLC/rest_server.cpp

CMakeFiles/Voice_for_VLC.dir/rest_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Voice_for_VLC.dir/rest_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kalos/CLionProjects/Voice_for_VLC/rest_server.cpp > CMakeFiles/Voice_for_VLC.dir/rest_server.cpp.i

CMakeFiles/Voice_for_VLC.dir/rest_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Voice_for_VLC.dir/rest_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kalos/CLionProjects/Voice_for_VLC/rest_server.cpp -o CMakeFiles/Voice_for_VLC.dir/rest_server.cpp.s

CMakeFiles/Voice_for_VLC.dir/TextOperation.cpp.o: CMakeFiles/Voice_for_VLC.dir/flags.make
CMakeFiles/Voice_for_VLC.dir/TextOperation.cpp.o: ../TextOperation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Voice_for_VLC.dir/TextOperation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Voice_for_VLC.dir/TextOperation.cpp.o -c /home/kalos/CLionProjects/Voice_for_VLC/TextOperation.cpp

CMakeFiles/Voice_for_VLC.dir/TextOperation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Voice_for_VLC.dir/TextOperation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kalos/CLionProjects/Voice_for_VLC/TextOperation.cpp > CMakeFiles/Voice_for_VLC.dir/TextOperation.cpp.i

CMakeFiles/Voice_for_VLC.dir/TextOperation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Voice_for_VLC.dir/TextOperation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kalos/CLionProjects/Voice_for_VLC/TextOperation.cpp -o CMakeFiles/Voice_for_VLC.dir/TextOperation.cpp.s

CMakeFiles/Voice_for_VLC.dir/NotValidURL.cpp.o: CMakeFiles/Voice_for_VLC.dir/flags.make
CMakeFiles/Voice_for_VLC.dir/NotValidURL.cpp.o: ../NotValidURL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Voice_for_VLC.dir/NotValidURL.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Voice_for_VLC.dir/NotValidURL.cpp.o -c /home/kalos/CLionProjects/Voice_for_VLC/NotValidURL.cpp

CMakeFiles/Voice_for_VLC.dir/NotValidURL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Voice_for_VLC.dir/NotValidURL.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kalos/CLionProjects/Voice_for_VLC/NotValidURL.cpp > CMakeFiles/Voice_for_VLC.dir/NotValidURL.cpp.i

CMakeFiles/Voice_for_VLC.dir/NotValidURL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Voice_for_VLC.dir/NotValidURL.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kalos/CLionProjects/Voice_for_VLC/NotValidURL.cpp -o CMakeFiles/Voice_for_VLC.dir/NotValidURL.cpp.s

# Object files for target Voice_for_VLC
Voice_for_VLC_OBJECTS = \
"CMakeFiles/Voice_for_VLC.dir/main.cpp.o" \
"CMakeFiles/Voice_for_VLC.dir/message.cpp.o" \
"CMakeFiles/Voice_for_VLC.dir/synch_queue.cpp.o" \
"CMakeFiles/Voice_for_VLC.dir/vlc_manager.cpp.o" \
"CMakeFiles/Voice_for_VLC.dir/NotRunningException.cpp.o" \
"CMakeFiles/Voice_for_VLC.dir/media.cpp.o" \
"CMakeFiles/Voice_for_VLC.dir/NotFoundException.cpp.o" \
"CMakeFiles/Voice_for_VLC.dir/rest_server.cpp.o" \
"CMakeFiles/Voice_for_VLC.dir/TextOperation.cpp.o" \
"CMakeFiles/Voice_for_VLC.dir/NotValidURL.cpp.o"

# External object files for target Voice_for_VLC
Voice_for_VLC_EXTERNAL_OBJECTS =

Voice_for_VLC: CMakeFiles/Voice_for_VLC.dir/main.cpp.o
Voice_for_VLC: CMakeFiles/Voice_for_VLC.dir/message.cpp.o
Voice_for_VLC: CMakeFiles/Voice_for_VLC.dir/synch_queue.cpp.o
Voice_for_VLC: CMakeFiles/Voice_for_VLC.dir/vlc_manager.cpp.o
Voice_for_VLC: CMakeFiles/Voice_for_VLC.dir/NotRunningException.cpp.o
Voice_for_VLC: CMakeFiles/Voice_for_VLC.dir/media.cpp.o
Voice_for_VLC: CMakeFiles/Voice_for_VLC.dir/NotFoundException.cpp.o
Voice_for_VLC: CMakeFiles/Voice_for_VLC.dir/rest_server.cpp.o
Voice_for_VLC: CMakeFiles/Voice_for_VLC.dir/TextOperation.cpp.o
Voice_for_VLC: CMakeFiles/Voice_for_VLC.dir/NotValidURL.cpp.o
Voice_for_VLC: CMakeFiles/Voice_for_VLC.dir/build.make
Voice_for_VLC: /usr/lib/libvlc.so
Voice_for_VLC: /usr/lib/x86_64-linux-gnu/libcpprest.so
Voice_for_VLC: /usr/lib/x86_64-linux-gnu/libboost_random.so
Voice_for_VLC: /usr/lib/x86_64-linux-gnu/libboost_system.so
Voice_for_VLC: /usr/lib/x86_64-linux-gnu/libboost_thread.so
Voice_for_VLC: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
Voice_for_VLC: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
Voice_for_VLC: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
Voice_for_VLC: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
Voice_for_VLC: /usr/lib/x86_64-linux-gnu/libboost_regex.so
Voice_for_VLC: /usr/lib/x86_64-linux-gnu/libssl.so
Voice_for_VLC: /usr/lib/x86_64-linux-gnu/libboost_system.so
Voice_for_VLC: /usr/lib/x86_64-linux-gnu/libcrypto.so
Voice_for_VLC: CMakeFiles/Voice_for_VLC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable Voice_for_VLC"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Voice_for_VLC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Voice_for_VLC.dir/build: Voice_for_VLC

.PHONY : CMakeFiles/Voice_for_VLC.dir/build

CMakeFiles/Voice_for_VLC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Voice_for_VLC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Voice_for_VLC.dir/clean

CMakeFiles/Voice_for_VLC.dir/depend:
	cd /home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kalos/CLionProjects/Voice_for_VLC /home/kalos/CLionProjects/Voice_for_VLC /home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release /home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release /home/kalos/CLionProjects/Voice_for_VLC/cmake-build-release/CMakeFiles/Voice_for_VLC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Voice_for_VLC.dir/depend

