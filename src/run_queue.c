#include "engine.h"

static int	get_color(t_engine *engine, unsigned s, int color)
{
	if (fabsf(engine->sectors[s].floor
			  - engine->sectors[engine->player.sector].floor) < FLOOR_DIFF)
		return (color);
	return (0);
}

int				check_repeat(t_engine *engine, int sectorno, int neighbor)
{
	t_queue *temp;

	temp = engine->queue;
	while (temp != engine->future)
	{
		/*
		 * мы перемещаемся из А в В. Если в очереди был переход из В в А, то это возврат назад. Так делать нельзя.
		 * это справедливо для выпуклых секторов
		 */
		if (temp->psec == neighbor && temp->sectorno == sectorno)
			return (0);
		temp++;
	}
	return (1);
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
		if (engine->sectors[sectorno].neighbors[i] <= -1)
			engine->wall.color = WALL_COLOR;
		else
			engine->wall.color = EDGE_COLOR;
		color = engine->wall.color;
		if (transform_wall(engine, i))
			render_scene(engine, sectorno,    //текущий сектор
						 engine->sectors[sectorno].neighbors[i], i);		//его сосед, границу с которым мы обрабатываем.
		if (engine->minimap.mod)
			minimap(engine, engine->sectors[sectorno].vertex[i],
					engine->sectors[sectorno].vertex[i + 1], color);
		else
			minimap_cut(engine, (t_xy){engine->wall.x0, engine->wall.y0},
						(t_xy){engine->wall.x1, engine->wall.y1}, engine->wall.color);
		i++;
	}
}