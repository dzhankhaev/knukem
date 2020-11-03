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

void		tex_init(t_engine *engine)	//	сопоставим координаты текстуры координатам стены после отрезания не попавших в кадр частей
{
	t_fline	w;
	t_fline	ow;

	w = engine->wall;
	ow = engine->ow;
	if (fabsf(w.y1 - w.y0) > fabsf(w.x1 - w.x0))
	{
		engine->u0 = (w.y0 - ow.y0) * engine->img[0].tx->w
					 / (ow.y1 - ow.y0);
		engine->u1 = (w.y1 - ow.y0) * engine->img[0].tx->w
					 / (ow.y1 - ow.y0);
	}
	else
	{
		engine->u0 = (w.x0 - ow.x0) * engine->img[0].tx->w
					 / (ow.x1 - ow.x0);
		engine->u1 = (w.x1 - ow.x0) * engine->img[0].tx->w
					 / (ow.x1 - ow.x0);
	}
}

int			transform_wall(t_engine *engine, int i)
{
	engine->wall = rotate_wall(engine->sectors[engine->present->sectorno],
							engine->player, i, engine->wall.color);
	//после поворота координата X является глубиной
	//Y - положение слева (отрицательный) или справа (положительный)
	if (engine->wall.x0 <= 0 && engine->wall.x1 <= 0)
	{
		engine->wall.color = 0;
		return (0); //стены за спиной не рендерятся
	}
	engine->ow = engine->wall;
	engine->wall = fov_wall_cut(engine->wall);	//обрезаем частично попавшие в поле зрения стены
	tex_init(engine);
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
