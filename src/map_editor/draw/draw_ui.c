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

void	draw_buttons(t_all *all, t_sdl *sdl, t_button *bn, int num)
{
	int i;
	int count;

	i = 0;
	count = num == 0 ? BUTTONS : BUTTONS - 4;
	while (i < count)
	{
		bn[i].color = bn[i].state == 1 ? RED : bn[i].color;
		bn[i].texture = get_text_surface(bn[i].title, all->font, bn[i].color);
		draw_texture(sdl->screen, bn[i].dstrect, bn[i].texture);
		if (i >= 2)
		{
			bn[i].state = 0;
			bn[i].color = WHITE;
		}
		SDL_FreeSurface(bn[i].texture);
		i++;
	}
}

void	draw_label(t_all *all, char *name, SDL_Rect area, SDL_Color color)
{
	SDL_Surface *surf;

	surf = get_text_surface(name, all->font, color);
	draw_texture(all->sdl.screen, area, surf);
	SDL_FreeSurface(surf);
}

void	draw_labels(t_all *all, t_labels label[5], int num)
{
	int i;

	i = num;
	while (i < 9)
	{
		draw_texture(all->sdl.screen, label[i].dst, label[i].surf);
		i++;
	}
	draw_buttons(all, &all->sdl, all->buttons, num);
}

void	draw_ui(t_all *all, t_sdl *sdl, t_button *btn)
{
	draw_fill_rect(all, (SDL_Rect){0, 0, W / 4, H}, GREY);
	draw_fill_rect(all, (SDL_Rect){4, 4, W / 4 - 8, H - 8}, LAZUR);
	if (btn[NEW_SECT].state || all->swap_num >= 0)
		draw_labels(all, all->labels, 0);
	else
		draw_labels(all, all->labels, 2);
	draw_digits(sdl, all, all->draw_floors.x, all->draw_floors.y);
	draw_setting_digits(all, &all->player.settings);
}
