# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/niar14/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/niar14/catkin_ws/build

# Include any dependencies generated for this target.
include beginner_tutorials/CMakeFiles/app.dir/depend.make

# Include the progress variables for this target.
include beginner_tutorials/CMakeFiles/app.dir/progress.make

# Include the compile flags for this target's objects.
include beginner_tutorials/CMakeFiles/app.dir/flags.make

beginner_tutorials/CMakeFiles/app.dir/src/kamera.cpp.o: beginner_tutorials/CMakeFiles/app.dir/flags.make
beginner_tutorials/CMakeFiles/app.dir/src/kamera.cpp.o: /home/niar14/catkin_ws/src/beginner_tutorials/src/kamera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/niar14/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object beginner_tutorials/CMakeFiles/app.dir/src/kamera.cpp.o"
	cd /home/niar14/catkin_ws/build/beginner_tutorials && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/app.dir/src/kamera.cpp.o -c /home/niar14/catkin_ws/src/beginner_tutorials/src/kamera.cpp

beginner_tutorials/CMakeFiles/app.dir/src/kamera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app.dir/src/kamera.cpp.i"
	cd /home/niar14/catkin_ws/build/beginner_tutorials && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/niar14/catkin_ws/src/beginner_tutorials/src/kamera.cpp > CMakeFiles/app.dir/src/kamera.cpp.i

beginner_tutorials/CMakeFiles/app.dir/src/kamera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app.dir/src/kamera.cpp.s"
	cd /home/niar14/catkin_ws/build/beginner_tutorials && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/niar14/catkin_ws/src/beginner_tutorials/src/kamera.cpp -o CMakeFiles/app.dir/src/kamera.cpp.s

# Object files for target app
app_OBJECTS = \
"CMakeFiles/app.dir/src/kamera.cpp.o"

# External object files for target app
app_EXTERNAL_OBJECTS =

/home/niar14/catkin_ws/devel/lib/beginner_tutorials/app: beginner_tutorials/CMakeFiles/app.dir/src/kamera.cpp.o
/home/niar14/catkin_ws/devel/lib/beginner_tutorials/app: beginner_tutorials/CMakeFiles/app.dir/build.make
/home/niar14/catkin_ws/devel/lib/beginner_tutorials/app: beginner_tutorials/CMakeFiles/app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/niar14/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/niar14/catkin_ws/devel/lib/beginner_tutorials/app"
	cd /home/niar14/catkin_ws/build/beginner_tutorials && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
beginner_tutorials/CMakeFiles/app.dir/build: /home/niar14/catkin_ws/devel/lib/beginner_tutorials/app

.PHONY : beginner_tutorials/CMakeFiles/app.dir/build

beginner_tutorials/CMakeFiles/app.dir/clean:
	cd /home/niar14/catkin_ws/build/beginner_tutorials && $(CMAKE_COMMAND) -P CMakeFiles/app.dir/cmake_clean.cmake
.PHONY : beginner_tutorials/CMakeFiles/app.dir/clean

beginner_tutorials/CMakeFiles/app.dir/depend:
	cd /home/niar14/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/niar14/catkin_ws/src /home/niar14/catkin_ws/src/beginner_tutorials /home/niar14/catkin_ws/build /home/niar14/catkin_ws/build/beginner_tutorials /home/niar14/catkin_ws/build/beginner_tutorials/CMakeFiles/app.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : beginner_tutorials/CMakeFiles/app.dir/depend

