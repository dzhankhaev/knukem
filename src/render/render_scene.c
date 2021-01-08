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
			*(engine->future++) = (t_queue){neighbor, a->x0, a->x1, sectorno};
		init_wall(engine, engine->sectors[neighbor], a->wall);
	}
}

static void		ifdoor(t_engine *engine, int sectorno, int neighbor, int i)
{
	t_temp	*a;

	a = &engine->rend_wall;
	if (neighbor > -1)
	{
		if (engine->sectors[neighbor].door > -1)
			a->wall[5] = perspective_transform(engine->wall,
											   engine->player.where.z - engine->sectors[neighbor].oldf +
											   engine->sectors[neighbor].ceil - engine->sectors[neighbor].door,
											   engine->player.vangle, FLOOR_COLOR);
	}
	if (engine->sectors[sectorno].door > -1)
	{
		a->wall[4] = perspective_transform(engine->wall,
										   engine->player.where.z - engine->sectors[sectorno].oldf,
										   engine->player.vangle, FLOOR_COLOR);
	}
}

static void		loop(t_engine *engine, int neighbor, t_ixyz t, int i)
{
	t_temp	*a;

	a = &engine->rend_wall;
	//потребуется для вычисления света и текстур. Для других вычислений нужно упорядочить
	ifdoor(engine, engine->present->sectorno, neighbor, i);
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
		if (engine->sectors[neighbor].floor >= engine->player.where.z)
			engine->vpfloor.boty[a->x] -= 1;
		if (neighbor > -1)
			if (engine->sectors[neighbor].door > -1)
				a->oy[1] = y_for_x(a->wall[5], a->x);
		if (engine->sectors[engine->present->sectorno].door > -1)
			a->oy[1] = y_for_x(a->wall[4], a->x);
		render_wall(engine, neighbor, t);
		a->x += 1;
	}
}

void			render_scene(t_engine *engine, int sectorno, int neighbor, int i)
{
	t_ixyz txset;

	door_mod(engine, neighbor, i);
	rendering_init(engine, sectorno, neighbor, i);
	txset = tx_wall_mod(engine, sectorno, i);
	loop(engine, neighbor, txset, i);
	txset = tx_plane_mod(engine, sectorno, i);
	render_hplane(engine, &engine->vpfloor, txset.x);
	render_hplane(engine, &engine->vpceil, txset.y);
	render_graf(engine, sectorno, i);
	start_danim(engine, neighbor, i);
	graf_mod(engine, sectorno, i);
	engine->edit.mod_w = -1;	//после того как модифицировали стену, нужно сбрасывать, иначе применится ко всем стенам
	render_line((t_line){0, W - 1, 0, 0, 0}, engine->screen, engine->borders);
	render_line((t_line){0, W - 1, H - 1, H - 1, 0}, engine->screen, engine->borders);
}