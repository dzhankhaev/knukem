/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

static t_fline	fov_wall_cut(t_fline wall)
{
	t_xy	i1;
	t_xy	i2;

	i1 = intersection_point(wall,
					(t_fline){0, RAY_POINT_X, 0, -RAY_POINT_Y, 0});
	i2 = intersection_point(wall,
					(t_fline){0, RAY_POINT_X, 0, RAY_POINT_Y, 0});
	return (cut_wall(wall, i1, i2));
}

void			tex_init(t_engine *engine, t_fline w, t_fline ow)
{
	if (fabsf(w.y1 - w.y0) > fabsf(w.x1 - w.x0))
	{
		engine->u0 = (w.y0 - ow.y0) * engine->img[w.color].tx->w
				/ (ow.y1 - ow.y0);
		engine->u1 = (w.y1 - ow.y0) * engine->img[w.color].tx->w
				/ (ow.y1 - ow.y0);
	}
	else
	{
		engine->u0 = (w.x0 - ow.x0) * engine->img[w.color].tx->w
				/ (ow.x1 - ow.x0);
		engine->u1 = (w.x1 - ow.x0) * engine->img[w.color].tx->w
				/ (ow.x1 - ow.x0);
	}
}

int				transform_wall(t_engine *engine, t_fline *wall)
{
	t_fline	ow;

	*wall = rotate_wall(*wall, engine->player);
	if (wall->x0 <= 0 && wall->x1 <= 0)
		return (0);
	ow = *wall;
	*wall = fov_wall_cut(*wall);
	tex_init(engine, *wall, ow);
	if (wall->x0 <= 0 || wall->x1 <= 0
		|| wall->x0 * -K > wall->y0
		|| wall->x1 * K < wall->y1)
		return (0);
	return (1);
}
