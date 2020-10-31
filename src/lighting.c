#include "math_utilits.h"

int				color_distance(t_engine *engine, t_line wall, int x, float ceil)
{
	int		z;
	//нужно проверить с какой стороны мы смотрим на стену
	//если слева - правая координата будет падать, если справа - будет расти
	//некорректно работает, если смотреть сверху
	//возможно не применимо для наклонных полов или потолков
	if (engine->player.where.z > ceil) //КОСТЫЛЬ частично помогает
		return (color_distance(engine, (t_line){wall.x0, wall.x1, wall.y1, wall.y0}, x, engine->player.where.z + 1));
	if (wall.y0 <= wall.y1)
	{
		//нужно проверить какая из координат является более дальней
		if (engine->wall.x0 > engine->wall.x1)
			z = ((float)(x - wall.x0) * (engine->wall.x1 - engine->wall.x0)
					/ (float)(wall.x0 - wall.x1) + engine->wall.x1) * 8.f;
		else
			z = ((float)(x - wall.x0) * (engine->wall.x1 - engine->wall.x0)
					/ (float)(wall.x1 - wall.x0) + engine->wall.x0) * 8.f;
	}
	else
	{
		if (engine->wall.x0 < engine->wall.x1)
			z = ((float)(x - wall.x0) * (engine->wall.x1 - engine->wall.x0)
					/ (float)(wall.x0 - wall.x1) + engine->wall.x1) * 8.f;
		else
			z = ((float)(x - wall.x0) * (engine->wall.x1 - engine->wall.x0)
					/ (float)(wall.x1 - wall.x0) + engine->wall.x0) * 8.f;
	}
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