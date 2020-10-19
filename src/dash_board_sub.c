
// // int		find_dirs(t_wad	*wad, char	*name)
// // {
// // 	int		i;

// // 	i = 0;
// // 	while(i < wad->numlumps)
// // 	{
// // 		if (ft_strcmp(name, wad->dirs[i].name) == 0)
// // 			return(i);
// // 		i++;
// // 	}
// // 	return (0);
// // }

// // void	fill_dirs(t_wad *wad, char *map)
// // {
// // 	int		i;

// // 	i = 0;
// // 	while (i < wad->numlumps)
// // 	{
// // 		ft_memcpy((char*)&wad->patchs[i], map + wad->dirs[i].filepos, 8);
// // 		ft_memcpy(wad->patchs[i].mem, map + wad->dirs[i].filepos, wad->dirs[i].size);
// // 		// wad->patchs[i].mem = (unsigned char*)(map + wad->dirs[i].filepos);
// // 		i++;
// // 	}
// // }

// // void	 fill_wad(t_wad *wad, char *map)
// // {
// // 	char	*mem;
// // 	size_t size;
// // 	size_t i;

// // 	i = 0;
// // 	mem = (char*)wad;
// // 	ft_memcpy(wad,map, 12);
// // 	wad->dirs = (t_directory*)malloc(sizeof(t_directory) * wad->numlumps);
// // 	wad->patchs = (t_patch*)malloc(sizeof(t_patch) * wad->numlumps);
// // 	mem = (char*)wad->dirs;
// // 	ft_memcpy(mem,(char*)map + wad->mem_start,wad->numlumps * sizeof(t_directory));
// // 	fill_dirs(wad, map);
// // }

// // SDL_Surface		*print_dash(char *lmp,t_engine *engine, t_wad *wad)
// // {
// // 	//загрузить цветовую гамму
// // 	char	*colormap;
// // 	int		fd;
// // 	t_patch		test;
// // 	SDL_Surface	*surf;
// // 	int	col_s;
// // 	int c = 0;
// // 	int i = 0;
// // 	int *map;
// // 	int	hm;
	
// // 	ft_memcpy((char*)wad->colormap, wad->patchs[find_dirs(wad, "PLAYPAL")].mem,
// // 																255 * 3 * 14);
// // 	//загрузить дашборд
// // 	fd = open(lmp, O_RDONLY);
// // 	read(fd, (char*)&test, 8);
// // 	hm = find_dirs(wad, lmp);
// // 	// ft_memcpy(wad->patchs[hm].mem)
// // 	// wad->patchs[hm].columnofs = (int*)malloc(sizeof(int) * test.width);
// // 	test.columnofs = (int*)malloc(sizeof(int) * test.width);
// // 	// ft_memcpy(wad->patchs[hm].columnofs,wad->patchs[hm].mem,test.width * 4);
// // 	read(fd, (char*)test.columnofs, test.width * 4);
// // 	test.colum = (char**)malloc(sizeof(char*) * test.width);
// // 	surf = SDL_CreateRGBSurface(0,test.width,test.height,32,
// // 											0xff0000,0xff00,0xff,0xff000000);
// // 	ft_bzero(surf->pixels, surf->pitch * surf->h);
// // 	while (c < test.width)
// // 	{
// // 		if (c != test.width - 1)
// // 			col_s = test.columnofs[c + 1] - test.columnofs[c];
// // 		test.colum[c] = (char*)malloc(col_s);
// // 		read(fd, test.colum[c], col_s);
// // 		pars_colum(test.colum[c], col_s, surf, c, 
// // 									(unsigned char*)wad->colormap[0], engine);
// // 		c++;
// // 	}
// // 	close(fd);
// // 	return(surf);
// // }


// SDL_Surface		*surface_from_patch(t_patch *patch)
// {
// 	unsigned int	*map;
// 	int				i;
// 	int				y;

// 	patch->surface = SDL_CreateRGBSurface(0, patch->width, patch->height, 
// 												32, RMASK, GMASK, BMASK, AMASK);
// 	i = -1;
// 	y = 0;
// 	ft_memset(patch->surface->pixels, 0xf, patch->surface->pitch * patch->surface->h);
// 	// while (++i < patch->width)
// 	// {
// 	// 	map = (unsigned int*)(surf->pixels + sizeof(int) * i);
// 	// 	map += patch->colum[i][y] * patch->width;
// 	// 	while (++y < patch->colum[i][1])
// 	// 	{
// 	// 		*map = 0xffffff00;
// 	// 		map += patch->width;
// 	// 	}
		
// 	// }
// 	return(NULL);
// }



// // char *load_wad(char *name_file)
// // {
// // 	char	*mem;
// // 	int		fd;
// // 	size_t	fr;
// // 	size_t	size;

// // 	size = 0;
// // 	mem = (char*)malloc(100000);
// // 	fd = open(name_file, O_RDONLY);
// // 	while((fr = read(fd,mem,100000)))
// // 		size += fr;
// // 	close(fd);
// // 	free(mem);
// // 	mem = (char*)malloc(size);
// // 	fd = open(name_file, O_RDONLY);
// // 	fr = read(fd, mem, size);
// // 	close(fd);
// // 	return (mem);
// // }


// void			pars_colum(char *colum, int col_s, SDL_Surface *surf,
// 						int col_n, unsigned char *colormap, t_engine *engine)
// {
// 	unsigned int	*map;
// 	unsigned int	space;
// 	unsigned int	index;
// 	unsigned int	color;
// 	int				pxs;
// 	char			*pt;
// 	int				ret;

// 	pt = colum;
// 	ret = 0;
// 	while (!(ret))
// 	{
// 		map = (unsigned int*)(surf->pixels + sizeof(int) * col_n);
// 		space = *(pt++);
// 		while (space > 0)
// 		{
// 			map += surf->w;
// 			space--;
// 		}
// 		pxs = *(pt++);
// 		pt++;
// 		while (pxs-- > 0)
// 		{
// 			index = (unsigned char)*pt;
// 			color = 0xFF000000 + (colormap[index * 3] << 16)
// 				+ (colormap[index * 3 + 1] << 8) + colormap[index * 3 + 2];
// 			*map = color;
// 			map += surf->w;
// 			pt++;
// 		}
// 		pt++;
// 		if ((unsigned char)*pt == 0xff)
// 			ret = 1;
// 	}
// }


void			fill_col(int *i, t_patch *patch, unsigned char *clp,
											int *pixel, int x)
{
	int		index;
	int		col;

	col = patch->colum[x][*i - 2];
	while (col--)
	{
		index = patch->colum[x][*i] * 3;
		*pixel = AMASK | (clp[index] << 16) | (clp[index + 1] << 8)
													| clp[index + 2];
		pixel += patch->width;
		(*i)++;
	}
}
