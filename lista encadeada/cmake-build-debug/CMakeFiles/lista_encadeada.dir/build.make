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
CMAKE_SOURCE_DIR = "D:\Projetos\Estrutura de Dados\lista encadeada"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Projetos\Estrutura de Dados\lista encadeada\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/lista_encadeada.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lista_encadeada.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lista_encadeada.dir/flags.make

CMakeFiles/lista_encadeada.dir/main.c.obj: CMakeFiles/lista_encadeada.dir/flags.make
CMakeFiles/lista_encadeada.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Projetos\Estrutura de Dados\lista encadeada\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lista_encadeada.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\lista_encadeada.dir\main.c.obj   -c "D:\Projetos\Estrutura de Dados\lista encadeada\main.c"

CMakeFiles/lista_encadeada.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lista_encadeada.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "D:\Projetos\Estrutura de Dados\lista encadeada\main.c" > CMakeFiles\lista_encadeada.dir\main.c.i

CMakeFiles/lista_encadeada.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lista_encadeada.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "D:\Projetos\Estrutura de Dados\lista encadeada\main.c" -o CMakeFiles\lista_encadeada.dir\main.c.s

# Object files for target lista_encadeada
lista_encadeada_OBJECTS = \
"CMakeFiles/lista_encadeada.dir/main.c.obj"

# External object files for target lista_encadeada
lista_encadeada_EXTERNAL_OBJECTS =

lista_encadeada.exe: CMakeFiles/lista_encadeada.dir/main.c.obj
lista_encadeada.exe: CMakeFiles/lista_encadeada.dir/build.make
lista_encadeada.exe: CMakeFiles/lista_encadeada.dir/linklibs.rsp
lista_encadeada.exe: CMakeFiles/lista_encadeada.dir/objects1.rsp
lista_encadeada.exe: CMakeFiles/lista_encadeada.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\Projetos\Estrutura de Dados\lista encadeada\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable lista_encadeada.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lista_encadeada.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lista_encadeada.dir/build: lista_encadeada.exe

.PHONY : CMakeFiles/lista_encadeada.dir/build

CMakeFiles/lista_encadeada.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lista_encadeada.dir\cmake_clean.cmake
.PHONY : CMakeFiles/lista_encadeada.dir/clean

CMakeFiles/lista_encadeada.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Projetos\Estrutura de Dados\lista encadeada" "D:\Projetos\Estrutura de Dados\lista encadeada" "D:\Projetos\Estrutura de Dados\lista encadeada\cmake-build-debug" "D:\Projetos\Estrutura de Dados\lista encadeada\cmake-build-debug" "D:\Projetos\Estrutura de Dados\lista encadeada\cmake-build-debug\CMakeFiles\lista_encadeada.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/lista_encadeada.dir/depend
