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

	i = 0;
	while (i < engine->sectors[engine->present->sectorno].npoints)
	{
		fill_queue(engine, engine->present->sectorno, i);
		//это обычная миникарта
//		minimap(engine, engine->sectors[engine->present->sectorno].vertex[i],
//	engine->sectors[engine->present->sectorno].vertex[i + 1],
//	engine->wall.color);
		transform_wall(engine, i);
		//это миникарта для просмотра отсеченных стен
		minimap_cut(engine, (t_xy){engine->wall.x0, engine->wall.y0},
				(t_xy){engine->wall.x1, engine->wall.y1}, engine->wall.color);
		i++;
	}
	//это лучи обзора
	render_line((t_line){0 + engine->minimap.point.x,
			  RAY_POINT_Y * engine->minimap.scale + engine->minimap.point.x,
			  0 + engine->minimap.point.y,
			  -RAY_POINT_X * engine->minimap.scale + engine->minimap.point.y,
			  0x0000FF}, engine->screen, engine->minimap.borders);
	render_line((t_line){0 + engine->minimap.point.x,
			 -RAY_POINT_Y * engine->minimap.scale + engine->minimap.point.x,
			 0 + engine->minimap.point.y,
			 -RAY_POINT_X * engine->minimap.scale + engine->minimap.point.y,
			 0x0000FF}, engine->screen, engine->minimap.borders);
}