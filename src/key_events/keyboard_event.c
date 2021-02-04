/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/12 20:55:18 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"
#include "events.h"

static void	once_events(t_engine *engine, t_player *player, t_edit *edit)
{
	event_edit2(player, edit);
	if (player->event.key.keysym.sym == SDLK_m)
		engine->minimap.mod = engine->minimap.mod ? 0 : 1;
	else if (player->event.key.keysym.sym == SDLK_l)
		engine->player.deep_sh = engine->player.deep_sh ? 0 : 1;
	else if (player->event.key.keysym.sym == SDLK_ESCAPE)
		engine->close_request = 1;
}

void		keyboard_event(t_engine *engine, t_player *player, t_edit *edit)
{
	while (SDL_PollEvent(&player->event))
	{
		if (player->event.type == SDL_KEYDOWN
			|| player->event.type == SDL_KEYUP)
		{
			event_movement(engine);
			event_edit(player, edit);
		}
		if (player->event.type == SDL_KEYDOWN)
			once_events(engine, player, edit);
		if (player->event.type == SDL_QUIT)
			engine->close_request = 1;
	}
}
