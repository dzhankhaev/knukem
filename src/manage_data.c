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
#include <fcntl.h>
#include "libft.h"

// void	load_data_(t_engine *engine)
// {
// 	char		*line;
// 	struct s_xy	*vert;
// 	struct s_xy	v;
// 	int			n;
// 	int			m;
// 	int			NumVertices;
// 	int			*num;
// 	int			fd;
// 	float		angle;

// 	vert = NULL;
// 	NumVertices = 0;
// 	engine->sectors = NULL;

// 	if (!(fd = open("map-clear.txt", O_RDONLY)))
// 	{
// 		perror("map-clear.txt");
// 		exit(1);
// 	}
// 	while (get_next_line(fd, line))
// 	{
		
// 	}
// 	close(fd);


// }


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
<<<<<<< HEAD
	ft_free_split(sub);
}
||||||| 1784372
	char Buf[256], word[256], *ptr;
	struct s_xy *vert = NULL, v;
	int n, m, NumVertices = 0;
	while (fgets(Buf, sizeof Buf, fp))
		switch (sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
		{
		case 'v': // vertex
			for (sscanf(ptr += n, "%f%n", &v.y, &n); sscanf(ptr += n, "%f%n", &v.x, &n) == 1;)
			{
				vert = realloc(vert, ++NumVertices * sizeof(*vert));
				vert[NumVertices - 1] = v;
                //NumVertices общее количество вершин
                //vert массив всех вершин где к примеру строка vertex	0	0 6 28 хранится как 0 0, 0 6, 0 28
                //никаких разделителей между строк нет
			}
			break;
		case 's': // sector
			engine->sectors = realloc(engine->sectors, ++engine->num_sectors * sizeof(*engine->sectors));
			t_sector *sect = &engine->sectors[engine->num_sectors - 1];
			int *num = NULL;
			//считывает пол и потолок
			sscanf(ptr += n, "%f%f%n", &sect->floor, &sect->ceil, &n);
			for (m = 0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#';)
			{
				num = realloc(num, ++m * sizeof(*num));
				num[m - 1] = atoi(word);
                //m хранит количество вершин + количество соседних секторов, причем первое == второму
                //num хранит все числа принадлижащие одному сектору, кроме пола и потолка
                //никаких разделителей между строк нет
			}
=======
	char Buf[256], word[256], *ptr;
	struct s_xy *vert = NULL, v;
	int n, m, NumVertices = 0;
	while (fgets(Buf, sizeof Buf, fp))
	{
		switch (sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
		{
		case 'v': // vertex
			for (sscanf(ptr += n, "%f%n", &v.y, &n); sscanf(ptr += n, "%f%n", &v.x, &n) == 1;)
			{
				vert = realloc(vert, ++NumVertices * sizeof(*vert));
				vert[NumVertices - 1] = v;
                //NumVertices общее количество вершин
                //vert массив всех вершин где к примеру строка vertex	0	0 6 28 хранится как 0 0, 0 6, 0 28
                //никаких разделителей между строк нет
			}
			break;  
		case 's': // sector
			engine->sectors = realloc(engine->sectors, ++engine->num_sectors * sizeof(*engine->sectors));
			t_sector *sect = &engine->sectors[engine->num_sectors - 1];
			int *num = NULL;
			//считывает пол и потолок
			sscanf(ptr += n, "%f%f%n", &sect->floor, &sect->ceil, &n);
			for (m = 0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#';)
			{
				num = realloc(num, ++m * sizeof(*num));
				num[m - 1] = atoi(word);
                //m хранит количество вершин + количество соседних секторов, причем первое == второму
                //num хранит все числа принадлижащие одному сектору, кроме пола и потолка
                //никаких разделителей между строк нет
			}
>>>>>>> master

<<<<<<< HEAD
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
	fd = open("map-clear.txt", O_RDONLY);
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
||||||| 1784372
			sect->npoints = m /= 2; //количество соседей и вершин этого сектора (всегда одинаково)
			sect->neighbors = malloc((m) * sizeof(*sect->neighbors));
			sect->vertex = malloc((m + 1) * sizeof(*sect->vertex));
			//цикл запишет правую половину num массива, то есть соседей
			for (n = 0; n < m; ++n)
				sect->neighbors[n] = num[m + n];
			for (n = 0; n < m; ++n)
			    //в num[n] перечислены номера вершин сектора
			    //в vert[num[n]] получаем координаты вершины по её номеру
                sect->vertex[n + 1] = vert[num[n]];
			sect->vertex[0] = sect->vertex[m];
			//в sect->vertex первая и последняя координаты одинаковы, то есть вершины закольцованы
			free(num);
			break;
		case 'p':; // player
			float angle;
			sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle, &n);
			engine->player.where = (t_xyz){v.x, v.y, 0};
			engine->player.velocity = (t_xyz){0, 0, 0};
			engine->player.angle = angle;
			engine->player.anglecos = 0;
			engine->player.anglesin = 0;
			engine->player.vangle = 0;
			engine->player.sector = n;
			engine->player.where.z = engine->sectors[engine->player.sector].floor + EYE_HEIGHT;
		}
	fclose(fp);
=======
			sect->npoints = m /= 2; //количество соседей и вершин этого сектора (всегда одинаково)
			sect->neighbors = malloc((m) * sizeof(*sect->neighbors));
			sect->vertex = malloc((m + 1) * sizeof(*sect->vertex));
			//цикл запишет правую половину num массива, то есть соседей
			for (n = 0; n < m; ++n)
				sect->neighbors[n] = num[m + n];
			for (n = 0; n < m; ++n)
			    //в num[n] перечислены номера вершин сектора
			    //в vert[num[n]] получаем координаты вершины по её номеру
                sect->vertex[n + 1] = vert[num[n]];
			sect->vertex[0] = sect->vertex[m];
			//в sect->vertex первая и последняя координаты одинаковы, то есть вершины закольцованы
			free(num);
			break;
		case 'p':; // player
			float angle;
			sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle, &n);
			engine->player.where = (t_xyz){v.x, v.y, 0};
			engine->player.velocity = (t_xyz){0, 0, 0};
			engine->player.angle = angle;
			engine->player.anglecos = 0;
			engine->player.anglesin = 0;
			engine->player.vangle = 0;
			engine->player.sector = n;
			engine->player.where.z = engine->sectors[engine->player.sector].floor + EYE_HEIGHT;
		}
	}
	fclose(fp);
>>>>>>> master
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
		if (engine->graf[i].g_num > 0)
		{
			free(engine->graf[i].wall);
			free(engine->graf[i].z);
			free(engine->graf[i].coord);
		}
		i++;
	}
	free(engine->sectors);
	free(engine->graf);
	engine->sectors = NULL;
	engine->num_sectors = 0;
}
