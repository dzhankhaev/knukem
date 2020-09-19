#include "engine.h"

static int	ft_create_window(t_engine *engine)
{
	engine->window = SDL_CreateWindow("Doom Nukem",
									SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									W, H,
									0);
	if (!engine->window)
	{
		ft_putendl("Failed to create window!");
		return (1);
	}
	return (0);
}

static int	ft_load_screen(t_engine *engine)
{
	engine->screen = SDL_GetWindowSurface(engine->window);
	if (!engine->screen)
	{
		ft_putendl("Failed to load screen!");
		return (1);
	}
	return (0);
}

int			init_engine(t_engine *engine)
{
	ft_bzero(engine, sizeof(*engine));
	load_data(engine);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_putendl("Couldn't initialize SDL!");
		return (1);
	}
	if (ft_create_window(engine) != 0 || ft_load_screen(engine) != 0)
		return (1);
	SDL_SetRelativeMouseMode(SDL_TRUE); //скрывает курсор, он движется относительно окна
	return (0);
}

void		clean_up(t_engine *engine)
{
	unload_data(engine);
	if (engine->screen)
		SDL_FreeSurface(engine->screen);
	if (engine->window)
		SDL_DestroyWindow(engine->window);
	SDL_Quit();
}
