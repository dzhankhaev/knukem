/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

static int	check_inter(t_engine *engine, int s, float *dx, float *dy)
{
	float	px;
	float	py;
	t_xy	*vert;

	px = engine->player.where.x;
	py = engine->player.where.y;
	vert = engine->sectors[engine->player.sector].vertex;
	if (determine_intersection((t_fline){px, px + *dx, py, py + *dy},
			(t_fline){vert[s].x, vert[s + 1].x, vert[s].y, vert[s + 1].y}) &&
		point_side(px + *dx, py + *dy, vert[s], vert[s + 1]) < 0)
		return (1);
	return (0);
}

static int	check_inter2(t_engine *engine, float *dx, float *dy, int old)
{
	t_sect		*sect;
	t_player	*player;
	int			s;

	player = &engine->player;
	sect = &engine->sectors[player->sector];
	s = 0;
	while (s < sect->npoints)
	{
		if (point_side(player->where.x + *dx, player->where.y + *dy,
	sect->vertex[s], sect->vertex[s + 1]) < 0
	&& engine->player.sector == old)
		{
			*dx = 0;
			*dy = 0;
			return (1);
		}
		s++;
	}
	return (0);
}

static void	step(t_engine *engine, int s, float *dx, float *dy)
{
	t_sect		*sect;
	t_player	*player;

	player = &engine->player;
	sect = &engine->sectors[player->sector];
	if (sect->neighbors[s] >= 0)
	{
		if (player->where.z + HEAD_HEIGHT >
	engine->sectors[sect->neighbors[s]].ceil || player->where.z -
	player->eyeheight + KNEE_HEIGHT < engine->sectors[sect->neighbors[s]].floor
	|| player->where.z + HEAD_HEIGHT + engine->sectors[sect->neighbors[s]].floor
	> engine->sectors[sect->neighbors[s]].ceil)
			vec_proect(sect->vertex[s], sect->vertex[s + 1], dx, dy);
		else
		{
			player->sector = sect->neighbors[s];
			if (player->ground)
			{
				player->falling = 1;
				player->ground = 0;
				player->velocity.z -= VSPEED;
			}
		}
	}
	else if (sect->neighbors[s] <= -1)
		vec_proect(sect->vertex[s], sect->vertex[s + 1], dx, dy);
}

static void	move_player(float *dx, float *dy, t_engine *engine)
{
	int		s;
	int		old;

	old = engine->player.sector;
	s = 0;
	while (s < engine->sectors[engine->player.sector].npoints)
	{
		// Проверяет произошло ли пересечение стороны сектора
		if (check_inter(engine, s, dx, dy))
		{
			step(engine, s, dx, dy);
			break ;
		}
		s++;
	}
	if (check_inter2(engine, dx, dy, old))
		return ;
	engine->player.where.x += *dx;
	engine->player.where.y += *dy;
}

void		move(t_engine *engine)
{
	fall(&engine->player, engine->sectors);
	move_player(&engine->player.velocity.x, &engine->player.velocity.y, engine);
}


