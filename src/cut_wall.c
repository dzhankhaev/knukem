#include "engine.h"

static t_fline	cut1(t_fline wall, t_xy i1)
{
	if (fabsf(wall.x0 - wall.x1) > fabsf(wall.y0 - wall.y1)
		&& wall.x0 > wall.x1)
	{
		wall.x1 = i1.x;
		wall.y1 = i1.y;
	}
	else
	{
		wall.x0 = i1.x;
		wall.y0 = i1.y;
	}
	return (wall);
}

static t_fline	cut2(t_fline wall, t_xy i2)
{
	if (fabsf(wall.x0 - wall.x1) < fabsf(wall.y0 - wall.y1)
		|| wall.x0 > wall.x1)
	{
		wall.x1 = i2.x;
		wall.y1 = i2.y;
	}
	else
	{
		wall.x0 = i2.x;
		wall.y0 = i2.y;
	}
	return (wall);
}
//обрежет стену, которая частично попала в поле зрения
//по левому лучу видимости и по правому
t_fline 		cut_wall(t_fline wall, t_xy i1, t_xy i2)
{
	float	t;
	int		color;

	color = wall.color;
	if (wall.y0 > wall.y1)
	{
		t = wall.x0;
		wall.x0 = wall.x1;
		wall.x1 = t;
		t = wall.y0;
		wall.y0 = wall.y1;
		wall.y1 = t;
	}
	if (i1.x != -1)
		wall = cut1(wall, i1);
	if (i2.x != -1)
		wall = cut2(wall, i2);
	wall.color = color;
	return (wall);
}