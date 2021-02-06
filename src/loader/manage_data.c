/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:29:45 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/08 01:03:38 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	load_vertex(int *vertices, t_all *all, t_xy **vertex, char **split)
{
	t_xy	v;
	char	**sub;
	int		i;

	v.y = ft_atoi(split[1]);
	sub = ft_strsplit(split[2], ' ');
	i = -1;
	while (++i < ft_arrlen((void**)sub))
	{
		(*vertices)++;
		v.x = ft_atoi(sub[i]);
		*vertex = ft_realloc(*vertex, sizeof(*vertex) * (*vertices));
		(*vertex)[(*vertices) - 1] = v;
		all->mapsize.x = v.x > all->mapsize.x ? v.x : all->mapsize.x;
		all->mapsize.y = v.y > all->mapsize.y ? v.y : all->mapsize.y;
		all->max_coord = (t_xy){all->mapsize.x, all->mapsize.y};
		all->min_coord.x = v.x < all->min_coord.x ? v.x : all->min_coord.x;
		all->min_coord.y = v.y < all->min_coord.y ? v.y : all->min_coord.y;
	}
	ft_free_split(sub);
}

static void	load_player(t_engine *engine, char **split)
{
	char **sub;

	sub = ft_strsplit(split[1], ' ');
	if (ft_arrlen((void**)sub) == 8)
	{
		engine->player.where = (t_xyz){ft_atof(sub[0]), ft_atof(sub[1]), 0};
		engine->player.velocity = (t_xyz){0, 0, 0};
		engine->player.angle = ft_atof(sub[2]);
		engine->player.anglecos = 0;
		engine->player.anglesin = 0;
		engine->player.vangle = 0;
		engine->player.sector = ft_atoi(sub[3]);
		engine->player.where.z =
				engine->sectors[engine->player.sector].floor + EYE_HEIGHT;
		engine->player.settings.inventory = ft_atoi(sub[4]);
		engine->player.settings.speed = ft_atoi(sub[5]);
		engine->player.settings.ammo = ft_atoi(sub[6]);
		engine->player.settings.gravity = ft_atoi(sub[7]);
	}
	ft_free_split(sub);
}

static void	loader(int fd, t_engine *engine, t_all *all)
{
	t_xy	*vert;
	char	*buf;
	int		vertices;
	char	**split;

	vert = NULL;
	vertices = 0;
	while (get_next_line(fd, &buf))
	{
		split = ft_strsplit(buf, '\t');
		if (ft_strequ(split[0], "vertex"))
			load_vertex(&vertices, all, &vert, split);
		else if (ft_strequ(split[0], "sector"))
			load_sector(engine, all, split, vert);
		else if (ft_strequ(split[0], "player"))
			load_player(engine, split);
		else if (ft_strequ(split[0], "final sector"))
			all->fin_sect = ft_atoi(split[1]);
		ft_free_split(split);
		ft_strdel(&buf);
	}
	free(vert);
}

void		load_data(t_engine *engine, t_all *all)
{
	int		fd;

	fd = open(all->name, O_RDONLY);
	if (fd == -1)
		error_and_close(__FILE__, __FUNCTION__);
	all->min_coord = (t_xy){0, 0};
	all->mapsize = (t_xyz){0, 0, 0};
	all->max_coord = (t_xy){0, 0};
	loader(fd, engine, all);
	all->draw_floors = (t_xy){0, (all->mapsize.z)};
	close(fd);
}

void		unload_data(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->num_sectors)
	{
		free(engine->sectors[i].vertex);
		free(engine->sectors[i].neighbors);
		if (engine->sectors[i].graf.g_num > 0)
		{
			free(engine->sectors[i].graf.wall);
			free(engine->sectors[i].graf.z);
			free(engine->sectors[i].graf.coord);
		}
		i++;
	}
	free(engine->sectors);
	engine->sectors = NULL;
	engine->num_sectors = 0;
}
