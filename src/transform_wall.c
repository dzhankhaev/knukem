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

t_xyz	rot_y(t_xyz p, float gamma)
{
	float	x;
	float	z;

	x = p.x;
	z = p.z;
//	p.x = x * cosf(gamma) + z * sinf(gamma);
	p.z = -x * sinf(gamma) + z * cosf(gamma);
	return (p);
}

static t_line	swap_coords(t_line p)
{
	int t;

	t = p.x0;
	p.x0 = p.x1;
	p.x1 = t;
	t = p.y0;
	p.y0 = p.y1;
	p.y1 = t;
	return (p);
}

t_line	perspective_transform(t_engine *engine, float height, int color)
{
	t_line	wall;
	float	z;
	t_xyz	p0;
	t_xyz	p1;

	wall.color = color;
	z = engine->sectors[engine->player.sector].floor
			+ engine->player.eyeheight - height;
	p0 = rot_y((t_xyz){engine->wall.x0, engine->wall.y0, z},
			engine->player.yaw);
	p1 = rot_y((t_xyz){engine->wall.x1, engine->wall.y1, z},
			engine->player.yaw);
	wall.x0 = (int)((W >> 1) + p0.y / p0.x * (W >> 1));
	wall.x1 = (int)((W >> 1) + p1.y / p1.x * (W >> 1));
	wall.y0 = (int)((H >> 1) + p0.z / p0.x * (H >> 1));
	wall.y1 = (int)((H >> 1) + p1.z / p1.x * (H >> 1));
	return (wall);
}

int				calculate_y_for_x(t_line wall, int x)
{
	int y;

	y = (x - wall.x0) * (wall.y1 - wall.y0) / (wall.x1 - wall.x0) + wall.y0;
	return (y);
}

void			render_walls(t_engine *engine, t_sector sector)
{
	t_line	wall[2];
	int		y[2];
	int		i;
	int		top_line[W] = {0};
	int 	bottom_line[W];

	i = 0;
	while (i < W)
		bottom_line[i++] = H - 1;
	wall[0] = perspective_transform(engine, sector.ceil, 0x4455FF);
	wall[1] = perspective_transform(engine, sector.floor, 0x44ff44);
	if (wall[0].x1 < wall[0].x0)
		wall[0] = swap_coords(wall[0]);
	i = wall[0].x0;
	while (i < wall[0].x1 && engine->present->sectorno == engine->player.sector)
	{
		y[0] = iclamp(calculate_y_for_x(wall[0], i), top_line[i], bottom_line[i]) - 1;
		y[1] = iclamp(calculate_y_for_x(wall[1], i), top_line[i], bottom_line[i]) + 1;
		render_vline((t_line){i, i, top_line[i], y[0], wall[0].color}, engine->screen);
		render_vline((t_line){i, i, y[1], bottom_line[i], wall[1].color}, engine->screen);
		render_vline((t_line){i, i, y[0], y[1], engine->wall.color}, engine->screen);
		i++;
	}
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
	render_walls(engine, sector);
}
