# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.25

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Users\hzoi\AppData\Local\JetBrains\CLion 2023.1.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Users\hzoi\AppData\Local\JetBrains\CLion 2023.1.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\OI-Codes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\OI-Codes\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/P3383.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/P3383.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/P3383.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/P3383.dir/flags.make

CMakeFiles/P3383.dir/Luogu/P3383.cpp.obj: CMakeFiles/P3383.dir/flags.make
CMakeFiles/P3383.dir/Luogu/P3383.cpp.obj: CMakeFiles/P3383.dir/includes_CXX.rsp
CMakeFiles/P3383.dir/Luogu/P3383.cpp.obj: C:/OI-Codes/Luogu/P3383.cpp
CMakeFiles/P3383.dir/Luogu/P3383.cpp.obj: CMakeFiles/P3383.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\OI-Codes\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/P3383.dir/Luogu/P3383.cpp.obj"
	C:\Users\hzoi\AppData\Local\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/P3383.dir/Luogu/P3383.cpp.obj -MF CMakeFiles\P3383.dir\Luogu\P3383.cpp.obj.d -o CMakeFiles\P3383.dir\Luogu\P3383.cpp.obj -c C:\OI-Codes\Luogu\P3383.cpp

CMakeFiles/P3383.dir/Luogu/P3383.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/P3383.dir/Luogu/P3383.cpp.i"
	C:\Users\hzoi\AppData\Local\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\OI-Codes\Luogu\P3383.cpp > CMakeFiles\P3383.dir\Luogu\P3383.cpp.i

CMakeFiles/P3383.dir/Luogu/P3383.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/P3383.dir/Luogu/P3383.cpp.s"
	C:\Users\hzoi\AppData\Local\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\OI-Codes\Luogu\P3383.cpp -o CMakeFiles\P3383.dir\Luogu\P3383.cpp.s

# Object files for target P3383
P3383_OBJECTS = \
"CMakeFiles/P3383.dir/Luogu/P3383.cpp.obj"

# External object files for target P3383
P3383_EXTERNAL_OBJECTS =

P3383.exe: CMakeFiles/P3383.dir/Luogu/P3383.cpp.obj
P3383.exe: CMakeFiles/P3383.dir/build.make
P3383.exe: CMakeFiles/P3383.dir/linkLibs.rsp
P3383.exe: CMakeFiles/P3383.dir/objects1
P3383.exe: CMakeFiles/P3383.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\OI-Codes\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable P3383.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\P3383.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/P3383.dir/build: P3383.exe
.PHONY : CMakeFiles/P3383.dir/build

CMakeFiles/P3383.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\P3383.dir\cmake_clean.cmake
.PHONY : CMakeFiles/P3383.dir/clean

CMakeFiles/P3383.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\OI-Codes C:\OI-Codes C:\OI-Codes\cmake-build-debug C:\OI-Codes\cmake-build-debug C:\OI-Codes\cmake-build-debug\CMakeFiles\P3383.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/P3383.dir/depend
