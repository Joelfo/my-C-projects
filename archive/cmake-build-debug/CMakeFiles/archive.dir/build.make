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
CMAKE_SOURCE_DIR = "D:\Projetos\Estrutura de Dados\archive"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Projetos\Estrutura de Dados\archive\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/archive.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/archive.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/archive.dir/flags.make

CMakeFiles/archive.dir/main.c.obj: CMakeFiles/archive.dir/flags.make
CMakeFiles/archive.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Projetos\Estrutura de Dados\archive\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/archive.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\archive.dir\main.c.obj   -c "D:\Projetos\Estrutura de Dados\archive\main.c"

CMakeFiles/archive.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/archive.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "D:\Projetos\Estrutura de Dados\archive\main.c" > CMakeFiles\archive.dir\main.c.i

CMakeFiles/archive.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/archive.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "D:\Projetos\Estrutura de Dados\archive\main.c" -o CMakeFiles\archive.dir\main.c.s

# Object files for target archive
archive_OBJECTS = \
"CMakeFiles/archive.dir/main.c.obj"

# External object files for target archive
archive_EXTERNAL_OBJECTS =

archive.exe: CMakeFiles/archive.dir/main.c.obj
archive.exe: CMakeFiles/archive.dir/build.make
archive.exe: CMakeFiles/archive.dir/linklibs.rsp
archive.exe: CMakeFiles/archive.dir/objects1.rsp
archive.exe: CMakeFiles/archive.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\Projetos\Estrutura de Dados\archive\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable archive.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\archive.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/archive.dir/build: archive.exe

.PHONY : CMakeFiles/archive.dir/build

CMakeFiles/archive.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\archive.dir\cmake_clean.cmake
.PHONY : CMakeFiles/archive.dir/clean

CMakeFiles/archive.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Projetos\Estrutura de Dados\archive" "D:\Projetos\Estrutura de Dados\archive" "D:\Projetos\Estrutura de Dados\archive\cmake-build-debug" "D:\Projetos\Estrutura de Dados\archive\cmake-build-debug" "D:\Projetos\Estrutura de Dados\archive\cmake-build-debug\CMakeFiles\archive.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/archive.dir/depend

