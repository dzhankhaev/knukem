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

static void		sdl(t_engine *engine)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exc(__FILE__, __FUNCTION__);
	if (!(engine->window = SDL_CreateWindow("doom-nukem",
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							W, H,
							0)))
	{
		SDL_Quit();
		exc(__FILE__, __FUNCTION__);
	}
	if (!(engine->screen = SDL_GetWindowSurface(engine->window)))
	{
		SDL_DestroyWindow(engine->window);
		SDL_Quit();
		exc(__FILE__, __FUNCTION__);
	}
}

static void		sdl_img(t_engine *engine)
{
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_FreeSurface(engine->screen);
		SDL_DestroyWindow(engine->window);
		SDL_Quit();
		exc(__FILE__, __FUNCTION__);
	}
}

void			init_engine(t_engine *engine, t_all *all)
{
	load_data(engine, all);
	sdl(engine);
	all->num_sectors = engine->num_sectors;
	all->sdl = (t_sdl *)malloc(sizeof(t_sdl) * 1);
	all->sdl->window = engine->window;
	all->sdl->screen = engine->screen;
	all->sectors = engine->sectors;
	all->player = engine->player;
	engine->max_queue = MAX_QUEUE;
	sdl_img(engine);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}
