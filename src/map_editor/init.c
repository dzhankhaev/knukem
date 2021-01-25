#include "editor.h"

void	load_fonts(t_sdl *sdl, t_all *all)
{
		if(TTF_Init()==-1) 
	{
    	SDL_DestroyWindow(sdl->window);
		SDL_Quit();
		error_and_close(__FILE__, __FUNCTION__);
	}

	all->font = NULL;
	all->font = TTF_OpenFont("fonts/CRA75.ttf", 36);
	all->s_font = NULL;
	all->s_font = TTF_OpenFont("fonts/cabin.ttf", 15);
	if(!all->font || !all->s_font) 
	{
    	SDL_DestroyWindow(sdl->window);
		SDL_Quit();
		error_and_close(__FILE__, __FUNCTION__);
	}
}

int		scaling(SDL_Rect area, t_xyz mapsize)
{
	int scale;

	scale = 0;
	if (mapsize.x < 15 || mapsize.x < 15)
		return (32);
	scale = (int)((area.h * area.w)/(mapsize.x * mapsize.y));
	while (mapsize.x * scale >= area.w || mapsize.y * scale >= area.h)
		scale--;
	return scale;
}

void    init_all(t_all *all)
{
	all->on = 1;
	load_fonts(all->sdl, all);
	all->mouse.z = 0; // переменная нажатия ЛКМ
	all->area = (SDL_Rect){W/4, 0, W - W/4, H}; // Область карты
	all->step = scaling(all->area, all->mapsize);
	all->point = (t_xyint){0,0};
	all->temp = NULL;
	all->temp = (t_sect*)malloc(sizeof(t_sect));
	all->swap_num = -1;
	all->d = (t_xy){0, 0}; 
	all->threed = 0;
	all->temp->npoints = 0;
	all->temp->vertex = NULL;
	all->player.picked = 0;
	// all->player.where.z = all->player.sector;
	all->iso = 0;
	all->set_floors = (t_xy){0, 10};
}