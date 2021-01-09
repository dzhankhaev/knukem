/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

void		anim0(t_engine *engine, int anim, int dsec, int i)
{
	if (anim == 0)
	{
		engine->sectors[dsec].door += 1;
		if (engine->player.sector == dsec)
			engine->sectors[dsec].door -= 1;
		engine->sectors[dsec].floor = engine->sectors[dsec].oldf
				+ engine->sectors[dsec].door;
		if (engine->sectors[dsec].floor >= engine->sectors[dsec].ceil)
			anim_delete(engine, i);
	}
	if (anim == 1)
	{
		engine->sectors[dsec].door -= 1;
		if (engine->player.sector == dsec)
			engine->sectors[dsec].door += 1;
		engine->sectors[dsec].floor = engine->sectors[dsec].oldf
				+ engine->sectors[dsec].door;
		if (engine->sectors[dsec].floor <= engine->sectors[dsec].oldf)
			anim_delete(engine, i);

	}
}

void 		door_anim(t_engine *engine)
{
	int i;
	int dsec;
	int anim;

	i = 0;
	while (i < 30)
	{
		if (engine->danimbuf[i] != -1)
		{
			dsec = engine->danimbuf[i];
			anim = engine->danimbuf[i + 1];
			if (engine->sectors[dsec].door != -1)
				anim0(engine, anim, dsec, i);
		}
		i += 2;
	}
}

void 		put_anim(t_engine *engine, int door)
{
	int	q;

	q = -2;
	while (q < 30)
		if (engine->danimbuf[(q += 2)] == door)
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
			break ;
		}
		q += 2;
	}
}

int 		gr(t_engine *engine, int dsec)
{
	int	q;
	int	k;
	int	sec;
	int nsec;

	q = 0;
	//проходим по стенам двери
	while (q < engine->sectors[dsec].npoints)
	{
		//смотрим в соседний сектор
		sec = engine->sectors[dsec].neighbors[q];
		if (sec > -1)
		{
			k = 0;
			//проходим по стенам соседа
			while (k < engine->sectors[sec].npoints)
			{
				nsec = engine->sectors[sec].neighbors[k];
				//для двери находим соответствующую грань соседа
				if (nsec == dsec)
				{
					int	t;
					int wall;
					//стена слева
					if (k == 0)
						wall = engine->sectors[sec].npoints - 1;
					else
						wall = k - 1;
					t = 0;
					//есть ли граффити на прилегающей стене
					while (t < engine->graf[sec].g_num)
					{
						if (engine->graf[sec].wall[t] == wall)
						{
							return (0);
						}
						t++;
					}

					//стена справа
					if (k == engine->sectors[sec].npoints - 1)
						wall = 0;
					else
						wall = k + 1;
					t = 0;
					//есть ли граффити на прилегающей стене
					while (t < engine->graf[sec].g_num)
					{
						if (engine->graf[sec].wall[t] == wall)
						{
							return (0);
						}
						t++;
					}
				}
				k++;
			}
		}

		q++;
	}
	return (1);
}

void		start_danim(t_engine *engine, int sec, int nei, int i)
{
	int door;
	//если игрок смотрит на дверь
	if (engine->edit.mod_w == i && nei > -1 && nei == engine->edit.mod_s &&
		engine->edit.door == 2 && engine->sectors[nei].door > -1 && gr(engine, nei))
		put_anim(engine, nei);
	//если игрок смотрит на граффити
	if (engine->edit.door == 4)
	{
		engine->edit.door = 0;
		//стена слева
		if (i == 0)
			door = engine->sectors[sec].neighbors[engine->sectors[sec].npoints
										 								- 1];
		else
			door = engine->sectors[sec].neighbors[i - 1];
		if (door > -1 && engine->sectors[door].door > -1)
			put_anim(engine, door);
		//стена справа
		if (i == engine->sectors[sec].npoints - 1)
			door = engine->sectors[sec].neighbors[0];
		else
			door = engine->sectors[sec].neighbors[i + 1];
		if (door > -1 && engine->sectors[door].door > -1)
			put_anim(engine, door);
	}
}