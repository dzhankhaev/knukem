#include "engine.h"
#include "editor.h"
#include "utilits.h"

/**
 * Setup a window app icon
 */
void setup_window_icon(t_engine *engine)
{
	SDL_Surface *iconSurface;
	load_img(engine, "icon.png", 6);
	iconSurface = engine->img[6].tx;
	//iconSurface = IMG_Load("textures/icon.png");

	// The icon requires the window pointer NOT the renderer
	SDL_SetWindowIcon(engine->window, iconSurface);

	// ...and can now free the appicon surface
	SDL_FreeSurface(iconSurface);
}

int main()
{
	t_engine	engine;
	t_all		all;

	init_engine(&engine, &all);
	general_init(&engine);
	setup_window_icon(&engine);
	load_img(&engine, "wall1.png", 0);
	load_img(&engine, "wall2.png", 1);
	load_img(&engine, "wall3.png", 2);
	load_img(&engine, "floor1.png", 3);
	load_img(&engine, "ceil1.png", 4);
	load_img(&engine, "sky1.png", 5);
	game_loop(&engine, &all);
	clean(&engine);

	return (0);
}
