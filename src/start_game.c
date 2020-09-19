#include "engine.h"
/*
void 	move(t_engine *engine)
{
	if (engine->player.wsad[2])
		rotate();
	else if (engine->player.wsad[3])
}
*/

t_line	rotate_coords(t_engine *engine, t_line wall)
{
	t_line	w;

	wall.x0 -= engine->player.where.x;
	wall.y0 -= engine->player.where.y;
	wall.x1 -= engine->player.where.x;
	wall.y1 -= engine->player.where.y;
	w = wall;
	wall.x0 = w.x0 * engine->player.anglecos +
			  w.y0 * engine->player.anglesin;
	wall.x1 = w.x1 * engine->player.anglecos +
			  w.y1 * engine->player.anglesin;
	wall.y0 = -w.x0 * engine->player.anglesin +
			  w.y0 * engine->player.anglecos;
	wall.y1 = -w.x1 * engine->player.anglesin +
			  w.y1 * engine->player.anglecos;
	return wall;
}

int check_repeating(unsigned *queue, int c)
{
	for (int i = 0; i < 32; i++)
	{
		if (queue[i] == c)
			return 0;
	}
	return 1;
}

void render_wall(t_engine *engine, unsigned s)
{
	int	color;
	int i;

	i = 0;
	while (i < engine->sectors[s].npoints)
	{
		if (engine->sectors[s].neighbors[i] == -1)
			color = 0xFFFFFF;
		else
		{
			color = 0;
			if (engine->future + 1 != engine->queue + engine->max_queue && engine->sectors[s].floor == 0
			&& check_repeating(engine->queue, engine->sectors[s].neighbors[i]))
				*(++engine->future) = engine->sectors[s].neighbors[i];
		}
		minimap(engine, (t_line){engine->minimap_scale * engine->sectors[s].vertex[i].x,
								 engine->minimap_scale * engine->sectors[s].vertex[i + 1].x,
								 engine->minimap_scale * engine->sectors[s].vertex[i].y,
								 engine->minimap_scale * engine->sectors[s].vertex[i + 1].y,
								 color});
		i++;
	}
}

void			draw(t_engine *engine)
{
	engine->max_queue = 32;
	engine->future = engine->queue;
	engine->present = engine->queue;
	*engine->present = CUR_SECT;
	while (engine->present++ + 1 != engine->queue + engine->max_queue)
	{
		render_wall(engine, *engine->present);
	}

}

void start_game(t_engine *engine)
{
	engine->minimap_x_y = (t_xy){W / 2, H / 2};
	engine->minimap_scale =  W / 50;
	while (!engine->close_request)
	{
		SDL_LockSurface(engine->screen);
		SDL_FillRect(engine->screen, NULL, 0x000000);
		draw(engine);
		SDL_UnlockSurface(engine->screen);
		SDL_UpdateWindowSurface(engine->window);
		keys_manager(engine);
		SDL_Delay(10);
	}
}
