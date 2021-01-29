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
	tmp = get_text_surface(cx, all->font, BLUE);
	free(cx);
	draw_texture(all->sdl.screen, area[0], tmp);
	SDL_FreeSurface(tmp);
	tmp = get_text_surface(cy, all->font, BLUE);
	free(cy);
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
	// area[2] = (SDL_Rect){W / 11, H * 0.46, W / 16, 50};
	// area[3] = (SDL_Rect){W / 11, H * 0.58, W / 16, 50};
	x = (int)all->draw_floors.x;
	y = (int)all->draw_floors.y;
	t = ft_itoa(x);
	tmp = get_text_surface(t, all->font, BLUE);
	free(t);
	draw_texture(sdl->screen, area[0], tmp);
	SDL_FreeSurface(tmp);
	t = ft_itoa(y);
	tmp = get_text_surface(t, all->font, BLUE);
	free(t);
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
		
		btn[i].texture = get_text_surface(btn[i].title, all->font, btn[i].color);
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
	while(i < 9)
	{
		draw_texture(all->sdl.screen, label[i].dst, label[i].surf);
		i++;
	}
	draw_buttons(all, &all->sdl, all->buttons, num);
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

void	draw_ui(t_all *all, t_sdl *sdl, t_button *btn)
{
	draw_fill_rect(all, (SDL_Rect){4, 4, W / 4 - 8, H - 8}, LAZUR);
	if(btn[NEW_SECT].state || all->swap_num >= 0)
		draw_labels(all, all->labels, 0);
	else
		draw_labels(all, all->labels, 2);
	draw_digits(sdl, all, all->draw_floors.x, all->draw_floors.y);
	draw_setting_digits(all, &all->player.settings);
}
