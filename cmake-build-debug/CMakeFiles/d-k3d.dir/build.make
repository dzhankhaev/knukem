# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/129/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/129/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chel/Desktop/knukem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chel/Desktop/knukem/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/d-k3d.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/d-k3d.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/d-k3d.dir/flags.make

CMakeFiles/d-k3d.dir/src/init_engine.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/init_engine.c.o: ../src/init_engine.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/d-k3d.dir/src/init_engine.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/init_engine.c.o   -c /home/chel/Desktop/knukem/src/init_engine.c

CMakeFiles/d-k3d.dir/src/init_engine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/init_engine.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/init_engine.c > CMakeFiles/d-k3d.dir/src/init_engine.c.i

CMakeFiles/d-k3d.dir/src/init_engine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/init_engine.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/init_engine.c -o CMakeFiles/d-k3d.dir/src/init_engine.c.s

CMakeFiles/d-k3d.dir/src/keys_manager.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/keys_manager.c.o: ../src/keys_manager.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/d-k3d.dir/src/keys_manager.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/keys_manager.c.o   -c /home/chel/Desktop/knukem/src/keys_manager.c

CMakeFiles/d-k3d.dir/src/keys_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/keys_manager.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/keys_manager.c > CMakeFiles/d-k3d.dir/src/keys_manager.c.i

CMakeFiles/d-k3d.dir/src/keys_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/keys_manager.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/keys_manager.c -o CMakeFiles/d-k3d.dir/src/keys_manager.c.s

CMakeFiles/d-k3d.dir/src/manage_data.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/manage_data.c.o: ../src/manage_data.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/d-k3d.dir/src/manage_data.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/manage_data.c.o   -c /home/chel/Desktop/knukem/src/manage_data.c

CMakeFiles/d-k3d.dir/src/manage_data.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/manage_data.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/manage_data.c > CMakeFiles/d-k3d.dir/src/manage_data.c.i

CMakeFiles/d-k3d.dir/src/manage_data.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/manage_data.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/manage_data.c -o CMakeFiles/d-k3d.dir/src/manage_data.c.s

CMakeFiles/d-k3d.dir/src/game_loop.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/game_loop.c.o: ../src/game_loop.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/d-k3d.dir/src/game_loop.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/game_loop.c.o   -c /home/chel/Desktop/knukem/src/game_loop.c

CMakeFiles/d-k3d.dir/src/game_loop.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/game_loop.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/game_loop.c > CMakeFiles/d-k3d.dir/src/game_loop.c.i

CMakeFiles/d-k3d.dir/src/game_loop.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/game_loop.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/game_loop.c -o CMakeFiles/d-k3d.dir/src/game_loop.c.s

CMakeFiles/d-k3d.dir/src/main.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/d-k3d.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/main.c.o   -c /home/chel/Desktop/knukem/src/main.c

CMakeFiles/d-k3d.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/main.c > CMakeFiles/d-k3d.dir/src/main.c.i

CMakeFiles/d-k3d.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/main.c -o CMakeFiles/d-k3d.dir/src/main.c.s

CMakeFiles/d-k3d.dir/src/run_queue.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/run_queue.c.o: ../src/run_queue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/d-k3d.dir/src/run_queue.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/run_queue.c.o   -c /home/chel/Desktop/knukem/src/run_queue.c

CMakeFiles/d-k3d.dir/src/run_queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/run_queue.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/run_queue.c > CMakeFiles/d-k3d.dir/src/run_queue.c.i

CMakeFiles/d-k3d.dir/src/run_queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/run_queue.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/run_queue.c -o CMakeFiles/d-k3d.dir/src/run_queue.c.s

CMakeFiles/d-k3d.dir/src/move.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/move.c.o: ../src/move.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/d-k3d.dir/src/move.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/move.c.o   -c /home/chel/Desktop/knukem/src/move.c

CMakeFiles/d-k3d.dir/src/move.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/move.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/move.c > CMakeFiles/d-k3d.dir/src/move.c.i

CMakeFiles/d-k3d.dir/src/move.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/move.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/move.c -o CMakeFiles/d-k3d.dir/src/move.c.s

CMakeFiles/d-k3d.dir/src/math_utilits/determine_intersection.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/math_utilits/determine_intersection.c.o: ../src/math_utilits/determine_intersection.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/d-k3d.dir/src/math_utilits/determine_intersection.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/math_utilits/determine_intersection.c.o   -c /home/chel/Desktop/knukem/src/math_utilits/determine_intersection.c

CMakeFiles/d-k3d.dir/src/math_utilits/determine_intersection.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/math_utilits/determine_intersection.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/math_utilits/determine_intersection.c > CMakeFiles/d-k3d.dir/src/math_utilits/determine_intersection.c.i

CMakeFiles/d-k3d.dir/src/math_utilits/determine_intersection.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/math_utilits/determine_intersection.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/math_utilits/determine_intersection.c -o CMakeFiles/d-k3d.dir/src/math_utilits/determine_intersection.c.s

CMakeFiles/d-k3d.dir/src/math_utilits/intersection_point.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/math_utilits/intersection_point.c.o: ../src/math_utilits/intersection_point.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/d-k3d.dir/src/math_utilits/intersection_point.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/math_utilits/intersection_point.c.o   -c /home/chel/Desktop/knukem/src/math_utilits/intersection_point.c

CMakeFiles/d-k3d.dir/src/math_utilits/intersection_point.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/math_utilits/intersection_point.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/math_utilits/intersection_point.c > CMakeFiles/d-k3d.dir/src/math_utilits/intersection_point.c.i

CMakeFiles/d-k3d.dir/src/math_utilits/intersection_point.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/math_utilits/intersection_point.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/math_utilits/intersection_point.c -o CMakeFiles/d-k3d.dir/src/math_utilits/intersection_point.c.s

CMakeFiles/d-k3d.dir/src/math_utilits/mathf.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/math_utilits/mathf.c.o: ../src/math_utilits/mathf.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/d-k3d.dir/src/math_utilits/mathf.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/math_utilits/mathf.c.o   -c /home/chel/Desktop/knukem/src/math_utilits/mathf.c

CMakeFiles/d-k3d.dir/src/math_utilits/mathf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/math_utilits/mathf.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/math_utilits/mathf.c > CMakeFiles/d-k3d.dir/src/math_utilits/mathf.c.i

CMakeFiles/d-k3d.dir/src/math_utilits/mathf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/math_utilits/mathf.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/math_utilits/mathf.c -o CMakeFiles/d-k3d.dir/src/math_utilits/mathf.c.s

CMakeFiles/d-k3d.dir/src/render/line/render_line.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/render/line/render_line.c.o: ../src/render/line/render_line.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/d-k3d.dir/src/render/line/render_line.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/render/line/render_line.c.o   -c /home/chel/Desktop/knukem/src/render/line/render_line.c

CMakeFiles/d-k3d.dir/src/render/line/render_line.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/render/line/render_line.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/render/line/render_line.c > CMakeFiles/d-k3d.dir/src/render/line/render_line.c.i

CMakeFiles/d-k3d.dir/src/render/line/render_line.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/render/line/render_line.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/render/line/render_line.c -o CMakeFiles/d-k3d.dir/src/render/line/render_line.c.s

CMakeFiles/d-k3d.dir/src/render/minimap.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/render/minimap.c.o: ../src/render/minimap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/d-k3d.dir/src/render/minimap.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/render/minimap.c.o   -c /home/chel/Desktop/knukem/src/render/minimap.c

CMakeFiles/d-k3d.dir/src/render/minimap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/render/minimap.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/render/minimap.c > CMakeFiles/d-k3d.dir/src/render/minimap.c.i

CMakeFiles/d-k3d.dir/src/render/minimap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/render/minimap.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/render/minimap.c -o CMakeFiles/d-k3d.dir/src/render/minimap.c.s

CMakeFiles/d-k3d.dir/src/math_utilits/rotate_wall.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/math_utilits/rotate_wall.c.o: ../src/math_utilits/rotate_wall.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/d-k3d.dir/src/math_utilits/rotate_wall.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/math_utilits/rotate_wall.c.o   -c /home/chel/Desktop/knukem/src/math_utilits/rotate_wall.c

CMakeFiles/d-k3d.dir/src/math_utilits/rotate_wall.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/math_utilits/rotate_wall.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/math_utilits/rotate_wall.c > CMakeFiles/d-k3d.dir/src/math_utilits/rotate_wall.c.i

CMakeFiles/d-k3d.dir/src/math_utilits/rotate_wall.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/math_utilits/rotate_wall.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/math_utilits/rotate_wall.c -o CMakeFiles/d-k3d.dir/src/math_utilits/rotate_wall.c.s

CMakeFiles/d-k3d.dir/src/transform_wall.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/transform_wall.c.o: ../src/transform_wall.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/d-k3d.dir/src/transform_wall.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/transform_wall.c.o   -c /home/chel/Desktop/knukem/src/transform_wall.c

CMakeFiles/d-k3d.dir/src/transform_wall.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/transform_wall.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/transform_wall.c > CMakeFiles/d-k3d.dir/src/transform_wall.c.i

CMakeFiles/d-k3d.dir/src/transform_wall.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/transform_wall.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/transform_wall.c -o CMakeFiles/d-k3d.dir/src/transform_wall.c.s

CMakeFiles/d-k3d.dir/src/cut_wall.c.o: CMakeFiles/d-k3d.dir/flags.make
CMakeFiles/d-k3d.dir/src/cut_wall.c.o: ../src/cut_wall.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/d-k3d.dir/src/cut_wall.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/d-k3d.dir/src/cut_wall.c.o   -c /home/chel/Desktop/knukem/src/cut_wall.c

CMakeFiles/d-k3d.dir/src/cut_wall.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/d-k3d.dir/src/cut_wall.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chel/Desktop/knukem/src/cut_wall.c > CMakeFiles/d-k3d.dir/src/cut_wall.c.i

CMakeFiles/d-k3d.dir/src/cut_wall.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/d-k3d.dir/src/cut_wall.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chel/Desktop/knukem/src/cut_wall.c -o CMakeFiles/d-k3d.dir/src/cut_wall.c.s

# Object files for target d-k3d
d__k3d_OBJECTS = \
"CMakeFiles/d-k3d.dir/src/init_engine.c.o" \
"CMakeFiles/d-k3d.dir/src/keys_manager.c.o" \
"CMakeFiles/d-k3d.dir/src/manage_data.c.o" \
"CMakeFiles/d-k3d.dir/src/game_loop.c.o" \
"CMakeFiles/d-k3d.dir/src/main.c.o" \
"CMakeFiles/d-k3d.dir/src/run_queue.c.o" \
"CMakeFiles/d-k3d.dir/src/move.c.o" \
"CMakeFiles/d-k3d.dir/src/math_utilits/determine_intersection.c.o" \
"CMakeFiles/d-k3d.dir/src/math_utilits/intersection_point.c.o" \
"CMakeFiles/d-k3d.dir/src/math_utilits/mathf.c.o" \
"CMakeFiles/d-k3d.dir/src/render/line/render_line.c.o" \
"CMakeFiles/d-k3d.dir/src/render/minimap.c.o" \
"CMakeFiles/d-k3d.dir/src/math_utilits/rotate_wall.c.o" \
"CMakeFiles/d-k3d.dir/src/transform_wall.c.o" \
"CMakeFiles/d-k3d.dir/src/cut_wall.c.o"

# External object files for target d-k3d
d__k3d_EXTERNAL_OBJECTS =

d-k3d: CMakeFiles/d-k3d.dir/src/init_engine.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/keys_manager.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/manage_data.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/game_loop.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/main.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/run_queue.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/move.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/math_utilits/determine_intersection.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/math_utilits/intersection_point.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/math_utilits/mathf.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/render/line/render_line.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/render/minimap.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/math_utilits/rotate_wall.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/transform_wall.c.o
d-k3d: CMakeFiles/d-k3d.dir/src/cut_wall.c.o
d-k3d: CMakeFiles/d-k3d.dir/build.make
d-k3d: CMakeFiles/d-k3d.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking C executable d-k3d"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/d-k3d.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/d-k3d.dir/build: d-k3d

.PHONY : CMakeFiles/d-k3d.dir/build

CMakeFiles/d-k3d.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/d-k3d.dir/cmake_clean.cmake
.PHONY : CMakeFiles/d-k3d.dir/clean

CMakeFiles/d-k3d.dir/depend:
	cd /home/chel/Desktop/knukem/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chel/Desktop/knukem /home/chel/Desktop/knukem /home/chel/Desktop/knukem/cmake-build-debug /home/chel/Desktop/knukem/cmake-build-debug /home/chel/Desktop/knukem/cmake-build-debug/CMakeFiles/d-k3d.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/d-k3d.dir/depend

