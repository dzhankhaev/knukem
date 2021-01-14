/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:32:02 by sisidra           #+#    #+#             */
/*   Updated: 2020/11/27 13:32:04 by sisidra          ###   ########.fr       */
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
	tmp = get_text_surface(all, cx, all->font, BLUE);
	draw_texture(all->sdl->screen, area[0], tmp);
	SDL_FreeSurface(tmp);
	tmp = get_text_surface(all, cy, all->font, BLUE);
	draw_texture(all->sdl->screen, area[1], tmp);
	SDL_FreeSurface(tmp);
	free(cx);
	free(cy);
}

void	draw_digits(t_sdl *sdl, t_all *all, int x, int y)
{
	SDL_Surface	*tmp;
	SDL_Rect	area[2];

	area[0] = (SDL_Rect){W / 11, H * 0.75, W / 16, 50};
	area[1] = (SDL_Rect){W / 11, H * 0.86, W / 16, 50};
	// area[2] = (SDL_Rect){W / 11, H * 0.46, W / 16, 50};
	// area[3] = (SDL_Rect){W / 11, H * 0.58, W / 16, 50};
	x = (int)all->draw_floors.x;
	y = (int)all->draw_floors.y;
	tmp = get_text_surface(all, ft_itoa(x), all->font, BLUE);
	draw_texture(sdl->screen, area[0], tmp);
	SDL_FreeSurface(tmp);
	tmp = get_text_surface(all, ft_itoa(y), all->font, BLUE);
	draw_texture(sdl->screen, area[1], tmp);
	SDL_FreeSurface(tmp);
	if (all->buttons[0].state == 1)
		set_level_digits(all, (int)all->set_floors.x, (int)all->set_floors.y);
	else if(all->swap_num >= 0)
		set_level_digits(all, (int)all->sectors[all->swap_num].floor, 
			(int)all->sectors[all->swap_num].ceil);
}

void	draw_buttons(t_all *all, t_sdl *sdl, t_button *btn, int num)
{
	int i;
	int count;

	i = 0;
	count = num == 0 ? BUTTONS : BUTTONS - 4;
	while (i < count)
	{ 
		btn[i].color = btn[i].state == 1 ? RED : btn[i].color;
		
		btn[i].texture = get_text_surface(all, btn[i].title, all->font, btn[i].color);
		draw_texture(sdl->screen, btn[i].dstrect, btn[i].texture);
		if (i >= 2)
		{
			btn[i].state = 0;
			btn[i].color = WHITE;
		}
		SDL_FreeSurface(btn[i].texture);
		i++;
    }
	
}

void	draw_labels(t_all *all, t_labels label[5], int num)
{
	int i;

	i = num;
	while(i < 5)
	{
		draw_texture(all->sdl->screen, label[i].dst, label[i].surf);
		i++;
	}
	draw_buttons(all, all->sdl, all->buttons, num);
}

void	draw_ui(t_all *all, t_sdl *sdl, t_button *btn)
{
	draw_fill_rect(all, (SDL_Rect){4, 4, W / 4 - 8, H - 8}, LAZUR);
	if(btn[NEW_SECT].state || all->swap_num >= 0)
		draw_labels(all, all->labels, 0);
	else
		draw_labels(all, all->labels, 2);
	draw_digits(sdl, all, all->draw_floors.x, all->draw_floors.y);
}
