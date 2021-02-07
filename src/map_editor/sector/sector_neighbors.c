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

int		check_match(t_sect *sect, t_xyz coord, t_xy *temp, int sect_num)
{
	int n;

	n = (int)coord.z;
	if (coord.x == temp[n - 1].x && coord.y == temp[n - 1].y)
		sect->neighbors[n - 1] = sect_num;
	else if (coord.x == temp[n + 1].x && coord.y == temp[n + 1].y)
		sect->neighbors[n] = sect_num;
	else if (coord.x == temp[sect->npoints - 1].x
		&& coord.y == temp[sect->npoints - 1].y)
		sect->neighbors[sect->npoints - 1] = sect_num;
	else
		return (0);
	return (1);
}

int		height_intersection(int x, int y, t_xyz h)
{
	if ((x >= (int)h.x && x <= (int)h.y) || (y > (int)h.x && y <= (int)h.y) ||
		((int)h.x >= x && (int)h.x <= y) || ((int)h.y >= y && (int)h.y <= y))
		return (1);
	return (0);
}

int		is_neighbor(t_all *all, t_xy coord, t_xy coord2, t_xyz h)
{
	unsigned int	i;
	unsigned int	j;
	t_xy			*temp;

	i = 0;
	while ((int)i < all->num_sectors - 1)
	{
		j = 0;
		temp = all->sectors[i].vertex;
		if (height_intersection(all->sectors[i].floor, all->sectors[i].ceil, h)
			&& (int)i != (int)h.z)
			while (j < all->sectors[i].npoints)
			{
				if (coord.x == temp[j].x && coord.y == temp[j].y)
					if (check_match(&all->sectors[i], \
						(t_xyz){coord2.x, coord2.y, j}, temp, h.z))
						return (i);
				j++;
			}
		i++;
	}
	return (-1);
}

int		get_neighbours(t_sect *sector, t_all *all, int self)
{
	unsigned int	i;
	t_xyz			h_self;
	int				n;
	int				res;

	h_self = (t_xyz){sector->floor, sector->ceil, self};
	n = sector->npoints;
	i = 0;
	res = 0;
	while (i < sector->npoints - 1)
	{
		sector->neighbors[i] = is_neighbor(all, sector->vertex[i],
			sector->vertex[i + 1], h_self);
		res = res == 1 ? 1 : check_sect_intersect(all, sector->neighbors[i], \
			sector->vertex[i], sector->vertex[i + 1]);
		i++;
	}
	sector->neighbors[i] = is_neighbor(all, sector->vertex[i],
		sector->vertex[0], h_self);
	res = res == 1 ? 1 : check_sect_intersect(all, sector->neighbors[i], \
			sector->vertex[i], sector->vertex[i + 1]);
	return (res);
}
