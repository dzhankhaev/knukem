#include "engine.h"
#include "math_utilits.h"

static t_fline	fov_raycast(t_engine *engine, float angle)
{
	t_fline	wall;

	wall = (t_fline){0,
					 50.f * cosf(angle),
					 0,
					 50.f * sinf(angle),
					 0x0000FF};
	//это миникарта для просмотра отсеченных стен (лучи)
	minimap(engine, (t_xy){wall.x0, wall.y0},
			(t_xy){wall.x1, wall.y1}, wall.color);
	return (wall);
}

static void		fov_wall_cut(t_engine *engine)
{
	t_xy	i1;
	t_xy	i2;
	//пересечение между лучом зрения и стеной
	i1 = intersection_point(engine->wall, fov_raycast(engine, LFOV));
	i2 = intersection_point(engine->wall, fov_raycast(engine, RFOV));
	engine->wall = wall_cut(engine->wall, i1, i2);
	//это миникарта для просмотра отсеченных стен
	minimap(engine, (t_xy){engine->wall.x0, engine->wall.y0},
			(t_xy){engine->wall.x1, engine->wall.y1}, engine->wall.color);
}

void			transform_wall(t_engine *engine, int i)
{
	t_sector sector;

	sector = engine->sectors[engine->present->sectorno];
	engine->wall = normi_wall(sector, engine->player, i, engine->wall.color);
	engine->wall = rotate_wall(engine->wall, engine->player);
	if (engine->wall.x0 <= 0 && engine->wall.x1 <= 0)
		return ; //стены за спиной не рендерятся
	fov_wall_cut(engine);
}