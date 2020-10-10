#include "engine.h"
#include "math_utilits.h"
#include "arg_defines.h"

static void	swap(float *x0, float *x1, float *y0, float *y1)
{
	float	t;

	t = *x0;
	*x0 = *x1;
	*x1 = t;
	t = *y0;
	*y0 = *y1;
	*y1 = t;
}
//найдём Xa, Ya - точки пересечения двух прямых
static t_xy	vertical1(float *arg)
{
	float Xa;
	float A2;
	float b2;
	float Ya;

	Xa = X1;
	A2 = (Y3 - Y4) / (X3 - X4);
	b2 = Y3 - A2 * X3;
	Ya = A2 * Xa + b2;
	if (X3 <= Xa && X4 >= Xa && fminf(Y1, Y2) <= Ya &&
		fmaxf(Y1, Y2) >= Ya)
	{
		return (t_xy){Xa, Ya};
	}
	return (t_xy){-1.f, -1.f};
}
//найдём Xa, Ya - точки пересечения двух прямых
static t_xy	vertical2(float *arg)
{
	float Xa;
	float A1;
	float b1;
	float Ya;

	Xa = X3;
	A1 = (Y1 - Y2) / (X1 - X2);
	b1 = Y1 - A1 * X1;
	Ya = A1 * Xa + b1;
	if (X1 <= Xa && X2 >= Xa && fminf(Y3, Y4) <= Ya &&
		fmaxf(Y3, Y4) >= Ya)
	{
		return (t_xy){Xa, Ya};
	}
	return (t_xy){-1.f, -1.f};
}

static t_xy	general(float *arg)
{
	float A1;
	float A2;
	float b1;
	float b2;
	float Xa;
	float Ya;

	A1 = (Y1 - Y2) / (X1 - X2);
	A2 = (Y3 - Y4) / (X3 - X4);
	b1 = Y1 - A1 * X1;
	b2 = Y3 - A2 * X3;
	if (A1 == A2)
		return (t_xy){-1.f, -1.f}; //отрезки параллельны
	Xa = (b2 - b1) / (A1 - A2);
	Ya = A2 * Xa + b2;
	if ((Xa < fmaxf(X1, X3)) || (Xa > fminf(X2, X4)))
		return (t_xy){-1.f, -1.f}; //точка Xa находится вне пересечения проекций отрезков на ось X
	else
		return (t_xy){Xa, Ya};
}

t_xy		intersection_point(float *arg)
{
	if (X1 > X2)
		swap(&X1, &X2, &Y1, &Y2);
	if (X3 > X4)
		swap(&X3, &X4, &Y3, &Y4);
	//Если конец первого отрезка находится левее начала правого отрезка (по оси X), то отрезки точно не имеют точки пересечения.
	if (X2 < X3)
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
	if (X1 == X2)
		return (vertical1(arg));
	// если второй отрезок вертикальный
	else if (X3 == X4)
		return (vertical2(arg));
	else //оба отрезка невертикальные
		return (general(arg));
}