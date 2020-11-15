#include "utilits.h"
#include "engine.h"

static void		rendering_init(t_engine *engine, int sectorno, int neighbor)
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
		init_wall(engine, engine->sectors[neighbor], a->wall);
	}
}

static void		loop(t_engine *engine, int neighbor, t_ixyz t)
{
	t_temp	*a;

	a = &engine->rend_wall;
	//потребуется для вычисления света и текстур. Для других вычислений нужно упорядочить
	a->w = a->wall[0];
	to_x_order(a->wall);
	a->l = engine->wall;
	a->x = a->x0;
	while (a->x < a->x1)
	{
//		X координата текстуры с учетом перспективы. ew.x - координата глубины. Остальные х - экранная координата ширины
//		https://en.wikipedia.org/wiki/Texture_mapping#Perspective_correctness
//		формула оптимизирована a = (x-wall[0].x0) / (wall[0].x1-wall[0].x0)
		a->txx = (engine->u0 * ((a->w.x1 - a->x) * a->l.x1)
				  + engine->u1 * ((a->x - a->w.x0) * a->l.x0))
				 / ((a->w.x1 - a->x) * a->l.x1 + (a->x - a->w.x0) * a->l.x0);
		ceil_and_floor_init(engine);		//y[0] и y[1] мы получаем тут путем линейной интерполяции
		render_wall(engine, neighbor, t);
		a->x += 1;
	}
}

void			render_scene(t_engine *engine, int sectorno, int neighbor, int i)
{
	t_ixyz	txset;

	rendering_init(engine, sectorno, neighbor);
	txset = (t_ixyz){engine->sectors[sectorno].txlist[i], 1, 2};
	if (engine->edit.mod_w != -1 && engine->edit.txno != -1)
	{
		if (engine->edit.mod_tx == 0)
		{
			engine->sectors[sectorno].txlist[i] = engine->edit.txno;
			txset = (t_ixyz){engine->sectors[sectorno].txlist[i], 1, 2};
		}
		else if (engine->edit.mod_tx == 3)
			txset = (t_ixyz){0, engine->edit.txno, 2};
		else if (engine->edit.mod_tx == 4)
			txset = (t_ixyz){0, 1, engine->edit.txno};
	}
	loop(engine, neighbor, txset);
	engine->edit.mod_w = -1;	//после того как модифицировали стену, нужно сбрасывать, иначе применится ко всем стенам
	txset = (t_ixyz){3, 4, 0};
	/*
	if (engine->edit.txno != -1 && sectorno == engine->edit.mod_s)
	{
		if (engine->edit.mod_tx == 1)
			txset = (t_ixyz){engine->edit.txno, 4, 0};
		else if (engine->edit.mod_tx == 2)
		 	txset = (t_ixyz){3, engine->edit.txno, 0};
	}
	*/
	render_hplane(engine, &engine->vpfloor, txset.x);
	render_hplane(engine, &engine->vpceil, txset.y);
}