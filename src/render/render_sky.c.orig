#include "engine.h"
#include "utilits.h"
/*
static void		loop(t_engine *engine, int *y_top, int *y_bot, int *x_table)
{
	int y1;
	int y2;
	int x;

	x = engine->vpceil.minx;
	while (x <= engine->vpceil.maxx)
	{
		y1 = engine->vpceil.topy[x];
		y2 = engine->vpceil.boty[x];
		if (y2 < y1)
			continue ;	//	при возможных пропусках точек на границах (а они есть), алгоритм развалится
		while (y1 < *y_top)		//если верхняя линия поднимается
			x_table[--(*y_top)] = x;
		while (y2 > *y_bot)		//если нижняя линия опускается
			x_table[++(*y_bot)] = x;
		while (*y_top < y1)		//если верхняя линия опускается
			render_hline(engine, *y_top, x_table[(*y_top)++], x, 5);
		while (*y_bot > y2)		//если нижняя линия поднимается
			render_hline(engine, *y_bot, x_table[(*y_bot)--], x, 5);
		x++;
	}
}


void			render_sky(t_engine *engine)
{
	int y;
	int	x_table[H];
	int y_top;
	int y_bot;

	y_top = engine->vpceil.topy[engine->vpceil.minx];
	y_bot = engine->vpceil.boty[engine->vpceil.minx];
	engine->rend_plane.z = engine->player.where.z - 30;
	y = y_top;
	while (y <= y_bot)
		x_table[y++] = engine->vpceil.minx;
	loop(engine, &y_top, &y_bot, x_table);
	//заливаем промежуток между top и bottom
	y = y_top;
	while (y <= y_bot)
	{
		render_hline(engine, y, x_table[y], engine->vpceil.maxx, 5);
		y++;
	}
<<<<<<< HEAD
}
 */
||||||| 1784372
}
=======
}
*/
>>>>>>> master
