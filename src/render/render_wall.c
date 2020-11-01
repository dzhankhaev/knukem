#include "utilits.h"

static void		render_ceil_and_floor(t_engine *engine, int x, t_line *wall,
										 int *y, int z)
{
	y[0] = iclamp(y_for_x(wall[0], x),
				  engine->tline[x], engine->bline[x]);		//линия потолка тек
	y[1] = iclamp(y_for_x(wall[1], x),
				  engine->tline[x], engine->bline[x]);		//линия пола тек
	render_vline((t_line){x, x, engine->tline[x], y[0], wall[0].color}, engine->screen);	//потолок
	render_vline((t_line){x, x, y[1], engine->bline[x], wall[1].color}, engine->screen);	//пол
}

static void		render_edge(t_engine *engine, int x, t_line *wall, int *y, int z)
{
	y[2] = iclamp(y_for_x(wall[2], x),
				  engine->tline[x], engine->bline[x]);		//линия потолка соседа
	y[3] = iclamp(y_for_x(wall[3], x),
				  engine->tline[x], engine->bline[x]);		//линия пола соседа
	//imin(y[2], y[1]) если потолок соседа ниже пола, то рисуем до пола, иначе до потолка
	render_vline((t_line){x, x, y[0], imin(y[2], y[1]), get_shadow(z, wall[2].color)}, engine->screen); //	верхняя линия раздела
	//imax(y[3], y[0]) если пол соседа выше потолка, то рисуем до потолка, иначе до пола
	render_vline((t_line){x, x, imax(y[3], y[0]), y[1], get_shadow(z, wall[3].color)}, engine->screen); //	нижняя линия раздела
	engine->tline[x] = iclamp(imax(y[0], y[2]), engine->tline[x], H - 1);
	engine->bline[x] = iclamp(imin(y[1], y[3]), 0, engine->bline[x]);
}

static void		init_ceil_and_floor(t_engine *engine, t_sector sector,
								 t_line *wall)
{
	float	z;

	z = engine->player.where.z;
	wall[0] = perspective_transform(engine->wall, z - sector.ceil,
									engine->player.vangle, CEIL_COLOR);
	wall[1] = perspective_transform(engine->wall, z - sector.floor,
									engine->player.vangle, FLOOR_COLOR);
}

static void		init_edge(t_engine *engine, t_sector sector, t_line *wall)
{
	float	z;

	z = engine->player.where.z;
	wall[2] = perspective_transform(engine->wall,z - sector.ceil,
									engine->player.vangle, TOP_COLOR);
	wall[3] = perspective_transform(engine->wall,z - sector.floor,
									engine->player.vangle, BOT_COLOR);
}

void			render_wall(t_engine *engine, int sectorno, int neighbor)
{	//0 потолок, 1 пол, 2 потолок соседа и верхняя линия раздела, 3 пол соседа и нижняя линия раздела
	//соседи отображаются нак грани текущего сектора, если они имеют общую грань
	t_line		wall[4];
	int			y[4];
	int			x0;
	int			x1;
	int 		z;

	init_ceil_and_floor(engine, engine->sectors[sectorno], wall);
	//потребуется для вычисления света. Для других вычислений нужно упорядочить
	t_line w = (t_line){wall[0].x0, wall[0].x1, wall[0].y0, wall[0].y1};
	//стены строго вертикально, потому у 0 и 1 иксы одинаковы
	x0 = imax(imin(wall[0].x0, wall[0].x1), engine->present->x0);			//заполняем в промежутке текущей стены
	x1 = imin(imax(wall[1].x0, wall[1].x1), engine->present->x1);			//иксы у пола и потолка всегда равны
	if (neighbor != -1)
	{
		if ((x1 > x0) && engine->future + 1 != engine->queue + engine->max_queue &&
			check_repeat(engine, sectorno, neighbor))
			*(engine->future++) = (t_queue){neighbor, x0, x1, sectorno};
		init_edge(engine, engine->sectors[neighbor], wall);
	}
	to_x_order(wall);
	while (x0 < x1)
	{
		z = color_distance(engine, w, x0);
		render_ceil_and_floor(engine, x0, wall, y, 0);
		if (neighbor != -1)
			render_edge(engine, x0, wall, y, z);
		else
			render_vline((t_line){x0, x0, y[0], y[1], get_shadow(z, engine->wall.color)}, engine->screen); //если стена, заполняем полностью
		x0++;
	}

}
