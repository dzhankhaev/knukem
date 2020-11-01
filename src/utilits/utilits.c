#include "engine.h"
#include "utilits.h"

int	imin(int a, int b)
{
	return (((a) < (b)) ? (a) : (b));
}

int	imax(int a, int b)
{
	return (((a) > (b)) ? (a) : (b));
}

float clamp(float a, float min, float max)
{
	return fminf(fmaxf(a, min), max);
}

int iclamp(int a, int min, int max)
{
	return imin(imax(a, min), max);
}