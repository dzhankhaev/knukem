#include "engine.h"
#include "utilits.h"

int main()
{
	t_engine engine;

	init_engine(&engine);
	general_init(&engine);
	get_filename(&engine, "wall.png", 0);
	load_img(&engine, 0);
	game_loop(&engine);
	clean(&engine);
	return (0);
}
