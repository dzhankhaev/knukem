#include "engine.h"

void	load_data(t_engine *engine, t_all *all)
{
	engine->sectors = NULL;
	FILE *fp = fopen("map-clear.txt", "rt");
	if (!fp)
	{
		perror("map-clear.txt");
		exit(1);
	}
	all->mapsize = (t_xyz){0, 0, 0};
	all->min_coord = (t_xy){0, 0};
	all->max_coord = (t_xy){0, 0};
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
				all->mapsize.x = v.x > all->mapsize.x ? v.x : all->mapsize.x;
				all->mapsize.y = v.y > all->mapsize.y ? v.y : all->mapsize.y;
				all->max_coord = (t_xy){all->mapsize.x, all->mapsize.y};
				all->min_coord.x = v.x < all->min_coord.x ? v.x : all->min_coord.x;
				all->min_coord.y = v.y < all->min_coord.y ? v.y : all->min_coord.y;
			}
			break;
		case 's': // sector
			engine->sectors = realloc(engine->sectors, ++engine->num_sectors * sizeof(*engine->sectors));
			t_sect *sect = &engine->sectors[engine->num_sectors - 1];
			int *num = NULL;
			//считывает пол и потолок
			sscanf(ptr += n, "%f%f%n", &sect->floor, &sect->ceil, &n);
			all->mapsize.z = sect->floor > all->mapsize.z ? sect->floor : all->mapsize.z;
			for (m = 0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#';)
			{
				num = realloc(num, ++m * sizeof(*num));
				num[m - 1] = atoi(word);
                //m хранит количество вершин + количество соседних секторов, причем первое == второму
                //num хранит все числа принадлижащие одному сектору, кроме пола и потолка
                //никаких разделителей между строк нет
			}

			sect->npoints = m /= 2; //количество соседей и вершин этого сектора (всегда одинаково)
			sect->neighbors = malloc((m) * sizeof(*sect->neighbors));
			sect->doors = malloc((m) * sizeof(*sect->doors));
			sect->vertex = malloc((m + 1) * sizeof(*sect->vertex));
			//цикл запишет правую половину num массива, то есть соседей
			for (n = 0; n < m; ++n)
			{
				sect->neighbors[n] = num[m + n];
				sect->doors[n] = -1;
			}
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
	free(vert);
	all->draw_floors = (t_xy){0, (all->mapsize.z)};
}

void unload_data(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->num_sectors)
	{
		free(engine->sectors[i].vertex);
		free(engine->sectors[i].neighbors);
		free(engine->sectors[i].doors);
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
