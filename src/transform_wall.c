#include "engine.h"
#include "math_utilits.h"

static t_fline	fov_raycast(float point_x, float point_y)
{
	return ((t_fline){0, point_x, 0, point_y, 0x0000FF});
}

static t_fline	fov_wall_cut(t_fline wall)
{
	t_xy	i1;
	t_xy	i2;
	//пересечение между лучом видимости и стеной
	i1 = intersection_point(wall, fov_raycast(RAY_POINT_X, -RAY_POINT_Y));
	i2 = intersection_point(wall, fov_raycast(RAY_POINT_X, RAY_POINT_Y));
	return (cut_wall(wall, i1, i2));
}

void			transform_wall(t_engine *engine, int i)
{
	t_sector sector;

	sector = engine->sectors[engine->present->sectorno];
	engine->wall = normi_wall(sector, engine->player, i, engine->wall.color);
	engine->wall = rotate_wall(engine->wall, engine->player);
	if (engine->wall.x0 <= 0 && engine->wall.x1 <= 0)
	{
		engine->wall.color = 0;
		return ; //стены за спиной не рендерятся
	}
	engine->wall = fov_wall_cut(engine->wall);
	if (engine->wall.x0 <= 0 || engine->wall.x1 <= 0
	|| engine->wall.x0 * -K >= engine->wall.y0
	|| engine->wall.x1 * K <= engine->wall.y1)
	{
		engine->wall.color = 0;
		return ; //то что не было отрезано и находится частично за спиной, а так же то что целиком лежит вне видимости тоже не рендерим.
	}

}