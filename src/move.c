#include <engine.h>
#include "arg_defines.h"

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
	float					arg[8];
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
	int i = 0;
	while (s < sect->npoints)
	{
		X1 = px;
		Y1 = py;
		X2 = px + dx;
		Y2 = py + dy;
		X3 = vert[s].x;
		Y3 = vert[s].y;
		X4 = vert[s + 1].x;
		Y4 = vert[s + 1].y;
		/* Проверяет произошло ли пересечение стороны сектора
     	*
     	* Because the edge vertices of each sector are defined in
     	* clockwise order, PointSide will always return -1 for a point
     	* that is outside the sector and 0 or 1 for a point that is inside.
     	*/
		if (determine_box_intersection(arg))
			printf("%i ПЕРЕСЕЧЕНИЕ\n", engine->tmp++);
		if (determine_box_intersection(arg) &&
			point_side(px + dx, py + dy, vert[s], vert[s + 1]) < 0)
		{
			if (sect->neighbors[s] >= 0)
			{	/*
				*	Ударяемся ли головой? (HEADMARGIN) (ПОКА ОТСУТСТВУЕТ) || Можем ли перешагнуть? (KNEEHEIGHT)
				*/
				if (engine->sectors[engine->player.sector].floor + engine->player.eyeheight + HeadMargin > engine->sectors[sect->neighbors[s]].ceil
				|| engine->sectors[engine->player.sector].floor + KneeHeight < engine->sectors[sect->neighbors[s]].floor)
					slide(vert[s], vert[s + 1], &dx, &dy);
				else
					engine->player.sector = sect->neighbors[s];
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
	move_player(engine->player.velocity.x, engine->player.velocity.y, engine);
}