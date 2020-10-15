/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_line_with_angle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeulah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 13:44:11 by abeulah           #+#    #+#             */
/*   Updated: 2020/02/25 14:10:29 by abeulah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	angle_less_than_45_1(t_line p, SDL_Surface *screen, t_line borders)
{
	int		*temp;
	t_delta	d;

	temp = (int *)screen->pixels;
	d.dx = abs(p.x1 - p.x0);
	d.dy = abs(p.y1 - p.y0);
	d.error = 0;
	d.derror = d.dy + 1;
	while (p.x0 < p.x1)
	{
		if (p.x0 >= borders.x0 && p.x0 < borders.x1
		&& p.y0 >= borders.y0 && p.y0 < borders.y1)
			temp[(p.y0 * W) + p.x0] = p.color;
		d.error += d.derror;
		if (d.error >= d.dx + 1)
		{
			p.y0++;
			d.error -= d.dx + 1;
		}
		p.x0++;
	}
}

void	angle_more_than_45_1(t_line p, SDL_Surface *screen, t_line borders)
{
	int 	*temp;
	t_delta	d;

	temp = (int *)screen->pixels;
	d.dx = abs(p.x1 - p.x0);
	d.dy = abs(p.y1 - p.y0);
	d.error = 0;
	d.derror = d.dx + 1;
	while (p.y0 < p.y1)
	{
		if (p.x0 >= borders.x0 && p.x0 < borders.x1
		&& p.y0 >= borders.y0 && p.y0 < borders.y1)
			temp[(p.y0 * W) + p.x0] = p.color;
		d.error += d.derror;
		if (d.error >= d.dy + 1)
		{
			p.x0++;
			d.error -= d.dy + 1;
		}
		p.y0++;
	}
}

void	angle_less_than_45_2(t_line p, SDL_Surface *screen, t_line borders)
{
	int		*temp;
	t_delta	d;

	temp = (int *)screen->pixels;
	d.dx = abs(p.x1 - p.x0);
	d.dy = abs(p.y1 - p.y0);
	d.error = 0;
	d.derror = d.dy + 1;
	while (p.x0 > p.x1)
	{
		if (p.x0 >= borders.x0 && p.x0 < borders.x1
		&& p.y0 >= borders.y0 && p.y0 < borders.y1)
			temp[(p.y0 * W) + p.x0] = p.color;
		d.error += d.derror;
		if (d.error >= d.dx + 1)
		{
			p.y0++;
			d.error -= d.dx + 1;
		}
		p.x0--;
	}
}

void	angle_more_than_45_2(t_line p, SDL_Surface *screen, t_line borders)
{
	int		*temp;
	t_delta	d;

	temp = (int *)screen->pixels;
	d.dx = abs(p.x1 - p.x0);
	d.dy = abs(p.y1 - p.y0);
	d.error = 0;
	d.derror = d.dx + 1;
	while (p.y0 > p.y1)
	{
		if (p.x0 >= borders.x0 && p.x0 < borders.x1
		&& p.y0 >= borders.y0 && p.y0 < borders.y1)
			temp[(p.y0 * W) + p.x0] = p.color;
		d.error += d.derror;
		if (d.error >= d.dy + 1)
		{
			p.x0++;
			d.error -= d.dy + 1;
		}
		p.y0--;
	}
}
