#include "engine.h"
#include "math_utilits.h"

static void 	keyboard_event(t_engine *engine, t_player *player)
{
	while (SDL_PollEvent(&player->event))
	{
		if (player->event.type == SDL_KEYDOWN || player->event.type == SDL_KEYUP)
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
			else if (player->event.key.keysym.sym == SDLK_v)	//режим полета
			{
				player->flying = player->event.type == SDL_KEYDOWN;
				if (player->flying)
				{
					player->ground = 0;			//игрок не на земле
					player->falling = 0;		//ускорение не применяется
					player->velocity.z = VSPEED;//вверх
				}
			}
			else if (player->event.key.keysym.sym == SDLK_c)	//режим полета
			{
				player->flying = player->event.type == SDL_KEYDOWN;
				if (player->flying)
				{
					player->ground = 0;
					player->falling = 0;
					player->velocity.z = -VSPEED;//вниз
				}
			}
			else if (player->event.key.keysym.sym == SDLK_LCTRL)	//присед
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
					&& player->speed == MOVE_SPEED) //	только при нормальной текущей скорости (игрок стоит)
			{
				player->speed = MOVE_SPEED +
							(player->event.type == SDL_KEYDOWN) * DSPRINT_SPEED;
			}
			else if (player->event.key.keysym.sym == SDLK_ESCAPE)
				engine->close_request = 1;
		}
		else if (player->event.type == SDL_QUIT)
			engine->close_request = 1;
		if (player->event.type == SDL_KEYDOWN && player->event.key.keysym.sym == SDLK_BACKQUOTE)	//	режим миникарты
			engine->minimap.mod = engine->minimap.mod ? 0 : 1;
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

static float	angle_fix(float angle)
{
	if (angle > 6.283185f)
		return (0.0001f);
	if (angle < -6.283185f)
		return (-0.0001f);
	if (angle == 0)
		return (0.0001f);
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
	keyboard_event(engine, player);
	SDL_GetRelativeMouseState(&x, &y);	//	позиция относительно предыдущей позиции
	player->vangle = clamp(player->vangle + y * 0.01f, -0.2f, 0.5f);	//вертикальный поворот
	player->angle = angle_fix(player->angle + x * 0.03f); //	горизонтальный поворот
	player->anglesin = sinf(player->angle);
	player->anglecos = cosf(player->angle);
	get_move_vector(player, move_vec);
	acceleration = player->wsad[0] || player->wsad[1] || player->wsad[2]
				|| player->wsad[3] ? ACCELERATION_PLUS : ACCELERATION_MINUS;
	player->velocity.x = player->velocity.x * acceleration
						 + move_vec[0] * acceleration;
	player->velocity.y = player->velocity.y * acceleration
						 + move_vec[1] * acceleration;
}
