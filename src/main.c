#include "engine.h"
#include "utilits.h"

int main()
{
	t_engine engine;

	init_engine(&engine);
	general_init(&engine);
	load_img(&engine, "wall1.png", 0);
	load_img(&engine, "wall2.png", 1);
	load_img(&engine, "wall3.png", 2);
	load_img(&engine, "floor1.png", 3);
	game_loop(&engine);
	clean(&engine);
	return (0);
}
