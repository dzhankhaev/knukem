#include "engine.h"
#include "utilits.h"

<<<<<<< HEAD
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
||||||| 1784372
static void		render_init(t_engine *engine, int sectorno, int neighbor)
{	//0 потолок, 1 пол, 2 потолок соседа и верхняя линия раздела, 3 пол соседа и нижняя линия раздела
	//соседи (линии раздела) отображаются нак грани текущего сектора, если они имеют общую грань
	t_temp		*a;

	a = &engine->rend_wall;
	init_ceil_floor(engine, engine->sectors[sectorno], a->wall);
	//стены строго вертикально, потому у 0 и 1 иксы одинаковы
	a->x0 = imax(imin(a->wall[0].x0, a->wall[0].x1), engine->present->x0);			//заполняем в промежутке текущей стены
	a->x1 = imin(imax(a->wall[1].x0, a->wall[1].x1), engine->present->x1);			//иксы у пола и потолка всегда равны
	if (neighbor != -1)
	{
		if ((a->x1 > a->x0) && engine->future + 1 != engine->queue + engine->max_queue &&
			check_repeat(engine, sectorno, neighbor))
			*(engine->future++) = (t_queue){neighbor, a->x0, a->x1, sectorno};
		init_edge(engine, engine->sectors[neighbor], a->wall);
	}
}

static void		loop(t_engine *engine, int neighbor)
=======
void		render_wall(t_engine *engine, int neighbor, t_ixyz t)
>>>>>>> master
{
	t_temp	*a;

	a = &engine->rend_wall;
<<<<<<< HEAD
	a->z = engine->player.deep_sh ? deep_shading(engine, a->w, a->x) : 0;

	if (neighbor > -1)
||||||| 1784372
	//потребуется для вычисления света и текстур. Для других вычислений нужно упорядочить
	a->w = a->wall[0];
	to_x_order(a->wall);
	a->l = engine->wall;
	a->x = a->x0;
	while (a->x < a->x1)
=======
	a->z = engine->player.deep_sh ? deep_shading(engine, a->w, a->x) : 0;
	if (neighbor > -1)
>>>>>>> master
	{
<<<<<<< HEAD
		//imin(y[2], y[1]) если потолок соседа ниже пола, то рисуем до пола, иначе до потолка
		render_vline(engine, (t_line){a->x, a->x, a->y[0],
									  imin(a->y[2], a->y[1])}, get_op1(a), t.z); //	верхняя линия раздела
		//imax(y[3], y[0]) если пол соседа выше потолка, то рисуем до потолка, иначе до пола
		render_vline(engine, (t_line){a->x, a->x, imax(a->y[3],
													   a->y[0]), a->y[1]}, get_op2(a), t.y);	//	нижняя линия раздела
		get_lines(engine);
||||||| 1784372
//		X координата текстуры с учетом перспективы. ew.x - координата глубины. Остальные х - экранная координата ширины
//		https://en.wikipedia.org/wiki/Texture_mapping#Perspective_correctness
//		формула оптимизирована a = (x-wall[0].x0) / (wall[0].x1-wall[0].x0)
		a->txx = (engine->u0 * ((a->w.x1 - a->x) * a->l.x1)
				  + engine->u1 * ((a->x - a->w.x0) * a->l.x0))
				 / ((a->w.x1 - a->x) * a->l.x1 + (a->x - a->w.x0) * a->l.x0);
		ceil_and_floor(engine);		//y[0] и y[1] мы получаем тут путем линейной интерполяции
		render_edge(engine, neighbor);
		a->x += 1;
=======
		a->oy[2] = y_for_x(a->wall[2], a->x);
		a->oy[3] = y_for_x(a->wall[3], a->x);
		a->y[2] = iclamp(a->oy[2],
						 engine->tline[a->x], engine->bline[a->x]);		//линия потолка соседа
		a->y[3] = iclamp(a->oy[3],
						 engine->tline[a->x], engine->bline[a->x]);		//линия пола соседа
		//imin(y[2], y[1]) если потолок соседа ниже пола, то рисуем до пола, иначе до потолка
		render_vline(engine, (t_line){a->x, a->x, a->y[0],
			imin(a->y[2], a->y[1]), a->wall[2].color}, get_op1(a), t.z); //	верхняя линия раздела
		//imax(y[3], y[0]) если пол соседа выше потолка, то рисуем до потолка, иначе до пола
		render_vline(engine, (t_line){a->x, a->x, imax(a->y[3],
				a->y[0]), a->y[1], a->wall[2].color}, get_op2(a), t.y);	//	нижняя линия раздела
		engine->tline[a->x] = iclamp(imax(a->y[0],
				a->y[2]), engine->tline[a->x], H - 1);
		engine->bline[a->x] = iclamp(imin(a->y[1],
				a->y[3]), 0, engine->bline[a->x]);
	}
	else
	{
		render_vline(engine, (t_line){a->x, a->x, a->y[0], a->y[1],
									  engine->wall.color}, get_op3(a), t.x);
>>>>>>> master
	}
<<<<<<< HEAD
	else if (neighbor < 0)
		render_vline(engine, (t_line){a->x, a->x, a->y[0], a->y[1]}, get_op3(a), t.x);
}
||||||| 1784372
}

void			render_wall(t_engine *engine, int sectorno, int neighbor)
{
	render_init(engine, sectorno, neighbor);
	loop(engine, neighbor);
	render_floor(engine);
	render_ceil(engine);
}
=======
}

>>>>>>> master
