/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_door_anim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	put_anim(t_engine *engine, int door)
{
	int	q;

	if (check_door_anim(engine, door))
		return ;
	q = 0;
	while (q < 30)
	{
		if (engine->danimbuf[q] == -1)
		{
			engine->danimbuf[q] = door;
			if (engine->sectors[door].floor < engine->sectors[door].ceil)
				engine->danimbuf[q + 1] = 0;
			else if (engine->sectors[door].floor > engine->sectors[door].oldf)
				engine->danimbuf[q + 1] = 1;
			else
				engine->danimbuf[q] = -1;
			if (!engine->player.game_mode && engine->player.cur_am &&
			engine->edit.door != 4)
				engine->player.cur_am--;
			engine->player.shot = 1;
			break ;
		}
		q += 2;
	}
}

static int	match2(t_engine *engine, int sec, int wall)
{
	int	t;

	t = 0;
	while (t < engine->sectors[sec].graf.g_num)
	{
		if (engine->sectors[sec].graf.wall[t] == wall)
			return (1);
		t++;
	}
	return (0);
}

static int	match(t_engine *engine, int sec, int dsec, unsigned int k)
{
	int wall;

	if (engine->sectors[sec].neighbors[k] == dsec)
	{
		if (k == 0)
			wall = engine->sectors[sec].npoints - 1;
		else
			wall = k - 1;
		if (match2(engine, sec, wall))
			return (1);
		if (k == engine->sectors[sec].npoints - 1)
			wall = 0;
		else
			wall = k + 1;
		if (match2(engine, sec, wall))
			return (1);
	}
	return (0);
}

static int	check_graf_control(t_engine *engine, int dsec)
{
	unsigned int	q;
	unsigned int	k;
	int				sec;

	q = 0;
	while (q < engine->sectors[dsec].npoints)
	{
		sec = engine->sectors[dsec].neighbors[q];
		if (sec > -1)
		{
			k = 0;
			while (k < engine->sectors[sec].npoints)
			{
				if (match(engine, sec, dsec, k))
					return (0);
				k++;
			}
		}
		q++;
	}
	return (1);
}

void		start_door_anim(t_engine *engine, int sec, int nei, unsigned int i)
{
	int door;

	if (engine->edit.mod_w == (int)i && nei > -1 && nei == engine->edit.mod_s &&
			engine->edit.door == 2 && engine->sectors[nei].door > -1
			&& check_graf_control(engine, nei)
			&& (engine->player.game_mode || engine->player.cur_am))
		put_anim(engine, nei);
	if (engine->edit.door == 4)
	{
		if (i == 0)
			door = engine->sectors[sec].neighbors[engine->sectors[sec].npoints
						- 1];
		else
			door = engine->sectors[sec].neighbors[i - 1];
		if (door > -1 && engine->sectors[door].door > -1)
			put_anim(engine, door);
		if (i == engine->sectors[sec].npoints - 1)
			door = engine->sectors[sec].neighbors[0];
		else
			door = engine->sectors[sec].neighbors[i + 1];
		if (door > -1 && engine->sectors[door].door > -1)
			put_anim(engine, door);
		engine->edit.door = 0;
	}
}
