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
//	p.z = -x * sinf(gamma) + z * cosf(gamma);
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

static void		vline(t_line p, SDL_Surface *screen)
{
	int	*temp;

	temp = (int *)screen->pixels;
	p.y0 = p.y0 < 0 ? 0 : p.y0;
	p.y0 = p.y0 > H - 1 ? H - 1 : p.y0;
	p.y1 = p.y1 > H - 1 ? H - 1 : p.y1;
	p.y1 = p.y1 < 0 ? 0 : p.y1;
	while (p.y0 < p.y1)
	{
//		if (p.y0 >= 0 && p.y0 < H - 1)
			temp[(p.y0 * W) + p.x0] = p.color;
		p.y0++;
	}
}

void			render_wall_borders(t_engine *engine, t_sector sector)
{
	t_line	wall;
	t_line	wall2;
	float	z;
	t_xyz	p0;
	t_xyz	p1;
	int		i;
	int		ytop[W];
	int 	ybottom[W];

	for(int ii = 0; ii < W; ii++)
	{
		ytop[ii] = 0;
		ybottom[ii] = H - 1;
	}
	wall.color = engine->wall.color;
	wall2.color = engine->wall.color;
	z = engine->sectors[engine->player.sector].floor + engine->player.eyeheight - sector.ceil;
	p0 = rot_y((t_xyz){engine->wall.x0, engine->wall.y0, z}, engine->player.yaw);
	p1 = rot_y((t_xyz){engine->wall.x1, engine->wall.y1, z}, engine->player.yaw);
	wall2.x0 = (int)((W >> 1) + p0.y / p0.x * (W >> 1));
	wall2.x1 = (int)((W >> 1) + p1.y / p1.x * (W >> 1));
	wall2.y0 = (int)((H >> 1) + p0.z / p0.x * (H >> 1));
	wall2.y1 = (int)((H >> 1) + p1.z / p1.x * (H >> 1));
	z = engine->sectors[engine->player.sector].floor + engine->player.eyeheight - sector.floor;
	p0 = rot_y((t_xyz){engine->wall.x0, engine->wall.y0, z}, engine->player.yaw);
	p1 = rot_y((t_xyz){engine->wall.x1, engine->wall.y1, z}, engine->player.yaw);
	wall.x0 = (int)((W >> 1) + p0.y / p0.x * (W >> 1));
	wall.x1 = (int)((W >> 1) + p1.y / p1.x * (W >> 1));
	wall.y0 = (int)((H >> 1) + p0.z / p0.x * (H >> 1));
	wall.y1 = (int)((H >> 1) + p1.z / p1.x * (H >> 1));

	if (wall.x1 < wall.x0)
		wall = swap_coords(wall);
	i = wall.x0;
	while (i < wall.x1 && engine->present->sectorno == engine->player.sector)
	{
		int ya = (i - wall2.x0) * (wall2.y1 - wall2.y0) / (wall2.x1 - wall2.x0) + wall2.y0;
		int yb = (i - wall.x0) * (wall.y1 - wall.y0) / (wall.x1 - wall.x0) + wall.y0;
		int cya = iclamp(ya, ytop[i], ybottom[i]);
		int cyb = iclamp(yb, ytop[i], ybottom[i]);
		vline((t_line){i, i, ytop[i], cya - 1, 0x4455FF}, engine->screen);
		vline((t_line){i, i, cyb + 1, ybottom[i], 0x44ff44}, engine->screen);
		vline((t_line){i, i, cya - 1, cyb + 1, engine->wall.color}, engine->screen);
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
	render_wall_borders(engine, sector);
}
