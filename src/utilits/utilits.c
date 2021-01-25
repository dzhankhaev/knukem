/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

int		imin(int a, int b)
{
	return (((a) < (b)) ? (a) : (b));
}

int		imax(int a, int b)
{
	return (((a) > (b)) ? (a) : (b));
}

float	clamp(float a, float min, float max)
{
	return (fminf(fmaxf(a, min), max));
}

int		iclamp(int a, int min, int max)
{
	return (imin(imax(a, min), max));
}

Uint32	get_pixel_color(SDL_Surface *surface, int x, int y)
{
	Uint8	*p;
	Uint32	rgb;

	p = (Uint8 *)(surface->pixels + y * surface->pitch
				+ (x * surface->format->BytesPerPixel));
	rgb = p[2] << 16 | p[1] << 8 | p[0];
	return (rgb);
}
