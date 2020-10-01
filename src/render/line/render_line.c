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

static void		from_left_top_to_right_down(t_line p, SDL_Surface *screen)
{
	if (abs(p.x1 - p.x0) > abs(p.y1 - p.y0))
		angle_less_than_45_1(p, screen);
	else
		angle_more_than_45_1(p, screen);
}

static void		from_right_top_to_left_down(t_line p, SDL_Surface *screen)
{
	if (abs(p.x1 - p.x0) > abs(p.y1 - p.y0))
		angle_less_than_45_2(p, screen);
	else
		angle_more_than_45_2(swap_coords(p), screen);
}

static void		render_perpendicular_line(t_line p, SDL_Surface *screen)
{
	int	*temp;

	temp = (int *)screen->pixels;
	if (p.x0 == p.x1)
	{
		p = p.y0 > p.y1 ? swap_coords(p) : p;
		while (p.y0 < p.y1 && p.x0 >= 0 && p.x0 < W && p.y0 >= 0 && p.y0 < H)
		{
			temp[(p.y0 * W) + p.x0] = p.color;
			p.y0++;
		}
	}
	else
	{
		p = p.x0 > p.x1 ? swap_coords(p) : p;
		while (p.x0 < p.x1 && p.x0 >= 0 && p.x0 < W && p.y0 >= 0 && p.y0 < H)
		{
			temp[(p.y0 * W) + p.x0] = p.color;
			p.x0++;
		}
	}
}

void			render_line(t_line p, SDL_Surface *screen)
{
	if (p.x0 == p.x1 || p.y0 == p.y1)
		render_perpendicular_line(p, screen);
	else if (p.x0 < p.x1 && p.y0 < p.y1)
		from_left_top_to_right_down(p, screen);
	else if (p.x0 > p.x1 && p.y0 > p.y1)
		from_left_top_to_right_down(swap_coords(p), screen);
	else if (p.x0 > p.x1 && p.y0 < p.y1)
		from_right_top_to_left_down(p, screen);
	else if (p.x0 < p.x1 && p.y0 > p.y1)
		from_right_top_to_left_down(swap_coords(p), screen);
}
