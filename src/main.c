#include "engine.h"
#include "editor.h"
#include "utilits.h"

int main()
{
	t_engine	engine;
	t_all		all;

	init_engine(&engine, &all);
	general_init(&engine);
	load_img(&engine, "wall1.png", 0);
	load_img(&engine, "wall2.png", 1);
	load_img(&engine, "wall3.png", 2);
	load_img(&engine, "wall4.png", 3);
	load_img(&engine, "wall5.png", 4);
	load_img(&engine, "wall6.png", 5);
	load_img(&engine, "wall7.png", 6);
	load_img(&engine, "floor1.png", 7);
	load_img(&engine, "ceil1.png", 8);
	load_img(&engine, "sky1.png", 9);
	game_loop(&engine, &all);
	clean(&engine);
	return (0);
}
