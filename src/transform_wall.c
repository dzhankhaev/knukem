#include "engine.h"
#include "math_utilits.h"

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

static void		render_perpendicular_line(t_line p, SDL_Surface *screen, t_line borders)
{
	int	*temp;

	temp = (int *)screen->pixels;
	while (p.y0 < p.y1)
	{
		if (p.x0 >= borders.x0 && p.x0 < borders.x1
			&& p.y0 >= borders.y0 && p.y0 < borders.y1)
			temp[(p.y0 * W) + p.x0] = p.color;
		p.y0++;
	}
}

/*
void			render_wall(t_engine *engine, t_sector sector)
{
	t_line	wall;

	wall.color = engine->wall.color;
	float z = sector.ceil - sector.floor;
	int x0 = H / 2 + (z / engine->wall.x0) * (H / 2);
	int x1 = H / 2 + (z / engine->wall.x1) * (H / 2);
	int y0 = W / 2 + (engine->wall.y0 / engine->wall.x0) * (W / 2);
	int y1 = W / 2 + (engine->wall.y1 / engine->wall.x1) * (W / 2);
	for (int i = y0; i < y1; i++)
	{
		wall.x0 = i;
		wall.x1 = i;
		wall.y0 = x0;
		wall.y1 = x1;
//		render_perpendicular_line(wall, engine->screen, engine->borders);
	}
}
*/

void			render_wall(t_engine *engine, t_sector sector)
{
	t_line	wall;

	wall.color = engine->wall.color;
	float z = engine->sectors[engine->player.sector].floor - sector.floor + engine->player.eyeheight;
	wall.x0 = (int)(W / 2.f + engine->wall.y0 / engine->wall.x0 * (W / 2.f));
	wall.x1 = (int)(W / 2.f + engine->wall.y1 / engine->wall.x1 * (W / 2.f));
	wall.y0 = (int)(z / engine->wall.x0 * (H / 2.f));
	wall.y1 = (int)(z / engine->wall.x1 * (H / 2.f));
	render_line(wall, engine->screen, engine->borders);
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
	|| engine->wall.x0 * -K > engine->wall.y0
	|| engine->wall.x1 * K < engine->wall.y1)
	{
		engine->wall.color = 0;
		return ; //то что не было отрезано и находится частично за спиной, а так же то что целиком лежит вне видимости тоже не рендерим.
	}
	render_wall(engine, sector);
}