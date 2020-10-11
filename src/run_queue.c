#include "engine.h"

static int	check_repeating(t_queue *queue, unsigned max_queue, int c)
{
	int	i;

	i = 0;
	while (i < queue[max_queue - 1].sectorno)
	{
		if (queue[i].sectorno == c)
			return 0;
		i++;
	}
	return 1;
}

static int	color(t_engine *engine, unsigned s, int color)
{
	if (fabsf(engine->sectors[s].floor
	- engine->sectors[engine->player.sector].floor) < floor_diff)
		return (color);
	return (0);
}

static void	fill_queue(t_engine *engine, int sectorno, int i)
{
	if (engine->sectors[sectorno].neighbors[i] == -1)
		engine->wall.color = color(engine, sectorno, 0xFFFFFF);
	else
	{
		engine->wall.color = color(engine, sectorno, 0xFF4444);
		if (engine->future + 1 != engine->queue + engine->max_queue
			&& check_repeating(engine->queue, engine->max_queue,
							   engine->sectors[sectorno].neighbors[i]))
		{
			engine->queue[engine->max_queue - 1].sectorno += 1;
			(engine->future++)->sectorno =
					engine->sectors[sectorno].neighbors[i];
		}
	}
}

void 		run_queue(t_engine *engine)
{
	int		i;
	int		sectorno;
	int		color;

	i = 0;
	sectorno = engine->present->sectorno;
	while (i < engine->sectors[sectorno].npoints)
	{
		fill_queue(engine, sectorno, i);
		color = engine->wall.color;
		transform_wall(engine, i);
		if (engine->minimap.mod)
			minimap(engine, engine->sectors[sectorno].vertex[i],
	engine->sectors[sectorno].vertex[i + 1], color);
		else
			minimap_cut(engine, (t_xy){engine->wall.x0, engine->wall.y0},
	(t_xy){engine->wall.x1, engine->wall.y1}, engine->wall.color);
		i++;
	}
}