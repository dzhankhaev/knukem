#include "engine.h"

static void keyboard_event(t_engine *engine)
{
	engine->player.eyeheight = EyeHeight;
	while (SDL_PollEvent(&engine->player.event))
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
				engine->player.eyeheight = EyeHeight -
						(engine->player.event.type == SDL_KEYDOWN) * DuckHeight;
			else if (engine->player.event.key.keysym.sym == SDLK_ESCAPE)
				engine->close_request = 1;

		}
		else if (engine->player.event.type == SDL_QUIT)
			engine->close_request = 1;
}

#define acceleration_plus 0.6f
#define acceleration_minus 0.8f

static void mouse_event(t_engine *engine)
{
	int	x;
	int	y;

	SDL_GetRelativeMouseState(&x, &y);	//	позиция относительно окна
	engine->player.angle += x * 0.03f;	//	горизонтальный поворот
	engine->player.anglesin = sinf(engine->player.angle);
	engine->player.anglecos = cosf(engine->player.angle);
	bzero(engine->player.move_vec, sizeof(engine->player.move_vec));
	if (engine->player.wsad[0])
	{
		engine->player.move_vec[0] += engine->player.anglecos * 0.2f;
		engine->player.move_vec[1] += engine->player.anglesin * 0.2f;
	}
	if (engine->player.wsad[1])
	{
		engine->player.move_vec[0] -= engine->player.anglecos * 0.2f;
		engine->player.move_vec[1] -= engine->player.anglesin * 0.2f;
	}
	if (engine->player.wsad[2])
	{
		engine->player.move_vec[0] += engine->player.anglesin * 0.2f;
		engine->player.move_vec[1] -= engine->player.anglecos * 0.2f;
	}
	if (engine->player.wsad[3])
	{
		engine->player.move_vec[0] -= engine->player.anglesin * 0.2f;
		engine->player.move_vec[1] += engine->player.anglecos * 0.2f;
	}
	engine->player.pushing = engine->player.wsad[0] || engine->player.wsad[1] || engine->player.wsad[2] || engine->player.wsad[3];
	engine->player.acceleration = engine->player.pushing ? acceleration_plus : acceleration_minus;
	engine->player.velocity.x = engine->player.velocity.x * engine->player.acceleration + engine->player.move_vec[0] * engine->player.acceleration;
	engine->player.velocity.y = engine->player.velocity.y * engine->player.acceleration + engine->player.move_vec[1] * engine->player.acceleration;
	if (engine->player.pushing)
		engine->player.moving = 1;
}


void	keys_manager(t_engine *engine)
{
	keyboard_event(engine);
	mouse_event(engine);
}
