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

void	draw_sector(t_sect *sect, t_all *all, SDL_Color color, t_xy delta)
{
	unsigned int	i;
	t_xy			s;
	t_xy			f;

	i = 0;
	while (i < sect->npoints)
	{
		s = (t_xy){(sect->vertex[i].x * all->step) + delta.x, \
				(sect->vertex[i].y * all->step) + delta.y};
		f = (t_xy){(sect->vertex[i + 1].x * all->step) + delta.x, \
				(sect->vertex[i + 1].y * all->step) + delta.y};
		if (sect->door < 0)
			color = (sect->neighbors[i] < 0 && i < sect->npoints) ? RED : BLUE;
		if (sect->oldf >= all->draw_floors.x && \
			sect->oldf <= all->draw_floors.y)
		{
			draw_line(all, &s, &f, \
				&all->sectors[all->swap_num] == sect ? YELLOW : color);
			draw_circle(all->sdl, s, 2, GREEN);
		}
		i++;
	}
}

void	draw_doors(t_all *all, t_sect *sectors)
{
	int i;
	t_sect	*temp;

	i = 0;
	while (i < all->num_sectors)
	{
		temp = &sectors[i];
		if (temp->door == 0)
			draw_sector(temp, all, GREEN, all->delta);
		else if (temp->door > 0)
			draw_sector(temp, all, LAZUR, all->delta);
		i++;
	}
}

void	draw_player(t_all *all, t_sdl *sdl, t_player *player, t_xy *c)
{
	SDL_Rect loc;
	
	loc = (SDL_Rect){0,0,0,0};
	if (all->player.picked == 0 && all->player.sector != -1)
		loc = (SDL_Rect){(player->where.x * all->step) + all->delta.x - all->step/2,
		 (player->where.y * all->step) + all->delta.y - all->step/2,
	 		 all->step, all->step};
	else if (all->player.picked == 1)
		loc = (SDL_Rect){all->point.x * all->step + c->x - all->step/2 + all->area.x,
			 all->point.y * all->step + c->y - all->step/2 + all->area.y, all->step, all->step};
	draw_texture(sdl->screen, loc, player->picture);
}

void	draw_map(t_sect *sect, t_all *all)
{
	int		i;
	t_sect	*temp;

	i = 0;
	while (i < all->num_sectors)
	{
		temp = &sect[i];
		if (temp->door < 0)
			draw_sector(temp, all, all->color, all->delta);
		i++;
	}
	draw_doors(all, all->sectors);
	if (all->swap_num != -1)
		draw_sector(&sect[all->swap_num], all, YELLOW, all->delta);
}

t_xy	get_coords(t_all *all)
{
	t_xy	xy;

	xy.x = all->point.x - all->d.x - (all->area.w / \
		(2 * all->step) - round(all->mapsize.x / 2));
	xy.y = all->point.y - all->d.y - (all->area.h / \
		(2 * all->step) - round(all->mapsize.y / 2));
	return (xy);
}

void	draw_temp(t_all *all, t_sdl *sdl, t_sect *temp, t_xy d)
{
	t_xy			s;
	t_xy			f;
	t_xy			xy;
	unsigned int	j;

	j = -1;
	xy = get_coords(all);
	while (++j < temp->npoints)
	{
		if (j == temp->npoints - 1)
		{
			s = (t_xy){(temp->vertex[j].x * all->step) + d.x,
			(temp->vertex[j].y * all->step) + d.y};
			f = (t_xy){(xy.x * all->step) + d.x, (xy.y * all->step) + d.y};
		}
		else
		{
			s = (t_xy){(temp->vertex[j].x * all->step) + d.x,
				(temp->vertex[j].y * all->step) + d.y};
			f = (t_xy){(temp->vertex[j + 1].x * all->step) + d.x,
				(temp->vertex[j + 1].y * all->step) + d.y};
		}
		draw_line(all, &s, &f, WHITE);
		draw_circle(sdl, s, 2, WHITE);
	}
}

void	draw_grid(t_all *all, SDL_Rect *area, int step)
{
	t_xy	c;

	c = (t_xy){area->x + (area->w / 2) % step, area->y + (area->h / 2) % step};
	while (c.x <= area->x + area->w)
	{
		draw_line(all, &(t_xy){c.x, 0}, &(t_xy){c.x, area->h}, GREY);
		c.x += step;
	}
	c.x = area->x;
	while (c.y <= area->y + area->h)
	{
		draw_line(all, &c, &(t_xy){area->x + area->w, c.y}, GREY);
		c.y += step;
	}
}
