# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/julian/projects/turbo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/julian/projects/turbo/build

# Include any dependencies generated for this target.
include submissions/codeforces/CMakeFiles/772b.dir/depend.make

# Include the progress variables for this target.
include submissions/codeforces/CMakeFiles/772b.dir/progress.make

# Include the compile flags for this target's objects.
include submissions/codeforces/CMakeFiles/772b.dir/flags.make

submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.o: submissions/codeforces/CMakeFiles/772b.dir/flags.make
submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.o: ../submissions/codeforces/772b.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/julian/projects/turbo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.o"
	cd /home/julian/projects/turbo/build/submissions/codeforces && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/772b.dir/772b.cpp.o -c /home/julian/projects/turbo/submissions/codeforces/772b.cpp

submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/772b.dir/772b.cpp.i"
	cd /home/julian/projects/turbo/build/submissions/codeforces && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/julian/projects/turbo/submissions/codeforces/772b.cpp > CMakeFiles/772b.dir/772b.cpp.i

submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/772b.dir/772b.cpp.s"
	cd /home/julian/projects/turbo/build/submissions/codeforces && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/julian/projects/turbo/submissions/codeforces/772b.cpp -o CMakeFiles/772b.dir/772b.cpp.s

submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.o.requires:

.PHONY : submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.o.requires

submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.o.provides: submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.o.requires
	$(MAKE) -f submissions/codeforces/CMakeFiles/772b.dir/build.make submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.o.provides.build
.PHONY : submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.o.provides

submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.o.provides.build: submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.o


# Object files for target 772b
772b_OBJECTS = \
"CMakeFiles/772b.dir/772b.cpp.o"

# External object files for target 772b
772b_EXTERNAL_OBJECTS =

submissions/codeforces/772b: submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.o
submissions/codeforces/772b: submissions/codeforces/CMakeFiles/772b.dir/build.make
submissions/codeforces/772b: submissions/codeforces/CMakeFiles/772b.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/julian/projects/turbo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 772b"
	cd /home/julian/projects/turbo/build/submissions/codeforces && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/772b.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
submissions/codeforces/CMakeFiles/772b.dir/build: submissions/codeforces/772b

.PHONY : submissions/codeforces/CMakeFiles/772b.dir/build

submissions/codeforces/CMakeFiles/772b.dir/requires: submissions/codeforces/CMakeFiles/772b.dir/772b.cpp.o.requires

.PHONY : submissions/codeforces/CMakeFiles/772b.dir/requires

submissions/codeforces/CMakeFiles/772b.dir/clean:
	cd /home/julian/projects/turbo/build/submissions/codeforces && $(CMAKE_COMMAND) -P CMakeFiles/772b.dir/cmake_clean.cmake
.PHONY : submissions/codeforces/CMakeFiles/772b.dir/clean

submissions/codeforces/CMakeFiles/772b.dir/depend:
	cd /home/julian/projects/turbo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/julian/projects/turbo /home/julian/projects/turbo/submissions/codeforces /home/julian/projects/turbo/build /home/julian/projects/turbo/build/submissions/codeforces /home/julian/projects/turbo/build/submissions/codeforces/CMakeFiles/772b.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : submissions/codeforces/CMakeFiles/772b.dir/depend

