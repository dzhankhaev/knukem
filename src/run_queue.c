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

/*
 * мы перемещаемся из А в В. Если в очереди был переход из В в А, то это возврат назад. Так делать нельзя.
 * это справедливо для выпуклых секторов
 */
int				check_repeat(t_engine *engine, int sectorno, int neighbor)
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

static void choose_edit(t_engine *engine, int i)
{
	if (engine->edit.mod_s == 0x01ab01 &&
		determine_intersection(engine->wall, (t_fline){0, 50, 0, 0}))
	{
		engine->edit.mod_s =
				engine->sectors[engine->present->sectorno].neighbors[i];	//этот сектор можно модифицировать
		if (engine->edit.mod_w == -1)
			engine->edit.mod_w = i;
	}

}

void 		run_queue(t_engine *engine)
{
	int		i;
	int		sectorno;
	int		color;

	i = 0;
	sectorno = engine->present->sectorno;
	while (i < engine->sectors[sectorno].npoints)
	{
		if (engine->sectors[sectorno].neighbors[i] <= -1)
			engine->wall.color = abs(engine->sectors[sectorno].neighbors[i]);
		else
			engine->wall.color = 0;
		color = engine->wall.color;
		engine->wall = (t_fline){
				engine->sectors[engine->present->sectorno].vertex[i].x,
				engine->sectors[engine->present->sectorno].vertex[i + 1].x,
				engine->sectors[engine->present->sectorno].vertex[i].y,
				engine->sectors[engine->present->sectorno].vertex[i + 1].y,
				engine->wall.color};
		if (transform_wall(engine, &engine->wall))
		{
			choose_edit(engine, i);
			render_scene(engine, sectorno,    //текущий сектор
				engine->sectors[sectorno].neighbors[i], i);		//его сосед, границу с которым мы обрабатываем.
		}
		/*if (transform_sprite(engine))
			render_sprite(engine);*/
		if (engine->minimap.mod)
			minimap(engine, engine->sectors[sectorno].vertex[i],
			engine->sectors[sectorno].vertex[i + 1], color);
		else
			minimap_cut(engine, (t_xy){engine->wall.x0, engine->wall.y0},
				(t_xy){engine->wall.x1, engine->wall.y1}, engine->wall.color);
		i++;
	}
}
