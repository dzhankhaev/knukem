/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilits.h"

float	vector_cross_product(float x0, float y0, float x1, float y1)
{
	return ((x0) * (y1) - (x1) * (y0));
}

float	point_side(float px, float py, t_xy vert, t_xy vert1)
{
	return (vector_cross_product(vert1.x - vert.x, vert1.y - vert.y,
							px - vert.x, py - vert.y));
}

int		y_for_x(t_line wall, int x)
{
	int		y;

	y = (wall.x1 - wall.x0);
	if (y == 0)
		y = 1;
	y = (x - wall.x0) * (wall.y1 - wall.y0) / y + wall.y0;
	return (y);
}

t_xy	point_proection(t_fline wall, t_xyz p)
{
	float	det_k;
	float	b1;
	float	b2;
	t_xy	a;

	b1 = p.x * (wall.x0 - wall.x1) + p.y * (wall.y0 - wall.y1);
	b2 = wall.x0 * wall.y1 - wall.y0 * wall.x1;
	a.y = (wall.x0 - wall.x1) * (wall.x0 - wall.x1) + (wall.y0 - wall.y1)
								* (wall.y0 - wall.y1);
	det_k = b1 * (wall.x0 - wall.x1) - b2 * (wall.y0 - wall.y1);
	a.x = det_k / a.y;
	det_k = (wall.x0 - wall.x1) * b2 + (wall.y0 - wall.y1) * b1;
	a.y = det_k / a.y;
	return (a);
}

float	get_vec_angle(float x1, float y1, float x2, float y2)
{
	float t;

	t = (x1 * x2 + y1 * y2) / (sqrtf(x1 * x1 + y1 * y1)
					* sqrtf(x2 * x2 + y2 * y2));
	if (t < -1)
		t = -1;
	else if (t > 1)
		t = 1;
	return (acosf(t));
}
