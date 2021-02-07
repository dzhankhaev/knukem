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

void	del_neighbour(int *arr, int len, int num)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (arr[i] == num)
			arr[i] = -1;
		i++;
	}
}

void	drop_neighs(t_sect *sectors, int *neighbors, int num, int del)
{
	int i;
	int index;

	i = 0;
	while (i < num)
	{
		if (neighbors[i] > -1)
		{
			index = neighbors[i];
			del_neighbour(sectors[index].neighbors, \
				sectors[index].npoints, del);
		}
		i++;
	}
}

void	free_graf(t_graf *graf)
{
	ft_memdel((void*)&graf->coord);
	ft_memdel((void*)&graf->z);
	ft_memdel((void*)&graf->wall);
	ft_memdel((void*)&graf->u);
}

void	remove_sector(t_all *all, t_sect *sectors)
{
	t_sect *del;

	if (all->swap_num != -1)
	{
		del = &sectors[all->swap_num];
		drop_neighs(all->sectors, del->neighbors, del->npoints, all->swap_num);
		ft_memdel((void*)&del->vertex);
		ft_memdel((void*)&del->neighbors);
		if (del->graf.g_num > 0)
			free_graf(&del->graf);
		if (all->num_sectors > 1 && all->swap_num != all->num_sectors - 1)
		{
			sectors[all->swap_num] = sectors[all->num_sectors - 1];
			get_neighbours(&sectors[all->swap_num], all, all->swap_num);
		}
		if (all->swap_num == all->player.sector)
			all->player.sector = -1;
		all->fin_sect = all->swap_num == all->fin_sect ? -1 : all->fin_sect;
		if (all->fin_sect == all->num_sectors - 1)
			all->fin_sect = all->swap_num;
		all->num_sectors -= 1;
		all->player.sector = which_sector_p(all, sectors, all->player.where);
		all->sectors = ft_realloc(sectors, sizeof(t_sect) * all->num_sectors);
		all->swap_num = -1;
	}
}
