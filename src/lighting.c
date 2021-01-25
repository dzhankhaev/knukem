/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/12 19:53:26 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilits.h"

Uint32	deep_shading(t_engine *engine, t_line wall, int x)
{
	float	z;

	z = (((float)(x - wall.x0) * (engine->wall.x1 - engine->wall.x0)
			/ (float)(wall.x1 - wall.x0) + engine->wall.x0));
	return ((Uint32)(z * DEEP_SHADING));
}

Uint32	get_shadow(Uint32 z, Uint32 color)
{
	Uint32	r;
	Uint32	g;
	Uint32	b;

	if (z == 0u)
		return (color);
	r = (color >> 16u);
	g = (((color >> 8u) & 255u));
	b = (color & 255u);
	r = z > r ? 0u : r - z;
	r = r > 255u ? 255u : r;
	g = z > g ? 0u : g - z;
	g = g > 255u ? 255u : g;
	b = z > b ? 0u : b - z;
	b = b > 255u ? 255u : b;
	color = (r << 16u) | (g << 8u) | b;
	return (color);
}
