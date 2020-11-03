cmake_minimum_required(VERSION 3.10.2)
project(doom-nukem C)
set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(d-k3d
        src/init.c
        src/key_events/keys_manager.c
        src/manage_data.c
        src/game_loop.c
        src/main.c
        src/run_queue.c
        src/movement/move.c
        src/utilits/math/determine_intersection.c
        src/utilits/math/intersection_point.c
        src/utilits/math/mathf.c
        src/render/line/render_line.c
        src/render/minimap.c
        includes/engine.h
        includes/utilits.h
        src/utilits/math/rotates.c
        src/transform_wall.c
        src/cut_wall.c
        src/render/line/render_vline.c
        src/render/wall/render_wall.c
        src/utilits/math/perspective_transform.c src/lighting.c src/movement/fall.c src/editor/real_time_edit.c src/key_events/event_edit.c includes/events.h src/key_events/event_movement.c src/utilits/swap.c src/utilits/utilits.c src/utilits/exit_options.c src/utilits/load_img.c src/render/wall/perspective_init.c src/render/wall/render_surfaces.c)

include_directories(d-k3d
        includes/
        )

target_link_libraries(d-k3d ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} -lm)