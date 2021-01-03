#include "utilits.h"
#include "engine.h"

static void		rendering_init(t_engine *engine, int sectorno, int neighbor, int i)
{	//0 потолок, 1 пол, 2 потолок соседа и верхняя линия раздела, 3 пол соседа и нижняя линия раздела
	//соседи (линии раздела) отображаются нак грани текущего сектора, если они имеют общую грань
	t_temp		*a;

	a = &engine->rend_wall;
	init_ceil_floor(engine, engine->sectors[sectorno], a->wall);
	//стены строго вертикально, потому у 0 и 1 иксы одинаковы
	a->x0 = imax(imin(a->wall[0].x0, a->wall[0].x1), engine->present->x0);			//заполняем в промежутке текущей стены
	a->x1 = imin(imax(a->wall[1].x0, a->wall[1].x1), engine->present->x1);			//иксы у пола и потолка всегда равны
	if (neighbor >= 0)
	{
		if ((a->x1 > a->x0) && engine->future + 1 != engine->queue + engine->max_queue &&
			check_repeat(engine, sectorno, neighbor))
		{
			if (engine->sectors[sectorno].doors[i] == -1)
				*(engine->future++) = (t_queue){neighbor, a->x0, a->x1,
												sectorno, engine->present->door};
			else if (engine->sectors[sectorno].doors[i] == 0 && neighbor > -1)
				*(engine->future++) = (t_queue){neighbor, a->x0, a->x1,
												sectorno, 1};
		}
		init_wall(engine, engine->sectors[neighbor], a->wall);
	}
}

static void		loop(t_engine *engine, int neighbor, t_ixyz t, int i, int sectorno)
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
		if (engine->sectors[sectorno].doors[i] == 0 && neighbor > -1)
		{
			engine->tdoor[a->x] = iclamp(a->y[2], engine->vpceil.boty[a->x], a->y[1]);
			engine->bdoor[a->x] = iclamp(a->y[3],a->y[0] , engine->vpfloor.topy[a->x]);
		}
		a->x += 1;
	}
}

void			door_mod(t_engine *engine, int sectorno, int neighbor, int i)
{
	//если стена модифицируема и является порталом установить её как дверь
	//doors столько же сколько и neighbors.
	//Нужно внести инфу в текущий сектор и в соседний
	//Для этого ищем соответствующую позицию у соседнего сектора
	int	q;

	if (engine->edit.mod_w == i && neighbor > -1
	&& neighbor == engine->edit.mod_s && engine->edit.door)
	{
		q = 0;
		engine->sectors[sectorno].doors[i] = 0;
		while (q < engine->sectors[neighbor].npoints)
		{
			if (engine->sectors[neighbor].neighbors[q] == sectorno)
			{
				engine->sectors[neighbor].doors[q] = 0;
				break ;
			}
			q++;
		}
	}
}

void			render_scene(t_engine *engine, int sectorno, int neighbor, int i)
{
	t_ixyz txset;

	rendering_init(engine, sectorno, neighbor, i);
	door_mod(engine, sectorno, neighbor, i);
	txset = tx_wall_mod(engine, sectorno, i);
	loop(engine, neighbor, txset, i, sectorno);
	txset = tx_plane_mod(engine, sectorno, i);
	render_hplane(engine, &engine->vpfloor, txset.x);
	render_hplane(engine, &engine->vpceil, txset.y);
	render_graf(engine, sectorno, i);
	graf_mod(engine, sectorno, i);
	engine->edit.mod_w = -1;	//после того как модифицировали стену, нужно сбрасывать, иначе применится ко всем стенам
	render_line((t_line){0, W - 1, 0, 0, 0}, engine->screen, engine->borders);
	render_line((t_line){0, W - 1, H - 1, H - 1, 0}, engine->screen, engine->borders);
}