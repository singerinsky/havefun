# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/gl/workspace/havefun

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gl/workspace/havefun

# Include any dependencies generated for this target.
include test/CMakeFiles/mini_run.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/mini_run.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/mini_run.dir/flags.make

test/CMakeFiles/mini_run.dir/main.cpp.o: test/CMakeFiles/mini_run.dir/flags.make
test/CMakeFiles/mini_run.dir/main.cpp.o: test/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/havefun/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/mini_run.dir/main.cpp.o"
	cd /home/gl/workspace/havefun/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mini_run.dir/main.cpp.o -c /home/gl/workspace/havefun/test/main.cpp

test/CMakeFiles/mini_run.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mini_run.dir/main.cpp.i"
	cd /home/gl/workspace/havefun/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/havefun/test/main.cpp > CMakeFiles/mini_run.dir/main.cpp.i

test/CMakeFiles/mini_run.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mini_run.dir/main.cpp.s"
	cd /home/gl/workspace/havefun/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/havefun/test/main.cpp -o CMakeFiles/mini_run.dir/main.cpp.s

test/CMakeFiles/mini_run.dir/main.cpp.o.requires:
.PHONY : test/CMakeFiles/mini_run.dir/main.cpp.o.requires

test/CMakeFiles/mini_run.dir/main.cpp.o.provides: test/CMakeFiles/mini_run.dir/main.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/mini_run.dir/build.make test/CMakeFiles/mini_run.dir/main.cpp.o.provides.build
.PHONY : test/CMakeFiles/mini_run.dir/main.cpp.o.provides

test/CMakeFiles/mini_run.dir/main.cpp.o.provides.build: test/CMakeFiles/mini_run.dir/main.cpp.o

# Object files for target mini_run
mini_run_OBJECTS = \
"CMakeFiles/mini_run.dir/main.cpp.o"

# External object files for target mini_run
mini_run_EXTERNAL_OBJECTS =

mini_run: test/CMakeFiles/mini_run.dir/main.cpp.o
mini_run: test/CMakeFiles/mini_run.dir/build.make
mini_run: lib/libmysql2redis.so
mini_run: test/CMakeFiles/mini_run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../mini_run"
	cd /home/gl/workspace/havefun/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mini_run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/mini_run.dir/build: mini_run
.PHONY : test/CMakeFiles/mini_run.dir/build

test/CMakeFiles/mini_run.dir/requires: test/CMakeFiles/mini_run.dir/main.cpp.o.requires
.PHONY : test/CMakeFiles/mini_run.dir/requires

test/CMakeFiles/mini_run.dir/clean:
	cd /home/gl/workspace/havefun/test && $(CMAKE_COMMAND) -P CMakeFiles/mini_run.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/mini_run.dir/clean

test/CMakeFiles/mini_run.dir/depend:
	cd /home/gl/workspace/havefun && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gl/workspace/havefun /home/gl/workspace/havefun/test /home/gl/workspace/havefun /home/gl/workspace/havefun/test /home/gl/workspace/havefun/test/CMakeFiles/mini_run.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/mini_run.dir/depend

