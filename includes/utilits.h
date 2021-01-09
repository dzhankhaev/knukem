/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITS_H
# define UTILITS_H

# include "engine.h"

float			point_side(float px, float py, t_xy vert, t_xy vert1);
int				y_for_x(t_line wall, int x);
float			vector_cross_product(float x0, float y0, float x1, float y1);
int				imax(int a, int b);
int				imin(int a, int b);
float			clamp(float a, float min, float max);
int				iclamp(int a, int min, int max);
t_line			swap_coords(t_line p);
void			to_x_order(t_line *wall);
t_xy			intersection_point(t_fline wall, t_fline twall);
int				determine_intersection(t_fline wall, t_fline twall);
t_fline			rotate_wall(t_fline wall, t_player player);
t_line			perspective_transform(t_fline w, float z, float yaw, int color);
void			exc(const char *file, const char *function);
void			clean(t_engine *engine);
void			load_img(t_engine *engine, char *name, int n);
t_xy			point_proection(t_fline wall, t_xyz p);
float			get_vec_angle(float x1, float y1, float x2, float y2);
Uint32			get_pixel_color(SDL_Surface *surface, int x, int y);
void			anim_delete(t_engine *engine, int i);
void			vec_proect(t_xy vert1, t_xy vert2, float *dx, float *dy);

#endif
