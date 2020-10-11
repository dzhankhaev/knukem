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

static t_line rotate_minimap(t_line wall, t_player player)
{
	t_line	w;

	w = wall;
	wall.x0 = w.x0 * player.anglecos + w.y0 * player.anglesin;
	wall.x1 = w.x1 * player.anglecos + w.y1 * player.anglesin;
	wall.y0 = -w.x0 * player.anglesin + w.y0 * player.anglecos;
	wall.y1 = -w.x1 * player.anglesin + w.y1 * player.anglecos;
	return (wall);
}

void	render_minimap_hud(t_minimap minimap, SDL_Surface *screen)
{
	t_line w;
	t_line borders;

	borders = minimap.borders;
	//это границы по краям миникарты
	w = (t_line){borders.x0, borders.x1, borders.y0, borders.y0, borders.color};
	render_line(w, screen, borders);
	w = (t_line){borders.x0, borders.x0, borders.y0, borders.y1, borders.color};
	render_line(w, screen, borders);
	w = (t_line){borders.x0, borders.x1, borders.y1 - 1, borders.y1 - 1,
			  borders.color};
	render_line(w, screen, borders);
	w = (t_line){borders.x1 - 1, borders.x1 - 1, borders.y0, borders.y1,
			  borders.color};
	render_line(w, screen, borders);
	//это стрелка игрока
	render_line(minimap.player_horizontal, screen, borders);
	render_line(minimap.player_vertical, screen, borders);
	//это лучи обзора
	render_line((t_line){minimap.point.x,
		RAY_POINT_Y * minimap.scale + minimap.point.x, minimap.point.y,
		-RAY_POINT_X * minimap.scale + minimap.point.y, 0x0000FF},
		screen, minimap.borders);
	render_line((t_line){minimap.point.x,
		-RAY_POINT_Y * minimap.scale + minimap.point.x, minimap.point.y,
		-RAY_POINT_X * minimap.scale + minimap.point.y, 0x0000FF},
		screen, minimap.borders);
}

// Это обычная миникарта
 void		minimap(t_engine *engine, t_xy v0, t_xy v1, int color)
{
	t_line			wall;
	t_player		player;
	t_minimap		minimap;

	player = engine->player;
	minimap = engine->minimap;
	if (color)
	{
		wall.color = color;
		wall.x0 = minimap.scale * v0.x - minimap.scale * player.where.x;
		wall.x1 = minimap.scale * v1.x - minimap.scale * player.where.x;
		wall.y0 = minimap.scale * v0.y - minimap.scale * player.where.y;
		wall.y1 = minimap.scale * v1.y - minimap.scale * player.where.y;
		wall = rotate90_minimap(wall);
		wall = rotate_minimap(wall, player);
		wall.x0 += minimap.point.x;
		wall.x1 += minimap.point.x;
		wall.y0 += minimap.point.y;
		wall.y1 += minimap.point.y;
		render_line(wall, engine->screen, engine->minimap.borders);
	}
}

//это миникарта для просмотра отсеченных стен
void		minimap_cut(t_engine *engine, t_xy v0, t_xy v1, int color)
{
	t_line			wall;
	t_minimap		minimap;

	minimap = engine->minimap;
	if (color)
	{
		wall.color = color;
		wall.x0 = minimap.scale * v0.x;
		wall.x1 = minimap.scale * v1.x;
		wall.y0 = minimap.scale * v0.y;
		wall.y1 = minimap.scale * v1.y;
		wall = rotate90_minimap(wall);
		wall.x0 += minimap.point.x;
		wall.x1 += minimap.point.x;
		wall.y0 += minimap.point.y;
		wall.y1 += minimap.point.y;
		render_line(wall, engine->screen, engine->minimap.borders);
	}
}