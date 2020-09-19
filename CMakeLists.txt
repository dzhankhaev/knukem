cmake_minimum_required(VERSION 3.16)
project(d-k3d C)
set(CMAKE_C_STANDARD 99)

add_executable(d-k3d
        #[[SRC]]
        src/init_engine.c
        src/keys_manager.c
        src/manage_data.c
        src/start_game.c
        src/main.c
        src/math_utilits/vector_operations.c
        src/math_utilits/mathf.c
        src/render/line/render_line.c
        src/render/line/render_line_with_angle.c
        src/render/rotate.c
        includes/engine.h
        includes/arg_defines.h
        includes/math_utilits.h

include_directories(d-k3d frameworks/SDL2.framework/Headers
        frameworks/SDL2_image.framework/Headers
        frameworks/SDL2_mixer.framework.framework/Headers
        frameworks/SDL2_ttf.framework/Headers
        includes
        libft)

target_link_libraries(d-k3d ${PROJECT_SOURCE_DIR}/SDL/sdl2/2.0.12_1/lib/libSDL2-2.0.0.dylib
        ${PROJECT_SOURCE_DIR}/SDL/sdl2/2.0.12_1/lib/libSDL2.dylib
        ${PROJECT_SOURCE_DIR}/SDL/sdl2_image/2.0.5/lib/libSDL2_image-2.0.0.dylib
        ${PROJECT_SOURCE_DIR}/SDL/sdl2_image/2.0.5/lib/libSDL2_image.dylib
        ${PROJECT_SOURCE_DIR}/SDL/sdl2_mixer/2.0.4/lib/libSDL2_mixer-2.0.0.dylib
        ${PROJECT_SOURCE_DIR}/SDL/sdl2_mixer/2.0.4/lib/libSDL2_mixer.dylib
        ${PROJECT_SOURCE_DIR}/SDL/sdl2_ttf/2.0.15/lib/libSDL2_ttf-2.0.0.dylib
        ${PROJECT_SOURCE_DIR}/SDL/sdl2_ttf/2.0.15/lib/libSDL2_ttf.dylib)