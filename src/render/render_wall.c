#include "math_utilits.h"

static void		cur_sector(t_engine *engine, int i, t_line *wall)
{
	int		y[2];

	y[0] = iclamp(y_for_x(wall[0], i),
				  engine->tline[i], engine->bline[i]) - 1;
	y[1] = iclamp(y_for_x(wall[1], i),
				  engine->tline[i], engine->bline[i]) + 1;
	render_vline((t_line){i, i, engine->tline[i], y[0], wall[0].color},
				 engine->screen);
	render_vline((t_line){i, i, y[1], engine->bline[i], wall[1].color},
				 engine->screen);
	render_vline((t_line){i, i, y[0], y[1], engine->wall.color},
				 engine->screen);
}

void			render_wall(t_engine *engine, t_sector sector)
{
	t_line	wall[2];
	int		i;

	wall[0] = perspective_transform(engine, sector.ceil, 0x4455FF);
	wall[1] = perspective_transform(engine, sector.floor, 0x44ff44);
	if (wall[0].x1 < wall[0].x0)
		wall[0] = swap_coords(wall[0]);
	i = wall[0].x0; //заполняем в промежутке текущей стены
	while (i < wall[0].x1 && engine->present->sectorno == engine->player.sector)
	{
		cur_sector(engine, i, wall);
		i++;
	}
}