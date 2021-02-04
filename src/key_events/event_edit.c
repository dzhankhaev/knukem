/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/12 19:35:09 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "events.h"

static void	numbers(t_player *player, t_edit *edit)
{
	if (player->event.key.keysym.sym == SDLK_0)
		edit->txno = 0;
	else if (player->event.key.keysym.sym == SDLK_1)
		edit->txno = 1;
	else if (player->event.key.keysym.sym == SDLK_2)
		edit->txno = 2;
	else if (player->event.key.keysym.sym == SDLK_3)
		edit->txno = 3;
	else if (player->event.key.keysym.sym == SDLK_4)
		edit->txno = 4;
	else if (player->event.key.keysym.sym == SDLK_5)
		edit->txno = 5;
	else if (player->event.key.keysym.sym == SDLK_6)
		edit->txno = 6;
	else if (player->event.key.keysym.sym == SDLK_7)
		edit->txno = 7;
	else if (player->event.key.keysym.sym == SDLK_8)
		edit->txno = 8;
	else if (player->event.key.keysym.sym == SDLK_9)
		edit->txno = 9;
}

void		event_edit22(t_player *player, t_edit *edit)
{
	numbers(player, edit);
	if (player->event.key.keysym.sym == SDLK_BACKQUOTE)
		edit->mod_tx = edit->mod_tx == 4 ? 0 : edit->mod_tx + 1;
	else if (player->event.key.keysym.sym == SDLK_e)
		edit->mod = 1;
	else if (player->event.key.keysym.sym == SDLK_g)
		edit->graf++;
	else if (player->event.key.keysym.sym == SDLK_BACKSPACE)
		edit->graf = 3;
	else if (player->event.key.keysym.sym == SDLK_h)
		edit->door = 1;
}

void		event_edit2(t_player *player, t_edit *edit)
{
	if (player->game_mode)
		event_edit22(player, edit);
	else
	{
		if (player->event.key.keysym.sym == SDLK_g)
			edit->graf_wall = -2;
		else if (player->event.key.keysym.sym == SDLK_r)
		{
			edit->graf = 2;
			edit->txno = 0;
		}
	}
	if (player->event.key.keysym.sym == SDLK_f)
		edit->door = 2;
}

void		event_edit(t_player *player, t_edit *edit)
{
	if (player->game_mode)
	{
		if (player->event.key.keysym.sym == SDLK_o)
			edit->hchange[0] = player->event.type == SDL_KEYDOWN;
		else if (player->event.key.keysym.sym == SDLK_p)
			edit->hchange[1] = player->event.type == SDL_KEYDOWN;
		else if (player->event.key.keysym.sym == SDLK_j)
			edit->hchange[2] = player->event.type == SDL_KEYDOWN;
		else if (player->event.key.keysym.sym == SDLK_k)
			edit->hchange[3] = player->event.type == SDL_KEYDOWN;
	}
}
