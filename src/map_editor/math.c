#include "editor.h"

float	vector_cross_product1(float x0, float y0, float x1, float y1)
{
	return ((x0) * (y1) - (x1) * (y0));
}

float			point_side1(float px, float py, t_xy vert, t_xy vert1)
{
	return (vector_cross_product1(vert1.x - vert.x, vert1.y - vert.y,
								 px - vert.x, py - vert.y));
}
// D = (х3 - х1) * (у2 - у1) - (у3 - у1) * (х2 - х1)

// float			point_side1(float px, float py, t_xy vert, t_xy vert1)
// {
// 	double 
// }
// void	isometric(t_all *all, t_xy *s, t_xyz rot, float add)
// {
// 	t_xyz temp;
// 	t_xyz start;

// 	start = (t_xyz){s->x, s->y, add};
// 	rot = (t_xyz){(M_PI / 25 * rot.x), (M_PI / 25 * rot.y), (M_PI / 135 * rot.z) * -1};
// 	temp.y = all->area.h / 2 + start.y * cos(rot.x) + start.z * sin(rot.x);
// 	temp.z = -(start.y * sin(rot.x)) + start.z * cos(rot.x);
// 	s->y = temp.y;
// 	start.z = temp.z;
// 	temp.x = all->area.w/2 + start.x * cos(rot.y) + start.z * sin(rot.y);
// 	temp.z = -(start.x * sin(rot.y)) + start.z * cos(rot.y);
// 	s->x = temp.x;
// 	start.z = temp.z;
// 	s->x -= all->area.w/2;
// 	s->y -= all->area.h/4; 

// }