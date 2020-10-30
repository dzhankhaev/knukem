#include "math_utilits.h"

int	int_min(int a, int b)
{
	return (((a) < (b)) ? (a) : (b));
}

int	int_max(int a, int b)
{
	return (((a) > (b)) ? (a) : (b));
}

float clamp(float a, float min, float max)
{
	return fminf(fmaxf(a, min), max);
}

int iclamp(int a, int min, int max)
{
	return int_min(int_max(a, min), max);
}

//векторное произведение
float	vector_cross_product(float x0, float y0, float x1, float y1)
{
	return ((x0) * (y1) - (x1) * (y0));
}

// С какой стороны от линии находится точка. Return value: <0, =0 or >0.
float			point_side(float px, float py, t_xy vert, t_xy vert1)
{
	return (vector_cross_product(vert1.x - vert.x, vert1.y - vert.y,
								 px - vert.x, py - vert.y));
}

int				y_for_x(t_line wall, int x)
{
	int		y;
//уравнение прямой?
	y = (x - wall.x0) * (wall.y1 - wall.y0) / (wall.x1 - wall.x0) + wall.y0;
	return (y);
}

t_line			swap_coords(t_line p)
{
	int t;

	t = p.x0;
	p.x0 = p.x1;
	p.x1 = t;
	t = p.y0;
	p.y0 = p.y1;
	p.y1 = t;
	return (p);
}