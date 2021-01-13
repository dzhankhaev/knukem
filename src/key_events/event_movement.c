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
		if (!player->ground && !player->falling)	//если игрок в режиме полета (он не падает, но и не на земле)
		{
			player->falling = 1;					//начнется падение с текущей точки
			player->velocity.z = 0;
		}
		else if (player->ground)					//прыжок доступен только на земле
		{
			player->velocity.z = VSPEED;			//сообщаем положительную скорость
			player->falling = 1;
			player->ground = 0;
		}
	}
}

static void	flying(t_player *player)
{
	if (player->game_mode && player->event.key.keysym.sym == SDLK_v)	//режим полета
	{
		player->flying = player->event.type == SDL_KEYDOWN;
		if (player->flying)
		{
			player->ground = 0;			//игрок не на земле
			player->falling = 0;		//ускорение не применяется
			player->velocity.z = VSPEED;//вверх
		}
	}
	else if (player->game_mode && player->event.key.keysym.sym == SDLK_c)
	{
		player->flying = player->event.type == SDL_KEYDOWN;
		if (player->flying)
		{
			player->ground = 0;
			player->falling = 0;
			player->velocity.z = -VSPEED;//вниз
		}
	}
}

static void	additional(t_player *player)
{
	if (player->event.key.keysym.sym == SDLK_LCTRL)	//присед
	{
		player->ground = 0;			//ускорение применяется только если игрок не на земле
		player->falling = 1;		//активируем ускорение для плавного падения
		player->eyeheight = EYE_HEIGHT -
							(player->event.type == SDL_KEYDOWN) * DSIT_HEIGHT;	//изменяем высоту взгляда
		player->speed = MOVE_SPEED +
						(player->event.type == SDL_KEYDOWN) * DSIT_SPEED;	//изменяем скорость
	}
	else if (player->event.key.keysym.sym == SDLK_x)	//падение на живот
	{
		player->ground = 0;
		player->falling = 1;
		player->eyeheight = EYE_HEIGHT -
							(player->event.type == SDL_KEYDOWN) * DFALL_HEIGHT;
		player->speed = MOVE_SPEED +
						(player->event.type == SDL_KEYDOWN) * DFALL_SPEED;
	}
	else if (player->event.key.keysym.sym == SDLK_LSHIFT
			&& (player->speed == MOVE_SPEED
			|| player->speed == MOVE_SPEED + DSPRINT_SPEED)) //	только когда игрок стоит или бежит
	{
		player->speed = MOVE_SPEED +
						(player->event.type == SDL_KEYDOWN) * DSPRINT_SPEED;
	}
}

void		event_movement(t_engine *engine)
{
	general_moves(&engine->player);
	flying(&engine->player);
	additional(&engine->player);
}
