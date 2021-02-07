/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 06:30:07 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/07 22:28:14 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "events.h"
#include "editor.h"

static void	reset(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < W)
	{
		engine->tline[i] = 0;
		engine->bline[i] = H - 1;
		i++;
	}
	engine->edit.mod_s = 0x01ab01;
	engine->edit.mod_w = -1;
	engine->edit.door = 0;
	if (engine->edit.graf != 1)
		engine->edit.txno = -1;
	engine->edit.graf_wall = -1;
	engine->player.shot = 0;
}

static int	check_anim(t_engine *engine)
{
	int	q;
	int	i;

	i = 0;
	while (i < engine->num_sectors)
	{
		q = -2;
		while (q < 30)
			if (engine->danimbuf[(q += 2)] == i)
				return (0);
		i++;
	}
	return (1);
}

static void	editor(t_engine *engine, t_all *all)
{
	if (engine->edit.mod && check_anim(engine))
	{
		print_message(all, RED, "ENTERING 2D!", 500);
		SDL_SetRelativeMouseMode(SDL_FALSE);
		engine->edit.mod = main_editor(engine, all);
		engine->close_request = all->threed == 2 ? 1 : 0;
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	else
		engine->edit.mod = 0;
}

void		game_loop(t_engine *engine, t_all *all)
{
	int		time;

	time = 0;
	while (!engine->close_request)
	{
		editor(engine, all);
		reset(engine);
		keys_manager(engine);
		if (engine->player.sector == all->fin_sect)
		{
			print_message(all, RED, "GAME OVER", 1000);
			engine->close_request = 1;
		}
		move(engine);
		draw(engine);
		door_anim(engine);
		real_time_edit(engine);
		put_hud(engine);
		if (SDL_GetTicks() - time < 32)
			SDL_Delay(32 - SDL_GetTicks() + time);
		time = SDL_GetTicks();
		SDL_UpdateWindowSurface(engine->window);
	}
	print_message(all, RED, "EXITING", 500);
}
