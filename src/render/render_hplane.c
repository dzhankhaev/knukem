#include "engine.h"

static void		loop(t_engine *engine, int *y_top, int *y_bot, int *x_table, t_vplane *p)
{
	int			y1;
	int			y2;
	int			x;

	x = p->minx;
	while (x <= p->maxx)
	{
		y1 = p->topy[x];
		y2 = p->boty[x];
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


void			render_hplane(t_engine *engine, t_vplane *p)
{
	int			y;
	int			x_table[H];
	int			y_top;
	int			y_bot;

	y_top = p->topy[p->minx];
	y_bot = p->boty[p->minx];
	engine->rend_plane.z = p->z;
	y = y_top;
	while (y <= y_bot)
		x_table[y++] = p->minx;
	loop(engine, &y_top, &y_bot, x_table, p);
	//заливаем промежуток между top и bottom
	y = y_top;
	while (y <= y_bot)
	{
		render_hline(engine, y, x_table[y], p->maxx, 3);
		y++;
	}
}