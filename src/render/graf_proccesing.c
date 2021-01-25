/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graf_proccesing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

static void	loop_graf(t_engine *engine, t_line w0, t_line w1, int x)
{
	int		y0;
	int		y1;
	int		oy0;
	int		oy1;
	t_temp	*a;

	a = &engine->rend_wall;
	a->x = x;
	a->txx = (engine->u0 * ((a->w.x1 - a->x) * a->l.x1)
			+ engine->u1 * ((a->x - a->w.x0) * a->l.x0))
			/ ((a->w.x1 - a->x) * a->l.x1 + (a->x - a->w.x0) * a->l.x0);
	y1 = y_for_x(w0, x);
	y0 = y_for_x(w1, x);
	oy0 = y0;
	oy1 = y1;
	y0 = iclamp(y0, engine->tline[x], engine->bline[x]);
	y1 = iclamp(y1, engine->tline[x], engine->bline[x]);
	y0 = iclamp(y0, engine->vpceil.boty[x], engine->vpfloor.topy[x]);
	y1 = iclamp(y1, engine->vpceil.boty[x], engine->vpfloor.topy[x]);
	if (y1 - y0 >= 3)
		render_vline(engine, (t_line){a->x, a->x, y0, y1,
					engine->wall.color},
					(t_line){0, 0, oy0, oy1, 0}, w0.color);
}

static void	render_graf(t_engine *engine, t_graf *graf, t_fline *w, int t)
{
	float	z;
	t_line	w0;
	t_line	w1;
	t_xy	x;

	z = engine->player.where.z;
	w0 = perspective_transform(*w, z - graf->z[t] + 1,
		engine->player.vangle, w->color);
	w1 = perspective_transform(*w, z - graf->z[t] - 1,
		engine->player.vangle, FLOOR_COLOR);
	x.x = (float)imax(imin(w0.x0, w0.x1), engine->present->x0);
	x.y = (float)imin(imax(w1.x0, w1.x1), engine->present->x1);
	engine->rend_wall.w = w0;
	if (w0.x0 > w0.x1)
	{
		w0 = swap_coords(w0);
		w1 = swap_coords(w1);
	}
	engine->rend_wall.x0 = (int)x.x;
	engine->rend_wall.l = *w;
	while (x.x < x.y)
	{
		loop_graf(engine, w0, w1, (int)x.x);
		x.x++;
	}
}

void		graf_proccesing(t_engine *engine, int sectorno, int i)
{
	t_graf	*graf;
	t_fline	w;
	int		t;

	graf = &engine->sectors[sectorno].graf;
	t = -1;
	while (++t < graf->g_num)
	{
		if (graf->wall[t] == i)
		{
			w = graf->coord[t];
			if (transform_wall(engine, &w))
			{
				if ((engine->edit.door == 2 || engine->edit.graf_wall == -2) &&
					determine_intersection(w, (t_fline){0, 3, 0, 0, 0}))
				{
					engine->edit.door = engine->edit.door == 2 ? 4
							: engine->edit.door;
					engine->edit.graf_wall = engine->edit.graf_wall == -2 ? t
							: -1;
				}
				render_graf(engine, graf, &w, t);
			}
		}
	}
}
