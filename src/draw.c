/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 06:30:07 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/07 22:28:14 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "editor.h"

static void	run_minimap_queue(t_engine *engine)
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

void		draw(t_engine *engine)
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
