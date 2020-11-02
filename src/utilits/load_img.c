#include "engine.h"
#include "utilits.h"

static void	get_fname(char *name, char *fname)
{
	int			i;

	fname[0] = 't';
	fname[1] = 'e';
	fname[2] = 'x';
	fname[3] = 't';
	fname[4] = 'u';
	fname[5] = 'r';
	fname[6] = 'e';
	fname[7] = 's';
	fname[8] = '/';
	i = 9;
	while (i <= 24)
		fname[i++] = '\0';
	i = 9;
	while (name[i - 9] != '\0')
	{
		fname[i] = name[i - 9];
		i++;
	}
}

void 		load_img(t_engine *engine, int n)
{
	SDL_Surface *img;
	char		fname[24];

	get_fname(engine->img[n].name, fname);
	if (!(img = IMG_Load(fname)))
	{
		clean(engine);
		exc(__FILE__, __FUNCTION__);
	}
	if (!(img = SDL_ConvertSurface(img, engine->screen->format, 0)))
	{
		clean(engine);
		exc(__FILE__, __FUNCTION__);
	}
	engine->img->tx = img;
}
//https://habr.com/ru/post/456656/

void		get_filename(t_engine *engine, char *name, int n)
{
	int	i;

	i = 0;
	while (i < 15 && name[i] != '\0')
	{
		engine->img[n].name[i] = name[i];
		i++;
	}
	while (i <= 15)
	{
		engine->img[n].name[i] = '\0';
		i++;
	}
}