#include "engine.h"
#include "utilits.h"

void			render_vline1(SDL_Surface *screen, t_line p)
{
	Uint32	*temp;

	temp = (Uint32 *)screen->pixels;
	p.y0 = iclamp(p.y0, 0, H - 1);
	p.y1 = iclamp(p.y1, 0, H - 1);
	while (p.y0 < p.y1)
	{
		temp[(p.y0 * W) + p.x0] = p.color;
		p.y0++;
	}
}

void		render_ceil_and_floor(t_engine *engine)
{
	t_temp	*a;

	a = &engine->rend_wall;
	a->oy[0] = y_for_x(a->wall[0], a->x);
	a->oy[1] = y_for_x(a->wall[1], a->x);
	a->y[0] = iclamp(a->oy[0],
					 engine->tline[a->x], engine->bline[a->x]);		//линия потолка тек
	a->y[1] = iclamp(a->oy[1],
					 engine->tline[a->x], engine->bline[a->x]);		//линия пола тек
	engine->yctop[a->x] = engine->tline[a->x];
	engine->ycbot[a->x] = a->y[0];
	engine->yftop[a->x] = a->y[1];
	engine->yfbot[a->x] = engine->bline[a->x];
	render_vline1(engine->screen, (t_line){a->x, a->x, engine->tline[a->x], a->y[0], a->wall[0].color});	//потолок
	render_vline1(engine->screen, (t_line){a->x, a->x, a->y[1], engine->bline[a->x], a->wall[1].color});	//пол

}

void		render_edge(t_engine *engine, int neighbor, Uint32 z)
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

