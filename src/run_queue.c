#include "engine.h"

static int	get_color(t_engine *engine, unsigned s, int color)
{
	if (fabsf(engine->sectors[s].floor
	- engine->sectors[engine->player.sector].floor) < floor_diff)
		return (color);
	return (0);
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
		if (engine->sectors[sectorno].neighbors[i] == -1)
			engine->wall.color = get_color(engine, sectorno, 0xDDDDDD);
		else
			engine->wall.color = get_color(engine, sectorno, 0xFF4444);
//		fill_queue(engine, sectorno, i);
		color = engine->wall.color;
		if (transform_wall(engine, i))
			render_wall(engine, sectorno,	//текущий сектор
			   engine->sectors[sectorno].neighbors[i]);		//его сосед, границу с которым мы обрабатываем.
		if (engine->minimap.mod)
			minimap(engine, engine->sectors[sectorno].vertex[i],
	engine->sectors[sectorno].vertex[i + 1], color);
		else
			minimap_cut(engine, (t_xy){engine->wall.x0, engine->wall.y0},
	(t_xy){engine->wall.x1, engine->wall.y1}, engine->wall.color);
		i++;
	}
}