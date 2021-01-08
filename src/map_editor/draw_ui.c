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

void	draw_labels(t_all *all, t_labels label[5], int i)
{
	while(i < 5)
	{
		draw_texture(all->sdl, label[i].dst, label[i].surf);
		i++;
	}
	// draw_texture(all->sdl, all->sprites.gun->dstrect, all->sprites.gun->texture);
	// draw_texture(all->sdl, all->sprites.aid->dstrect, all->sprites.aid->texture);
	// draw_texture(all->sdl, all->sprites.enemy->dstrect, all->sprites.enemy->texture);
	// draw_texture(all->sdl, all->sprites.bazooka->dstrect, all->sprites.bazooka->texture);
	// draw_texture(all->sdl, all->sprites.player->dstrect, all->player.picture);


}

void	draw_digits(t_sdl *sdl, t_all *all, int x, int y)
{
	SDL_Surface	*tmp;
	SDL_Rect	area[4];

	area[0] = (SDL_Rect){W / 11, H * 0.75, W / 16, 50};
	area[1] = (SDL_Rect){W / 11, H * 0.86, W / 16, 50};
	area[2] = (SDL_Rect){W / 11, H * 0.46, W / 16, 50};
	area[3] = (SDL_Rect){W / 11, H * 0.58, W / 16, 50};
	x = (int)all->draw_floors.x;
	y = (int)all->draw_floors.y;
	tmp = get_text_surface(all, ft_itoa(x), all->font, BLUE);
	draw_texture(sdl, area[0], tmp);
	SDL_FreeSurface(tmp);
	tmp = get_text_surface(all, ft_itoa(y), all->font, BLUE);
	draw_texture(sdl, area[1], tmp);
	SDL_FreeSurface(tmp);
	if (all->buttons[0].state == 1)
	{
		x = (int)all->set_floors.x;
		y = (int)all->set_floors.y;
		tmp = get_text_surface(all, ft_itoa(x), all->font, BLUE);
		draw_texture(sdl, area[2], tmp);
		SDL_FreeSurface(tmp);
		tmp = get_text_surface(all, ft_itoa(y), all->font, BLUE);
		draw_texture(sdl, area[3], tmp);
		SDL_FreeSurface(tmp);	
	}
}

void	draw_buttons(t_all *all, t_sdl *sdl, t_button *btn)
{
	int i;
	int count;

	i = 0;
	count = all->buttons[0].state == 1 ? BUTTONS : BUTTONS - 4;
	while (i < count)
	{ 
		btn[i].color = btn[i].state == 1 ? RED : btn[i].color;
		
		btn[i].texture = get_text_surface(all, btn[i].title, all->font, btn[i].color);
		draw_texture(sdl, btn[i].dstrect, btn[i].texture);
		if (i >= 2)
		{
			btn[i].state = 0;
			btn[i].color = WHITE;
		}
		SDL_FreeSurface(btn[i].texture);
		i++;
    }
	
}

void	draw_sprite_buttons(t_all *all, t_sdl *sdl, t_button *buttons)
{
	int i;

	i = 0;
	while(i < 5)
	{
		if(buttons[i].state == 1)
			draw_rect(all, buttons[i].dstrect, GREEN, 3);
		draw_texture(sdl, buttons[i].dstrect, buttons[i].texture);
		i++;
	}
}

void	draw_ui(t_all *all, t_sdl *sdl, t_button *btn)
{
	draw_fill_rect(all, (SDL_Rect){4, 4, W / 4 - 8, H - 8}, LAZUR);
	draw_labels(all, all->labels, btn[0].state == 1 ? 0 : 2);
	draw_digits(sdl, all, all->draw_floors.x, all->draw_floors.y);
	draw_buttons(all, sdl, btn);
	if(!(all->buttons[NEW_SECT].state))
		draw_sprite_buttons(all, sdl, all->sprites.buttons);
}
