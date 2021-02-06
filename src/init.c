/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
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

static void		init_minimap(t_engine *engine)
{
	engine->minimap.point = (t_xy){W - W / 8, H / 6};
	engine->minimap.scale = W / 200;
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
	engine->minimap.borders = (t_line){W - W / 4, W, 0, H / 3,
									0x555555};
	engine->minimap.mod = 1;
}

static void		general_init2(t_engine *engine, t_all *all)
{
	int		i;
	char	*sub_name;

	sub_name = ft_strjoin(all->src_dir, "hud/");
	load_surfaces(sub_name, &engine->hud);
	free(sub_name);
	i = 0;
	while (i < engine->num_sectors)
	{
		engine->sectors[i].oldf = engine->sectors[i].floor;
		if (engine->sectors[i].door > -1)
			engine->sectors[i].floor += engine->sectors[i].door;
		i++;
	}
	i = 0;
	while (i < 30)
	{
		engine->danimbuf[i] = -1;
		i++;
	}
}

void			general_init(t_engine *engine, t_all *all)
{
	engine->borders = (t_line){0, W, 0, H, 0x555555};
	engine->player.cur_inv = 0;
	engine->player.cur_am = engine->player.settings.ammo;
	engine->player.shot = 0;
	engine->player.stand = 1;
	engine->player.falling = 0;
	engine->player.flying = 0;
	engine->player.ground = 1;
	engine->player.eyeheight = EYE_HEIGHT;
	engine->player.vangle = 0.f;
	engine->player.move_speed = ((float)engine->player.settings.speed / 100.f)
			* 0.3f + MOVE_SPEED;
	engine->player.speed = engine->player.move_speed;
	engine->player.deep_sh = 0;
	engine->edit.mod_tx = 0;
	engine->edit.mod = 1;
	engine->edit.graf = 0;
	engine->hud_inp = (t_inp_hud){.weapons = 0b11101, .health = 125, .face = 1,
	.buttons = 0, .flag = 0, .fire = 0, .ammo = engine->player.cur_am};
	general_init2(engine, all);
	init_minimap(engine);
}
