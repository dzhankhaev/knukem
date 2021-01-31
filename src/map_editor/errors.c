/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:32:59 by sisidra           #+#    #+#             */
/*   Updated: 2020/11/27 13:33:02 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		error_and_close(const char *file, const char *function)
{
	int		i;

	i = 0;
	write(1, "ERROR: In file ", 15);
	while (file[i] != '\0')
		write(1, &file[i++], 1);
	write(1, " function ", 10);
	i = 0;
	while (function[i] != '\0')
		write(1, &function[i++], 1);
	write(1, " is not success finishing!\n", 27);
	exit(0);
}

int			print_message(t_all *all, SDL_Color color, char *text, int delay)
{
	SDL_Surface	*temp;
	SDL_Rect	area;

	area = (SDL_Rect){W / 2 - 175, H / 2 - 25, 300, 50};
	temp = get_text_surface(text, all->font, color);
	draw_fill_rect(all, area, GREY);
	draw_texture(all->sdl.screen, area, temp);
	SDL_UpdateWindowSurface(all->sdl.window);
	SDL_Delay(delay);
	SDL_FreeSurface(temp);
	return (0);
}
