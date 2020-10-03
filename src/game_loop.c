#include "engine.h"

void			draw(t_engine *engine)
{
	engine->max_queue = 32;
	engine->future = engine->queue;
	engine->present = engine->queue;
	engine->present->sectorno = CUR_SECT;
	while (engine->present + 1 != engine->queue + engine->max_queue)
	{
		fill_queue(engine, engine->present->sectorno);
		engine->present++;
	}

}

void init_minimap(t_engine *engine)
{
	engine->minimap.point = (t_xy){W - W / 8, H - H / 6};
	engine->minimap.scale =  W / 100;
	engine->minimap.player_horizontal.color = 0x4444FF;
	engine->minimap.player_horizontal.x0 = engine->minimap.point.x - 5;
	engine->minimap.player_horizontal.y0 = engine->minimap.point.y;
	engine->minimap.player_horizontal.x1 = engine->minimap.point.x + 5;
	engine->minimap.player_horizontal.y1 = engine->minimap.point.y;
	engine->minimap.player_vertical.color = 0x4444FF;
	engine->minimap.player_vertical.x0 = engine->minimap.point.x;
	engine->minimap.player_vertical.y0 = engine->minimap.point.y - 11;
	engine->minimap.player_vertical.x1 = engine->minimap.point.x;
	engine->minimap.player_vertical.y1 = engine->minimap.point.y + 3;
	engine->minimap.borders = (t_line){W - W / 4, W,
									H - H / 3, H, 0x555555};
}

void game_loop(t_engine *engine)
{
	engine->borders = (t_line){0, W, 0, H, 0};
	init_minimap(engine);
	while (!engine->close_request)
	{
		SDL_LockSurface(engine->screen);
		SDL_FillRect(engine->screen, NULL, 0x000000);
		move(engine);
		draw(engine);
		SDL_UnlockSurface(engine->screen);
		SDL_UpdateWindowSurface(engine->window);
		keys_manager(engine);
		SDL_Delay(10);
	}
}
