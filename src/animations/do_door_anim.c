/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_door_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

static void	anim0(t_engine *engine, int anim, int dsec, int i)
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

void		door_anim(t_engine *engine)
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
