#ifndef MATH_UTILITS_H
#define MATH_UTILITS_H

#include "engine.h"

float			point_side(float px, float py, t_xy vert, t_xy vert1);
t_xy			intersection_point(t_fline wall, t_fline twall);
int				determine_intersection(t_fline wall, t_fline twall);
float			clamp(float a, float min, float max);
int				y_for_x(t_line wall, int x);
t_line			swap_coords(t_line p);
int				int_max(int a, int b);
int				int_min(int a, int b);
int				iclamp(int a, int min, int max);
float			vector_cross_product(float x0, float y0, float x1, float y1);
t_fline			rotate_wall(t_sector sector, t_player player, int i, int color);
t_xyz			vrotate(t_xyz p, float angle);
t_line			perspective_transform(t_engine *engine, float h, int color);
#endif
