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

void	select_sprite(t_all *all, int x, int y)
{	
	t_xyz	where;

	where = (t_xyz){x, y, all->draw_floors.x};
	where = (t_xyz){x, y, which_sector(all, all->sectors, where)};
	all->sprites.swap = which_sprite(all, &all->sprites, where);
}

void	select_sector(t_all *all, int x, int y)
{
	t_xyz	where;

	where = (t_xyz){x, y, all->draw_floors.x};
	all->swap_num = which_sector(all, all->sectors, where);
	printf("%f\n",all->draw_floors.x);
	// else
		// all->swap = NULL;
	
}

void	map_click(t_xyz *mouse, t_all *all)
{
	int x;
	int y;

	x = all->point.x - all->d.x - ((all->area.w/(2 * all->step)) - round(all->mapsize.x/2));
	y = all->point.y - all->d.y - ((all->area.h/(2 * all->step)) - round(all->mapsize.y/2));
	if(all->buttons[0].state == 1)
	{
		all->temp->floor = all->set_floors.x;
        all->temp->ceil = all->set_floors.y;
		all->temp->neighbors = NULL;
        new_sector(all, x, y);
	}
    else if(all->sprites.picked != -1)
    {
		add_sprite(all, x, y, all->sprites.picked);

		// all->player.where = (t_xyz){x, y, all->draw_floors.x};
    	// all->player.sector = which_sector(all, all->sectors, all->player.where);
		// all->player.where.z += EYE_HEIGHT; 
		// all->player.picked = 0;
		// all->buttons[1].state = 0;
		// all->buttons[1].color = WHITE;
	}
	else if(all->buttons[1].state)
		select_sprite(all, x, y);
	else
		select_sector(all, x, y);
}
