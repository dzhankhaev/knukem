#include "engine.h"

static void keyboard_event(t_engine *engine)
{
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
			{
				engine->player.ducking = engine->player.event.type == SDL_KEYDOWN;
				engine->player.falling = 1;
			}
			else if (engine->player.event.key.keysym.sym == SDLK_ESCAPE)
				engine->close_request = 1;

		}
		else if (engine->player.event.type == SDL_QUIT)
			engine->close_request = 1;
}
//проверяет, выходит ли значение за границы, если выходит, вернет ближайшую границу
static float clampf(float a, float min, float max)
{
	//	берём большее
	a = a > min ? a : min;
	//	берём меньшее
	a = a < max ? a : max;
	return (a);
}

static void mouse_event(t_engine *engine)
{
	int	x;
	int	y;

	SDL_GetRelativeMouseState(&x, &y);	//	СМЕЩЕНИЕ относительно предыдущей позиции
	engine->player.angle += (float)x * 0.03f;	//	горизонтальный поворот
	engine->player.anglesin = sinf(engine->player.angle);
	engine->player.anglecos = cosf(engine->player.angle);

}

void	keys_manager(t_engine *engine)
{
	keyboard_event(engine);
	mouse_event(engine);
}
