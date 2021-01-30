/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:32:47 by sisidra           #+#    #+#             */
/*   Updated: 2020/11/27 13:32:49 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	put_pxl(SDL_Surface *screen, SDL_Color col, int x, int y)
{
	Uint32	*temp;
	int		pos;
	Uint32	color;

	temp = (Uint32*)screen->pixels;
	pos = y * W + x;
	color = col.a << 24 | col.r << 16 | col.g << 8 | col.b;
	if (x >= 0 && y >= 0 && x < W && y < H)
		temp[pos] = color;
}
