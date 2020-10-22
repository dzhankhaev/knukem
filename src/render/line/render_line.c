/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_a_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeulah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 17:56:10 by abeulah           #+#    #+#             */
/*   Updated: 2020/02/25 18:11:12 by abeulah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static t_line	swap_coords(t_line p)
{
	int t;

	t = p.x0;
	p.x0 = p.x1;
	p.x1 = t;
	t = p.y0;
	p.y0 = p.y1;
	p.y1 = t;
	return (p);
}

static void		render_perpendicular_line(t_line p, SDL_Surface *screen, t_line borders)
{
	int	*temp;

	temp = (int *)screen->pixels;
	if (p.x0 == p.x1)
	{
		p = p.y0 > p.y1 ? swap_coords(p) : p;
		while (p.y0 < p.y1)
		{
			if (p.x0 >= borders.x0 && p.x0 < borders.x1
				&& p.y0 >= borders.y0 && p.y0 < borders.y1)
				temp[(p.y0 * W) + p.x0] = p.color;
			p.y0++;
		}
	}
	else
	{
		p = p.x0 > p.x1 ? swap_coords(p) : p;
		while (p.x0 < p.x1)
		{
			if (p.x0 >= borders.x0 && p.x0 < borders.x1
				&& p.y0 >= borders.y0 && p.y0 < borders.y1)
				temp[(p.y0 * W) + p.x0] = p.color;
			p.x0++;
		}
	}
}

void			render_line(t_line p, SDL_Surface *screen, t_line borders)
{
	if (p.x0 > p.x1)
		p = swap_coords(p);
	if (p.x0 == p.x1 || p.y0 == p.y1)
		render_perpendicular_line(p, screen, borders);
	else if (p.y0 < p.y1)
	{
		if (abs(p.x1 - p.x0) > abs(p.y1 - p.y0))
			angle_less_than_45_1(p, screen, borders);
		else
			angle_more_than_45_1(p, screen, borders);
	}
	else
	{
		if (abs(p.x1 - p.x0) > abs(p.y1 - p.y0))
			angle_less_than_45_2(swap_coords(p), screen, borders);
		else
			angle_more_than_45_2(p, screen, borders);
	}
}
