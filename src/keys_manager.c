#include "engine.h"
#include "math_utilits.h"

static void keyboard_event(t_engine *engine)
{
	while (SDL_PollEvent(&engine->player.event))
	{
		if (engine->player.event.type == SDL_KEYDOWN || engine->player.event.type == SDL_KEYUP)
		{
			if (engine->player.event.key.keysym.sym == 'w')
				engine->player.wsad[0] = engine->player.event.type == SDL_KEYDOWN;
			else if (engine->player.event.key.keysym.sym == 's')
				engine->player.wsad[1] = engine->player.event.type == SDL_KEYDOWN;
			else if (engine->player.event.key.keysym.sym == 'a')
				engine->player.wsad[2] = engine->player.event.type == SDL_KEYDOWN;
			else if (engine->player.event.key.keysym.sym == 'd')
				engine->player.wsad[3] = engine->player.event.type == SDL_KEYDOWN;
			else if (engine->player.event.key.keysym.sym == ' ')
			{
				if (engine->player.ground)
				{
					engine->player.velocity.z += 0.5f;
					engine->player.falling = 1;
				}
			}
			else if (engine->player.event.key.keysym.sym == SDLK_LCTRL)
				engine->player.eyeheight = EYE_HEIGHT -
						(engine->player.event.type == SDL_KEYDOWN) * SIT_HEIGHT;
			else if (engine->player.event.key.keysym.sym == SDLK_ESCAPE)
				engine->close_request = 1;
		}
		else if (engine->player.event.type == SDL_QUIT)
			engine->close_request = 1;
		if (engine->player.event.type == SDL_KEYDOWN && engine->player.event.key.keysym.sym == '`')
			engine->minimap.mod = engine->minimap.mod ? 0 : 1;
	}
}

static void mouse_event(t_player *player)
{
	int			x;
	int			y;
	float		move_vec[2];

	SDL_GetRelativeMouseState(&x, &y);	//	позиция относительно предыдущей позиции
	player->tvangle = clamp(player->tvangle + y * 0.01f, -0.2f, 0.5f);
	player->vangle = player->tvangle - player->velocity.z * 0.5f; //вертикальный поворот
	player->angle += x * 0.03f;	//	горизонтальный поворот
	player->anglesin = sinf(player->angle);
	player->anglecos = cosf(player->angle);
	bzero(move_vec, sizeof(move_vec));
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
	player->pushing = player->wsad[0] || player->wsad[1] || player->wsad[2] || player->wsad[3];
	player->acceleration = player->pushing ? ACCELERATION_PLUS : ACCELERATION_MINUS;
	player->velocity.x = player->velocity.x * player->acceleration + move_vec[0] * player->acceleration;
	player->velocity.y = player->velocity.y * player->acceleration + move_vec[1] * player->acceleration;
}


void	keys_manager(t_engine *engine)
{
	keyboard_event(engine);
	mouse_event(&engine->player);
}
