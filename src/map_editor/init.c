#include "editor.h"

void	load_fonts(t_sdl *sdl, t_all *all)
{
		if(TTF_Init()==-1) 
	{
    	SDL_DestroyWindow(sdl->window);
		SDL_Quit();
		error_and_close(__FILE__, __FUNCTION__);
	}

	all->font = TTF_OpenFont("fonts/CRA75.ttf", 36);
	if(!all->font) 
	{
    	SDL_DestroyWindow(sdl->window);
		SDL_Quit();
		error_and_close(__FILE__, __FUNCTION__);
	}
}

static void			init_sdl(t_sdl *sdl, t_all *all)
{
//	sdl->window = NULL;
//	if (SDL_Init(SDL_INIT_VIDEO) != 0)
//		error_and_close(__FILE__, __FUNCTION__);
//	if (!(sdl->window = SDL_CreateWindow("Map Editor",
//			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH,
//			HEIGHT, SDL_WINDOW_SHOWN)))
//	{
//		SDL_Quit();
//		error_and_close(__FILE__, __FUNCTION__);
//	}
	sdl->renderer = NULL;
	if (!(sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
			SDL_RENDERER_SOFTWARE)))
	{
		printf("%s", SDL_GetError());
		SDL_DestroyWindow(sdl->window);
		SDL_Quit();
		error_and_close(__FILE__, __FUNCTION__);
	}
	SDL_SetRenderDrawBlendMode(sdl->renderer, SDL_BLENDMODE_BLEND);

	load_fonts(sdl, all);
}

t_all    *init_all(t_all *all)
{
//	t_all	*all;

//	all = NULL;
//    if (!(all = (t_all*)malloc(sizeof(t_all))))
//		error_and_close(__FILE__, __FUNCTION__);
//	all->sdl = NULL;
//	if (!(all->sdl = (t_sdl*)malloc(sizeof(t_sdl))))
//		error_and_close(__FILE__, __FUNCTION__);
    init_sdl(all->sdl, all);
	all->mouse.z = 0; // переменная нажатия ЛКМ
	//all->area = (SDL_Rect){319, 4, 876, 691};
	all->area = (SDL_Rect){WIDTH/4, 4, WIDTH - WIDTH/4 - 4, HEIGHT - 8}; // Область карты
//	all->edit = (t_edit){0, (t_xyz){0,0,0}};
	all->step = all->area.h / 23;
	all->point = (t_xyint){0,0};
	all->temp = NULL;
	all->temp = (t_sect*)malloc(sizeof(t_sect));
	// all->swap = NULL;
	// all->sectors = (t_sect*)malloc(sizeof(t_sect));
	all->temp->npoints = 0;
	all->temp->vertex = NULL;
	all->player.picked = 0;
	all->min_coord = (t_xy){0, 0};
	all->max_coord = (t_xy){0, 0};
	all->iso = 0;
	all->set_floors = (t_xy){0, 0};
	all->draw_floors = (t_xy){0, 0};
	return(0);
}