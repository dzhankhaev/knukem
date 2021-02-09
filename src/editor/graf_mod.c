/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graf_mod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/02/09 03:37:36 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

static void		graf_memalloc(t_engine *engine, int sectorno, int i)
{
	t_graf *graf;

	graf = &engine->sectors[sectorno].graf;
	graf->g_num++;
	graf->wall = (int *)ft_realloc(graf->wall, sizeof(int) * graf->g_num);
	graf->u = (int *)ft_realloc(graf->u, sizeof(int) * graf->g_num);
	graf->z = (float *)ft_realloc(graf->z, sizeof(float) * graf->g_num);
	graf->coord = (t_fline *)ft_realloc(graf->coord,
							sizeof(t_fline) * graf->g_num);
	graf->u[graf->g_num - 1] = 1;
	graf->wall[graf->g_num - 1] = i;
	graf->z[graf->g_num - 1] = engine->player.where.z;
	graf->coord[graf->g_num - 1] =
		(t_fline){engine->sectors[sectorno].vertex[i].x,
			engine->sectors[sectorno].vertex[i + 1].x,
			engine->sectors[sectorno].vertex[i].y,
			engine->sectors[sectorno].vertex[i + 1].y,
			engine->edit.txno == -1 ? 0 : engine->edit.txno};
}

static t_fline	get_coord(t_fline c)
{
	float	t;

	if (c.x0 < c.x1 && c.y0 > c.y1)
	{
		t = c.x0;
		c.x0 = c.x1;
		c.x1 = t;
		t = c.y0;
		c.y0 = c.y1;
		c.y1 = t;
	}
	else if (c.x0 > c.x1 && c.y0 > c.y1)
	{
		t = c.x0;
		c.x0 = c.x1;
		c.x1 = t;
		t = c.y0;
		c.y0 = c.y1;
		c.y1 = t;
	}
	return (c);
}

static void		create_coord(t_engine *engine, int sectorno)
{
	t_graf	*graf;
	float	angle;
	t_xy	a;
	t_xy	b;
	t_fline	c;

	graf = &engine->sectors[sectorno].graf;
	c = get_coord(graf->coord[graf->g_num - 1]);
	a = point_proection(c,
				(t_xyz){engine->player.where.x,
						engine->player.where.y, 0});
	angle = get_vec_angle(c.x1
				- c.x0,
				c.y1
				- c.y0, 1, 0);
	b.x = a.x + 1 * cosf(angle);
	b.y = a.y + 1 * sinf(angle);
	graf->coord[graf->g_num - 1] = (t_fline){a.x, b.x, a.y, b.y,
			graf->coord[graf->g_num - 1].color};
}

static void		delete_graf(t_engine *engine, int sectorno)
{
	if (engine->edit.graf == 3)
	{
		free(engine->sectors[sectorno].graf.coord);
		free(engine->sectors[sectorno].graf.z);
		free(engine->sectors[sectorno].graf.wall);
		free(engine->sectors[sectorno].graf.u);
		engine->sectors[sectorno].graf.coord = 0;
		engine->sectors[sectorno].graf.z = 0;
		engine->sectors[sectorno].graf.wall = 0;
		engine->sectors[sectorno].graf.u = 0;
		engine->sectors[sectorno].graf.g_num = 0;
		engine->edit.graf = 0;
	}
	else if (engine->edit.graf_wall > -1 && engine->sectors[sectorno].graf.g_num
			> 0 && engine->player.cur_inv < engine->player.settings.inventory &&
	engine->sectors[sectorno].graf.coord[engine->edit.graf_wall].color == 0
	&& engine->sectors[sectorno].graf.u[engine->edit.graf_wall] == 0)
	{
		delete_one_graf(engine, sectorno);
		engine->player.cur_inv++;
	}
}

void			graf_mod(t_engine *engine, int sectorno, int i)
{
	if (engine->edit.mod_w != -1 && engine->edit.graf == 2)
	{
		engine->edit.graf = 0;
		if (engine->sectors[sectorno].neighbors[i] <= -1)
		{
			if (engine->player.game_mode)
			{
				graf_memalloc(engine, sectorno, i);
				create_coord(engine, sectorno);
				engine->edit.txno = -1;
			}
			else if (!engine->player.game_mode && engine->player.cur_inv > 0)
			{
				graf_memalloc(engine, sectorno, i);
				create_coord(engine, sectorno);
				engine->player.cur_inv--;
				engine->edit.txno = -1;
			}
		}
	}
	delete_graf(engine, sectorno);
}
