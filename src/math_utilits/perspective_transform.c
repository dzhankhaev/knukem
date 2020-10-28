#include "math_utilits.h"

t_line	perspective_transform(t_engine *engine, float h, int color)
{
	t_line	wall;
	float	z;
	t_xyz	p0;
	t_xyz	p1;

	wall.color = color;
	z = engine->sectors[engine->player.sector].floor
		+ engine->player.eyeheight - h;
	p0 = vrotate((t_xyz){engine->wall.x0, engine->wall.y0, z},
				 engine->player.yaw);
	p1 = vrotate((t_xyz){engine->wall.x1, engine->wall.y1, z},
				 engine->player.yaw);
	wall.x0 = (int)((W >> 1) + p0.y / p0.x * (W >> 1));
	wall.x1 = (int)((W >> 1) + p1.y / p1.x * (W >> 1));
	wall.y0 = (int)((H >> 1) + p0.z / p0.x * (H >> 1));
	wall.y1 = (int)((H >> 1) + p1.z / p1.x * (H >> 1));
	return (wall);
}