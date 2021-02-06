/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:32:47 by sisidra           #+#    #+#             */
/*   Updated: 2020/11/27 13:32:49 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "engine.h"

int		check_event_type(Uint32 type)
{
	if (type == SDL_KEYDOWN || type == SDL_KEYUP || \
		type == SDL_MOUSEMOTION || type == SDL_MOUSEBUTTONUP ||\
		type == SDL_MOUSEBUTTONDOWN)
		return (1);
	else
		return (0);
}

void	interact(t_all *all)
{
	SDL_Event		event;
	Uint32			cur_time;
	Uint32			last_time;

	while ((last_time = SDL_GetTicks()) && all->threed == 0)
	{
		while (SDL_PollEvent(&event))
		{
			on_event(all, &event);
			cur_time = SDL_GetTicks();
			if (cur_time - last_time > FPS)
				break ;
		}
		processing(all);
		if (check_event_type(event.type))
		{
			SDL_LockSurface(all->sdl.screen);
			draw_all(all, &all->sdl, all->buttons);
			event.type = 0;
			SDL_UnlockSurface(all->sdl.screen);
			SDL_UpdateWindowSurface(all->sdl.window);
		}
	}
}

int		main_editor(t_engine *engine, t_all *all)
{
	all->threed = 0;
	interact(all);
	engine->sectors = all->sectors;
	engine->player.where = all->player.where;
	engine->player.sector = all->player.sector;
	engine->player.settings = all->player.settings;
	engine->player.move_speed = ((float)engine->player.settings.speed / 100.f)
								* 0.3f + MOVE_SPEED;
	engine->player.speed = engine->player.move_speed;
	engine->num_sectors = all->num_sectors;
	return (0);
}
