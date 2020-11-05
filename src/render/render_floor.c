#include "engine.h"
#include "utilits.h"

Uint32		get_tx(SDL_Surface *surface, int x, int y)
{
	Uint8	*p;
	Uint32	rgb;

	p = (Uint8 *)(surface->pixels + y * surface->pitch
				  + (x * surface->format->BytesPerPixel));
	rgb = p[2] << 16 | p[1] << 8 | p[0];
	return (rgb);
}

void			render_hline(t_engine *engine, int y, int xbegin, int xend, int dist, int txno)
{
	Uint32	*temp;
	int		x;

	int du = (int)(dist * engine->player.anglesin) % W;
	int dv = (int)(-1 * dist * engine->player.anglecos) % H;
	int u = ((x + (int)((float)dist * engine->player.anglecos)) * W) % W;
	int v = ((y + (int)((float)dist * engine->player.anglesin)) * H) % H;

	temp = (Uint32 *)engine->screen->pixels;
	x = xbegin;
	while (x < xend)
	{
		temp[(y * W) + x] = get_tx(engine->img[txno].tx, u, v);
		u += du;
		v += dv;
		x++;
	}
}

static void		loop(t_engine *engine, int *y_top, int *y_bot, int *x_table, int dist)
{
	int y1;
	int y2;
	int x;

	x = engine->vpfloor.MinX;
	while (x <= engine->vpfloor.MaxX)
	{
		y1 = engine->vpfloor.TopY[x];
		y2 = engine->vpfloor.BotY[x];
		if (y2 < y1)
			continue ;	//	при возможных пропусках точек на границах (а они есть), алгоритм развалится
		while (y1 < *y_top)		//если верхняя линия поднимается
			x_table[--(*y_top)] = x;
		while (y2 > *y_bot)		//если нижняя линия опускается
			x_table[++(*y_bot)] = x;
		while (*y_top < y1)		//если верхняя линия опускается
		{
			render_hline(engine, *y_top, x_table[*y_top], x, dist, 3);
			(*y_top)++;
		}
		while (*y_bot > y2)		//если нижняя линия поднимается
		{
			render_hline(engine, *y_bot, x_table[*y_bot], x, dist, 3);
			(*y_bot)--;
		}
		x++;
	}
}

void			render_floor(t_engine *engine)
{
	int y;
	int	x_table[H];
	int y_top;
	int y_bot;
	int	dist = (engine->player.where.z - engine->sectors[engine->present->sectorno].floor) * (H >> 1);

	y_top = engine->vpfloor.TopY[engine->vpfloor.MinX];
	y_bot = engine->vpfloor.BotY[engine->vpfloor.MinX];
	y = y_top;
	while (y <= y_bot)
		x_table[y++] = engine->vpfloor.MinX;
	loop(engine, &y_top, &y_bot, x_table, dist);
	//заливаем промежуток между top и bottom
	y = y_top;
	while (y <= y_bot)
	{
		render_hline(engine, y, x_table[y], engine->vpfloor.MaxX, dist, 3);
		y++;
	}
}