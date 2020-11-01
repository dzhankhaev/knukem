#include "engine.h"
#include "events.h"

void		draw(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < W)
	{
		engine->tline[i] = 0;
		engine->bline[i++] = H - 1;
	}
	engine->edit.mod_s = -1;
	engine->max_queue = MAX_QUEUE;
	t_queue queue[engine->max_queue];
	engine->queue = queue;
	engine->queue[engine->max_queue - 1].sectorno = 1;
	engine->future = engine->queue + 1;
	engine->present = engine->queue;
	*engine->present = (t_queue){engine->player.sector, 0, W - 1, -1};
	while (engine->present != engine->future)
	{
		run_queue(engine);
		engine->present++;
	}
	render_minimap_hud(engine->minimap, engine->screen);
}

void		init_minimap(t_engine *engine)
{
	engine->minimap.point = (t_xy){W - W / 8, H - H / 6};
	engine->minimap.scale =  W / 200;
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
	engine->minimap.borders = (t_line){W - W / 4, W,H - H / 3, H,
									0x555555};
	engine->minimap.mod = 0;
}

static void general_init(t_engine *engine)
{
	engine->borders = (t_line){0, W, 0, H, 0x555555};
	engine->player.falling = 0;
	engine->player.flying = 0;
	engine->player.ground = 1;
	engine->player.eyeheight = EYE_HEIGHT;
	engine->player.vangle = 0.f;
	engine->player.speed = MOVE_SPEED;
	init_minimap(engine);
}

void		game_loop(t_engine *engine)
{
	int		time;

	general_init(engine);
	time = 0;
	while (!engine->close_request)
	{
		keys_manager(engine);
		move(engine);
		SDL_LockSurface(engine->screen);
		draw(engine);
		SDL_UnlockSurface(engine->screen);
		if (SDL_GetTicks() - time < 32)
			SDL_Delay(32 - SDL_GetTicks() + time);
		time = SDL_GetTicks();
		SDL_UpdateWindowSurface(engine->window);
	}
}