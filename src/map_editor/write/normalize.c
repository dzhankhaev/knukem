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

void	norm_sect(t_sect *sect, int j, t_xy	*min)
{
	sect->vertex[j].x += (min->x < 0) ? -min->x : min->x;
	sect->vertex[j].y += (min->y < 0) ? -min->y : min->y;
	if (sect->graf.g_num > 0)
	{	
		sect->graf.coord->x0 += (min->x < 0) ? -min->x : min->x;
		sect->graf.coord->x1 += (min->x < 0) ? -min->x : min->x;
		sect->graf.coord->y0 += (min->y < 0) ? -min->y : min->y;
		sect->graf.coord->y1 += (min->y < 0) ? -min->y : min->y;
	}
}

void	normalize(t_sect *sectors, int num, t_all *all)
{
	int				i;
	unsigned int	j;
	t_xy			*min;

	min = &all->min_coord;
	i = 0;
	while (i < num)
	{
		j = 0;
		while (j <= sectors[i].npoints)
		{
			norm_sect(&sectors[i], j, min);
			j++;
		}
		i++;
	}
	all->player.where.x += (min->x < 0) ? -min->x : min->x;
	all->player.where.y += (min->y < 0) ? -min->y : min->y;
	all->max_coord.x += (min->x < 0) ? -min->x : 0;
	all->max_coord.y += (min->y < 0) ? -min->y : 0;
	min->x += (min->x < 0) ? -min->x : 0;
	min->y += (min->y < 0) ? -min->y : 0;
}