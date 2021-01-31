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

SDL_Surface	*get_text_surface(char *name, TTF_Font *font, SDL_Color color)
{
	SDL_Surface	*text;

	if (!(text = TTF_RenderText_Blended(font, name, color)))
		error_and_close(__FILE__, __FUNCTION__);
	return (text);
}

Uint32		get_pixel_color1(SDL_Surface *surface, const int x,\
									const int y)
{
	Uint8	*p;
	Uint32	rgb;

	p = (Uint8 *)surface->pixels + y * surface->pitch + x
			* surface->format->BytesPerPixel;
	rgb = p[3] << 24 | p[2] << 16 | p[1] << 8 | p[0];
	return (rgb);
}

void		draw_texture(SDL_Surface *screen, SDL_Rect area, SDL_Surface *txt)
{
	float		x;
	float		y;
	Uint32		col;
	t_xy		k;

	k.x = (float)txt->w / area.w;
	k.y = (float)txt->h / area.h;
	y = 0;
	while (y < area.h)
	{
		x = 0;
		while (x < area.w)
		{
			col = get_pixel_color1(txt, k.x * x, k.y * y);
			if (col >> 24 != 0 && col ^ 0xFF00FFFF)
				put_pxl(screen, (SDL_Color){col >> 16, col >> 8, col, 255}, \
					area.x + x, area.y + y);
			x++;
		}
		y++;
	}
}
