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


void fff(t_engine *engine, t_line p);


void	angle_less_1(t_line p, t_engine *engine)
{
	t_delta	d;
	int		a;

	d.dx = abs(p.x1 - p.x0);
	d.dy = abs(p.y1 - p.y0);
	d.error = 0;
	d.derror = d.dy + 1;
	a = SDL_GetTicks();
	while (p.x0 < p.x1 && SDL_GetTicks() - a < 5)
	{

		fff(engine, p);
		d.error += d.derror;
		if (d.error >= d.dx + 1)
		{
			p.y0++;
			d.error -= d.dx + 1;
		}
		p.x0++;
	}
}

void	angle_more_1(t_line p, t_engine *engine)
{
	t_delta	d;
	int		a;

	d.dx = abs(p.x1 - p.x0);
	d.dy = abs(p.y1 - p.y0);
	d.error = 0;
	d.derror = d.dx + 1;
	a = SDL_GetTicks();
	while (p.y0 < p.y1 && SDL_GetTicks() - a < 5)
	{

		fff(engine, p);
		d.error += d.derror;
		if (d.error >= d.dy + 1)
		{
			p.x0++;
			d.error -= d.dy + 1;
		}
		p.y0++;
	}
}

void	angle_less_2(t_line p, t_engine *engine)
{
	t_delta	d;
	int		a;

	d.dx = abs(p.x1 - p.x0);
	d.dy = abs(p.y1 - p.y0);
	d.error = 0;
	d.derror = d.dy + 1;
	a = SDL_GetTicks();
	while (p.x0 > p.x1 && SDL_GetTicks() - a < 5)
	{

		fff(engine, p);
		d.error += d.derror;
		if (d.error >= d.dx + 1)
		{
			p.y0++;
			d.error -= d.dx + 1;
		}
		p.x0--;
	}
}

void	angle_more_2(t_line p, t_engine *engine)
{
	t_delta	d;
	int		a;

	d.dx = abs(p.x1 - p.x0);
	d.dy = abs(p.y1 - p.y0);
	d.error = 0;
	d.derror = d.dx + 1;
	a = SDL_GetTicks();
	while (p.y0 > p.y1 && SDL_GetTicks() - a < 5)
	{
		fff(engine, p);
		d.error += d.derror;
		if (d.error >= d.dy + 1)
		{
			p.x0++;
			d.error -= d.dy + 1;
		}
		p.y0--;
	}
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

static void		perpendicular_line(t_engine *engine, t_line p)
{
	int	a;

	a = SDL_GetTicks();
	if (p.x0 == p.x1)
	{
		p = p.y0 > p.y1 ? swap_coords(p) : p;
		if (engine->key == 0)
			fff(engine, p);
		while (p.y0 < p.y1 && SDL_GetTicks() - a < 5)
			p.y0++;
		if (engine->key == 1)
			fff(engine, p);
	}
	else
	{
		p = p.x0 > p.x1 ? swap_coords(p) : p;
		while (p.x0 < p.x1 && SDL_GetTicks() - a < 5)
		{
			fff(engine, p);
			p.x0++;
		}
	}
}

void			brazenheim(t_line p, t_engine *engine)
{
	if (p.x0 > p.x1)
		p = swap_coords(p);
	if (p.x0 == p.x1 || p.y0 == p.y1)
		perpendicular_line(engine, p);
	else if (p.y0 < p.y1)
	{
		if (abs(p.x1 - p.x0) > abs(p.y1 - p.y0))
			angle_less_1(p, engine);
		else
			angle_more_1(p, engine);
	}
	else
	{
		if (abs(p.x1 - p.x0) > abs(p.y1 - p.y0))
			angle_less_2(swap_coords(p), engine);
		else
			angle_more_2(p, engine);
	}
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

void fff(t_engine *engine, t_line p)
{
	if (engine->key == 0)
	{
		engine->top_line[p.x0] = p.y0;
	}
	else
	{
		engine->bottom_line[p.x0] = p.y0;
	}
}

t_line			calc_floor_and_ceil(t_engine *engine, t_sector sector)
{
	float	z;
	t_xyz	p0;
	t_xyz	p1;
	t_line	wall;

	wall.color = engine->wall.color;
	z = engine->sectors[engine->player.sector].floor + engine->player.eyeheight - sector.ceil;
	p0 = rot_y((t_xyz){engine->wall.x0, engine->wall.y0, z}, engine->player.yaw);
	p1 = rot_y((t_xyz){engine->wall.x1, engine->wall.y1, z}, engine->player.yaw);
	wall.x0 = (int)((W >> 1) + p0.y / p0.x * (W >> 1));
	wall.x1 = (int)((W >> 1) + p1.y / p1.x * (W >> 1));
	wall.y0 = (int)((H >> 1) + p0.z / p0.x * (H >> 1));
	wall.y1 = (int)((H >> 1) + p1.z / p1.x * (H >> 1));
	engine->key = 0;
	brazenheim(wall, engine);
	z = engine->sectors[engine->player.sector].floor + engine->player.eyeheight - sector.floor;
	p0 = rot_y((t_xyz){engine->wall.x0, engine->wall.y0, z}, engine->player.yaw);
	p1 = rot_y((t_xyz){engine->wall.x1, engine->wall.y1, z}, engine->player.yaw);
	wall.x0 = (int)((W >> 1) + p0.y / p0.x * (W >> 1));
	wall.x1 = (int)((W >> 1) + p1.y / p1.x * (W >> 1));
	wall.y0 = (int)((H >> 1) + p0.z / p0.x * (H >> 1));
	wall.y1 = (int)((H >> 1) + p1.z / p1.x * (H >> 1));
	engine->key = 1;
	brazenheim(wall, engine);
	return (wall);
}

void			render_wall_borders(t_engine *engine, t_sector sector)
{
	t_line	wall;
	int		i;

	wall = calc_floor_and_ceil(engine, sector);
	if (wall.x1 < wall.x0)
		wall = swap_coords(wall);
	i = wall.x0;
	while (i < wall.x1 && engine->present->sectorno == engine->player.sector)
	{
		vline((t_line){i, i, 0, engine->top_line[i], 0x4455FF}, engine->screen);
		vline((t_line){i, i, engine->bottom_line[i], H, 0x44ff44}, engine->screen);
		vline((t_line){i, i, engine->top_line[i], engine->bottom_line[i], engine->wall.color}, engine->screen);
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
//	render_wall_borders(engine, sector);
}

/*

void fff(t_engine *engine, t_line p)
{
	static int a;
	static int b;
	if (engine->key == 0)
	{
		if (p.y0 > engine->top_line[p.x0])
		{
			engine->tline[p.x0] = p.y0;
		}
		else
		{
			engine->top_line[p.x0] = p.y0;
			engine->tline[p.x0] = p.y0;
		}
	}
	else
	{
		if (p.y0 < engine->bottom_line[p.x0])
		{
			engine->bline[p.x0] = p.y0;
		}
		else
		{
			engine->bottom_line[p.x0] = p.y0;
			engine->bline[p.x0] = p.y0;
		}
	}
}
 */