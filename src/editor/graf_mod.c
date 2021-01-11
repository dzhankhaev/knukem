/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graf_mod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

static void		graf_memalloc(t_engine *engine, int sectorno, int i)
{
	t_graf *graf;

	graf = &engine->graf[sectorno];
	graf->g_num++;
	//выделяем память
	graf->wall = (int *)ft_realloc(graf->wall, sizeof(int) * graf->g_num);
	graf->z = (float *)ft_realloc(graf->z, sizeof(float) * graf->g_num);
	graf->coord = (t_fline *)ft_realloc(graf->coord,
							sizeof(t_fline) * graf->g_num);
	//заносим необходимые данные
	graf->wall[graf->g_num - 1] = i;
	graf->z[graf->g_num - 1] = engine->player.where.z;
	graf->coord[graf->g_num - 1] =
		(t_fline){engine->sectors[sectorno].vertex[i].x,
			engine->sectors[sectorno].vertex[i + 1].x,
			engine->sectors[sectorno].vertex[i].y,
			engine->sectors[sectorno].vertex[i + 1].y,
			engine->edit.txno == -1 ? 1 : engine->edit.txno};
}

static t_fline get_coord(t_fline c)
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

	graf = &engine->graf[sectorno];
	c = get_coord(graf->coord[graf->g_num - 1]);
	//проекция
	a = point_proection(c,
				(t_xyz){engine->player.where.x,
						engine->player.where.y, 0});
	angle = get_vec_angle(c.x1
				- c.x0,
				c.y1
				- c.y0, 1, 0);
	//прокладывание отрезка вдоль стены
	b.x = a.x + 1 * cosf(angle);
	b.y = a.y + 1 * sinf(angle);
	graf->coord[graf->g_num - 1] = (t_fline){a.x, b.x, a.y, b.y,
			graf->coord[graf->g_num - 1].color};
}

void			graf_mod(t_engine *engine, int sectorno, int i)
{
	//если стена модифицируема и включен режим редактора граффити
	if (engine->edit.mod_w != -1 && engine->edit.graf == 2)
	{
		engine->edit.graf = 0;
		if (engine->sectors[sectorno].neighbors[i] <= -1)
		{
			graf_memalloc(engine, sectorno, i);
			create_coord(engine, sectorno);
		}
	}
	//если подана команда на удаление граффити
	if (engine->edit.graf == 3)
	{
		free(engine->graf[sectorno].coord);
		free(engine->graf[sectorno].z);
		free(engine->graf[sectorno].wall);
		engine->graf[sectorno].coord = 0;
		engine->graf[sectorno].z = 0;
		engine->graf[sectorno].wall = 0;
		engine->graf[sectorno].g_num = 0;
		engine->edit.graf = 0;
	}
}
