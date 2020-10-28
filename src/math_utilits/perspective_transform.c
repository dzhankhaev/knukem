#include "math_utilits.h"

t_line	perspective_transform(t_fline w, float z, float yaw, int color)
{
	t_line	wall;
	t_xyz	p0;
	t_xyz	p1;

	wall.color = color;
	p0 = vrotate((t_xyz){w.x0, w.y0, z}, yaw);
	p1 = vrotate((t_xyz){w.x1, w.y1, z}, yaw);
	wall.x0 = (int)((W >> 1) + p0.y / p0.x * (W >> 1));
	wall.x1 = (int)((W >> 1) + p1.y / p1.x * (W >> 1));
	wall.y0 = (int)((H >> 1) + p0.z / p0.x * (H >> 1));
	wall.y1 = (int)((H >> 1) + p1.z / p1.x * (H >> 1));
	if (wall.x1 < wall.x0)
		wall = swap_coords(wall);
	return (wall);
}