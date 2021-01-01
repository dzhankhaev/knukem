#include "engine.h"
#include "events.h"

static void	reset(t_engine *engine)
{
	int	i;

	i = 0;
	//линия раздела (для рендеринга)
	while (i < W)
	{
		engine->tline[i] = 0;
		engine->bline[i] = H - 1;
		engine->yctop[i] = 0;
		engine->ycbot[i] = H - 1;
		engine->yftop[i] = 0;
		engine->yfbot[i++] = H - 1;
	}
	engine->edit.mod_s = 0x01ab01;	//запрет на модификацию (прежде нужно найти цель)
	engine->edit.mod_w = -1;	//запрет на модификацию (прежде нужно найти цель)
	engine->edit.door = 0;		//
	if (engine->edit.graf != 1)	//в режиме граффити текстуры помещений менять нельзя
		engine->edit.txno = -1;
}

static void	draw(t_engine *engine)
{
	t_queue	queue[MAX_QUEUE];
	//все переменные ниже нужно сбрасывать каждый новый кадр
	engine->max_queue = MAX_QUEUE;
	engine->queue = queue;
	*engine->queue = (t_queue){engine->player.sector, 0, W - 1, -1};
	engine->future = engine->queue + 1;
	engine->present = engine->queue;
	while (engine->present != engine->future)
	{
		run_queue(engine);
		engine->present++;
	}
	render_minimap_hud(engine->minimap, engine->screen);
}

void		game_loop(t_engine *engine, t_all *all)
{
	int		time;

	time = 0;

	while (!engine->close_request)
	{
		if (engine->edit.mod)
		{
			SDL_SetRelativeMouseMode(SDL_FALSE);
			engine->edit.mod = main_editor(engine, "map-clear", all);
//			SDL_SetRelativeMouseMode(SDL_TRUE); //скрывает курсор, он движется относительно окна
		}
		reset(engine);
		keys_manager(engine);
		move(engine);
		SDL_LockSurface(engine->screen);
		draw(engine);
		SDL_UnlockSurface(engine->screen);
		real_time_edit(engine);
		if (SDL_GetTicks() - time < 32)
			SDL_Delay(32 - SDL_GetTicks() + time);
		time = SDL_GetTicks();
		SDL_UpdateWindowSurface(engine->window);
	}
}
