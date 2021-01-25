/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_point.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

static t_xy		vertical1(t_fline wall, t_fline twall)
{
	float xa;
	float a2;
	float b2;
	float ya;

	xa = wall.x0;
	a2 = (twall.y0 - twall.y1) / (twall.x0 - twall.x1);
	b2 = twall.y0 - a2 * twall.x0;
	ya = a2 * xa + b2;
	if (twall.x0 <= xa && twall.x1 >= xa && fminf(wall.y0, wall.y1) <= ya &&
		fmaxf(wall.y0, wall.y1) >= ya)
	{
		return (t_xy){xa, ya};
	}
	return (t_xy){-1.f, -1.f};
}

static t_xy		vertical2(t_fline wall, t_fline twall)
{
	float xa;
	float a1;
	float b1;
	float ya;

	xa = twall.x0;
	a1 = (wall.y0 - wall.y1) / (wall.x0 - wall.x1);
	b1 = wall.y0 - a1 * wall.x0;
	ya = a1 * xa + b1;
	if (wall.x0 <= xa && wall.x1 >= xa && fminf(twall.y0, twall.y1) <= ya &&
		fmaxf(twall.y0, twall.y1) >= ya)
	{
		return (t_xy){xa, ya};
	}
	return (t_xy){-1.f, -1.f};
}

static t_xy		general(t_fline wall, t_fline twall)
{
	float a1;
	float a2;
	float b1;
	float b2;
	float xa;

	a1 = (wall.y0 - wall.y1) / (wall.x0 - wall.x1);
	a2 = (twall.y0 - twall.y1) / (twall.x0 - twall.x1);
	b1 = wall.y0 - a1 * wall.x0;
	b2 = twall.y0 - a2 * twall.x0;
	if (a1 == a2)
		return (t_xy){-1.f, -1.f};
	xa = (b2 - b1) / (a1 - a2);
	if ((xa < fmaxf(wall.x0, twall.x0)) || (xa > fminf(wall.x1, twall.x1)))
		return (t_xy){-1.f, -1.f};
	else
		return (t_xy){xa, a2 * xa + b2};
}

static t_fline	swap(t_fline wall)
{
	float	t;

	if (wall.x0 > wall.x1)
	{
		t = wall.x0;
		wall.x0 = wall.x1;
		wall.x1 = t;
		t = wall.y0;
		wall.y0 = wall.y1;
		wall.y1 = t;
	}
	return (wall);
}

t_xy			intersection_point(t_fline wall, t_fline twall)
{
	wall = swap(wall);
	twall = swap(twall);
	if (wall.x1 < twall.x0)
		return ((t_xy){-1.f, -1.f});
	if (wall.x0 == wall.x1)
		return (vertical1(wall, twall));
	else if (twall.x0 == twall.x1)
		return (vertical2(wall, twall));
	else
		return (general(wall, twall));
}
