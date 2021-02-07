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

int		is_intersectred(t_xy v11, t_xy v12, t_xy v21, t_xy v22)
{
	t_xy c1;
	t_xy c2;

	c1 = (t_xy){point_side1(v11.x, v11.y, v21, v22),\
		point_side1(v12.x, v12.y, v21, v22)};
	c2 = (t_xy){point_side1(v21.x, v21.y, v11, v12),\
		point_side1(v22.x, v22.y, v11, v12)};
	c1.x = c1.x >= 0 ? 1 : -1;
	c1.y = c1.y >= 0 ? 1 : -1;
	c2.x = c2.x >= 0 ? 1 : -1;
	c2.y = c2.y >= 0 ? 1 : -1;
	if (c1.x + c1.y + c2.x + c2.y == 0)
		return (1);
	return (0);
}

int		check_intersections(t_sect *sect)
{
	unsigned int	i;
	unsigned int	j;
	t_xy			*v;

	i = 0;
	v = sect->vertex;
	while (i < sect->npoints)
	{
		j = i + 2;
		while (j < sect->npoints)
		{
			if (is_intersectred(v[i], v[i + 1], v[j], v[j + 1]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	validate_sector(t_sect *sect, t_all *all)
{
	int n;
	int failure;

	failure = 0;
	check_sector(sect);
	if (all->num_sectors == 1)
	{
		n = sect->npoints;
		while (--n >= 0)
			sect->neighbors[n] = -1;
	}
	else
	{
		failure = get_neighbours(sect, all, all->num_sectors - 1);
		if (failure || check_intersections(sect))
		{
			all->swap_num = all->num_sectors == 0 ? 0 : all->num_sectors - 1;
			print_message(all, RED, "INVALID SECTOR!", 1000);
			remove_sector(all, all->sectors);
		}
	}
}

void	init_new_sector(t_sect *sect, t_sect *temp)
{
	if (!(sect->vertex = malloc(sizeof(t_xy) * temp->npoints)))
		error_and_close(__FILE__, __FUNCTION__);
	if (!(sect->neighbors = malloc(sizeof(t_xy) * (temp->npoints - 1))))
		error_and_close(__FILE__, __FUNCTION__);
	sect->npoints = temp->npoints;
	sect->floor = temp->floor;
	sect->oldf = temp->floor;
	sect->ceil = temp->ceil;
	sect->door = -1;
	sect->txf = 1;
	sect->txc = 1;
	sect->txw0 = 1;
	sect->txw1 = 1;
	sect->graf.g_num = 0;
	sect->graf.coord = NULL;
	sect->graf.wall = NULL;
	sect->graf.u = NULL;
	sect->graf.z = NULL;
}

void	new_sector(t_all *all, t_sect *temp, int x, int y)
{
	unsigned int	i;
	int				*num_sect;

	i = 0;
	num_sect = &all->num_sectors;
	all->min_coord.x = fmin(x, all->min_coord.x);
	all->min_coord.y = fmin(y, all->min_coord.y);
	all->max_coord.x = fmax(x, all->max_coord.x);
	all->max_coord.y = fmax(y, all->max_coord.y);
	temp->vertex = ft_realloc(temp->vertex, (++temp->npoints) * sizeof(t_xy));
	check_vert(all, &x, &y, temp);
	temp->vertex[temp->npoints - 1] = (t_xy){x, y};
	if (temp->vertex[0].x == x && temp->vertex[0].y == y && temp->npoints > 3)
	{
		all->sectors = ft_realloc(all->sectors, ++(*num_sect) * sizeof(t_sect));
		init_new_sector(&all->sectors[*num_sect - 1], temp);
		while (i < temp->npoints)
		{
			all->sectors[*num_sect - 1].vertex[i] = temp->vertex[i];
			i++;
		}
		all->sectors[*num_sect - 1].npoints--;
		validate_sector(&all->sectors[*num_sect - 1], all);
		temp->npoints = 0;
	}
}
