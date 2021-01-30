/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_manager.c                                     :+:      :+:    :+:   */
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

static void		get_move_vector(t_player *player, float *move_vec)
{
	move_vec[0] = 0;
	move_vec[1] = 0;
	if (player->wsad[0])
	{
		move_vec[0] += player->anglecos * player->speed;
		move_vec[1] += player->anglesin * player->speed;
	}
	if (player->wsad[1])
	{
		move_vec[0] -= player->anglecos * player->speed;
		move_vec[1] -= player->anglesin * player->speed;
	}
	if (player->wsad[2])
	{
		move_vec[0] += player->anglesin * player->speed;
		move_vec[1] -= player->anglecos * player->speed;
	}
	if (player->wsad[3])
	{
		move_vec[0] -= player->anglesin * player->speed;
		move_vec[1] += player->anglecos * player->speed;
	}
}

static float	angle_fix(float angle)
{
	if (angle > 6.265732f)
		return (0.0001f);
	if (angle < 0.0001f)
		return (6.265732f);
	return (angle);
}

static void		eyeheight_correcting(t_engine *engine)
{
	float ceil;
	float floor;

	ceil = engine->sectors[engine->player.sector].ceil;
	floor = engine->sectors[engine->player.sector].floor;
	while (engine->player.stand && engine->player.eyeheight
	+ HEAD_HEIGHT > ceil - floor)
		engine->player.eyeheight--;
	if (engine->player.stand && engine->player.eyeheight
	+ HEAD_HEIGHT < ceil - floor)
		engine->player.eyeheight = EYE_HEIGHT;
}

void			keys_manager(t_engine *engine)
{
	int			x;
	int			y;
	float		move_vec[2];
	float		acceleration;
	t_player	*player;

	player = &engine->player;
	keyboard_event(engine, player, &engine->edit);
	eyeheight_correcting(engine);
	if (SDL_GetRelativeMouseState(&x, &y) & SDL_BUTTON_LMASK)
		engine->hud_inp.fire = 1;
	player->vangle = clamp(player->vangle + y * CAMERA_DY, -VLIMIT, VLIMIT);
	player->angle = angle_fix(player->angle + x * CAMERA_DX);
	player->anglesin = sinf(player->angle);
	player->anglecos = cosf(player->angle);
	engine->rend_plane.pcos = cosf(-engine->player.angle);
	engine->rend_plane.psin = sinf(-engine->player.angle);
	get_move_vector(player, move_vec);
	acceleration = (player->wsad[0] || player->wsad[1] || player->wsad[2]
				|| player->wsad[3] ? ACCELERATION_PLUS : ACCELERATION_MINUS);
	player->velocity.x = player->velocity.x * acceleration
					+ move_vec[0] * acceleration;
	player->velocity.y = player->velocity.y * acceleration
					+ move_vec[1] * acceleration;
}
