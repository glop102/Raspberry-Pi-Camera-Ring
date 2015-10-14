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
CMAKE_SOURCE_DIR = /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland

# Include any dependencies generated for this target.
include containers/avi/CMakeFiles/writer_avi.dir/depend.make

# Include the progress variables for this target.
include containers/avi/CMakeFiles/writer_avi.dir/progress.make

# Include the compile flags for this target's objects.
include containers/avi/CMakeFiles/writer_avi.dir/flags.make

containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.o: containers/avi/CMakeFiles/writer_avi.dir/flags.make
containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.o: containers/avi/avi_writer.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.o"
	cd /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/avi && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/writer_avi.dir/avi_writer.c.o   -c /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/avi/avi_writer.c

containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/writer_avi.dir/avi_writer.c.i"
	cd /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/avi && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/avi/avi_writer.c > CMakeFiles/writer_avi.dir/avi_writer.c.i

containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/writer_avi.dir/avi_writer.c.s"
	cd /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/avi && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/avi/avi_writer.c -o CMakeFiles/writer_avi.dir/avi_writer.c.s

containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.o.requires:
.PHONY : containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.o.requires

containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.o.provides: containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.o.requires
	$(MAKE) -f containers/avi/CMakeFiles/writer_avi.dir/build.make containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.o.provides.build
.PHONY : containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.o.provides

containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.o.provides.build: containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.o

# Object files for target writer_avi
writer_avi_OBJECTS = \
"CMakeFiles/writer_avi.dir/avi_writer.c.o"

# External object files for target writer_avi
writer_avi_EXTERNAL_OBJECTS =

build/lib/writer_avi.so: containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.o
build/lib/writer_avi.so: containers/avi/CMakeFiles/writer_avi.dir/build.make
build/lib/writer_avi.so: build/lib/libcontainers.so
build/lib/writer_avi.so: build/lib/libvcos.so
build/lib/writer_avi.so: containers/avi/CMakeFiles/writer_avi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library ../../build/lib/writer_avi.so"
	cd /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/avi && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/writer_avi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
containers/avi/CMakeFiles/writer_avi.dir/build: build/lib/writer_avi.so
.PHONY : containers/avi/CMakeFiles/writer_avi.dir/build

containers/avi/CMakeFiles/writer_avi.dir/requires: containers/avi/CMakeFiles/writer_avi.dir/avi_writer.c.o.requires
.PHONY : containers/avi/CMakeFiles/writer_avi.dir/requires

containers/avi/CMakeFiles/writer_avi.dir/clean:
	cd /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/avi && $(CMAKE_COMMAND) -P CMakeFiles/writer_avi.dir/cmake_clean.cmake
.PHONY : containers/avi/CMakeFiles/writer_avi.dir/clean

containers/avi/CMakeFiles/writer_avi.dir/depend:
	cd /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/avi /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/avi /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/containers/avi/CMakeFiles/writer_avi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : containers/avi/CMakeFiles/writer_avi.dir/depend
