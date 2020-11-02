#include "utilits.h"

Uint32			deep_shading(t_engine *engine, t_line wall, int x)
{
	float	z;
//найти модификатор освещения в зависимости от дальности
//эта формула линейной интерполяции https://en.wikipedia.org/wiki/Linear_interpolation
	z = (((float)(x - wall.x0) * (engine->wall.x1 - engine->wall.x0)
			/ (float)(wall.x1 - wall.x0) + engine->wall.x0));
	return ((Uint32)(z * DEEP_SHADING));
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