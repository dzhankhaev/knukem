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

int		sprites_in_sect(t_all *all, t_button *sprites, int num)
{
	int i;
	int j;

	i = 0;
	while(i < 4)
	{
		j = 0;
		while(j < sprites[i].num)
		{
			if(which_sector(all, all->sectors, sprites[i].sprite_coords[j]) == num)
				return 1;
			j++;
		}
		i++;
	}
	if(all->player.sector == num)
		return 1;
	return 0;
}

void	select_sprite(t_all *all, int x, int y)
{	
	t_xyz	where;

	where = (t_xyz){x, y, all->draw_floors.x};
	where = (t_xyz){x, y, which_sector(all, all->sectors, where)};
	all->sprites.swap = which_sprite(all, &all->sprites, where);
}

void	select_sector(t_all *all, int x, int y, SDL_MouseButtonEvent *event)
{
	t_xyz	where;
	t_sect	*sect;

	where = (t_xyz){x, y, all->draw_floors.x};
	all->swap_num = which_sector(all, all->sectors, where);
	if (event->button == SDL_BUTTON_RIGHT && all->swap_num != -1 &&\
		!(sprites_in_sect(all, all->sprites.buttons, all->swap_num)))
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

	x = all->point.x - all->d.x - ((all->area.w/(2 * all->step)) - round(all->mapsize.x/2));
	y = all->point.y - all->d.y - ((all->area.h/(2 * all->step)) - round(all->mapsize.y/2));
	// printf("button[1] = %d\nsprite picked = %d\n", all->buttons[1].state, all->sprites.picked);
	if(all->buttons[0].state)
	{
		all->temp->floor = all->set_floors.x;
        all->temp->ceil = all->set_floors.y;
		all->temp->neighbors = NULL;
        new_sector(all, x, y);
	}
    else if(all->buttons[1].state && all->sprites.picked != -1)
		add_sprite(all, x, y, all->sprites.picked);
	else if(all->buttons[1].state && all->sprites.picked == -1)
		select_sprite(all, x, y);
	else
		select_sector(all, x, y, event);
}
