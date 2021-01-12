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

void	load_vertex(int *vertices, t_all *all, t_xy **vertex, char **split)
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

void	load_sector_sub(t_engine *engine, t_all *all, char **spl, int *arr_len)
{
    t_sect		*sect;
    char		**sub;

    engine->sectors = ft_realloc(engine->sectors,
                                 ++engine->num_sectors * sizeof(*engine->sectors));
    sect = &engine->sectors[engine->num_sectors - 1];
    sub = ft_strsplit(spl[1], ' ');
    sect->floor = ft_atoi(sub[0]);
    sect->ceil = ft_atoi(sub[1]);
    all->mapsize.z = sect->floor > all->mapsize.z ? sect->floor : all->mapsize.z;
    ft_free_split(sub);
    sub = ft_strsplit(spl[2], ' ');
    *arr_len = ft_arrlen((void**)sub);
    sect->vertex = (t_xy*)malloc(sizeof(t_xy) * (*arr_len) + 1);
    ft_free_split(sub);
}

void	load_sector(t_engine *engine, t_all *all, char **split, t_xy *vert)
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
    sub = ft_strsplit(split[3], ' ');
    sect->npoints = arr_len;
    sect->neighbors = (int*)malloc(sizeof(int) * arr_len);
    i = -1;
    while (++i < arr_len)
        sect->neighbors[i] = ft_atoi(sub[i]);
    ft_free_split(sub);
    if (ft_arrlen((void**)split) >= 5)
        sect->door = ft_atoi(split[4]);
    else
        sect->door = -1;
	sub = ft_strsplit(split[5], ' ');
	sect->txf = ft_atoi(sub[0]);
	sect->txc = ft_atoi(sub[1]);
	sect->txw0 = ft_atoi(sub[2]);
	sect->txw1 = ft_atoi(sub[3]);
	ft_free_split(sub);
}

void	load_player(t_engine *engine, char **split)
{
    char **sub;

    sub = ft_strsplit(split[1], ' ');
    if (ft_arrlen((void**)sub) == 4)
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
    }
    ft_free_split(sub);
}

void	load_data(t_engine *engine, t_all *all)
{
    int		fd;
    char	*buf;
    t_xy	*vert;
    int		vertices;
    char	**split;

    vert = NULL;
    vertices = 0;
    *engine = (t_engine){.sectors = NULL, .num_sectors = 0};
    fd = open("new_map.txt", O_RDONLY);
    *all = (t_all){.mapsize = (t_xyz){0, 0, 0}, .min_coord = (t_xy){0, 0}};
    all->max_coord = (t_xy){0, 0};
    while (get_next_line(fd, &buf))
    {
        split = ft_strsplit(buf, '\t');
        if (ft_strequ(split[0], "vertex"))
            load_vertex(&vertices, all, &vert, split);
        else if (ft_strequ(split[0], "sector"))
            load_sector(engine, all, split, vert);
        else if (ft_strequ(split[0], "player"))
            load_player(engine, split);
        ft_free_split(split);
        ft_strdel(&buf);
    }
    all->draw_floors = (t_xy){0, (all->mapsize.z)};
    free(vert);
    close(fd);
}

void unload_data(t_engine *engine)
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
