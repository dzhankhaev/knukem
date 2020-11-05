#include "engine.h"
#include "utilits.h"

static void	init_minimap(t_engine *engine)
{
	engine->minimap.point = (t_xy){W - W / 8, H - H / 6};
	engine->minimap.scale =  W / 200;
	engine->minimap.player_horizontal.color = 0x4444FF;
	engine->minimap.player_horizontal.x0 = engine->minimap.point.x - 5;
	engine->minimap.player_horizontal.y0 = engine->minimap.point.y;
	engine->minimap.player_horizontal.x1 = engine->minimap.point.x + 5;
	engine->minimap.player_horizontal.y1 = engine->minimap.point.y;
	engine->minimap.player_vertical.color = 0x4444FF;
	engine->minimap.player_vertical.x0 = engine->minimap.point.x;
	engine->minimap.player_vertical.y0 = engine->minimap.point.y - 11;
	engine->minimap.player_vertical.x1 = engine->minimap.point.x;
	engine->minimap.player_vertical.y1 = engine->minimap.point.y + 3;
	engine->minimap.borders = (t_line){W - W / 4, W,H - H / 3, H,
									   0x555555};
	engine->minimap.mod = 0;
}

void general_init(t_engine *engine)
{
	engine->borders = (t_line){0, W, 0, H, 0x555555};
	engine->player.falling = 0;
	engine->player.flying = 0;
	engine->player.ground = 1;
	engine->player.eyeheight = EYE_HEIGHT;
	engine->player.vangle = 0.f;
	engine->player.speed = MOVE_SPEED;
	engine->player.deep_sh = 0;
	init_minimap(engine);
}

static void sdl(t_engine *engine)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exc(__FILE__, __FUNCTION__);
	if (!(engine->window = SDL_CreateWindow("doom-nukem",
											SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											W, H,
											0)))
	{
		SDL_Quit();
		exc(__FILE__, __FUNCTION__);
	}
	if (!(engine->screen = SDL_GetWindowSurface(engine->window)))
	{
		SDL_DestroyWindow(engine->window);
		SDL_Quit();
		exc(__FILE__, __FUNCTION__);
	}
}

static void sdl_img(t_engine *engine)
{
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_FreeSurface(engine->screen);
		SDL_DestroyWindow(engine->window);
		SDL_Quit();
		exc(__FILE__, __FUNCTION__);
	}
}

void		init_engine(t_engine *engine)
{
	bzero(engine, sizeof(*engine));
	load_data(engine);
	sdl(engine);
	sdl_img(engine);
}
