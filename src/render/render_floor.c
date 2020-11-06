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

void			render_hline(t_engine *engine, int y, int xbegin, int xend, int txno) {
	Uint32 *temp;
	int x;

	x = xbegin;
	temp = (Uint32 *) engine->screen->pixels;

//	float X = (engine->player.where.z - engine->sectors[engine->present->sectorno].floor) / (((float)(y << 1) / H - 1) - engine->player.vangle);
//	float Y = X * (((float)x - (W / 2.f)) / (W / 2.f));
//	float rtx = X * cosf(-engine->player.angle) + Y * sinf(-engine->player.angle);
//	float rtz = -X * sinf(-engine->player.angle) + Y * cosf(-engine->player.angle);
//	Y = (rtx + engine->player.where.x) * 256;
//	X = (rtz + engine->player.where.y) * 256;
//	float X1 = X;
//	float Y1 = X1 * (((float)(x + 1) - (W / 2.f)) / (W / 2.f));
//	rtx = X1 * cosf(-engine->player.angle) + Y1 * sinf(-engine->player.angle);
//	rtz = -X1 * sinf(-engine->player.angle) + Y1 * cosf(-engine->player.angle);
//	Y1 = (rtx + engine->player.where.x) * 256;
//	X1 = (rtz + engine->player.where.y) * 256;
//	float dx = (X1 - X);
//	float dy = (Y1 - y);
	while (x < xend)
	{
		float X = (engine->player.where.z - engine->sectors[engine->present->sectorno].floor) / (((float)(y << 1) / H - 1) - engine->player.vangle);
		float Y = X * (((float)x - (W / 2.f)) / (W / 2.f));
		float rtx = X * cosf(-engine->player.angle) + Y * sinf(-engine->player.angle);
		float rtz = -X * sinf(-engine->player.angle) + Y * cosf(-engine->player.angle);
		Y = (rtx + engine->player.where.x) * 256;
		X = (rtz + engine->player.where.y) * 256;
		temp[(y * W) + x] = get_tx(engine->img[txno].tx, (int)X % engine->img[txno].tx->w, (int)Y % engine->img[txno].tx->h);
		x++;
//		X += dx;
	}
}

static void		loop(t_engine *engine, int *y_top, int *y_bot, int *x_table)
{
	int y1;
	int y2;
	int x;

	x = engine->vpfloor.minx;
	while (x <= engine->vpfloor.maxx)
	{
		y1 = engine->vpfloor.topy[x];
		y2 = engine->vpfloor.boty[x];
		if (y2 < y1)
			continue ;	//	при возможных пропусках точек на границах (а они есть), алгоритм развалится
		while (y1 < *y_top)		//если верхняя линия поднимается
			x_table[--(*y_top)] = x;
		while (y2 > *y_bot)		//если нижняя линия опускается
			x_table[++(*y_bot)] = x;
		while (*y_top < y1)		//если верхняя линия опускается
		{
			render_hline(engine, *y_top, x_table[*y_top], x, 3);
			(*y_top)++;
		}
		while (*y_bot > y2)		//если нижняя линия поднимается
		{
			render_hline(engine, *y_bot, x_table[*y_bot], x, 3);
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
	// WindowYCenterWithOffset=WindowYCenter+tan(M_PI/180.0*PlayerAngleVertical)*WindowHeight/2;

	y_top = engine->vpfloor.topy[engine->vpfloor.minx];
	y_bot = engine->vpfloor.boty[engine->vpfloor.minx];
	y = y_top;
	while (y <= y_bot)
		x_table[y++] = engine->vpfloor.minx;
	loop(engine, &y_top, &y_bot, x_table);
	//заливаем промежуток между top и bottom
	y = y_top;
	while (y <= y_bot)
	{
		render_hline(engine, y, x_table[y], engine->vpfloor.maxx, 3);
		y++;
	}
}