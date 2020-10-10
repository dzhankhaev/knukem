#include "engine.h"

static int	check_repeating(t_queue *queue, unsigned max_queue, int c)
{
	for (int i = 0; i < max_queue; i++)
	{
		if (queue[i].sectorno == c)
			return 0;
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

void 		fill_queue(t_engine *engine)
{
	int		i;
	t_queue	*present;

	present = engine->present;
	i = 0;
	while (i < engine->sectors[present->sectorno].npoints)
	{
		if (engine->sectors[present->sectorno].neighbors[i] == -1)
			engine->wall.color = color(engine, present->sectorno, 0xFFFFFF);
		else
		{
			engine->wall.color = color(engine, present->sectorno, 0xFF4444);
			if (engine->future + 1 != engine->queue + engine->max_queue
	&& check_repeating(engine->queue, engine->max_queue,
	engine->sectors[present->sectorno].neighbors[i]))
				(++engine->future)->sectorno =
						engine->sectors[present->sectorno].neighbors[i];
		}
		//это обычная миникарта
//		minimap(engine, engine->sectors[present->sectorno].vertex[i],
//		engine->sectors[present->sectorno].vertex[i + 1], engine->wall.color);
		transform_wall(engine, i);
		i++;
	}
}