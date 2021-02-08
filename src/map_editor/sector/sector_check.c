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

t_xy		*remove_vertex(t_xy *vert, int num, int npoints)
{
	int		i;
	int		j;
	t_xy	*tmp;

	i = 0;
	j = 0;
	tmp = (t_xy*)malloc(sizeof(t_xy) * (npoints));
	while (j < npoints)
	{
		if (j == num)
			j++;
		tmp[i] = (t_xy){vert[j].x, vert[j].y};
		i++;
		j++;
	}
	tmp[npoints - 1] = tmp[0];
	ft_memdel((void*)&vert);
	vert = tmp;
	return (vert);
}

void		check_sector_shape(t_sect *sect)
{
	t_xy			*temp;
	unsigned int	i;
	float			side;

	i = 0;
	temp = sect->vertex;
	while (i < sect->npoints - 1)
	{
		side = point_side1(temp[i + 1].x, temp[i + 1].y, temp[i], temp[i + 2]);
		if (side > 0)
		{
			sect->vertex = remove_vertex(temp, i + 1, sect->npoints);
			sect->npoints -= 1;
			check_sector_shape(sect);
			break ;
		}
		i++;
	}
	side = point_side1(temp[0].x, temp[0].y, temp[i], temp[1]);
	if (i == sect->npoints - 1 && side > 0)
	{
		sect->vertex = remove_vertex(temp, 0, sect->npoints);
		sect->npoints -= 1;
		check_sector_shape(sect);
	}
}

int			revert_sector(t_sect *sect)
{
	t_xy			*temp;
	unsigned int	i;

	i = 0;
	if (!(temp = (t_xy*)malloc(sizeof(t_xy) * (sect->npoints + 1))))
		error_and_close(__FILE__, __FUNCTION__);
	while (i < sect->npoints)
	{
		temp[i] = sect->vertex[sect->npoints - i];
		i++;
	}
	temp[i] = temp[0];
	ft_memdel((void*)&sect->vertex);
	sect->vertex = temp;
	return (0);
}

int			check_sector_order(t_sect *sect)
{
	int				res;
	unsigned int	i;
	t_xy			vertex1;
	t_xy			vertex2;

	res = 0;
	i = 0;
	while (i < sect->npoints)
	{
		vertex1 = sect->vertex[i];
		vertex2 = sect->vertex[i + 1];
		res += (vertex2.x - vertex1.x) * (vertex2.y + vertex1.y);
		i++;
	}
	return (res > 0 ? 0 : 1);
}

int			check_sector(t_sect *sect)
{
	if (!(check_sector_order(sect)))
		revert_sector(sect);
	check_sector_shape(sect);
	return (1);
}
