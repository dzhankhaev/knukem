#include "engine.h"
#include "utilits.h"

void			render_hline21(t_engine *engine, int y, int xbegin, int xend, int txno)
{
	Uint32 *temp;
	t_temp2 *a;
	int x;

	a = &engine->rend_plane;
	x = xbegin;
	temp = (Uint32 *) engine->screen->pixels;
	a->mapx = (engine->player.where.z -
			engine->sectors[engine->present->sectorno].floor) /
					(((float)(y << 1) / H - 1) - engine->player.vangle);
	a->cosx = a->mapx * a->pcos;
	a->sinx = -a->mapx * a->psin;
	while (x < xend)
	{
		a->mapy = a->mapx * (((float)x - (W >> 1)) / (W >> 1));
		a->txy = (int)(((a->cosx + a->mapy * a->psin) + engine->player.where.x)
					   * 256) % engine->img[txno].tx->h;
		a->txx = (int)(((a->sinx + a->mapy * a->pcos) + engine->player.where.y)
					   * 256) % engine->img[txno].tx->w;
		temp[(y * W) + x] = get_pixel_color(engine->img[txno].tx,
											a->txx, a->txy);
		x++;
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
		{
			x++;
			continue ;	//	при возможных пропусках точек на границах (а они есть), алгоритм развалится
		}
		while (y1 < *y_top)		//если верхняя линия поднимается
			x_table[--(*y_top)] = x;
		while (y2 > *y_bot)		//если нижняя линия опускается
			x_table[++(*y_bot)] = x;
		while (*y_top < y1)		//если верхняя линия опускается
			render_hline(engine, *y_top, x_table[(*y_top)++], x, 3);
		while (*y_bot > y2)		//если нижняя линия поднимается
			render_hline(engine, *y_bot, x_table[(*y_bot)--], x, 3);
		x++;
	}
}


void			render_floor(t_engine *engine)
{
	int y;
	int	x_table[H];
	int y_top;
	int y_bot;

	y_top = engine->vpfloor.topy[engine->vpfloor.minx];
	y_bot = engine->vpfloor.boty[engine->vpfloor.minx];
	engine->rend_plane.z = engine->player.where.z - engine->sectors[engine->present->sectorno].floor;
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