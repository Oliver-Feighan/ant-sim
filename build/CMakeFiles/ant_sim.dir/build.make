# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/of15641/Documents/OwnProjects/ant-sim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/of15641/Documents/OwnProjects/ant-sim/build

# Include any dependencies generated for this target.
include CMakeFiles/ant_sim.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ant_sim.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ant_sim.dir/flags.make

CMakeFiles/ant_sim.dir/src/main.cpp.o: CMakeFiles/ant_sim.dir/flags.make
CMakeFiles/ant_sim.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/of15641/Documents/OwnProjects/ant-sim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ant_sim.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ant_sim.dir/src/main.cpp.o -c /Users/of15641/Documents/OwnProjects/ant-sim/src/main.cpp

CMakeFiles/ant_sim.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ant_sim.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/of15641/Documents/OwnProjects/ant-sim/src/main.cpp > CMakeFiles/ant_sim.dir/src/main.cpp.i

CMakeFiles/ant_sim.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ant_sim.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/of15641/Documents/OwnProjects/ant-sim/src/main.cpp -o CMakeFiles/ant_sim.dir/src/main.cpp.s

CMakeFiles/ant_sim.dir/src/ant.cpp.o: CMakeFiles/ant_sim.dir/flags.make
CMakeFiles/ant_sim.dir/src/ant.cpp.o: ../src/ant.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/of15641/Documents/OwnProjects/ant-sim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ant_sim.dir/src/ant.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ant_sim.dir/src/ant.cpp.o -c /Users/of15641/Documents/OwnProjects/ant-sim/src/ant.cpp

CMakeFiles/ant_sim.dir/src/ant.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ant_sim.dir/src/ant.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/of15641/Documents/OwnProjects/ant-sim/src/ant.cpp > CMakeFiles/ant_sim.dir/src/ant.cpp.i

CMakeFiles/ant_sim.dir/src/ant.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ant_sim.dir/src/ant.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/of15641/Documents/OwnProjects/ant-sim/src/ant.cpp -o CMakeFiles/ant_sim.dir/src/ant.cpp.s

# Object files for target ant_sim
ant_sim_OBJECTS = \
"CMakeFiles/ant_sim.dir/src/main.cpp.o" \
"CMakeFiles/ant_sim.dir/src/ant.cpp.o"

# External object files for target ant_sim
ant_sim_EXTERNAL_OBJECTS =

ant_sim: CMakeFiles/ant_sim.dir/src/main.cpp.o
ant_sim: CMakeFiles/ant_sim.dir/src/ant.cpp.o
ant_sim: CMakeFiles/ant_sim.dir/build.make
ant_sim: /Users/of15641/opt/anaconda3/envs/ant_sim/lib/libsfml-graphics.2.5.1.dylib
ant_sim: /Users/of15641/opt/anaconda3/envs/ant_sim/lib/libsfml-window.2.5.1.dylib
ant_sim: /Users/of15641/opt/anaconda3/envs/ant_sim/lib/libsfml-system.2.5.1.dylib
ant_sim: CMakeFiles/ant_sim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/of15641/Documents/OwnProjects/ant-sim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ant_sim"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ant_sim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ant_sim.dir/build: ant_sim

.PHONY : CMakeFiles/ant_sim.dir/build

CMakeFiles/ant_sim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ant_sim.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ant_sim.dir/clean

CMakeFiles/ant_sim.dir/depend:
	cd /Users/of15641/Documents/OwnProjects/ant-sim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/of15641/Documents/OwnProjects/ant-sim /Users/of15641/Documents/OwnProjects/ant-sim /Users/of15641/Documents/OwnProjects/ant-sim/build /Users/of15641/Documents/OwnProjects/ant-sim/build /Users/of15641/Documents/OwnProjects/ant-sim/build/CMakeFiles/ant_sim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ant_sim.dir/depend

