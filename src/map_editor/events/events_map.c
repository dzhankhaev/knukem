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

void	select_sector(t_all *all, int x, int y, SDL_MouseButtonEvent *event)
{
	t_xyz	where;
	t_sect	*sect;

	where = (t_xyz){x, y, all->draw_floors.x};
	all->swap_num = which_sector(all, all->sectors, where);
	if (event->button == SDL_BUTTON_RIGHT && all->swap_num != -1 &&\
		all->player.sector != all->swap_num && !(doors_close(all)))
	{
		sect = &all->sectors[all->swap_num];
		if (sect->door == -1)
			sect->door = 0;
		else
			sect->door = sect->door == 0 ? sect->ceil - sect->oldf : -1;
		if (sect->door > 0)
			sect->floor += sect->door;
		else if (sect->door <= 0)
			sect->floor = sect->oldf;
		all->swap_num = -1;
	}
	else if (event->button == SDL_BUTTON_MIDDLE && all->swap_num != -1 &&\
	all->player.sector != all->swap_num && all->sectors[all->swap_num].door < 0)
	{
		all->fin_sect = all->swap_num;
		all->swap_num = -1;
	}
}

void	set_player(int x, int y, t_all *all)
{
	t_xyz	where;
	int		sect;

	where = (t_xyz){x, y, all->draw_floors.x};
	sect = which_sector_p(all, all->sectors, where);
	if (sect != -1)
	{
		if (all->sectors[sect].ceil - all->sectors[sect].floor > 6 &&\
			all->sectors[sect].door == -1 && sect != all->fin_sect)
		{
			all->player.where = where;
			all->player.sector = sect;
			all->player.picked = 0;
			all->buttons[1].state = 0;
			all->buttons[1].color = WHITE;
		}
		else
			print_message(all, RED, "NOT GOOD!", 1000);
	}
}

int		is_portal(t_all *all, t_xyz point, t_sect *sect)
{
	unsigned int	i;
	int				*num;
	int				*t;
	t_sect			tmp_sect;
	int				res;

	res = 0;
	num = which_sectors(all, all->sectors, point);
	t = num;
	while (*num != -1)
	{
		i = 1;
		tmp_sect = all->sectors[num[0]];
		while (i <= tmp_sect.npoints)
		{
			if (is_vector_equal(sect->vertex[sect->npoints - 1],
(t_xy){point.x, point.y}, tmp_sect.vertex[i], tmp_sect.vertex[i - 1]) &&\
					tmp_sect.neighbors[i - 1] > -1)
				res = 1;
			i++;
		}
		num++;
	}
	ft_memdel((void*)&t);
	return (res);
}

int		pre_check(t_all *all, t_xyz point, t_sect *sect)
{
	int num;

	if (sect->npoints > 0)
		if (point.x == sect->vertex[sect->npoints - 1].x &&\
			point.y == sect->vertex[sect->npoints - 1].y)
			return (0);
	if (sect->npoints >= 1 && is_portal(all, point, sect))
	{
		print_message(all, RED, "PORTAL EXISTS!", 1000);
		return (0);
	}
	if ((num = which_sector(all, all->sectors, point)) > -1)
	{
		if (inside_sector((t_xyint){point.x, point.y}, &all->sectors[num]))
		{
			print_message(all, RED, "INSIDE SECTOR!", 1000);
			return (0);
		}
	}
	return (1);
}

void	map_click(t_all *all, SDL_MouseButtonEvent *event)
{
	int x;
	int y;

	x = all->point.x - all->d.x - ((all->area.w / (2 * all->step)) -\
		round(all->mapsize.x / 2));
	y = all->point.y - all->d.y - ((all->area.h / (2 * all->step)) -\
		round(all->mapsize.y / 2));
	if (all->buttons[NEW_SECT].state)
	{
		all->temp.floor = all->set_floors.x;
		all->temp.ceil = all->set_floors.y;
		all->temp.neighbors = NULL;
		if (pre_check(all, (t_xyz){x, y, all->set_floors.x}, &all->temp))
			new_sector(all, &all->temp, x, y);
	}
	else if (all->player.picked)
		set_player(x, y, all);
	else
		select_sector(all, x, y, event);
}
