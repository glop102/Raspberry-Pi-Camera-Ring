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
include host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/depend.make

# Include the progress variables for this target.
include host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/progress.make

# Include the compile flags for this target's objects.
include host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/flags.make

host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.o: host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/flags.make
host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.o: host_applications/linux/apps/vcmailbox/vcmailbox.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.o"
	cd /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/host_applications/linux/apps/vcmailbox && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/vcmailbox.dir/vcmailbox.c.o   -c /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/host_applications/linux/apps/vcmailbox/vcmailbox.c

host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vcmailbox.dir/vcmailbox.c.i"
	cd /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/host_applications/linux/apps/vcmailbox && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/host_applications/linux/apps/vcmailbox/vcmailbox.c > CMakeFiles/vcmailbox.dir/vcmailbox.c.i

host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vcmailbox.dir/vcmailbox.c.s"
	cd /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/host_applications/linux/apps/vcmailbox && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/host_applications/linux/apps/vcmailbox/vcmailbox.c -o CMakeFiles/vcmailbox.dir/vcmailbox.c.s

host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.o.requires:
.PHONY : host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.o.requires

host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.o.provides: host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.o.requires
	$(MAKE) -f host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/build.make host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.o.provides.build
.PHONY : host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.o.provides

host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.o.provides.build: host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.o

# Object files for target vcmailbox
vcmailbox_OBJECTS = \
"CMakeFiles/vcmailbox.dir/vcmailbox.c.o"

# External object files for target vcmailbox
vcmailbox_EXTERNAL_OBJECTS =

build/bin/vcmailbox: host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.o
build/bin/vcmailbox: host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/build.make
build/bin/vcmailbox: build/lib/libvchostif.a
build/bin/vcmailbox: build/lib/libvchiq_arm.so
build/bin/vcmailbox: build/lib/libvcos.so
build/bin/vcmailbox: build/lib/libvcfiled_check.a
build/bin/vcmailbox: host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../../../../build/bin/vcmailbox"
	cd /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/host_applications/linux/apps/vcmailbox && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vcmailbox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/build: build/bin/vcmailbox
.PHONY : host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/build

host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/requires: host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/vcmailbox.c.o.requires
.PHONY : host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/requires

host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/clean:
	cd /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/host_applications/linux/apps/vcmailbox && $(CMAKE_COMMAND) -P CMakeFiles/vcmailbox.dir/cmake_clean.cmake
.PHONY : host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/clean

host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/depend:
	cd /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/host_applications/linux/apps/vcmailbox /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/host_applications/linux/apps/vcmailbox /home/pi/git/Raspberry-Pi-Camera-Ring/Camera/userland/host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : host_applications/linux/apps/vcmailbox/CMakeFiles/vcmailbox.dir/depend

