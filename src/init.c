/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "editor.h"
#include "utilits.h"

void			load_sprites(t_engine *engine) //TODO (coordinates hardcoded)
{
	engine->sprites1 = (t_sprites1*)malloc(sizeof(t_sprites1));
	engine->sprites1->weapon_sprite = (t_weapon_sprites*)malloc(sizeof(t_weapon_sprites) * WEAPON_SPRITE_NUM);
	engine->sprites1->weapon_sprite->sector = 0;
	engine->sprites1->weapon_sprite->where.x = 10;
	engine->sprites1->weapon_sprite->where.y = 10;
	engine->sprites1->weapon_sprite->where.z = 5;
	engine->sprites1->weapon_sprite->visible = 1;
	if(!(engine->sprites1->weapon_sprite->texture = get_texture2("shotgun.bmp")))
		error_and_close(__FILE__, __FUNCTION__);
	//engine->sprites1.weapon_sprite->dstrect = (SDL_Rect){W / 10, H * 0.2, 200, 200};
}

static void		init_minimap(t_engine *engine)
{
	engine->minimap.point = (t_xy){W - W / 8, H / 6};
	engine->minimap.scale =  W / 200;
	engine->minimap.player_horizontal.color = 0x4444FF;
	engine->minimap.player_horizontal.x0 = engine->minimap.point.x - 5;
	engine->minimap.player_horizontal.y0 = engine->minimap.point.y;
	engine->minimap.player_horizontal.x1 = engine->minimap.point.x + 5;
	engine->minimap.player_horizontal.y1 = engine->minimap.point.y;
	engine->minimap.player_vertical.color = 0x4444FF;
	engine->minimap.player_vertical.x0 = engine->minimap.point.x;
	engine->minimap.player_vertical.y0 = engine->minimap.point.y - 11;
	engine->minimap.player_vertical.x1 = engine->minimap.point.x;
	engine->minimap.player_vertical.y1 = engine->minimap.point.y + 3;
	engine->minimap.borders = (t_line){W - W / 4, W,0, H / 3,
									0x555555};
	engine->minimap.mod = 0;
}

void			general_init2(t_engine *engine)
{
	int	i;

	i = 0;
	engine->graf = (t_graf *)malloc(sizeof(t_graf) * (engine->num_sectors));
	while (i < engine->num_sectors)
	{
		engine->graf[i].g_num = 0;
		engine->graf[i].wall = 0;
		engine->graf[i].coord = 0;
		engine->graf[i].z = 0;
		i++;
	}
	i = 0;
	while (i < 30)
	{
		engine->danimbuf[i] = -1;
		i++;
	}
}

void			general_init(t_engine *engine)
{
	int	i;

	engine->borders = (t_line){0, W, 0, H, 0x555555};
	engine->player.falling = 0;
	engine->player.flying = 0;
	engine->player.ground = 1;
	engine->player.eyeheight = EYE_HEIGHT;
	engine->player.vangle = 0.f;
	engine->player.speed = MOVE_SPEED;
	engine->player.deep_sh = 0;
	engine->edit.mod_tx = 0;
	engine->edit.mod = 1;
	engine->edit.graf = 0;
	general_init2(engine);
	init_minimap(engine);
}

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
	ft_bzero(engine, sizeof(*engine));
	load_data(engine, all);
	sdl(engine);
	all->num_sectors = engine->num_sectors;
	all->sdl = (t_sdl *)malloc(sizeof(t_sdl) * 1);
	all->sdl->window = engine->window;
	all->sdl->screen = engine->screen;
	all->sectors = engine->sectors;
	all->player = engine->player;
	sdl_img(engine);
	load_sprites(engine);
}
