#include "utilits.h"

//векторное произведение
float	vector_cross_product(float x0, float y0, float x1, float y1)
{
	return ((x0) * (y1) - (x1) * (y0));
}

// С какой стороны от линии находится точка. Возвращает <0, 0, >0
float			point_side(float px, float py, t_xy vert, t_xy vert1)
{
	return (vector_cross_product(vert1.x - vert.x, vert1.y - vert.y,
								 px - vert.x, py - vert.y));
}

int				y_for_x(t_line wall, int x)
{
	int		y;
//привести y к экранным координатам
	y = (x - wall.x0) * (wall.y1 - wall.y0) / (wall.x1 - wall.x0) + wall.y0;
	return (y);
}