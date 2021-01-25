/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

int			check_repeat(t_engine *engine, int sectorno, int neighbor)
{
	t_queue *temp;

	temp = engine->queue;
	while (temp != engine->future)
	{
		if (temp->psec == neighbor && temp->sectorno == sectorno)
			return (0);
		temp++;
	}
	return (1);
}

static void	choose_edit(t_engine *engine, int i)
{
	if (engine->edit.mod_s == 0x01ab01 &&
		determine_intersection(engine->wall, (t_fline){0, 50, 0, 0, 0}))
	{
		engine->edit.mod_s =
				engine->sectors[engine->present->sectorno].neighbors[i];
		if (engine->edit.mod_w == -1)
			engine->edit.mod_w = i;
	}
}

void		run_queue(t_engine *engine)
{
	unsigned int	i;
	int				sectorno;

	i = 0;
	sectorno = engine->present->sectorno;
	while (i < engine->sectors[sectorno].npoints)
	{
		engine->wall = (t_fline){
				engine->sectors[engine->present->sectorno].vertex[i].x,
				engine->sectors[engine->present->sectorno].vertex[i + 1].x,
				engine->sectors[engine->present->sectorno].vertex[i].y,
				engine->sectors[engine->present->sectorno].vertex[i + 1].y,
				0};
		if (transform_wall(engine, &engine->wall))
		{
			choose_edit(engine, i);
			render_scene(engine, sectorno,
				engine->sectors[sectorno].neighbors[i], i);
		}
		i++;
	}
}
