# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/apple/Desktop/MIPT/TP/TP_project/Battleship

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/apple/Desktop/MIPT/TP/TP_project/Battleship/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Players.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Players.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Players.dir/flags.make

CMakeFiles/Players.dir/Players.cpp.o: CMakeFiles/Players.dir/flags.make
CMakeFiles/Players.dir/Players.cpp.o: ../Players.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/apple/Desktop/MIPT/TP/TP_project/Battleship/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Players.dir/Players.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Players.dir/Players.cpp.o -c /Users/apple/Desktop/MIPT/TP/TP_project/Battleship/Players.cpp

CMakeFiles/Players.dir/Players.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Players.dir/Players.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/apple/Desktop/MIPT/TP/TP_project/Battleship/Players.cpp > CMakeFiles/Players.dir/Players.cpp.i

CMakeFiles/Players.dir/Players.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Players.dir/Players.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/apple/Desktop/MIPT/TP/TP_project/Battleship/Players.cpp -o CMakeFiles/Players.dir/Players.cpp.s

# Object files for target Players
Players_OBJECTS = \
"CMakeFiles/Players.dir/Players.cpp.o"

# External object files for target Players
Players_EXTERNAL_OBJECTS =

libPlayers.dylib: CMakeFiles/Players.dir/Players.cpp.o
libPlayers.dylib: CMakeFiles/Players.dir/build.make
libPlayers.dylib: CMakeFiles/Players.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/apple/Desktop/MIPT/TP/TP_project/Battleship/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libPlayers.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Players.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Players.dir/build: libPlayers.dylib
.PHONY : CMakeFiles/Players.dir/build

CMakeFiles/Players.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Players.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Players.dir/clean

CMakeFiles/Players.dir/depend:
	cd /Users/apple/Desktop/MIPT/TP/TP_project/Battleship/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/apple/Desktop/MIPT/TP/TP_project/Battleship /Users/apple/Desktop/MIPT/TP/TP_project/Battleship /Users/apple/Desktop/MIPT/TP/TP_project/Battleship/cmake-build-debug /Users/apple/Desktop/MIPT/TP/TP_project/Battleship/cmake-build-debug /Users/apple/Desktop/MIPT/TP/TP_project/Battleship/cmake-build-debug/CMakeFiles/Players.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Players.dir/depend
