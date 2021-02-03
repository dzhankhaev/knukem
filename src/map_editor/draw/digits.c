/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:31:50 by sisidra           #+#    #+#             */
/*   Updated: 2020/11/27 13:31:54 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	set_level_digits(t_all *all, int x, int y)
{
	SDL_Surface	*tmp;
	SDL_Rect	area[2];
	char		*cx;
	char		*cy;

	cx = ft_itoa(x);
	cy = ft_itoa(y);
	area[0] = (SDL_Rect){W / 11, H * 0.46, W / 16, 50};
	area[1] = (SDL_Rect){W / 11, H * 0.58, W / 16, 50};
	tmp = get_text_surface(cx, all->font, BLUE);
	ft_memdel((void*)&cx);
	draw_texture(all->sdl.screen, area[0], tmp);
	SDL_FreeSurface(tmp);
	tmp = get_text_surface(cy, all->font, BLUE);
	ft_memdel((void*)&cy);
	draw_texture(all->sdl.screen, area[1], tmp);
	SDL_FreeSurface(tmp);
}

void	draw_digits(t_sdl *sdl, t_all *all, int x, int y)
{
	SDL_Surface	*tmp;
	SDL_Rect	area[2];
	char		*t;

	area[0] = (SDL_Rect){W / 11, H * 0.75, W / 16, 50};
	area[1] = (SDL_Rect){W / 11, H * 0.86, W / 16, 50};
	x = (int)all->draw_floors.x;
	y = (int)all->draw_floors.y;
	t = ft_itoa(x);
	tmp = get_text_surface(t, all->font, BLUE);
	ft_memdel((void*)&t);
	draw_texture(sdl->screen, area[0], tmp);
	SDL_FreeSurface(tmp);
	t = ft_itoa(y);
	tmp = get_text_surface(t, all->font, BLUE);
	ft_memdel((void*)&t);
	draw_texture(sdl->screen, area[1], tmp);
	SDL_FreeSurface(tmp);
	if (all->buttons[0].state == 1)
		set_level_digits(all, (int)all->set_floors.x, (int)all->set_floors.y);
	else if (all->swap_num >= 0)
		set_level_digits(all, (int)all->sectors[all->swap_num].floor,\
			(int)all->sectors[all->swap_num].ceil);
}

void	draw_setting_digits(t_all *all, t_settings *settings)
{
	char		*digit;
	SDL_Rect	area;

	digit = NULL;
	digit = ft_itoa(settings->inventory);
	area = (SDL_Rect){W / 4 - 100, H * 0.15, 50, 50};
	draw_label(all, digit, area, BLUE);
	ft_memdel((void*)&digit);
	digit = ft_itoa(settings->speed);
	area = (SDL_Rect){W / 4 - 100, H * 0.21, 50, 50};
	draw_label(all, digit, area, BLUE);
	ft_memdel((void*)&digit);
	digit = ft_itoa(settings->gravity);
	area = (SDL_Rect){W / 4 - 100, H * 0.27, 50, 50};
	draw_label(all, digit, area, BLUE);
	ft_memdel((void*)&digit);
	digit = ft_itoa(settings->ammo);
	area = (SDL_Rect){W / 4 - 100, H * 0.33, 50, 50};
	draw_label(all, digit, area, BLUE);
	ft_memdel((void*)&digit);
}
