#include "math_utilits.h"

static void		render_ceil_and_floor(t_engine *engine, int i, t_line *wall,
								   int *y)
{
	y[0] = iclamp(y_for_x(wall[0], i),
				  engine->tline[i], engine->bline[i]) - 1;
	y[1] = iclamp(y_for_x(wall[1], i),
				  engine->tline[i], engine->bline[i]) + 1;
	render_vline((t_line){i, i, engine->tline[i], y[0], wall[0].color},
				 engine->screen);
	render_vline((t_line){i, i, y[1], engine->bline[i], wall[1].color},
				 engine->screen);
}

static void		render_edge(t_engine *engine, int i, t_line *wall, int *y)
{
	y[2] = iclamp(y_for_x(wall[2], i),
				engine->tline[i], engine->bline[i]) - 1;
	y[3] = iclamp(y_for_x(wall[3], i),
				engine->tline[i], engine->bline[i]) + 1;
	engine->tline[i] = iclamp(int_max(y[0], y[2]), engine->tline[i], H - 1);
	engine->bline[i] = iclamp(int_min(y[1], y[3]), 0, engine->bline[i]);
	render_vline((t_line){i, i, y[0], engine->tline[i], wall[2].color},
				engine->screen);	//	верхняя линия раздела
	render_vline((t_line){i, i, engine->bline[i], y[1], wall[3].color},
				 engine->screen);	//	нижняя линия раздела
	render_vline((t_line){i, i, engine->tline[i], engine->bline[i],
				 engine->wall.color}, engine->screen);	//	то, что между ними
}

static void		init_ceil_and_floor(t_engine *engine, t_sector sector,
								 t_line *wall)
{
	float	z;

	z = engine->sectors[engine->player.sector].floor + engine->player.eyeheight;
	wall[0] = perspective_transform(engine->wall, z - sector.ceil,
									engine->player.yaw, 0x0D384F);
	wall[1] = perspective_transform(engine->wall, z - sector.floor,
									engine->player.yaw, 0x4F3B0D);
}

static void		init_edge(t_engine *engine, t_sector sector, t_line *wall)
{
	float	z;

	z = engine->sectors[engine->player.sector].floor + engine->player.eyeheight;
	wall[2] = perspective_transform(engine->wall,z - sector.ceil,
									engine->player.yaw, 0xAAAAAA);
	wall[3] = perspective_transform(engine->wall,z - sector.floor,
									engine->player.yaw, 0xAAAAAA);
}


void			render_wall(t_engine *engine, t_sector sector, int neighbor)
{	//0 потолок, 1 пол, 2 потолок соседа и верхняя линия раздела, 3 пол соседа и нижняя линия раздела
	t_line	wall[4];
	int		y[4];
	int		i;
	int		n;

	init_ceil_and_floor(engine, sector, wall);
	if (neighbor != -1)
		init_edge(engine, engine->sectors[neighbor], wall);
	i = int_max(wall[0].x0, engine->present->x0);	//заполняем в промежутке текущей стены
	n = int_min(wall[0].x1, engine->present->x1);	//иксы у пола и потолка всегда равны
	while (i < n && engine->present->sectorno == engine->player.sector)
	{
		render_ceil_and_floor(engine, i, wall, y);
		if (neighbor != -1)
			render_edge(engine, i, wall, y);
		else
			render_vline((t_line){i, i, y[0], y[1],
					engine->wall.color}, engine->screen); //если нет линий раздела, заполняем полностью
		i++;
	}
}