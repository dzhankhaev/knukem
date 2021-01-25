/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static t_fline	cut1(t_fline wall, t_xy i1)
{
	if (fabsf(wall.x0 - wall.x1) > fabsf(wall.y0 - wall.y1)
		&& wall.x0 > wall.x1)
	{
		wall.x1 = i1.x;
		wall.y1 = i1.y;
	}
	else
	{
		wall.x0 = i1.x;
		wall.y0 = i1.y;
	}
	return (wall);
}

static t_fline	cut2(t_fline wall, t_xy i2)
{
	if (fabsf(wall.x0 - wall.x1) < fabsf(wall.y0 - wall.y1)
		|| wall.x0 > wall.x1)
	{
		wall.x1 = i2.x;
		wall.y1 = i2.y;
	}
	else
	{
		wall.x0 = i2.x;
		wall.y0 = i2.y;
	}
	return (wall);
}

t_fline			cut_wall(t_fline wall, t_xy i1, t_xy i2)
{
	float	t;
	int		color;

	color = wall.color;
	if (wall.y0 > wall.y1)
	{
		t = wall.x0;
		wall.x0 = wall.x1;
		wall.x1 = t;
		t = wall.y0;
		wall.y0 = wall.y1;
		wall.y1 = t;
	}
	if (i1.x != -1)
		wall = cut1(wall, i1);
	if (i2.x != -1)
		wall = cut2(wall, i2);
	wall.color = color;
	return (wall);
}
