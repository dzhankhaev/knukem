#include "utilits.h"

Uint32			color_distance(t_engine *engine, t_line wall, int x)
{
	Uint32		z;

	z = (Uint32)(((float)(x - wall.x0) * (engine->wall.x1 - engine->wall.x0)
			/ (float)(wall.x1 - wall.x0) + engine->wall.x0) * 8.f);
	return (z);
}

Uint32		get_shadow(Uint32 z, Uint32 color)
{
	Uint32	r;
	Uint32	g;
	Uint32	b;

	r = color >> 16;
	g = ((color >> 8) & 255);
	b = color & 255;
	r = iclamp(r - z, 0, 255);
	g = iclamp(g - z, 0, 255);
	b = iclamp(b - z, 0, 255);
	color = (r << 16) | (g << 8) | b;
	return (color);
}