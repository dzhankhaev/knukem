/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:31:50 by sisidra           #+#    #+#             */
/*   Updated: 2020/11/27 13:31:54 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_xy	get_coords(t_all *all)
{
	t_xy	xy;

	xy.x = all->point.x - all->d.x - (all->area.w / \
		(2 * all->step) - round(all->mapsize.x / 2));
	xy.y = all->point.y - all->d.y - (all->area.h / \
		(2 * all->step) - round(all->mapsize.y / 2));
	return (xy);
}

void	draw_sector(t_sect *sect, t_all *all, SDL_Color color, t_xy delta)
{
	unsigned int	i;
	t_xy			s;
	t_xy			f;
	SDL_Color		col;

	col = color;
	i = 0;
	while (i < sect->npoints)
	{
		s = (t_xy){(sect->vertex[i].x * all->step) + delta.x, \
				(sect->vertex[i].y * all->step) + delta.y};
		f = (t_xy){(sect->vertex[i + 1].x * all->step) + delta.x, \
				(sect->vertex[i + 1].y * all->step) + delta.y};
		if (sect->door < 0)
			col = (sect->neighbors[i] < 0 && i < sect->npoints) ? color : BLUE;
		if (sect->oldf >= all->draw_floors.x && \
			sect->oldf <= all->draw_floors.y)
		{
			draw_line(all, &s, &f, \
				&all->sectors[all->swap_num] == sect ? YELLOW : col);
			draw_circle(&all->sdl, s, 2, GREEN);
		}
		i++;
	}
}
