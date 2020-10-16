#include <fcntl.h>
#include <unistd.h>
#include "engine.h"
#include <stdlib.h>
#include "libft.h"

typedef struct	s_patch
{
	unsigned short	width;
	unsigned short	height;
	unsigned short	l_offset;
	unsigned short	r_offsrt;
	int				*columnofs;
	char			**colum;
}				t_patch;

void	update_win(t_engine *engine, SDL_Surface *surf)
{
	SDL_BlitScaled(surf,NULL,engine->screen,NULL);
	// SDL_UpdateWindowSurface(engine->window);
}

void			pars_colum(char *colum, int col_s, SDL_Surface *surf, 
									int col_n, char *colormap, t_engine *engine)
{
	unsigned int	*map;
	unsigned int	space;
	unsigned int	index;
	unsigned int	color;
	int				pxs;
	char			*pt;
	int				ret;

	pt = colum;
	ret = 0;
	while(!(ret))
	{	
		map = (unsigned int*)(surf->pixels + sizeof(int) * col_n);
		space = *(pt++);
		while (space > 0 )
		{
			map += surf->w;
			space--;
		}
		pxs = *(pt++);
		pt++;
		while (pxs-- > 0)
		{
			index = (unsigned char)*pt;
			color = 0xFF000000 + ((unsigned char)colormap[index * 3] << 16) 
						+ ((unsigned char)colormap[index * 3 + 1] << 8) 
						+ (unsigned char)colormap[index * 3 + 2];
			*map = color;
			map += surf->w;
			pt++;
		}
		pt++;
		if ((unsigned char)*pt == 0xff)
			ret = 1;
	}
}

SDL_Surface		*print_dash(char *lmp,t_engine *engine)
{
	//загрузить цветовую гамму
	char	colormap[255*3];
	int		fd;
	t_patch		test;
	SDL_Surface	*surf;
	int	col_s;
	int c = 0;
	int i = 0;
	int *map;

	fd = open("playpal.pal", O_RDONLY);
	read(fd, colormap, 255 * 3);
	close(fd);
	//загрузить дашборд
	fd = open(lmp, O_RDONLY);
	read(fd, (char*)&test, 8);
	test.columnofs = (int*)malloc(sizeof(int) * test.width);
	read(fd, (char*)test.columnofs, test.width * 4);
	test.colum = (char**)malloc(sizeof(char*) * test.width);
	surf = SDL_CreateRGBSurface(0,test.width,test.height,32,0xff0000,0xff00,0xff,0xff000000);
	ft_bzero(surf->pixels, surf->pitch * surf->h);
	while (c < test.width)
	{
		if (c != test.width - 1)
			col_s = test.columnofs[c + 1] - test.columnofs[c];
		test.colum[c] = (char*)malloc(col_s);
		read(fd, test.colum[c], col_s);
		pars_colum(test.colum[c], col_s, surf, c, colormap, engine);
		c++;
	}
	close(fd);
	return(surf);
}

int main()
{
	t_engine 	engine;
	SDL_Surface	*lmp;

	if (init_engine(&engine) != 0)
		return (1);
	int c = 0;
	lmp = print_dash("STGNUM2.lmp", &engine);
	SDL_BlitScaled(lmp,NULL,engine.screen,NULL);
	SDL_UpdateWindowSurface(engine.window);
	while (!engine.close_request)
	{
		while (SDL_PollEvent(&engine.player.event))
		if (engine.player.event.type == SDL_KEYDOWN || engine.player.event.type == SDL_KEYUP)
		{

			if (engine.player.event.key.keysym.sym == SDLK_LCTRL)
				engine.player.eyeheight = EyeHeight -
						(engine.player.event.type == SDL_KEYDOWN) * DuckHeight;
			else if (engine.player.event.key.keysym.sym == SDLK_ESCAPE)
				engine.close_request = 1;

		}
		else if (engine.player.event.type == SDL_QUIT)
			engine.close_request = 1;
		SDL_UpdateWindowSurface(engine.window);		
	}
	return (0);
}