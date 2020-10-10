#include "engine.h"

static t_fline	swap(t_fline wall)
{
	float	t;

	if (wall.y0 > wall.y1)
	{
		t = wall.x0;
		wall.x0 = wall.x1;
		wall.x1 = t;
		t = wall.y0;
		wall.y0 = wall.y1;
		wall.y1 = t;
	}
	return (wall);
}

static t_fline	cut1(t_fline wall, t_xy i1)
{
	if (i1.x != -1)
	{
		wall = swap(wall);
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
	}
	return (wall);
}

static t_fline	cut2(t_fline wall, t_xy i2)
{
	if (i2.x != -1)
	{
		wall = swap(wall);
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
	}
	return (wall);
}
//обрежет стену, которая частично попала в поле зрения
//по левому лучу зрения и по правому
t_fline 		wall_cut(t_fline wall, t_xy i1, t_xy i2)
{
	wall = cut1(wall, i1);
	wall = cut2(wall, i2);
	return (wall);
}