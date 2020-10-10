#ifndef MATH_UTILITS_H
#define MATH_UTILITS_H

#include "engine.h"

float			point_side(float px, float py, t_xy vert, t_xy vert1);
t_xy			intersection_point(float *arg);
int				determine_intersection(float *arg);
int				clamp(int a, int min, int max);
int				int_max(int a, int b);
int				int_min(int a, int b);
float			vector_cross_product(float x0, float y0, float x1, float y1);
//int 			clamp(int a, int min, int max);

#endif
