#include "engine.h"
#include "math_utilits.h"

//найдём Xa, Ya - точки пересечения двух прямых
static t_xy	vertical1(t_fline wall, t_fline twall)
{
	float Xa;
	float A2;
	float b2;
	float Ya;

	Xa = wall.x0;
	A2 = (twall.y0 - twall.y1) / (twall.x0 - twall.x1);
	b2 = twall.y0 - A2 * twall.x0;
	Ya = A2 * Xa + b2;
	if (twall.x0 <= Xa && twall.x1 >= Xa && fminf(wall.y0, wall.y1) <= Ya &&
		fmaxf(wall.y0, wall.y1) >= Ya)
	{
		return (t_xy){Xa, Ya};
	}
	return (t_xy){-1.f, -1.f};
}
//найдём Xa, Ya - точки пересечения двух прямых
static t_xy	vertical2(t_fline wall, t_fline twall)
{
	float Xa;
	float A1;
	float b1;
	float Ya;

	Xa = twall.x0;
	A1 = (wall.y0 - wall.y1) / (wall.x0 - wall.x1);
	b1 = wall.y0 - A1 * wall.x0;
	Ya = A1 * Xa + b1;
	if (wall.x0 <= Xa && wall.x1 >= Xa && fminf(twall.y0, twall.y1) <= Ya &&
		fmaxf(twall.y0, twall.y1) >= Ya)
	{
		return (t_xy){Xa, Ya};
	}
	return (t_xy){-1.f, -1.f};
}

static t_xy	general(t_fline wall, t_fline twall)
{
	float A1;
	float A2;
	float b1;
	float b2;
	float Xa;

	A1 = (wall.y0 - wall.y1) / (wall.x0 - wall.x1);
	A2 = (twall.y0 - twall.y1) / (twall.x0 - twall.x1);
	b1 = wall.y0 - A1 * wall.x0;
	b2 = twall.y0 - A2 * twall.x0;
	if (A1 == A2)
		return (t_xy){-1.f, -1.f}; //отрезки параллельны
	Xa = (b2 - b1) / (A1 - A2);
	if ((Xa < fmaxf(wall.x0, twall.x0)) || (Xa > fminf(wall.x1, twall.x1)))
		return (t_xy){-1.f, -1.f}; //точка Xa находится вне пересечения проекций отрезков на ось X
	else
		return (t_xy){Xa, A2 * Xa + b2};
}

static t_fline swap(t_fline wall)
{
	float	t;

	if (wall.x0 > wall.x1)
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

t_xy		intersection_point(t_fline wall, t_fline twall)
{
	wall = swap(wall);
	twall = swap(twall);
	//Если конец первого отрезка находится левее начала правого отрезка (по оси X), то отрезки точно не имеют точки пересечения.
	if (wall.x1 < twall.x0)
		return ((t_xy){-1.f, -1.f});
	/* ЭТОТ КУСОК СКОРЕЕ ВСЕГО НЕ НУЖЕН
	//если оба отрезка вертикальные
	if ((X1 == X2) && (X3 == X4))
	{
		//если они лежат на одном X
		if (X1 == X3)
		{
			//проверим пересекаются ли они, т.е. есть ли у них общий Y
			//для этого возьмём отрицание от случая, когда они НЕ пересекаются
			if (!((fmaxf(Y1, Y2) < fminf(Y3, Y4)) ||
				  (fminf(Y1, Y2) > fmaxf(Y3, Y4))))
			{
				return (t_xy){X1, Y1};
			}
		}
		return (t_xy){-1.f, -1.f};
	}
	*/
	//если первый отрезок вертикальный
	if (wall.x0 == wall.x1)
		return (vertical1(wall, twall));
	// если второй отрезок вертикальный
	else if (twall.x0 == twall.x1)
		return (vertical2(wall, twall));
	else //оба отрезка невертикальные
		return (general(wall, twall));
}