#include "utilits.h"

int				color_distance(t_engine *engine, t_line wall, int x)
{
	int		z;

	z = ((float)(x - wall.x0) * (engine->wall.x1 - engine->wall.x0)
			/ (float)(wall.x1 - wall.x0) + engine->wall.x0) * 8.f;
	return (z);
}
//		z = ((float)(x - wall.x0) * (engine->wall.x0 - engine->wall.x1) / (float)(wall.x1 - wall.x0) + engine->wall.x1) * 8.f;
unsigned		get_shadow(int z, unsigned color)
{
	unsigned	r;
	unsigned	g;
	unsigned	b;

	r = color >> 16;
	g = ((color >> 8) & 255);
	b = color & 255;
	r = iclamp(r - z, 0, 255);
	g = iclamp(g - z, 0, 255);
	b = iclamp(b - z, 0, 255);
	color = (r << 16) | (g << 8) | b;
	return (color);
}