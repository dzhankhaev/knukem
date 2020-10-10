#include "engine.h"
#include "arg_defines.h"
#include "math_utilits.h"

static int	check_repeating(t_queue *queue, unsigned max_queue, int c)
{
	for (int i = 0; i < max_queue; i++)
	{
		if (queue[i].sectorno == c)
			return 0;
	}
	return 1;
}

static int	minimap_set_line_color(t_engine *engine, unsigned s, int color)
{
	if (fabsf(engine->sectors[s].floor
	- engine->sectors[engine->player.sector].floor) < floor_diff)
		return (color);
	return (0);
}

static t_fline swap(t_fline wall)
{
	float	t;

	if (wall.y0 > wall.y1)
	{
		t = wall.x0;
		wall.x0 = wall.x1;
		wall.x1 = t;
		t = wall.y0;
		wall.y0 = wall.y1;
		wall.y1 = t;
	}
	return (wall);
}

static t_fline check(t_fline wall, t_xy i1, t_xy i2)
{
	wall = swap(wall);
	if (i1.x != -1)
	{
		if (fabsf(wall.x0 - wall.x1) > fabsf(wall.y0 - wall.y1)
		&& wall.x0 > wall.x1)
		{
			wall.x1 = i1.x;
			wall.y1 = i1.y;
		}
		else
		{
			wall.x0 = i1.x;
			wall.y0 = i1.y;
		}
	}
	if (i2.x != -1)
	{
		if (fabsf(wall.x0 - wall.x1) < fabsf(wall.y0 - wall.y1)
		|| wall.x0 > wall.x1)
		{
			wall.x1 = i2.x;
			wall.y1 = i2.y;
		}
		else
		{
			wall.x0 = i2.x;
			wall.y0 = i2.y;
		}
	}
	return (wall);
}

t_fline fov_raycast(t_engine *engine, float angle)
{
	t_fline	wall;

	wall = (t_fline){0,
					 50.f * cosf(angle),
					 0,
					 50.f * sinf(angle),
					 0x0000FF};
	minimap(engine, (t_xy){wall.x0, wall.y0},
			(t_xy){wall.x1, wall.y1}, wall.color);
	return (wall);
}

void	check_wall_behind(t_engine *engine, int color)
{
	float	arg[8];
	t_xy	i1;
	t_xy	i2;
	t_fline	twall;

	engine->wall.color = color;
	twall = fov_raycast(engine, LFOV);
	X1 = twall.x0;
	X2 = twall.x1;
	X3 = engine->wall.x0;
	X4 = engine->wall.x1;
	Y1 = twall.y0;
	Y2 = twall.y1;
	Y3 = engine->wall.y0;
	Y4 = engine->wall.y1;
	i1 = intersection_point(arg);
	twall = fov_raycast(engine, RFOV);
	X1 = twall.x0;
	X2 = twall.x1;
	X3 = engine->wall.x0;
	X4 = engine->wall.x1;
	Y1 = twall.y0;
	Y2 = twall.y1;
	Y3 = engine->wall.y0;
	Y4 = engine->wall.y1;
	i2 = intersection_point(arg);
	engine->wall = check(engine->wall, i1, i2);
	minimap(engine, (t_xy){engine->wall.x0, engine->wall.y0},
				(t_xy){engine->wall.x1, engine->wall.y1}, engine->wall.color);
}

void		render_wall(t_engine *engine, int i, int color)
{
	t_sector sector;

	sector = engine->sectors[engine->present->sectorno];
	engine->wall = normi_wall(sector, engine->player, i);
	engine->wall = rotate_wall(engine->wall, engine->player);
	if (engine->wall.x0 <= 0 && engine->wall.x1 <= 0)
	{
		engine->wall.color = 0;
		return ; //стены за спиной не рендерятся
	}
	check_wall_behind(engine, color);
}

void 		fill_queue(t_engine *engine)
{
	int		color;
	int		i;
	t_queue	*present;

	present = engine->present;
	i = 0;
	while (i < engine->sectors[present->sectorno].npoints)
	{
		if (engine->sectors[present->sectorno].neighbors[i] == -1)
			color = minimap_set_line_color(engine, present->sectorno, 0xFFFFFF);
		else
		{
			color = minimap_set_line_color(engine, present->sectorno, 0xFF4444);
			if (engine->future + 1 != engine->queue + engine->max_queue
	&& check_repeating(engine->queue, engine->max_queue,
	engine->sectors[present->sectorno].neighbors[i]))
				(++engine->future)->sectorno =
						engine->sectors[present->sectorno].neighbors[i];
		}
//		minimap(engine, engine->sectors[present->sectorno].vertex[i],
//				engine->sectors[present->sectorno].vertex[i + 1], color);
		render_wall(engine, i, color);
		i++;
	}
}