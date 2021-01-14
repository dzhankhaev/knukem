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
		all->player.sector != all->swap_num)
	{
		sect = &all->sectors[all->swap_num];
		sect->door = sect->door == -1 ? 0 : (sect->door == 0 ?\
			sect->ceil - sect->oldf : -1);
		if(sect->door > 0)
			sect->floor += sect->door;
		else if(sect->door <= 0)
			sect->floor = sect->oldf; 
		all->swap_num = -1;
	}

	// printf("%f\n",all->draw_floors.x);
	// else
		// all->swap = NULL;
	
}

void	map_click(t_xyz *mouse, t_all *all, SDL_MouseButtonEvent *event)
{
	int x;
	int y;

	x = all->point.x - all->d.x - ((all->area.w / (2 * all->step)) -\
		round(all->mapsize.x / 2));
	y = all->point.y - all->d.y - ((all->area.h / (2 * all->step)) -\
		round(all->mapsize.y / 2));
	if(all->buttons[NEW_SECT].state)
	{
		all->temp->floor = all->set_floors.x;
        all->temp->ceil = all->set_floors.y;
		all->temp->neighbors = NULL;
        new_sector(all, all->temp, x, y);
	}
	else
		select_sector(all, x, y, event);
}
