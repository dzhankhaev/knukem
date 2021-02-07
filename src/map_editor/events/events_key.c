/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:32:36 by sisidra           #+#    #+#             */
/*   Updated: 2021/01/12 17:48:01 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		mode_switch(t_all *all, int mode)
{
	if (all->player.sector == -1)
	{
		print_message(all, RED, "SET PLAYER!", 1000);
		return (0);
	}
	if (all->fin_sect == -1)
	{
		print_message(all, RED, "SET FINAL SECTOR!", 1000);
		return (0);
	}
	else
	{
		normalize(all->sectors, all->num_sectors, all);
		if (mode)
			print_message(all, RED, "MAP SAVED!", 500);
		else
			print_message(all, RED, "ENTERING 3D!", 500);
	}
	return (1);
}

void	key_press(t_all *all)
{
	const Uint8	*keystate;

	keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_E] && mode_switch(all, 0))
		all->threed = 1;
	else if (keystate[SDL_SCANCODE_ESCAPE] && mode_switch(all, 0))
		all->threed = 2;
	else if (keystate[SDL_SCANCODE_DELETE] || keystate[SDL_SCANCODE_BACKSPACE])
		remove_sector(all, all->sectors);
	else if (keystate[SDL_SCANCODE_TAB] && mode_switch(all, 1))
		write_map(all);
	else if (keystate[SDL_SCANCODE_RIGHT])
		all->d.x += abs((int)(all->d.x)) <= 300 ? 1 :
			print_message(all, RED, "SIZE LIMIT!", 1000);
	else if (keystate[SDL_SCANCODE_LEFT])
		all->d.x -= abs((int)(all->d.x)) <= 300 ? 1 :
			print_message(all, RED, "SIZE LIMIT!", 1000);
	else if (keystate[SDL_SCANCODE_UP])
		all->d.y -= abs((int)(all->d.x)) <= 300 ? 1 :
			print_message(all, RED, "SIZE LIMIT!", 1000);
	else if (keystate[SDL_SCANCODE_DOWN])
		all->d.y += abs((int)(all->d.x)) <= 300 ? 1 :
			print_message(all, RED, "SIZE LIMIT!", 1000);
}
