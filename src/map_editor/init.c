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

int		scaling(SDL_Rect area, t_xyz mapsize)
{
	int scale;

	scale = 0;
	if (mapsize.x < 15 || mapsize.x < 15)
		return (32);
	scale = (int)((area.h * area.w) / (mapsize.x * mapsize.y));
	while (mapsize.x * scale >= area.w || mapsize.y * scale >= area.h)
		scale--;
	return (scale);
}

void	init_all(t_all *all)
{
	all->mouse.z = 0;
	all->area = (SDL_Rect){W / 4, 0, W - W / 4, H};
	all->step = scaling(all->area, all->mapsize);
	all->point = (t_xyint){0, 0};
	all->swap_num = -1;
	all->d = (t_xy){0, 0};
	all->threed = 0;
	all->temp.neighbors = NULL;
	all->temp.npoints = 0;
	all->temp.vertex = NULL;
	all->player.picked = 0;
	all->set_floors = (t_xy){0, 10};
}
