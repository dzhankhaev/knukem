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

void			graf_memalloc(t_engine *engine, int sectorno, int neighbor, int i)
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
	graf->wall[graf->g_num - 1] = neighbor;
	graf->z[graf->g_num - 1] = engine->player.where.z;
	graf->coord[graf->g_num - 1] =
			(t_fline){engine->sectors[sectorno].vertex[i].x,
					  engine->sectors[sectorno].vertex[i + 1].x,
					  engine->sectors[sectorno].vertex[i].y,
					  engine->sectors[sectorno].vertex[i + 1].y};
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

void			graf_mod(t_engine *engine, int sectorno, int neighbor, int i)
{
	if (engine->edit.mod_w != -1 && engine->edit.graf != -1)
	{
		if (engine->sectors[sectorno].neighbors[i] <= -1)
		{
			graf_memalloc(engine, sectorno, neighbor, i);
			create_coord(engine, sectorno);
		}
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
	graf_mod(engine, sectorno, neighbor, i);

	if (engine->graf[sectorno].sectorno != -1)
	{
		int t = 0;
		while (t < engine->graf[sectorno].g_num)
		{
			if (engine->graf[sectorno].wall[t] == neighbor)
			{
				t_fline	g;
				t_fline	w;
				g.x0 = engine->graf[sectorno].coord[t].x0 - engine->player.where.x;
				g.y0 = engine->graf[sectorno].coord[t].y0 - engine->player.where.y;
				g.x1 = engine->graf[sectorno].coord[t].x1 - engine->player.where.x;
				g.y1 = engine->graf[sectorno].coord[t].y1 - engine->player.where.y;

				w = g;
				g.x0 = w.x0 * engine->player.anglecos + w.y0 * engine->player.anglesin;
				g.x1 = w.x1 * engine->player.anglecos + w.y1 * engine->player.anglesin;
				g.y0 = -w.x0 * engine->player.anglesin + w.y0 * engine->player.anglecos;
				g.y1 = -w.x1 * engine->player.anglesin + w.y1 * engine->player.anglecos;

				t_xyz p0 = (t_xyz){engine->graf[sectorno].coord[t].x0,
								  engine->graf[sectorno].coord[t].y0,
								  engine->graf[sectorno].z[t]};
				t_xyz p1 = (t_xyz){engine->graf[sectorno].coord[t].x1,
								   engine->graf[sectorno].coord[t].y1,
								   engine->graf[sectorno].z[t]};
				p0.z = p0.z + p0.x * engine->player.vangle;
				p1.z = p1.z + p1.x * engine->player.vangle;
				t_line ig;
				ig.x0 = (int)((W >> 1) + p0.y / p0.x * (W >> 1));
				ig.x1 = (int)((W >> 1) + p1.y / p1.x * (W >> 1));
				ig.y0 = (int)((H >> 1) + p0.z / p0.x * (H >> 1));
				ig.y1 = (int)((H >> 1) + p1.z / p1.x * (H >> 1));
				ig.color = 0x00ff00;

			}
			t++;
		}

	}

	engine->edit.mod_w = -1;	//после того как модифицировали стену, нужно сбрасывать, иначе применится ко всем стенам
}