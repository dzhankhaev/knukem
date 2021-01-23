/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil_and_floor_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

static void	get_vplanes(t_engine *engine)
{
	t_temp	*a;

	a = &engine->rend_wall;
	engine->vpceil.minx = a->x0;
	engine->vpceil.maxx = a->x1;
	engine->vpceil.topy[a->x] = engine->tline[a->x];
	engine->vpceil.boty[a->x] = a->y[0];
	engine->vpceil.z = engine->player.where.z -
			engine->sectors[engine->present->sectorno].ceil;
	engine->vpfloor.minx = a->x0;
	engine->vpfloor.maxx = a->x1;
	engine->vpfloor.topy[a->x] = a->y[1];
	engine->vpfloor.boty[a->x] = engine->bline[a->x];
	engine->vpfloor.z = engine->player.where.z -
			engine->sectors[engine->present->sectorno].floor;
	engine->vpfloor.s = engine->present->sectorno;
}

void		ceil_and_floor_init(t_engine *engine)
{
	t_temp	*a;

	a = &engine->rend_wall;
	a->oy[0] = y_for_x(a->wall[0], a->x);
	a->oy[1] = y_for_x(a->wall[1], a->x);
	a->y[0] = iclamp(a->oy[0], engine->tline[a->x], engine->bline[a->x]);
	a->y[1] = iclamp(a->oy[1], engine->tline[a->x], engine->bline[a->x]);
	a->oy[2] = y_for_x(a->wall[2], a->x);
	a->oy[3] = y_for_x(a->wall[3], a->x);
	a->y[2] = iclamp(a->oy[2], engine->tline[a->x], engine->bline[a->x]);
	a->y[3] = iclamp(a->oy[3], engine->tline[a->x], engine->bline[a->x]);
	get_vplanes(engine);
}
