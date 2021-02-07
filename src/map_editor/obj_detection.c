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

int		inside_sector(t_xyint point, t_sect *sector)
{
	unsigned int	i;
	int				p;

	i = 0;
	while (i < sector->npoints)
	{
		p = point_side1(point.x, point.y, sector->vertex[i], \
			sector->vertex[i + 1]);
		if (p == 0)
			return (0);
		i++;
	}
	return (1);
}

int		which_sector_p(t_all *all, t_sect *sectors, t_xyz where)
{
	int				i;
	int				p;
	unsigned int	j;

	i = 0;
	p = 0;
	while (i < all->num_sectors)
	{
		j = 0;
		if (where.z == all->sectors[i].oldf)
			while (j < all->sectors[i].npoints)
			{
				p = point_side1(where.x, where.y, sectors[i].vertex[j],\
					sectors[i].vertex[j + 1]);
				if (p <= 0)
					break ;
				j++;
			}
		if (p > 0)
			return (i);
		i++;
	}
	return (-1);
}

int		which_sector(t_all *all, t_sect *sectors, t_xyz where)
{
	int				i;
	int				p;
	unsigned int	j;

	i = 0;
	p = 0;
	while (i < all->num_sectors)
	{
		j = 0;
		if (where.z == all->sectors[i].oldf)
			while (j < all->sectors[i].npoints)
			{
				p = point_side1(where.x, where.y, sectors[i].vertex[j],\
					sectors[i].vertex[j + 1]);
				if (p < 0)
					break ;
				j++;
			}
		if (p > 0)
			return (i);
		i++;
	}
	return (-1);
}

int		get_rel_pos(int npoints, t_xyz where, t_xy *vert1, t_xy *vert2)
{
	int j;
	int p;

	j = 0;
	while (j < npoints)
	{
		p = point_side1(where.x, where.y, *vert1, *vert2);
		if (p < 0)
			break ;
		j++;
	}
	return (p);
}

int		*which_sectors(t_all *all, t_sect *sectors, t_xyz where)
{
	int				i;
	int				p;
	int				*ret;
	int				count;
	unsigned int	j;

	i = 0;
	p = 0;
	count = 0;
	ret = malloc(sizeof(int));
	while (i < all->num_sectors)
	{
		j = 0;
		if (where.z == sectors[i].oldf)
			p = get_rel_pos(sectors[i].npoints, where, &sectors[i].vertex[j],\
			&sectors[i].vertex[j + 1]);
		if (p >= 0)
		{
			ret = ft_realloc(ret, sizeof(int) * (count + 2));
			ret[count++] = i;
		}
		i++;
	}
	ret[count] = -1;
	return (ret);
}
