#include "utilits.h"

//векторное произведение
float	vector_cross_product(float x0, float y0, float x1, float y1)
{
	return ((x0) * (y1) - (x1) * (y0));
}

// С какой стороны от линии находится точка. Возвращает <0, 0, >0
float			point_side(float px, float py, t_xy vert, t_xy vert1)
{
	return (vector_cross_product(vert1.x - vert.x, vert1.y - vert.y,
								 px - vert.x, py - vert.y));
}

int				y_for_x(t_line wall, int x)
{
	int		y;
//привести y к экранным координатам
//эта формула линейной интерполяции https://en.wikipedia.org/wiki/Linear_interpolation
	y = (x - wall.x0) * (wall.y1 - wall.y0) / (wall.x1 - wall.x0) + wall.y0;
	return (y);
}

double				square(double x)
{
	return x*x;
}

double squareRoot(double number)
{
	if (number < 0)
		number *= (-1);
	int start = 0, end = number;
	int mid;

	// To store the answer
	float ans;

	// To find integral part of square
	// root of number
	while (start <= end)
	{

		// Find mid
		mid = (start + end) / 2;

		// If number is perfect square
		// then break
		if (mid * mid == number)
		{
			ans = mid;
			break;
		}

		// Increment start if integral
		// part lies on right side
		// of the mid
		if (mid * mid < number)
		{
			start = mid + 1;
			ans = mid;
		}

			// Decrement end if integral part
			// lies on the left side of the mid
		else
		{
			end = mid - 1;
		}
	}

	// To find the fractional part
	// of square root upto 5 decimal
	float increment = 0.1;
	for(int i = 0; i < 5; i++)
	{
		while (ans * ans <= number)
		{
			ans += increment;
		}

		// Loop terminates,
		// when ans * ans > number
		ans = ans - increment;
		increment = increment / 10;
	}
	return ans;
}