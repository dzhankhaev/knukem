/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeulah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 17:56:10 by abeulah           #+#    #+#             */
/*   Updated: 2020/02/25 18:11:12 by abeulah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void		swap_point(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

static void		render(t_line p, t_line borders, SDL_Surface *screen)
{
	Uint32	*temp;

	temp = (Uint32 *)screen->pixels;
	if (p.x0 >= borders.x0 && p.x0 < borders.x1
		&& p.y0 >= borders.y0 && p.y0 < borders.y1)
		temp[(p.y0 * W) + p.x0] = p.color;
}

static int		normi_line(t_line *p)
{
	int	steep;

	steep = 0;
	if (abs(p->x0 - p->x1) < abs(p->y0 - p->y1))
	{
		swap_point(&p->x0, &p->y0);
		swap_point(&p->x1, &p->y1);
		steep = 1;
	}
	if (p->x0 > p->x1)
	{
		swap_point(&p->x0, &p->x1);
		swap_point(&p->y0, &p->y1);
	}
	return (steep);
}

static t_delta	get_delta(t_line p)
{
	t_delta	d;

	d.dx = p.x1 - p.x0;
	d.dy = p.y1 - p.y0;
	d.derror = abs(d.dy) * 2;
	d.error = 0;
	return (d);
}

void			render_line(t_line p, SDL_Surface *screen, t_line borders)
{
	int		steep;
	t_delta	d;
	int		y;
	int		x;
	int		t;

	steep = normi_line(&p);
	d = get_delta(p);
	y = p.y0;
	x = p.x0 - 1;
	t = SDL_GetTicks();
	while (++x <= p.x1 && SDL_GetTicks() - t < 5)
	{
		if (steep)
			render((t_line){y, 0, x, 0, p.color}, borders, screen);
		else
			render((t_line){x, 0, y, 0, p.color}, borders, screen);
		d.error += d.derror;
		if (d.error > d.dx)
		{
			y += (p.y1 > p.y0 ? 1 : -1);
			d.error -= d.dx * 2;
		}
	}
}
