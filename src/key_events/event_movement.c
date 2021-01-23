/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "events.h"

static void	general_moves(t_player *player)
{
	if (player->event.key.keysym.sym == SDLK_w)
		player->wsad[0] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_s)
		player->wsad[1] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_a)
		player->wsad[2] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_d)
		player->wsad[3] = player->event.type == SDL_KEYDOWN;
	else if (player->event.key.keysym.sym == SDLK_SPACE)
	{
		if (!player->ground && !player->falling)
		{
			player->falling = 1;
			player->velocity.z = 0;
		}
		else if (player->ground)
		{
			player->velocity.z = VSPEED;
			player->falling = 1;
			player->ground = 0;
		}
	}
}

static void	flying(t_player *player)
{
	if (player->game_mode && player->event.key.keysym.sym == SDLK_v)
	{
		player->flying = player->event.type == SDL_KEYDOWN;
		if (player->flying)
		{
			player->ground = 0;
			player->falling = 0;
			player->velocity.z = VSPEED;
		}
	}
	else if (player->game_mode && player->event.key.keysym.sym == SDLK_c)
	{
		player->flying = player->event.type == SDL_KEYDOWN;
		if (player->flying)
		{
			player->ground = 0;
			player->falling = 0;
			player->velocity.z = -VSPEED;
		}
	}
}

static void	additional(t_player *player)
{
	if (player->event.key.keysym.sym == SDLK_LCTRL)
	{
		player->ground = 0;
		player->falling = 1;
		player->eyeheight = EYE_HEIGHT -
				(player->event.type == SDL_KEYDOWN) * DSIT_HEIGHT;
		player->speed = player->move_speed +
						(player->event.type == SDL_KEYDOWN) * DSIT_SPEED;
		player->stand = player->event.type != SDL_KEYDOWN;
	}
	else if (player->event.key.keysym.sym == SDLK_x)
	{
		player->ground = 0;
		player->falling = 1;
		player->eyeheight = EYE_HEIGHT -
							(player->event.type == SDL_KEYDOWN) * DFALL_HEIGHT;
		player->speed = player->move_speed +
						(player->event.type == SDL_KEYDOWN) * DFALL_SPEED;
		player->stand = player->event.type != SDL_KEYDOWN;
	}
}

static void	additional2(t_player *player)
{
	if (player->event.key.keysym.sym == SDLK_LSHIFT
	&& (player->speed == player->move_speed || player->speed ==
	player->move_speed + (((float)player->settings.speed / 100.f) * 0.3f)))
	{
		player->speed = player->move_speed + (player->event.type == SDL_KEYDOWN)
	* (((float)player->settings.speed / 100.f) * 0.3f);
	}
}

void		event_movement(t_engine *engine)
{
	general_moves(&engine->player);
	flying(&engine->player);
	additional(&engine->player);
	additional2(&engine->player);
}
