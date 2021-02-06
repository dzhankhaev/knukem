/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:29:45 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/08 01:03:38 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	load_sector_sub(t_engine *engine, t_all *all,
							char **spl, int *arr_len)
{
	t_sect		*sect;
	char		**sub;

	engine->sectors = ft_realloc(engine->sectors,
				++engine->num_sectors * sizeof(*engine->sectors));
	sect = &engine->sectors[engine->num_sectors - 1];
	sub = ft_strsplit(spl[1], ' ');
	sect->floor = (float)ft_atoi(sub[0]);
	sect->ceil = (float)ft_atoi(sub[1]);
	all->mapsize.z = sect->floor > all->mapsize.z ?
			sect->floor : all->mapsize.z;
	ft_free_split(sub);
	sub = ft_strsplit(spl[2], ' ');
	*arr_len = ft_arrlen((void**)sub);
	sect->vertex = (t_xy*)malloc(sizeof(t_xy) * (*arr_len) + 1);
	ft_free_split(sub);
}

static void	load_graf2(t_sect *sect, char **sub)
{
	int		i;

	i = 0;
	while (i < sect->graf.g_num * 7)
	{
		sect->graf.u[i / 7] = 0;
		sect->graf.wall[i / 7] = ft_atoi(sub[i]);
		sect->graf.z[i / 7] = (float)ft_atoi(sub[i + 1]) / 1024.f;
		sect->graf.coord[i / 7].x0 = (float)ft_atoi(sub[i + 2]) / 1024.f;
		sect->graf.coord[i / 7].x1 = (float)ft_atoi(sub[i + 3]) / 1024.f;
		sect->graf.coord[i / 7].y0 = (float)ft_atoi(sub[i + 4]) / 1024.f;
		sect->graf.coord[i / 7].y1 = (float)ft_atoi(sub[i + 5]) / 1024.f;
		sect->graf.coord[i / 7].color = (Uint32)ft_atoi(sub[i + 6]);
		i += 7;
	}
}

static void	load_graf(t_sect *sect, char **split)
{
	char	**sub;

	sect->graf.g_num = ft_atoi(split[6]);
	if (sect->graf.g_num)
	{
		sect->graf.u = (int *)malloc(sizeof(int) * sect->graf.g_num);
		sect->graf.wall = (int *)malloc(sizeof(int) * sect->graf.g_num);
		sect->graf.z = (float *)malloc(sizeof(float) * sect->graf.g_num);
		sect->graf.coord = (t_fline *)malloc(sizeof(t_fline)
				* sect->graf.g_num);
		sub = ft_strsplit(split[7], ' ');
		load_graf2(sect, sub);
		ft_free_split(sub);
	}
	else
	{
		sect->graf.u = NULL;
		sect->graf.wall = NULL;
		sect->graf.z = NULL;
		sect->graf.coord = NULL;
	}
}

static void	load_sector2(int arr_len, char **split, t_sect *sect)
{
	char		**sub;
	int			i;

	sub = ft_strsplit(split[3], ' ');
	sect->npoints = arr_len;
	sect->neighbors = (int*)malloc(sizeof(int) * arr_len);
	i = -1;
	while (++i < arr_len)
		sect->neighbors[i] = ft_atoi(sub[i]);
	ft_free_split(sub);
	if (ft_arrlen((void**)split) >= 5)
		sect->door = ft_atoi(split[4]);
	sub = ft_strsplit(split[5], ' ');
	sect->txf = ft_atoi(sub[0]);
	sect->txc = ft_atoi(sub[1]);
	sect->txw0 = ft_atoi(sub[2]);
	sect->txw1 = ft_atoi(sub[3]);
	ft_free_split(sub);
}

void		load_sector(t_engine *engine, t_all *all, char **split, t_xy *vert)
{
	int			arr_len;
	t_sect		*sect;
	t_xy		v;
	char		**sub;
	int			i;

	load_sector_sub(engine, all, split, &arr_len);
	sect = &engine->sectors[engine->num_sectors - 1];
	sub = ft_strsplit(split[2], ' ');
	i = -1;
	while (++i < arr_len)
	{
		v = (t_xy){.x =vert[ft_atoi(sub[i])].x, .y = vert[ft_atoi(sub[i])].y};
		sect->vertex[i + 1] = v;
		if (i == arr_len - 1)
			sect->vertex[0] = v;
	}
	ft_free_split(sub);
	load_sector2(arr_len, split, sect);
	load_graf(sect, split);
}
