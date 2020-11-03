#include "engine.h"
#include "utilits.h"


void		render_ceil_and_floor(t_engine *engine, int x, t_line *wall,
										 int *y)
{
	y[0] = iclamp(y_for_x(wall[0], x),
				  engine->tline[x], engine->bline[x]);		//линия потолка тек
	y[1] = iclamp(y_for_x(wall[1], x),
				  engine->tline[x], engine->bline[x]);		//линия пола тек
	render_vline(engine->screen, (t_line){x, x, engine->tline[x], y[0], wall[0].color});	//потолок
	render_vline(engine->screen, (t_line){x, x, y[1], engine->bline[x], wall[1].color});	//пол
}

void		render_edge(t_engine *engine, int x, t_line *wall, int *y, Uint32 z)
{
	y[2] = iclamp(y_for_x(wall[2], x),
				  engine->tline[x], engine->bline[x]);		//линия потолка соседа
	y[3] = iclamp(y_for_x(wall[3], x),
				  engine->tline[x], engine->bline[x]);		//линия пола соседа
	//imin(y[2], y[1]) если потолок соседа ниже пола, то рисуем до пола, иначе до потолка
	render_vline(engine->screen, (t_line){x, x, y[0], imin(y[2], y[1]), get_shadow(z, wall[2].color)}); //	верхняя линия раздела
	//imax(y[3], y[0]) если пол соседа выше потолка, то рисуем до потолка, иначе до пола
	render_vline(engine->screen, (t_line){x, x, imax(y[3], y[0]), y[1], get_shadow(z, wall[3].color)}); //	нижняя линия раздела
	engine->tline[x] = iclamp(imax(y[0], y[2]), engine->tline[x], H - 1);
	engine->bline[x] = iclamp(imin(y[1], y[3]), 0, engine->bline[x]);
}