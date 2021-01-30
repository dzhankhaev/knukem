/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilits.h"
#include "engine.h"

static void		rendering_init(t_engine *engine, int sectorno, int neighbor)
{
	t_temp		*a;

	a = &engine->rend_wall;
	init_ceil_floor(engine, engine->sectors[sectorno], a->wall);
	a->x0 = imax(imin(a->wall[0].x0, a->wall[0].x1), engine->present->x0);
	a->x1 = imin(imax(a->wall[1].x0, a->wall[1].x1), engine->present->x1);
	if (neighbor >= 0)
	{
		if ((a->x1 > a->x0) && engine->future + 1 != engine->queue +
		engine->max_queue && check_repeat(engine, sectorno, neighbor))
			*(engine->future++) = (t_queue){neighbor, a->x0, a->x1, sectorno};
		init_wall(engine, engine->sectors[neighbor], a->wall);
	}
}

static void		ifdoor(t_engine *engine, int sectorno, int neighbor)
{
	t_temp	*a;

	a = &engine->rend_wall;
	if (neighbor > -1)
	{
		if (engine->sectors[neighbor].door > -1)
			a->wall[5] = perspective_transform(engine->wall,
				engine->player.where.z - engine->sectors[neighbor].oldf +
				engine->sectors[neighbor].ceil - engine->sectors[neighbor].door,
				engine->player.vangle, FLOOR_COLOR);
	}
	if (engine->sectors[sectorno].door > -1)
	{
		a->wall[4] = perspective_transform(engine->wall,
				engine->player.where.z - engine->sectors[sectorno].oldf,
				engine->player.vangle, FLOOR_COLOR);
	}
}

static void		loop(t_engine *engine, int neighbor, t_ixyz t)
{
	t_temp	*a;

	a = &engine->rend_wall;
	ifdoor(engine, engine->present->sectorno, neighbor);
	a->w = a->wall[0];
	to_x_order(a->wall);
	a->l = engine->wall;
	a->x = a->x0;
	while (a->x < a->x1)
	{
		a->txx = (engine->u0 * ((a->w.x1 - a->x) * a->l.x1)
				+ engine->u1 * ((a->x - a->w.x0) * a->l.x0))
				/ ((a->w.x1 - a->x) * a->l.x1 + (a->x - a->w.x0) * a->l.x0);
		ceil_and_floor_init(engine);
		if (engine->sectors[neighbor].floor >= engine->player.where.z)
			engine->vpfloor.boty[a->x] -= 1;
		if (neighbor > -1)
			if (engine->sectors[neighbor].door > -1)
				a->oy[1] = y_for_x(a->wall[5], a->x);
		if (engine->sectors[engine->present->sectorno].door > -1)
			a->oy[1] = y_for_x(a->wall[4], a->x);
		render_wall(engine, neighbor, t);
		a->x += 1;
	}
}

void			render_scene(t_engine *engine,
					int sectorno, int neighbor, int i)
{
	t_ixyz txset;

	door_mod(engine, neighbor, i);
	rendering_init(engine, sectorno, neighbor);
	txset = tx_wall_mod(engine, sectorno, i);
	loop(engine, neighbor, txset);
	txset = tx_plane_mod(engine, sectorno);
	render_hplane(engine, &engine->vpfloor, txset.x);
	render_hplane(engine, &engine->vpceil, txset.y);
	graf_proccesing(engine, sectorno, i);
	start_door_anim(engine, sectorno, neighbor, i);
	graf_mod(engine, sectorno, i);
	engine->hud_inp.buttons = engine->player.cur_inv;
	engine->hud_inp.ammo = engine->player.cur_am;
	if (engine->player.shot)
		engine->hud_inp.fire = engine->player.shot;
	engine->edit.mod_w = -1;
	render_line((t_line){0, W - 1, 0, 0, 0},
			engine->screen, engine->borders);
	render_line((t_line){0, W - 1, H - 1, H - 1, 0},
			engine->screen, engine->borders);
	render_cross(engine);
}
