cmake_minimum_required(VERSION 3.16)
project(d-k3d C)
set(CMAKE_C_STANDARD 99)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(d-k3d
		#[[TODO]]

		src/animations/do_door_anim.c
		src/animations/start_door_anim.c
		src/archiver
		#[[src/archiver/archiver.c
		src/archiver/pack.c
		src/archiver/unpack.c]]
		src/editor
		src/editor/door_mod.c
		src/editor/graf_mod.c
		src/editor/real_time_edit.c
		src/editor/tx_mod.c
		src/key_events
		src/key_events/event_edit.c
		src/key_events/event_movement.c
		src/key_events/keys_manager.c
		src/map_editor
		src/map_editor/draw_all.c
		src/map_editor/draw_map.c
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
		src/map_editor/sector_add.c
		src/map_editor/sector_check.c
		src/map_editor/sector_neighbors.c
		src/map_editor/sector_remove.c
		src/map_editor/sprites.c
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
		src/render/graf_proccesing.c
		src/render/minimap.c
		src/render/render_hplane.c
		src/render/render_scene.c
		src/render/sprite_render.c
		src/render/transform_sprite.c
		src/utilits
		src/utilits/math
		src/utilits/math/determine_intersection.c
		src/utilits/math/intersection_point.c
		src/utilits/math/mathf.c
		src/utilits/math/mathf2.c
		src/utilits/math/perspective_transform.c
		src/utilits/math/rotates.c
		src/utilits/anim_delete.c
		src/utilits/exit_options.c
		src/utilits/load_img.c
		src/utilits/swap.c
		src/utilits/utilits.c
		src/archiver.c
		src/cut_wall.c
		src/dash_board.c
		src/dash_board_fill_hud.c
		src/dash_board_sub.c
		src/game_loop.c
		#[[src/hud.c]]
		src/init.c
		src/init_engine.c
		src/lighting.c
		src/main.c
		src/manage_data.c
		src/pack.c
		src/run_queue.c
		src/transform_wall.c
		src/unpack.c

		libft/c_add.c
		libft/c_arg.c
		libft/c_mod.c
		libft/c_pow.c
		libft/c_set.c
		libft/c_sqr.c
		libft/c_sub.c
		libft/ft_arrlen.c
		libft/ft_atof.c
		libft/ft_atoi.c
		libft/ft_bzero.c
		libft/ft_free_split.c
		libft/ft_isalnum.c
		libft/ft_isalpha.c
		libft/ft_isascii.c
		libft/ft_isdigit.c
		libft/ft_isprint.c
		libft/ft_itoa.c
		libft/ft_lstadd.c
		libft/ft_lstdel.c
		libft/ft_lstdelone.c
		libft/ft_lstiter.c
		libft/ft_lstmap.c
		libft/ft_lstnew.c
		libft/ft_memalloc.c
		libft/ft_memccpy.c
		libft/ft_memchr.c
		libft/ft_memcmp.c
		libft/ft_memcpy.c
		libft/ft_memdel.c
		libft/ft_memmove.c
		libft/ft_memset.c
		libft/ft_putchar.c
		libft/ft_putchar_fd.c
		libft/ft_putendl.c
		libft/ft_putendl_fd.c
		libft/ft_putnbr.c
		libft/ft_putnbr_fd.c
		libft/ft_putstr.c
		libft/ft_putstr_fd.c
		libft/ft_realloc.c
		libft/ft_strcat.c
		libft/ft_strchr.c
		libft/ft_strclr.c
		libft/ft_strcmp.c
		libft/ft_strcpy.c
		libft/ft_strdel.c
		libft/ft_strdup.c
		libft/ft_strequ.c
		libft/ft_striter.c
		libft/ft_striteri.c
		libft/ft_strjoin.c
		libft/ft_strlcat.c
		libft/ft_strlen.c
		libft/ft_strmap.c
		libft/ft_strmapi.c
		libft/ft_strncat.c
		libft/ft_strncmp.c
		libft/ft_strncpy.c
		libft/ft_strnequ.c
		libft/ft_strnew.c
		libft/ft_strnstr.c
		libft/ft_strrchr.c
		libft/ft_strsplit.c
		libft/ft_strstr.c
		libft/ft_strsub.c
		libft/ft_strtrim.c
		libft/ft_swap.c
		libft/ft_tolower.c
		libft/ft_toupper.c
		libft/get_next_line.c src/editor/delete_one_graf.c)

include_directories(d-k3d
		includes/
		libft/
		${SDL2_INCLUDE_DIRS}
		${SDL2_IMAGE_INCLUDE_DIRS}
		)

#[[set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)]]

target_link_libraries(d-k3d #[[${LIBFT}]] ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} -lm)
