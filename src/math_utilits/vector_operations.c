#include "math_utilits.h"
#include "arg_defines.h"

//векторное произведение
static float	vertor_cross_product(float x0, float y0, float x1, float y1)
{
	return ((x0) * (y1) - (x1) * (y0));
}

// С какой стороны от линии находится точка. Return value: <0, =0 or >0.
float			point_side(float px, float py, t_xy vert, t_xy vert1)
{
	return (vertor_cross_product(vert1.x - vert.x, vert1.y - vert.y,
							  px - vert.x, py - vert.y));
}

// Точка пересечения двух линий
t_xy			determine_intersection_point(float *arg)
{
	t_xy	a;

	a.x = vertor_cross_product(
			vertor_cross_product(X1, Y1, X2, Y2),
			(X1) - (X2),
			vertor_cross_product(Y3, Y3, X4, Y4),
			(X3) - (X4))
					/
			vertor_cross_product(
			(X1) - (X2),
			(Y1) - (Y2),
			(X3) - (X4),
			(Y3) - (Y4));
	a.y = vertor_cross_product(
			vertor_cross_product(X1, Y1, X2, Y2),
			(Y1) - (Y2),
			vertor_cross_product(X3, Y3, X4, Y4),
			(Y3) - (Y4))
					/
			vertor_cross_product(
			(X1) - (X2),
			(Y1) - (Y2),
			(X3) - (X4),
			(Y3) - (Y4));
	return (a);
}

// Пересекаются ли две 2д коробки (2d box)
int				determine_box_intersection(float *arg)
{
	int	a;
	int	b;

	// Overlap a:  Determine whether the two number ranges overlap.
	a = (fminf(X1, X2) <= fmaxf(X3, X4)) && (fminf(X3, X4) <= fmaxf(X1, X2));
	// Overlap b:  Determine whether the two number ranges overlap.
	b = (fminf(Y1, Y2) <= fmaxf(Y3, Y4)) && (fminf(Y3, Y4) <= fmaxf(Y1, Y2));
	return (a && b);
}