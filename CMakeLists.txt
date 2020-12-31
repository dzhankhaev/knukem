cmake_minimum_required(VERSION 3.16)
project(d-k3d C)
set(CMAKE_C_STANDARD 99)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(d-k3d
		#[[TODO]]

		src/editor/real_time_edit.c
		src/key_events
		src/key_events/event_edit.c
		src/key_events/event_movement.c
		src/key_events/keys_manager.c
		src/map_editor/draw_all.c
		src/map_editor/draw_map.c
		src/map_editor/draw_sprites.c
		src/map_editor/draw_ui.c
		src/map_editor/drawing_utils.c
		src/map_editor/errors.c
		src/map_editor/events_all.c
		src/map_editor/events_map.c
		src/map_editor/init.c
		src/map_editor/main.c
		src/map_editor/math.c
		src/map_editor/obj_detection.c
		src/map_editor/pixels.c
		src/map_editor/reader.c
		src/map_editor/sector_add.c
		src/map_editor/sector_check.c
		src/map_editor/sector_neighbors.c
		src/map_editor/sector_remove.c
		src/map_editor/texture.c
		src/map_editor/write.c
		src/movement
		src/movement/fall.c
		src/movement/move.c
		src/render
		src/render/line
		src/render/line/render_hline.c
		src/render/line/render_line.c
		src/render/line/render_vline.c
		src/render/wall
		src/render/wall/perspective_init.c
		src/render/wall/render_wall.c
		src/render/wall/wall_tx_init.c
		src/render/ceil_and_floor_init.c
		src/render/minimap.c
		src/render/render_hplane.c
		src/render/render_scene.c
		src/render/render_sky.c
		src/render/sprite_render.c
		src/render/transform_sprite.c
		src/utilits
		src/utilits/math
		src/utilits/math/determine_intersection.c
		src/utilits/math/intersection_point.c
		src/utilits/math/mathf.c
		src/utilits/math/perspective_transform.c
		src/utilits/math/rotates.c
		src/utilits/exit_options.c
		src/utilits/load_img.c
		src/utilits/swap.c
		src/utilits/utilits.c
		src/cut_wall.c
		src/game_loop.c
		src/init.c
		src/lighting.c
		src/main.c
		src/manage_data.c
		src/run_queue.c
		src/transform_wall.c
        src/render/render_graf.c src/editor/graf_mod.c src/editor/tx_mod.c)

include_directories(d-k3d
		includes/
		libft/
		)

set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)

target_link_libraries(d-k3d ${LIBFT} ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} -lm)