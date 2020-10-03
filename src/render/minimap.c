#include "engine.h"

static t_line rotate90_minimap(t_line wall)
{
	t_line	w;

	w = wall;
	wall.x0 = w.y0;
	wall.x1 = w.y1;
	wall.y0 = -w.x0;
	wall.y1 = -w.x1;
	return (wall);
}

static void render_borders(t_line borders, SDL_Surface *screen)
{
	t_line w;

	w = (t_line){borders.x0, borders.x1, borders.y0, borders.y0, borders.color};
	render_line(w, screen, borders);
	w = (t_line){borders.x0, borders.x0, borders.y0, borders.y1, borders.color};
	render_line(w, screen, borders);
	w = (t_line){borders.x0, borders.x1, borders.y1 - 1, borders.y1 - 1, borders.color};
	render_line(w, screen, borders);
	w = (t_line){borders.x1 - 1, borders.x1 - 1, borders.y0, borders.y1, borders.color};
	render_line(w, screen, borders);
}

void		minimap(t_engine *engine, t_line wall)
{
	t_line			w;
	t_player		player;

	player = engine->player;
	render_line(engine->minimap.player_horizontal, engine->screen, engine->minimap.borders);
	render_line(engine->minimap.player_vertical, engine->screen, engine->minimap.borders);
	render_borders(engine->minimap.borders, engine->screen);
	if (wall.color)
	{
		wall.x0 -= engine->minimap.scale * player.where.x;
		wall.y0 -= engine->minimap.scale * player.where.y;
		wall.x1 -= engine->minimap.scale * player.where.x;
		wall.y1 -= engine->minimap.scale * player.where.y;
		wall = rotate90_minimap(wall);
		w = wall;
		wall.x0 = w.x0 * player.anglecos + w.y0 * player.anglesin;
		wall.x1 = w.x1 * player.anglecos + w.y1 * player.anglesin;
		wall.y0 = -w.x0 * player.anglesin + w.y0 * player.anglecos;
		wall.y1 = -w.x1 * player.anglesin + w.y1 * player.anglecos;
		wall.x0 += engine->minimap.point.x;
		wall.y0 += engine->minimap.point.y;
		wall.x1 += engine->minimap.point.x;
		wall.y1 += engine->minimap.point.y;
		render_line(wall, engine->screen, engine->minimap.borders);
	}
}