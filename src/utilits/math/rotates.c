#include "engine.h"

static t_fline	normi_wall(t_sector sector, t_player player, int i, int color)
{
	t_fline		wall;

	wall.x0 = sector.vertex[i].x - player.where.x;
	wall.y0 = sector.vertex[i].y - player.where.y;
	wall.x1 = sector.vertex[i + 1].x - player.where.x;
	wall.y1 = sector.vertex[i + 1].y - player.where.y;
	wall.color = color;
	return (wall);
}

t_fline			rotate_wall(t_sector sector, t_player player, int i, int color)
{
	t_fline	w;
	t_fline	wall;

	wall = normi_wall(sector, player, i, color);
	w = wall;
	wall.x0 = w.x0 * player.anglecos + w.y0 * player.anglesin;
	wall.x1 = w.x1 * player.anglecos + w.y1 * player.anglesin;
	wall.y0 = -w.x0 * player.anglesin + w.y0 * player.anglecos;
	wall.y1 = -w.x1 * player.anglesin + w.y1 * player.anglecos;
	return (wall);
}