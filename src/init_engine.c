/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/12 19:53:26 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "editor.h"
#include "utilits.h"

static void		sdl(t_engine *engine, t_all *all)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		free(all->name);
		exc(__FILE__, __FUNCTION__);
	}
	if (!(engine->window = SDL_CreateWindow("doom-nukem",
											SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											W, H,
											0)))
	{
		free(all->name);
		SDL_Quit();
		exc(__FILE__, __FUNCTION__);
	}
	if (!(engine->screen = SDL_GetWindowSurface(engine->window)))
	{
		free(all->name);
		SDL_DestroyWindow(engine->window);
		SDL_Quit();
		exc(__FILE__, __FUNCTION__);
	}
}

static void		sdl_img(t_engine *engine, t_all *all)
{
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		free(all->name);
		SDL_FreeSurface(engine->screen);
		SDL_DestroyWindow(engine->window);
		SDL_Quit();
		exc(__FILE__, __FUNCTION__);
	}
}

static void		load_fonts(t_sdl *sdl, t_all *all, t_engine *engine)
{
	if (TTF_Init()==-1)
	{
		free(all->name);
		SDL_FreeSurface(engine->screen);
		SDL_DestroyWindow(sdl->window);
		SDL_Quit();
		error_and_close(__FILE__, __FUNCTION__);
	}

	all->font = NULL;
	all->font = TTF_OpenFont("fonts/CRA75.ttf", 36);
	if (!all->font)
	{
		free(all->name);
		SDL_FreeSurface(engine->screen);
		SDL_DestroyWindow(sdl->window);
		SDL_Quit();
		error_and_close(__FILE__, __FUNCTION__);
	}
}

void	init_blank_map(t_engine *engine, t_all *all)
{
	all->sectors = NULL;
	all->min_coord = (t_xy){0, 0};
	all->mapsize = (t_xyz){0, 0, 0};
	all->max_coord = (t_xy){0, 0};
	all->num_sectors = 0;
	all->player.sector = -1;
	all->draw_floors = (t_xy){0, 10};
	all->fin_sect = -1;
	all->player.settings = (t_settings){1, 10, 10, 0};
	all->name = ft_strdup("new_map.txt");
}

void			init_engine(t_engine *engine, t_all *all)
{
	sdl(engine, all);
	sdl_img(engine, all);
	all->sdl.window = engine->window;
	all->sdl.screen = engine->screen;
	load_fonts(&all->sdl, all, engine);
	if(!(all->threed))
	{
		load_data(engine, all);
		all->num_sectors = engine->num_sectors;
		all->sectors = engine->sectors;
		all->player = engine->player;
	}
	else
		init_blank_map(engine, all);
	engine->max_queue = MAX_QUEUE;
	load_texture(all);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}
