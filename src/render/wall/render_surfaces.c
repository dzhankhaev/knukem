#include "engine.h"
#include "utilits.h"

void		ceil_and_floor(t_engine *engine)
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
	engine->vpceil.boty[a->x] = a->y[0];				//нижняя линия потолка
	engine->vpfloor.minx = a->x0;
	engine->vpfloor.maxx = a->x1;
	engine->vpfloor.topy[a->x] = a->y[1];				//верхняя линия пола
	engine->vpfloor.boty[a->x] = engine->bline[a->x];	//нижняя линия пола
}

void		render_edge(t_engine *engine, int neighbor)
{
	t_temp	*a;

	a = &engine->rend_wall;
	a->z = engine->player.deep_sh ? deep_shading(engine, a->w, a->x) : 0;
	if (neighbor > -1)
	{
		a->oy[2] = y_for_x(a->wall[2], a->x);
		a->oy[3] = y_for_x(a->wall[3], a->x);
		a->y[2] = iclamp(a->oy[2],
						 engine->tline[a->x], engine->bline[a->x]);		//линия потолка соседа
		a->y[3] = iclamp(a->oy[3],
						 engine->tline[a->x], engine->bline[a->x]);		//линия пола соседа
		//imin(y[2], y[1]) если потолок соседа ниже пола, то рисуем до пола, иначе до потолка
		render_vline(engine, (t_line){a->x, a->x, a->y[0],
									  imin(a->y[2], a->y[1]), a->wall[2].color}, get_op1(a), 2); //	верхняя линия раздела
		//imax(y[3], y[0]) если пол соседа выше потолка, то рисуем до потолка, иначе до пола
		render_vline(engine, (t_line){a->x, a->x, imax(a->y[3],
													   a->y[0]), a->y[1], a->wall[2].color}, get_op2(a), 1);	//	нижняя линия раздела
		engine->tline[a->x] = iclamp(imax(a->y[0],
										  a->y[2]), engine->tline[a->x], H - 1);
		engine->bline[a->x] = iclamp(imin(a->y[1],
										  a->y[3]), 0, engine->bline[a->x]);
	}
	else
	{
		render_vline(engine, (t_line){a->x, a->x, a->y[0], a->y[1],
									  engine->wall.color}, get_op3(a), 0);
	}
}

