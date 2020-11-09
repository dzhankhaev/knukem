#include "engine.h"
#include "utilits.h"
#include "events.h"

static void 	keyboard_event(t_engine *engine, t_player *player, t_edit *edit)
{
	while (SDL_PollEvent(&player->event))
	{
		if (player->event.type == SDL_KEYDOWN || player->event.type == SDL_KEYUP) //плавные
		{
			event_movement(player);		//всё что связано с движением игрока
			event_edit(player, edit);	//всё что связано с редактированием карты
		}
		if (player->event.type == SDL_KEYDOWN)	//однократные
		{
			event_edit2(player, edit);
			if (player->event.key.keysym.sym == SDLK_m)		//	режим миникарты
				engine->minimap.mod = engine->minimap.mod ? 0 : 1;
			else if (player->event.key.keysym.sym == SDLK_l)	//	затенение
				engine->player.deep_sh = engine->player.deep_sh ? 0 : 1;
			else if (player->event.key.keysym.sym == SDLK_ESCAPE)	//	закрытие
				engine->close_request = 1;
		}
		if (player->event.type == SDL_QUIT)
			engine->close_request = 1;
	}
}

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
//не выходим за пределы круга [~0;~359]
static float	angle_fix(float angle)
{
	if (angle > 6.265732f)
		return (0.0001f);
	if (angle < 0.0001f)
		return (6.265732f);
	return (angle);
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
	real_time_edit(engine);
	SDL_GetRelativeMouseState(&x, &y);	//	позиция относительно предыдущей позиции
	player->vangle = clamp(player->vangle + y * CAMERA_DY, -VLIMIT, VLIMIT);	//вертикальный поворот
	player->angle = angle_fix(player->angle + x * CAMERA_DX); //	горизонтальный поворот
	player->anglesin = sinf(player->angle);
	player->anglecos = cosf(player->angle);
	engine->rend_plane.pcos = cosf(-engine->player.angle);	//используется для рендеринга горизонтальных поверхностей
	engine->rend_plane.psin = sinf(-engine->player.angle);	//
	get_move_vector(player, move_vec);
	acceleration = player->wsad[0] || player->wsad[1] || player->wsad[2]
				|| player->wsad[3] ? ACCELERATION_PLUS : ACCELERATION_MINUS;
	player->velocity.x = player->velocity.x * acceleration
						 + move_vec[0] * acceleration;
	player->velocity.y = player->velocity.y * acceleration
						 + move_vec[1] * acceleration;
}
