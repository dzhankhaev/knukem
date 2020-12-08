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
	load_img(&engine, "floor1.png", 3);
	load_img(&engine, "ceil1.png", 4);
	load_img(&engine, "sky1.png", 5);
	game_loop(&engine, &all);
	clean(&engine);

	return (0);
}
