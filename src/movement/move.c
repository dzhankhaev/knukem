#include <engine.h>
#include "utilits.h"

void	slide(t_xy vert1, t_xy vert2, float *dx, float *dy)
{
	float	xd;
	float	yd;


	xd = fabs(vert2.x - vert1.x);
	yd = fabs(vert2.y - vert1.y);
	*dx = xd * (*dx * xd + yd * *dy) / (xd * xd + yd * yd);
	*dy = yd * (*dx * xd + yd * *dy) / (xd * xd + yd * yd);
}

void	move_player(float dx, float dy, t_engine *engine)
{
	float					px;
	float					py;
	unsigned				s;
	const t_xy				*vert;
	const t_sector			*sect;
	unsigned				old;

	old = engine->player.sector;
	s = 0;
	px = engine->player.where.x;
	py = engine->player.where.y;
	sect = &engine->sectors[engine->player.sector];
	vert = sect->vertex;
	while (s < sect->npoints)
	{
		// Проверяет произошло ли пересечение стороны сектора
		if (determine_intersection((t_fline){px, px + dx, py, py + dy},
			(t_fline){vert[s].x, vert[s + 1].x, vert[s].y, vert[s + 1].y}) &&
			point_side(px + dx, py + dy, vert[s], vert[s + 1]) < 0)
		{
			if (sect->neighbors[s] >= 0)
			{
				//	Ударяемся ли головой? || Можем ли перешагнуть?
				if (engine->player.where.z + HEAD_HEIGHT > engine->sectors[sect->neighbors[s]].ceil
				|| engine->player.where.z - engine->player.eyeheight + KNEE_HEIGHT < engine->sectors[sect->neighbors[s]].floor)
					slide(vert[s], vert[s + 1], &dx, &dy);
				else
				{
					engine->player.sector = sect->neighbors[s];
					if (engine->player.ground)
					{
						engine->player.falling = 1;
						engine->player.ground = 0;
						engine->player.velocity.z -= VSPEED;
					}
				}
			}
			else if (sect->neighbors[s] == -1)
				slide(vert[s], vert[s + 1], &dx, &dy);
			break ;
		}
		s++;
	}
	s = 0;
	while (s < sect->npoints)
	{
		if (point_side(px + dx, py + dy, vert[s], vert[s + 1]) < 0 && engine->player.sector == old)
			return;
		s++;
	}
	engine->player.where.x += dx;
	engine->player.where.y += dy;
}

void	move(t_engine *engine)
{
	fall(&engine->player, engine->sectors);
	move_player(engine->player.velocity.x, engine->player.velocity.y, engine);
}