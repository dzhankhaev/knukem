#include "utilits.h"
#include "engine.h"

// Пересекаются ли два отрезка
int				determine_intersection(t_fline wall, t_fline twall)
{
	t_xy	a;

	a = intersection_point(wall, twall);
	if (a.x == -1)
		return (0);
	return (1);
}