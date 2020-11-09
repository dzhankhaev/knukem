#include "engine.h"
#include "utilits.h"

void		ceil_and_floor_init(t_engine *engine)
{
	t_temp	*a;

	a = &engine->rend_wall;
	a->oy[0] = y_for_x(a->wall[0], a->x);
	a->oy[1] = y_for_x(a->wall[1], a->x);
	a->y[0] = iclamp(a->oy[0],
					 engine->tline[a->x], engine->bline[a->x]);		//линия потолка тек
	a->y[1] = iclamp(a->oy[1],
					 engine->tline[a->x], engine->bline[a->x]);		//линия пола тек
	engine->vpceil.minx = a->x0;
	engine->vpceil.maxx = a->x1;
	engine->vpceil.topy[a->x] = engine->tline[a->x];	//верхняя линия потолка
	engine->vpceil.boty[a->x] = a->y[0] - 1;				//нижняя линия потолка
	engine->vpceil.z = engine->player.where.z -
					   engine->sectors[engine->present->sectorno].ceil;
	engine->vpfloor.minx = a->x0;
	engine->vpfloor.maxx = a->x1;
	engine->vpfloor.topy[a->x] = a->y[1];				//верхняя линия пола
	engine->vpfloor.boty[a->x] = engine->bline[a->x] - 1;	//нижняя линия пола
	engine->vpfloor.z = engine->player.where.z -
						engine->sectors[engine->present->sectorno].floor;
}