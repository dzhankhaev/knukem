#include "engine.h"

void	draw(t_engine *engine)
{
	engine->max_queue = MAX_QUEUE;
	engine->queue[engine->max_queue - 1].sectorno = 1;
	engine->future = engine->queue + 1;
	engine->present = engine->queue;
	engine->present->sectorno = CUR_SECT;
	while (engine->present != engine->future)
	{
		run_queue(engine);
		engine->present++;
	}
	render_minimap_hud(engine->minimap, engine->screen);
}

void	init_minimap(t_engine *engine)
{
//	engine->minimap.point = (t_xy){((W - W / 1.5) + (W - W / 4)) / 2, (H - H / 1.25 + H - H / 5) / 2};
	engine->minimap.point = (t_xy){W - W / 8, H - H / 6};
	engine->minimap.scale =  W / 125;
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
//	engine->minimap.borders = (t_line){0, W, 0, H, 0x555555};
	engine->minimap.borders = (t_line){W - W / 4, W,H - H / 3, H, 0x555555};
	engine->minimap.mod = 0;
}

void	game_loop(t_engine *engine)
{
	engine->borders = (t_line){0, W, 0, H, 0x555555};
	engine->player.cntrl = 0;
	engine->player.eyeheight = EyeHeight;
	engine->player.temp_yaw = 1.f;
	init_minimap(engine);
	while (!engine->close_request)
	{
		for(int i = 0; i < W; i++)
		{
			engine->top_line[i] = 0;
			engine->bottom_line[i] = H - 1;
		}
		SDL_LockSurface(engine->screen);
		SDL_FillRect(engine->screen, NULL, 0x000000);
		keys_manager(engine);
		move(engine);
		draw(engine);
		SDL_UnlockSurface(engine->screen);
		SDL_UpdateWindowSurface(engine->window);
		SDL_Delay(10);
	}
}
