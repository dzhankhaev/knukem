#include "engine.h"
#include "math_utilits.h"

static void keyboard_event(t_engine *engine, t_player *player)
{
	while (SDL_PollEvent(&player->event))
	{
		if (player->event.type == SDL_KEYDOWN || player->event.type == SDL_KEYUP)
		{
			if (player->event.key.keysym.sym == 'w')
				player->wsad[0] = player->event.type == SDL_KEYDOWN;
			else if (player->event.key.keysym.sym == 's')
				player->wsad[1] = player->event.type == SDL_KEYDOWN;
			else if (player->event.key.keysym.sym == 'a')
				player->wsad[2] = player->event.type == SDL_KEYDOWN;
			else if (player->event.key.keysym.sym == 'd')
				player->wsad[3] = player->event.type == SDL_KEYDOWN;
			else if (player->event.key.keysym.sym == ' ')
			{
				if (!player->falling)
				{
					player->velocity.z += VSPEED;
					player->falling = 1;
				}
			}
			else if (player->event.key.keysym.sym == SDLK_LCTRL)
				player->eyeheight = EYE_HEIGHT -
					(player->event.type == SDL_KEYDOWN) * DSIT_HEIGHT;
			else if (player->event.key.keysym.sym == 'c')
				player->eyeheight = EYE_HEIGHT -
					(player->event.type == SDL_KEYDOWN) * DFALL_HEIGHT;
			else if (player->event.key.keysym.sym == SDLK_ESCAPE)
				engine->close_request = 1;
		}
		else if (player->event.type == SDL_QUIT)
			engine->close_request = 1;
		if (player->event.type == SDL_KEYDOWN && player->event.key.keysym.sym == '`')
			engine->minimap.mod = engine->minimap.mod ? 0 : 1;
	}
}

static void	get_move_vector(t_player *player, float *move_vec)
{
	move_vec[0] = 0;
	move_vec[1] = 0;
	if (player->wsad[0])
	{
		move_vec[0] += player->anglecos * MAX_SPEED;
		move_vec[1] += player->anglesin * MAX_SPEED;
	}
	if (player->wsad[1])
	{
		move_vec[0] -= player->anglecos * MAX_SPEED;
		move_vec[1] -= player->anglesin * MAX_SPEED;
	}
	if (player->wsad[2])
	{
		move_vec[0] += player->anglesin * MAX_SPEED;
		move_vec[1] -= player->anglecos * MAX_SPEED;
	}
	if (player->wsad[3])
	{
		move_vec[0] -= player->anglesin * MAX_SPEED;
		move_vec[1] += player->anglecos * MAX_SPEED;
	}
}

void	keys_manager(t_engine *engine)
{
	int			x;
	int			y;
	float		move_vec[2];
	t_player	*player;

	player = &engine->player;
	keyboard_event(engine, player);
	SDL_GetRelativeMouseState(&x, &y);	//	позиция относительно предыдущей позиции
	player->vangle = clamp(player->vangle + y * 0.01f, -0.2f, 0.5f);	//вертикальный поворот
	player->angle += x * 0.03f;	//	горизонтальный поворот
	player->anglesin = sinf(player->angle);
	player->anglecos = cosf(player->angle);
	get_move_vector(player, move_vec);
	player->acceleration = player->wsad[0] || player->wsad[1] || player->wsad[2]
				|| player->wsad[3] ? ACCELERATION_PLUS : ACCELERATION_MINUS;
	player->velocity.x = player->velocity.x * player->acceleration
						 + move_vec[0] * player->acceleration;
	player->velocity.y = player->velocity.y * player->acceleration
						 + move_vec[1] * player->acceleration;
}
