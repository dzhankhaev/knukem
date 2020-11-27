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
	int l;

	l = i == 0 ? 2 : 4;
	while(i <= l)
	{
		draw_texture(all->sdl, label[i].dst, label[i].surf);
		i++;
	}
}

void	draw_digits(t_sdl *sdl, t_all *all, int x, int y)
{
	SDL_Surface *tmp;
	SDL_Rect	area[2];

	tmp = NULL;
	if (all->buttons[0].state == 1)
	{
		x = (int)all->set_floors.x;
		y = (int)all->set_floors.y;
	}
	area[0] = (SDL_Rect){W/16, 250, W/8, 150};
	area[1] = (SDL_Rect){W/16, 450, W/8, 150};
	tmp = get_text_surface(all, ft_itoa(x), area[0], BLUE);
	draw_texture(sdl, area[0], tmp);
	SDL_FreeSurface(tmp);
	tmp = get_text_surface(all, ft_itoa(y), area[1], BLUE);
	draw_texture(sdl, area[1], tmp);
	SDL_FreeSurface(tmp);
}

void	draw_player(t_all *all, t_sdl *sdl, t_player *player, t_xy *c)
{
	SDL_Rect loc;

	if (all->player.picked == 0)
		loc = (SDL_Rect){(player->where.x * all->step) + all->delta.x - all->step/2,
		 (player->where.y * all->step) + all->delta.y - all->step/2,
	 		 all->step, all->step};
	else if (all->player.picked == 1)
		loc = (SDL_Rect){all->point.x * all->step + c->x - all->step/2 + all->area.x,
			 all->point.y * all->step + c->y - all->step/2 + all->area.y, all->step, all->step};
	draw_texture(sdl, loc, player->picture);
}

void	draw_buttons(t_all *all, t_sdl *sdl, t_button *btn)
{
	int i;

	i = 0;
	while (i < BUTTONS)
	{ 
		btn[i].color = btn[i].state == 1 ? RED : btn[i].color;
		
		btn[i].texture = get_text_surface(all, btn[i].title, btn[i].dstrect, btn[i].color);
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

void	draw_ui(t_all *all, t_sdl *sdl, t_button *btn)
{
	draw_fill_rect(all, (SDL_Rect){4, 4, W / 4 - 8, H - 8}, LAZUR);
	draw_labels(all, all->labels, btn[0].state == 1 ? 3 : 0);
	draw_digits(sdl, all, all->draw_floors.x, all->draw_floors.y);
	draw_buttons(all, sdl, btn);
}
