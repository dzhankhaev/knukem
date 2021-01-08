#include "engine.h"
#include "utilits.h"

static void	get_lines(t_engine *engine)
{
	t_temp	*a;

	a = &engine->rend_wall;
	engine->tline[a->x] = iclamp(imax(a->y[0],
									  a->y[2]), engine->tline[a->x], H - 1);
	engine->bline[a->x] = iclamp(imin(a->y[1],
									  a->y[3]), 0, engine->bline[a->x]);
}

void		render_wall(t_engine *engine, int neighbor, t_ixyz t)
{
	t_temp	*a;

	a = &engine->rend_wall;
	a->z = engine->player.deep_sh ? deep_shading(engine, a->w, a->x) : 0;

	if (neighbor > -1)
	{
		//imin(y[2], y[1]) если потолок соседа ниже пола, то рисуем до пола, иначе до потолка
		render_vline(engine, (t_line){a->x, a->x, a->y[0],
									  imin(a->y[2], a->y[1])}, get_op1(a), t.z); //	верхняя линия раздела
		//imax(y[3], y[0]) если пол соседа выше потолка, то рисуем до потолка, иначе до пола
		render_vline(engine, (t_line){a->x, a->x, imax(a->y[3],
													   a->y[0]), a->y[1]}, get_op2(a), t.y);	//	нижняя линия раздела
		get_lines(engine);
	}
	else if (neighbor < 0)
		render_vline(engine, (t_line){a->x, a->x, a->y[0], a->y[1]}, get_op3(a), t.x);
}