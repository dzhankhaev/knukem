cmake_minimum_required(VERSION 3.16)
project(d-k3d C)
set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(d-k3d
        #[[SRC]]
        src/init_engine.c
        src/keys_manager.c
        src/manage_data.c
        src/game_loop.c
        src/main.c
        src/fill_queue.c
        src/move.c
        src/math_utilits/vector_operations.c
        src/math_utilits/mathf.c
        src/render/line/render_line.c
        src/render/minimap.c
        src/render/line/render_line_with_angle.c
        src/render/rotate.c
        includes/engine.h
        includes/arg_defines.h
        includes/math_utilits.h
        )

include_directories(d-k3d
        includes/
        )

target_link_libraries(d-k3d ${SDL2_LIBRARIES} -lm)