# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Projetos\Estrutura de Dados\strings"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Projetos\Estrutura de Dados\strings\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/strings.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/strings.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/strings.dir/flags.make

CMakeFiles/strings.dir/main.c.obj: CMakeFiles/strings.dir/flags.make
CMakeFiles/strings.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Projetos\Estrutura de Dados\strings\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/strings.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\strings.dir\main.c.obj   -c "D:\Projetos\Estrutura de Dados\strings\main.c"

CMakeFiles/strings.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/strings.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "D:\Projetos\Estrutura de Dados\strings\main.c" > CMakeFiles\strings.dir\main.c.i

CMakeFiles/strings.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/strings.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "D:\Projetos\Estrutura de Dados\strings\main.c" -o CMakeFiles\strings.dir\main.c.s

# Object files for target strings
strings_OBJECTS = \
"CMakeFiles/strings.dir/main.c.obj"

# External object files for target strings
strings_EXTERNAL_OBJECTS =

strings.exe: CMakeFiles/strings.dir/main.c.obj
strings.exe: CMakeFiles/strings.dir/build.make
strings.exe: CMakeFiles/strings.dir/linklibs.rsp
strings.exe: CMakeFiles/strings.dir/objects1.rsp
strings.exe: CMakeFiles/strings.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\Projetos\Estrutura de Dados\strings\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable strings.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\strings.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/strings.dir/build: strings.exe

.PHONY : CMakeFiles/strings.dir/build

CMakeFiles/strings.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\strings.dir\cmake_clean.cmake
.PHONY : CMakeFiles/strings.dir/clean

CMakeFiles/strings.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Projetos\Estrutura de Dados\strings" "D:\Projetos\Estrutura de Dados\strings" "D:\Projetos\Estrutura de Dados\strings\cmake-build-debug" "D:\Projetos\Estrutura de Dados\strings\cmake-build-debug" "D:\Projetos\Estrutura de Dados\strings\cmake-build-debug\CMakeFiles\strings.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/strings.dir/depend

