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

int		get_order_num(t_xy coord, int **vert)
{
	int x;
	int y;
	int ret;

	ret = 0;
	y = 0;
	while (y < coord.y)
		ret += vert[y++][0];
	x = 1;
	while (vert[y][x] < coord.x && x < vert[y][0])
	{
		ret += 1;
		x++;
	}
	return (ret);
}

int		*sorted_insert(int *line, int n, int *k)
{
	int i;
	int len;

	len = *k + 1;
	i = 1;
	while (i < len)
		if (line[i++] == n)
			return (line);
	*k = *k + 1;
	line = ft_realloc(line, sizeof(int) * (++len));
	i = 1;
	while (line[i] < n && i < len - 1)
		i++;
	while (len > i)
	{
		line[len - 1] = line[len - 2];
		len--;
	}
	line[i] = n;
	return (line);
}

int		*get_x(t_sect *sectors, int num, int y, int *line)
{
	int				i;
	unsigned int	j;
	int				k;

	k = 0;
	i = 0;
	line[0] = k;
	while (i < num)
	{
		j = 0;
		while (j < sectors[i].npoints)
		{
			if (sectors[i].vertex[j].y == y)
				line = sorted_insert(line, (int)sectors[i].vertex[j].x, &k);
			j++;
		}
		i++;
	}
	line[0] = k;
	return (line);
}

int		**get_vertexes(t_all *all)
{
	int		y;
	int		**yx;

	y = 0;
	yx = (int**)malloc((all->max_coord.y + 1) * sizeof(int*));
	while (y <= all->max_coord.y)
	{
		yx[y] = (int*)malloc(sizeof(int));
		yx[y] = get_x(all->sectors, all->num_sectors, y, yx[y]);
		y++;
	}
	return (yx);
}
