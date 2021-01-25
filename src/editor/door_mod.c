/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_mod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int	check_nei(t_engine *engine, int neighbor)
{
	unsigned int	q;
	int				s;

	q = 0;
	while (q < engine->sectors[neighbor].npoints)
	{
		s = engine->sectors[neighbor].neighbors[q];
		if (s > -1)
			if (engine->sectors[s].door != -1)
				return (0);
		q++;
	}
	return (1);
}

void		door_mod(t_engine *engine, int neighbor, int i)
{
	int q;

	if (engine->edit.mod_w == i && neighbor > -1
		&& neighbor == engine->edit.mod_s && engine->edit.door == 1)
	{
		q = -2;
		while (q < 30)
			if (engine->danimbuf[(q += 2)] == neighbor)
				return ;
		if (engine->sectors[neighbor].door == -1 && check_nei(engine, neighbor))
			engine->sectors[neighbor].door = 0;
		else
		{
			engine->sectors[neighbor].door = -1;
			engine->sectors[neighbor].floor = engine->sectors[neighbor].oldf;
		}
	}
}
