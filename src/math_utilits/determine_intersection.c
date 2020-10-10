#include "math_utilits.h"
#include "engine.h"

// Пересекаются ли два отрезка
int				determine_intersection(float *arg)
{
	t_xy	a;

	a = intersection_point(arg);
	if (a.x == -1)
		return (0);
	return (1);
}