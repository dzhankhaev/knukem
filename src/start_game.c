#include "engine.h"

void			draw(t_engine *engine)
{
	engine->max_queue = 32;
	engine->future = engine->queue;
	engine->present = engine->queue;
	engine->present->sectorno = CUR_SECT;
	while (engine->present + 1 != engine->queue + engine->max_queue)
	{
		render_wall(engine, engine->present->sectorno);
		engine->present++;
	}

}

void start_game(t_engine *engine)
{
	engine->minimap_x_y = (t_xy){W / 2, H / 2};
	engine->minimap_scale =  W / 50;
	while (!engine->close_request)
	{
		SDL_LockSurface(engine->screen);
		SDL_FillRect(engine->screen, NULL, 0x000000);
		move(engine);
		draw(engine);
		SDL_UnlockSurface(engine->screen);
		SDL_UpdateWindowSurface(engine->window);
		keys_manager(engine);
		SDL_Delay(10);
	}
}
