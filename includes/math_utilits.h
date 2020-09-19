#ifndef MATH_UTILITS_H
#define MATH_UTILITS_H

#include "engine.h"

float			point_side(float px, float py, t_xy vert_s, t_xy vert_s1);
t_xy			determine_intersection_point(float *arg);
int				determine_box_intersection(float *arg);
int				int_max(int a, int b);
int				int_min(int a, int b);
int 			clamp(int a, int min, int max);

#endif
