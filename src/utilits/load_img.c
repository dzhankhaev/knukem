/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/02/09 03:47:31 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "utilits.h"

void		load_img(t_engine *engine, char *name, int n)
{
	SDL_Surface *img;
	SDL_Surface	*i;

	if (!(img = IMG_Load(name)))
	{
		clean(engine);
		exc(__FILE__, __FUNCTION__);
	}
	i = img;
	if (!(img = SDL_ConvertSurface(img, engine->screen->format, 0)))
	{
		SDL_FreeSurface(i);
		clean(engine);
		exc(__FILE__, __FUNCTION__);
	}
	SDL_FreeSurface(i);
	engine->img[n].tx = img;
}
