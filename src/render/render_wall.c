#include "engine.h"
/*
t_line	rotate_coords(t_engine *engine, t_line wall)
{
	t_line	w;

	wall.x0 -= engine->player.where.x;
	wall.y0 -= engine->player.where.y;
	wall.x1 -= engine->player.where.x;
	wall.y1 -= engine->player.where.y;
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
*/
int check_repeating(t_queue_obj *queue, int c)
{
	for (int i = 0; i < 32; i++)
	{
		if (queue[i].sectorno == c)
			return 0;
	}
	return 1;
}

int show_line_on_minimap(t_engine *engine, unsigned s, int color)
{
	if (fabsf(engine->sectors[s].floor
	- engine->sectors[engine->player.sector].floor) < floor_diff)
		return (color);
	return (0);
}

void render_wall(t_engine *engine, unsigned s)
{
	int	color;
	int i;

	i = 0;
	while (i < engine->sectors[s].npoints)
	{
		if (engine->sectors[s].neighbors[i] == -1)
			color = show_line_on_minimap(engine, s, 0xFFFFFF);
		else
		{
			color = show_line_on_minimap(engine, s, 0xFF4444);
			if (engine->future + 1 != engine->queue + engine->max_queue
				&& check_repeating(engine->queue, engine->sectors[s].neighbors[i]))
				(++engine->future)->sectorno = engine->sectors[s].neighbors[i];
		}
		minimap(engine, (t_line){engine->minimap_scale * engine->sectors[s].vertex[i].x,
								 engine->minimap_scale * engine->sectors[s].vertex[i + 1].x,
								 engine->minimap_scale * engine->sectors[s].vertex[i].y,
								 engine->minimap_scale * engine->sectors[s].vertex[i + 1].y,
								 color});
		i++;
	}
}