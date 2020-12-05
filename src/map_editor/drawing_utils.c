/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:32:11 by sisidra           #+#    #+#             */
/*   Updated: 2020/11/27 13:32:13 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_line(t_all *all, t_xy *start, t_xy *fin, SDL_Color color)
{
	float		dx;
	float		dy;
	int	l;
	int i;
	float x, y;

	l = (int)fmax(abs((int)start->x - (int)fin->x), abs((int)start->y - (int)fin->y));
	dx = (fin->x - start->x) / l;
	dy = (fin->y - start->y) / l;
	x = (int)(start->x);
	y = (int)(start->y); 
	i = 0;

	while (i < l)
	{
		x = x + dx;
		y = y + dy;
		i++;
		put_pxl(all->sdl, color, x, y);
	} 	
}

void	draw_circle(t_sdl *sdl, t_xy coord, int r, SDL_Color col)
{
	int 	i;
	float	angle;
	float dx;
	float dy;
	//printf("x:y = %d : %d\n", x, y);
	while (r >= 0)
	{
		i = 0;
		while (i < 20)
		{
			angle = (2 * M_PI * i)/20;
			dx = r * cosf(angle);
			dy = r * sinf(angle);
			put_pxl(sdl, col, roundf(coord.x + dx), roundf(coord.y + dy));
			i++;
		}
		r--;
	}
}

void	draw_rect(t_all *all, SDL_Rect area, SDL_Color color, int border)
{
	int x;
	int y;

	area = (SDL_Rect){area.x - border, area.y - border, area.w + border * 2, \
		area.h + border * 2};
	x = area.x;
	y = area.y;
	while(x <= area.x + area.w)
	{
		draw_line(all, &(t_xy){x, y}, &(t_xy){x, area.y + area.h}, color);
		x++;
		if(x - area.x == border)
			x = area.x + area.w - border+1;
	}
	while(y <= area.y + area.h)
	{
		draw_line(all, &(t_xy){x, y}, &(t_xy){area.x, y}, color);
		y++;
		if(y - area.y == border)
			y = area.y + area.h - border + 1;
	}
}

void    draw_fill_rect(t_all *all, SDL_Rect area, SDL_Color color)
{
    int x;
    int y;

    x = area.x;
    while (x < area.x + area.w)
    {
        y = area.y;
        while(y < area.y + area.h)
        {
			put_pxl(all->sdl, color, x, y);
            y++;
        }
        x++;
    }
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

void    draw_texture(t_sdl *sdl, SDL_Rect area, SDL_Surface *txt)
{
    float x;
    float y;
    Uint32 col;
	float kx, ky;
	
	kx = (float)txt->w / area.w;
	ky = (float)txt->h / area.h;
	
    y = 0;
    while(y < area.h)
    {
        x = 0;
        while(x < area.w)
        {
            col = get_pixel_color1(txt,kx*x, ky*y);
			if(col >> 24 != 0)
				put_pxl(sdl, (SDL_Color){col >> 16, col >> 8, col, 255}, area.x + x, area.y + y);
			x++;
        }
		y++;
    }
}
