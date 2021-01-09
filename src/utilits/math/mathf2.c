/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathf2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilits.h"

void	vec_proect(t_xy vert1, t_xy vert2, float *dx, float *dy)
{
	float	xd;
	float	yd;
	float	proection;

	xd = vert2.x - vert1.x;
	yd = vert2.y - vert1.y;
	proection = (*dx * xd + yd * *dy) / (xd * xd + yd * yd);
	*dx = xd * proection;
	*dy = yd * proection;
}
