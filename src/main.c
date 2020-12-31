#include "engine.h"
#include "editor.h"
#include "utilits.h"

int main()
{
	t_engine	engine;
	t_all		all;

	init_engine(&engine, &all);
	general_init(&engine);
	engine.graf = (t_graf *)malloc(sizeof(t_graf) * (engine.num_sectors + 1));
	for(int i = 0;i<engine.num_sectors;i++)
	{
		engine.graf[i].sectorno = -1;
		engine.graf[i].g_num = 0;
		engine.graf[i].wall = 0;
		engine.graf[i].coord = 0;
		engine.graf[i].z = 0;
		engine.graf[i].txno = 0;
	}
	load_img(&engine, "wall1.png", 0);
	load_img(&engine, "wall2.png", 1);
	load_img(&engine, "wall3.png", 2);
	load_img(&engine, "floor1.png", 3);
	load_img(&engine, "ceil1.png", 4);
	load_img(&engine, "sky1.png", 5);
	game_loop(&engine, &all);
	for(int i = 0;i<engine.num_sectors;i++)
	{
//		for(int j = 0;j < engine.graf[i].g_num;j++)
			printf("sectorno %d g_num %d\n",engine.graf[i].sectorno, engine.graf[i].g_num);

	}
	clean(&engine);

	return (0);
}
