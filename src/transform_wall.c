#include "engine.h"
#include "math_utilits.h"

static t_fline	fov_raycast(t_engine *engine, float point_x, float point_y)
{
	t_fline	wall;

	wall = (t_fline){0, point_x, 0, point_y, 0x0000FF};
	//это миникарта для просмотра отсеченных стен (лучи видимости)
	minimap(engine, (t_xy){wall.x0, wall.y0},
			(t_xy){wall.x1, wall.y1}, wall.color);
	return (wall);
}

static void		fov_wall_cut(t_engine *engine)
{
	t_xy	i1;
	t_xy	i2;
	//пересечение между лучом видимости и стеной
	i1 = intersection_point(engine->wall,
						 fov_raycast(engine, RAY_POINT_X, -RAY_POINT_Y));
	i2 = intersection_point(engine->wall,
						 fov_raycast(engine, RAY_POINT_X, RAY_POINT_Y));
	engine->wall = cut_wall(engine->wall, i1, i2);
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
	if (engine->wall.x0 <= 0 || engine->wall.x1 <= 0
	|| engine->wall.x0 * -K >= engine->wall.y0
	|| engine->wall.x1 * K <= engine->wall.y1)
		return ; //то что не было отрезано и находится частично за спиной, а так же то что целиком лежит вне видимости тоже не рендерим.
	//это миникарта для просмотра отсеченных стен
	minimap(engine, (t_xy){engine->wall.x0, engine->wall.y0},
			(t_xy){engine->wall.x1, engine->wall.y1}, engine->wall.color);
}