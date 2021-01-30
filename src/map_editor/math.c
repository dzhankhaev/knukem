/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:32:47 by sisidra           #+#    #+#             */
/*   Updated: 2020/11/27 13:32:49 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

float	vector_cross_product1(float x0, float y0, float x1, float y1)
{
	return ((x0) * (y1) - (x1) * (y0));
}

float	point_side1(float px, float py, t_xy vert, t_xy vert1)
{
	return (vector_cross_product1(vert1.x - vert.x, vert1.y - vert.y,
								px - vert.x, py - vert.y));
}

int		is_vector_equal(t_xy a0, t_xy a1, t_xy b0, t_xy b1)
{
	if ((a0.x == b0.x && a0.y == b0.y) || (a0.x == b1.x && a0.y == b1.y))
		if ((a1.x == b0.x && a1.y == b0.y) || (a1.x == b1.x && a1.y == b1.y))
			return (1);
	return (0);
}

void	closest_point(t_all *all, t_xyint point)
{
	t_xy	c;

	c = (t_xy){(all->area.w / 2) % all->step, (all->area.h / 2) % all->step};
	if (all->player.picked)
	{
		all->point.x = ((float)point.x - all->area.x - c.x) / all->step;
		all->point.y = ((float)point.y - all->area.y - c.y) / all->step;
	}
	else
	{
		all->point.x = round(((float)point.x - all->area.x - c.x) / all->step);
		all->point.y = round(((float)point.y - all->area.y - c.y) / all->step);
	}
}
