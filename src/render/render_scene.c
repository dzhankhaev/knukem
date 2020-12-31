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
	if (neighbor >= 0)
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

t_ixyz			tx_wall_mod(t_engine *engine, int sectorno, int i)
{
	t_ixyz	txset;
	int		q;
	int		k;

	txset = (t_ixyz){abs(engine->sectors[sectorno].neighbors[i]), 1, 2};
	if (engine->edit.mod_w != -1 && engine->edit.txno != -1)
	{
		if (engine->sectors[sectorno].neighbors[i] <= -1)
			engine->sectors[sectorno].neighbors[i] = engine->edit.txno * -1;
		if (engine->edit.mod_tx == 0)
			txset = (t_ixyz){abs(engine->sectors[sectorno].neighbors[i]), 1, 2};
		else if (engine->edit.mod_tx == 3)
			txset = (t_ixyz){0, engine->edit.txno, 2};
		else if (engine->edit.mod_tx == 4)
			txset = (t_ixyz){0, 1, engine->edit.txno};
	}
	return (txset);
}

t_ixyz			tx_plane_mod(t_engine *engine, int sectorno, int i)
{
	t_ixyz txset;

	txset = (t_ixyz){3, 4, 0};
	return (txset);
}

void			graf_memalloc(t_engine *engine, int sectorno, int i)
{
	t_graf *graf;

	graf = &engine->graf[sectorno];
	graf->g_num++;
	//выделяем память
	graf->wall = (int *)realloc(graf->wall, sizeof(int) * graf->g_num);
	graf->z = (float *)realloc(graf->z, sizeof(float) * graf->g_num);
	graf->coord = (t_fline *)realloc(graf->coord, sizeof(t_fline)
	* graf->g_num);
	graf->txno = (int *)realloc(graf->txno, sizeof(int) * graf->g_num);
	//заносим необходимые данные
	graf->sectorno = sectorno;
	graf->txno[graf->g_num - 1] = 1;
	graf->wall[graf->g_num - 1] = i;
	graf->z[graf->g_num - 1] = engine->player.where.z;
	graf->coord[graf->g_num - 1] =
			(t_fline){engine->sectors[sectorno].vertex[i].x,
					  engine->sectors[sectorno].vertex[i + 1].x,
					  engine->sectors[sectorno].vertex[i].y,
					  engine->sectors[sectorno].vertex[i + 1].y,
					  1};
}

void			create_coord(t_engine *engine, int sectorno)
{
	t_graf	*graf;
	float	angle;
	t_xy	a;
	t_xy	b;

	graf = &engine->graf[sectorno];
	//проекция
	a = point_proection(graf->coord[graf->g_num - 1],
						(t_xyz){engine->player.where.x,
								engine->player.where.y, 0});
	angle = get_vec_angle(graf->coord[graf->g_num - 1].x1
			- graf->coord[graf->g_num - 1].x0,
			graf->coord[graf->g_num - 1].y1
			- graf->coord[graf->g_num - 1].y0,1,0);
	//прокладывание отрезка вдоль стены
	a.x -= engine->player.where.x;
	a.y -= engine->player.where.y;
	b.x = a.x + 1 * cosf(angle);
	b.y = a.y + 1 * sinf(angle);
	a.x += engine->player.where.x;
	a.y += engine->player.where.y;
	b.x += engine->player.where.x;
	b.y += engine->player.where.y;
	graf->coord[graf->g_num - 1] = (t_fline){a.x, b.x, a.y, b.y};
}

void			graf_mod(t_engine *engine, int sectorno, int i)
{
	if (engine->edit.mod_w != -1 && engine->edit.graf != -1)
	{
		if (engine->sectors[sectorno].neighbors[i] <= -1)
		{
			graf_memalloc(engine, sectorno, i);
			create_coord(engine, sectorno);
		}
	}
}

void			loop_graf(t_engine *engine, t_line w0, t_line w1, int x)
{
	int		y0;
	int		y1;
	int		oy0;
	int		oy1;
	t_temp	*a;

	a = &engine->rend_wall;
	a->x = x;
	a->txx = (engine->u0 * ((a->w.x1 - a->x) * a->l.x1)
			  + engine->u1 * ((a->x - a->w.x0) * a->l.x0))
			 / ((a->w.x1 - a->x) * a->l.x1 + (a->x - a->w.x0) * a->l.x0);
	y1 = y_for_x(w0, x);
	y0 = y_for_x(w1, x);
	oy0 = y0;
	oy1 = y1;
	y0 = iclamp(y0, engine->tline[x], engine->bline[x]);
	y1 = iclamp(y1, engine->tline[x], engine->bline[x]);
	y0 = iclamp(y0, engine->vpceil.boty[x], engine->vpfloor.topy[x]);
	y1 = iclamp(y1, engine->vpceil.boty[x], engine->vpfloor.topy[x]);
	if (y1 - y0 >= 3)
		render_vline(engine, (t_line){a->x, a->x, y0, y1,
									  engine->wall.color},
					 (t_line){0, 0, oy0, oy1, 0}, w0.color);
}

void 			render_graf2(t_engine *engine, t_graf graf, t_fline *w, int t)
{
	float	z;
	t_line	w0;
	t_line	w1;
	int		x0;
	int		x1;

	z = engine->player.where.z;
	w0 = perspective_transform(*w,z - graf.z[t] + 1,
							   engine->player.vangle, w->color);
	w1 = perspective_transform(*w,z - graf.z[t] - 1,
							   engine->player.vangle, FLOOR_COLOR);
	x0 = imax(imin(w0.x0, w0.x1), engine->present->x0);
	x1 = imin(imax(w1.x0, w1.x1), engine->present->x1);
	engine->rend_wall.w = w0;
	if (w0.x0 > w0.x1)
	{
		w0 = swap_coords(w0);
		w1 = swap_coords(w1);
	}
	engine->rend_wall.x0 = x0;
	engine->rend_wall.l = *w;
	while (x0 < x1)
	{
		loop_graf(engine, w0, w1, x0);
		x0++;
	}
}

void			render_graf(t_engine *engine, int sectorno, int i)
{
	t_graf	graf;
	t_fline	w;
	int		t;

	graf = engine->graf[sectorno];
	t = 0;
	while (t < graf.g_num)
	{
		if (graf.wall[t] == i)
		{
			w = graf.coord[t];
			if (transform_wall(engine, &w))
				render_graf2(engine, graf, &w, t);
		}
		t++;
	}
}

void			render_scene(t_engine *engine, int sectorno, int neighbor, int i)
{
	t_ixyz txset;

	rendering_init(engine, sectorno, neighbor);
	txset = tx_wall_mod(engine, sectorno, i);
	loop(engine, neighbor, txset);
	txset = tx_plane_mod(engine, sectorno, i);
	render_hplane(engine, &engine->vpfloor, txset.x);
	render_hplane(engine, &engine->vpceil, txset.y);
	graf_mod(engine, sectorno, i);
	render_graf(engine, sectorno, i);
	engine->edit.mod_w = -1;	//после того как модифицировали стену, нужно сбрасывать, иначе применится ко всем стенам
	render_line((t_line){0, W - 1, 0, 0, 0}, engine->screen, engine->borders);
	render_line((t_line){0, W - 1, H - 1, H - 1, 0}, engine->screen, engine->borders);
}