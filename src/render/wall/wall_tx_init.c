#include "engine.h"
#include "utilits.h"

//get origin p
t_line		get_op1(t_temp *a)
{
	return ((t_line){0, 0, a->oy[0],
				  imin(a->oy[2], a->oy[1]), 0});
}

t_line		get_op2(t_temp *a)
{
	return ((t_line){0, 0, imax(a->oy[3], a->oy[0]),
					 a->oy[1], 0});
}

t_line		get_op3(t_temp *a)
{
	return ((t_line){0, 0, a->oy[0], a->oy[1], 0});
}