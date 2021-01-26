/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilits.h"

void		exc(const char *file, const char *function)
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

void		clean(t_engine *engine)
{
	unload_data(engine);
	IMG_Quit();
	SDL_FreeSurface(engine->img[0].tx);
	SDL_FreeSurface(engine->img[1].tx);
	SDL_FreeSurface(engine->img[2].tx);
	SDL_FreeSurface(engine->img[3].tx);
	SDL_FreeSurface(engine->img[4].tx);
	if (engine->screen)
		SDL_FreeSurface(engine->screen);
	if (engine->window)
		SDL_DestroyWindow(engine->window);
}
