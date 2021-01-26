/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 06:30:07 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/07 22:28:14 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "events.h"

static void	reset(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < W)
	{
		engine->tline[i] = 0;
		engine->bline[i] = H - 1;
		i++;
	}
	engine->edit.mod_s = 0x01ab01;
	engine->edit.mod_w = -1;
	engine->edit.door = 0;
	if (engine->edit.graf != 1)
		engine->edit.txno = -1;
	engine->edit.graf_wall = -1;
	engine->player.shot = 0;
}

void		run_minimap_queue(t_engine *engine)
{
	unsigned int	i;
	int				sectorno;
	int				neighbor;

	i = 0;
	sectorno = engine->present->sectorno;
	while (i < engine->sectors[sectorno].npoints)
	{
		neighbor = engine->sectors[sectorno].neighbors[i];
		if (neighbor <= -1)
			engine->wall.color = WALL_COLOR;
		else
			engine->wall.color = EDGE_COLOR * engine->player.game_mode;
		engine->wall.color *= (engine->sectors[sectorno].floor
			< engine->player.where.z + 6)
			* (engine->sectors[sectorno].floor > engine->player.where.z - 12);
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
	t_queue	queue[MAX_QUEUE];

	SDL_LockSurface(engine->screen);
	SDL_FillRect(engine->screen, 0, 0x000000);
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
		while (engine->present != engine->future)
		{
			run_minimap_queue(engine);
			engine->present++;
		}
	}
	SDL_UnlockSurface(engine->screen);
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
			engine->edit.mod = main_editor(engine, all);
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}
		else
			engine->edit.mod = 0;
		reset(engine);
		keys_manager(engine);
		move(engine);
		draw(engine);
		door_anim(engine);
		real_time_edit(engine);
		put_hud(engine);
		if (SDL_GetTicks() - time < 32)
			SDL_Delay(32 - SDL_GetTicks() + time);
		time = SDL_GetTicks();
		SDL_UpdateWindowSurface(engine->window);
	}
}
