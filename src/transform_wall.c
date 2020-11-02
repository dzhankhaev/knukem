#include "engine.h"
#include "utilits.h"

static t_fline	fov_wall_cut(t_fline wall)
{
	t_xy	i1;
	t_xy	i2;
	//пересечение между лучом видимости и стеной
	i1 = intersection_point(wall,
		(t_fline){0, RAY_POINT_X, 0, -RAY_POINT_Y});
	i2 = intersection_point(wall,
		(t_fline){0, RAY_POINT_X, 0, RAY_POINT_Y});
	return (cut_wall(wall, i1, i2));
}

void		save_wall_position(t_engine *engine)
{
	engine->w = engine->wall;
	engine->w.x0 = engine->wall.x0 + engine->player.where.x;
	engine->w.y0 = engine->wall.y0 + engine->player.where.y;
	engine->w.x1 = engine->wall.x1 + engine->player.where.x;
	engine->w.y1 = engine->wall.y1 + engine->player.where.y;
}

int			transform_wall(t_engine *engine, int i)
{
	engine->w = engine->wall;
	engine->wall = rotate_wall(engine->sectors[engine->present->sectorno],
							engine->player, i, engine->wall.color);
	//после поворота координата X является глубиной
	//Y - положение слева (отрицательный) или справа (положительный)
	if (engine->wall.x0 <= 0 && engine->wall.x1 <= 0)
	{
		engine->wall.color = 0;
		return (0); //стены за спиной не рендерятся
	}
//	save_wall_position(engine);
	engine->wall = fov_wall_cut(engine->wall);
	//обрезаем частично попавшие в поле зрения стены
	if (engine->wall.x0 <= 0 || engine->wall.x1 <= 0
	|| engine->wall.x0 * -K > engine->wall.y0
	|| engine->wall.x1 * K < engine->wall.y1)
	{
		engine->wall.color = 0;
		return (0); //то что не было отрезано и находится частично за спиной, а так же то что целиком лежит вне видимости тоже не рендерим.
	}
	if (engine->edit.mod_s == -1 &&
		determine_intersection(engine->wall, (t_fline){0, 50, 0, 0}))
		engine->edit.mod_s =
				engine->sectors[engine->present->sectorno].neighbors[i];	//этот сектор можно модифицировать
	return (1);
}
