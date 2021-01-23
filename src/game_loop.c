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
        i++;
    }
    engine->edit.mod_s = 0x01ab01;	//запрет на модификацию (прежде нужно найти цель)
    engine->edit.mod_w = -1;	//запрет на модификацию (прежде нужно найти цель)
    engine->edit.door = 0;		//
    if (engine->edit.graf != 1)	//в режиме граффити текстуры помещений менять нельзя
        engine->edit.txno = -1;
    engine->edit.graf_wall = -1;
	engine->player.shot = 0;
}

void 		run_minimap_queue(t_engine *engine)
{
	int		i;
	int		sectorno;
	int		neighbor;

	i = 0;
	sectorno = engine->present->sectorno;
	while (i < engine->sectors[sectorno].npoints)
	{
		neighbor = engine->sectors[sectorno].neighbors[i];
		if (neighbor <= -1)
			engine->wall.color = WALL_COLOR;
		else
			engine->wall.color = EDGE_COLOR * engine->player.game_mode;
		minimap(engine, engine->sectors[sectorno].vertex[i],
				engine->sectors[sectorno].vertex[i + 1], engine->wall.color);
		if (engine->future + 1 != engine->queue + engine->max_queue &&
			neighbor > -1 && check_repeat(engine, sectorno, neighbor))
			*(engine->future++) = (t_queue){neighbor, 0, W, sectorno};
		i++;
	}
}

static void	draw(t_engine *engine)
{
    /*
     * START
     */
    Uint32 start = SDL_GetTicks();
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
	if (engine->minimap.mod)
	{
		render_minimap_hud(&engine->minimap, engine->screen);
		engine->future = engine->queue + 1;
		engine->present = engine->queue;
		ft_bzero(engine->queue + 1, sizeof(t_queue) * (MAX_QUEUE - 1));
		while (engine->present != engine->future)
		{
			run_minimap_queue(engine);
			engine->present++;
		}
	}
    //printf("%i\n", SDL_GetTicks() - start);
    /*
     * END
     */
    //engine->present--;
    /*
    while (engine->present != engine->queue)
    {
        if (transform_sprite(engine)) {
            render_sprite(engine);
        }
        engine->present--;
    }
    */
}

static int	check_anim(t_engine *engine)
{
	int	q;
	int	i;

	i = 0;
	while (i < engine->num_sectors)
	{
		q = -2;
		while (q < 30)
			if (engine->danimbuf[(q += 2)] == i)
				return (0);
		i++;
	}
	return (1);
}

void		game_loop(t_engine *engine, t_all *all)
{
	int		time;

	time = 0;
	while (!engine->close_request)
	{
		if (engine->edit.mod && check_anim(engine))
		{
			SDL_SetRelativeMouseMode(SDL_FALSE);
			engine->edit.mod = main_editor(engine, "map-clear", all);
			SDL_SetRelativeMouseMode(SDL_TRUE); //скрывает курсор, он движется относительно окна
		}
		else
			engine->edit.mod = 0;
		reset(engine);
		keys_manager(engine);
		move(engine);
		SDL_LockSurface(engine->screen);
		SDL_FillRect(engine->screen, 0, 0x000000);
		draw(engine);
		door_anim(engine);
		SDL_UnlockSurface(engine->screen);
		real_time_edit(engine);
		put_hud(engine);
		if (SDL_GetTicks() - time < 32)
			SDL_Delay(32 - SDL_GetTicks() + time);
		time = SDL_GetTicks();
		SDL_UpdateWindowSurface(engine->window);
	}
}
