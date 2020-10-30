#include "math_utilits.h"

static void		render_ceil_and_floor(t_engine *engine, int x, t_line *wall,
										 int *y, int z)
{
	y[0] = iclamp(y_for_x(wall[0], x),
				  engine->tline[x], engine->bline[x]) - 1;
	y[1] = iclamp(y_for_x(wall[1], x),
				  engine->tline[x], engine->bline[x]) + 1;
	render_vline((t_line){x, x, engine->tline[x], y[0], wall[0].color}, engine->screen);
	render_vline((t_line){x, x, y[1], engine->bline[x], wall[1].color}, engine->screen);
}

static void		render_edge(t_engine *engine, int x, t_line *wall, int *y, int z)
{
	y[2] = iclamp(y_for_x(wall[2], x),
				  engine->tline[x], engine->bline[x]) - 1;
	y[3] = iclamp(y_for_x(wall[3], x),
				  engine->tline[x], engine->bline[x]) + 1;
	render_vline((t_line){x, x, y[0], y[2], get_shadow(z, wall[2].color)}, engine->screen); //	верхняя линия раздела
	render_vline((t_line){x, x, y[3], y[1], get_shadow(z, wall[3].color)}, engine->screen); //	нижняя линия раздела
	engine->tline[x] = iclamp(int_max(y[0], y[2]), engine->tline[x], H - 1);
	engine->bline[x] = iclamp(int_min(y[1], y[3]), 0, engine->bline[x]);
}

static void		init_ceil_and_floor(t_engine *engine, t_sector sector,
								 t_line *wall)
{
	float	z;

	z = engine->sectors[engine->player.sector].floor + engine->player.eyeheight;
	wall[0] = perspective_transform(engine->wall, z - sector.ceil,
									engine->player.vangle, CEIL_COLOR);
	wall[1] = perspective_transform(engine->wall, z - sector.floor,
									engine->player.vangle, FLOOR_COLOR);
}

static void		init_edge(t_engine *engine, t_sector sector, t_line *wall)
{
	float	z;

	z = engine->sectors[engine->player.sector].floor + engine->player.eyeheight;
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
	x0 = int_max(wall[0].x0, engine->present->x0);	//заполняем в промежутке текущей стены
	x1 = int_min(wall[0].x1, engine->present->x1);	//иксы у пола и потолка всегда равны
	if (neighbor != -1)
	{
		if ((x1 > x0) && engine->future + 1 != engine->queue + engine->max_queue)
		{
			if (check_repeat(engine, sectorno, neighbor))
				*(engine->future++) = (t_queue){neighbor, x0, x1, sectorno};
		}
		init_edge(engine, engine->sectors[neighbor], wall);
	}
	while (x0 < x1)
	{
		z = color_distance(engine, wall[0], x0);
		render_ceil_and_floor(engine, x0, wall, y, z);
		if (neighbor != -1)
			render_edge(engine, x0, wall, y, z);
		else
		{
			render_vline((t_line){x0, x0, y[0], y[1], get_shadow(z, engine->wall.color)}, engine->screen); //если стена, заполняем полностью
		}
		x0++;
	}

}
