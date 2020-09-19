#include "engine.h"

static void	show_player(t_engine *engine)
{
	t_line w;
	w.color = 0x4444FF;
	w.x0 = W / 2;
	w.y0 = 0;
	w.x1 = W / 2;
	w.y1 = H;
	render_line(w, engine->screen);
	w.x0 = 0;
	w.y0 = H / 2;
	w.x1 = W;
	w.y1 = H / 2;
	render_line(w, engine->screen);
}

void		minimap(t_engine *engine, t_line wall)
{
	t_line		w;
	t_player	player;

	player = engine->player;
	show_player(engine);
	if (wall.color)
	{
		wall.x0 -= engine->minimap_scale * player.where.x;
		wall.y0 -= engine->minimap_scale * player.where.y;
		wall.x1 -= engine->minimap_scale * player.where.x;
		wall.y1 -= engine->minimap_scale * player.where.y;
		w = wall;
		wall.x0 = w.x0 * player.anglecos + w.y0 * player.anglesin;
		wall.x1 = w.x1 * player.anglecos + w.y1 * player.anglesin;
		wall.y0 = -w.x0 * player.anglesin + w.y0 * player.anglecos;
		wall.y1 = -w.x1 * player.anglesin + w.y1 * player.anglecos;
		wall.x0 += engine->minimap_x_y.x;
		wall.y0 += engine->minimap_x_y.y;
		wall.x1 += engine->minimap_x_y.x;
		wall.y1 += engine->minimap_x_y.y;
		render_line(wall, engine->screen);
	}
}