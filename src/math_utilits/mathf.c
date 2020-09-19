#include "math_utilits.h"

int	int_min(int a, int b)
{
	return (((a) < (b)) ? (a) : (b));
}

int	int_max(int a, int b)
{
	return (((a) > (b)) ? (a) : (b));
}

int clamp(int a, int min, int max)
{
	return int_min(int_max(a, min), max);
}

/*


t_line	rotate_coords(t_engine *engine, t_line wall)
{
	t_line	w;

	wall.x0 = wall.x0 - engine->player.where.x;
	wall.y0 = wall.y0 - engine->player.where.y;
	wall.x1 = wall.x1 - engine->player.where.x;
	wall.y1 = wall.y1 - engine->player.where.y;
	w = wall;
	wall.x0 = w.x0 * engine->player.anglecos +
			  w.y0 * engine->player.anglesin;
	wall.x1 = w.x1 * engine->player.anglecos +
			  w.y1 * engine->player.anglesin;
	wall.y0 = -w.x0 * engine->player.anglesin +
			  w.y0 * engine->player.anglecos;
	wall.y1 = -w.x1 * engine->player.anglesin +
			  w.y1 * engine->player.anglecos;
	return wall;
}

void minimap(t_engine *engine, t_line wall)
{
	t_line	w;

	wall.x0 = (wall.x0 * W / 50) - (W / 50 * engine->player.where.x);
	wall.y0 = (wall.y0 * W / 50) - (W / 50 * engine->player.where.y);
	wall.x1 = (wall.x1 * W / 50) - (W / 50 * engine->player.where.x);
	wall.y1 = (wall.y1 * W / 50) - (W / 50 * engine->player.where.y);
	w = wall;
	wall.x0 = w.x0 * engine->player.anglecos +
			  w.y0 * engine->player.anglesin;
	wall.x1 = w.x1 * engine->player.anglecos +
			  w.y1 * engine->player.anglesin;
	wall.y0 = -w.x0 * engine->player.anglesin +
			  w.y0 * engine->player.anglecos;
	wall.y1 = -w.x1 * engine->player.anglesin +
			  w.y1 * engine->player.anglecos;


	t_xy	minimap_point;
	minimap_point.x = W / 2;
	minimap_point.y = H / 2;
	wall.x0 = wall.x0 + minimap_point.x;
	wall.y0 = wall.y0 + minimap_point.y;
	wall.x1 = wall.x1 + minimap_point.x;
	wall.y1 = wall.y1 + minimap_point.y;
	render_line(wall, engine->screen);
}

int check_repeating(unsigned *queue, int c)
{
	for (int i = 0; i < 32; i++)
	{
		if (queue[i] == c)
			return 0;
	}
	return 1;
}

void wall1(t_engine *engine, unsigned s)
{
	t_line	wall;

	int i = 0;
	t_xy *vertex;
	while (i < engine->sectors[s].npoints)
	{
		if (engine->sectors[s].neighbors[i] == -1)
			wall.color = 0xFFFFFF;
		else
		{
			wall.color = 0xFF4444;
			if (engine->future + 1 != engine->queue + engine->max_queue
			&& check_repeating(engine->queue, engine->sectors[s].neighbors[i])
								&& engine->sectors[s].floor == 0)
			{
				engine->future++;
				*engine->future = engine->sectors[s].neighbors[i];
			}
		}
		vertex = engine->sectors[s].vertex;
		wall.x0 = vertex[i].x;
		wall.y0 = vertex[i].y;
		wall.x1 = vertex[i + 1].x;
		wall.y1 = vertex[i + 1].y;
		minimap(engine, wall);
		wall = rotate_coords(engine, wall);
		i++;
	}
}


*/