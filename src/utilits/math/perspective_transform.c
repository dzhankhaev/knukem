#include "utilits.h"

static t_xyz	vrotate(t_xyz p, float vangle) //используется для обработки вертикального угла взгляда
{
	p.z = p.z + p.x * vangle;
	return (p);
}
//Х - глубина, Y - положение (слева, справа)
//В экранных X - столбцы, Y - строки
//для обратного преобразования
//X = z / (((float)(wall.y0 << 1) / H - 1) - vangle);
//Y = X * (((float)wall.x0 - (W / 2.f)) / (W / 2.f));


// преобразование координат точки.
t_line			perspective_transform(t_fline w, float z, float vangle,
							   int color)
{
	t_line	wall;
	t_xyz	p0;
	t_xyz	p1;

	wall.color = color;
	p0 = vrotate((t_xyz){w.x0, w.y0, z}, vangle);
	p1 = vrotate((t_xyz){w.x1, w.y1, z}, vangle);
	wall.x0 = (int)((W >> 1) + p0.y / p0.x * (W >> 1));
	wall.x1 = (int)((W >> 1) + p1.y / p1.x * (W >> 1));
	wall.y0 = (int)((H >> 1) + p0.z / p0.x * (H >> 1));
	wall.y1 = (int)((H >> 1) + p1.z / p1.x * (H >> 1));

	return (wall);
}