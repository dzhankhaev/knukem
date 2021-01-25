/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 07:04:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "editor.h"
#include "utilits.h"

/**
 * Setup a window app icon
 */
void setup_window_icon(t_engine *engine)
{
	SDL_Surface *iconSurface;
	load_img(engine, "icon.png", 6);
	iconSurface = engine->img[6].tx;
	//iconSurface = IMG_Load("textures/icon.png");

	// The icon requires the window pointer NOT the renderer
	SDL_SetWindowIcon(engine->window, iconSurface);

	// ...and can now free the appicon surface
	SDL_FreeSurface(iconSurface);
}

void	arg_check(t_engine *engine, t_all *all, int av, char **ac)
{
	ft_bzero(engine, sizeof(*engine));
	engine->player.game_mode = 1;
	if (av == 1)
	{
		all->name = ft_strdup("new_map.txt");
		new_map(all->name);
	}
	else if (av == 2)
		all->name = ft_strdup(ac[1]);
	else if (av == 3)
	{
		if (ac[2][0] == 'g' && ac[2][1] == '\0')
		{
			all->name = ft_strdup(ac[1]);
			engine->player.game_mode = 0;
		}
		else
			exit(0);
	}
}

void	clean_all(t_all *all)
{
	int i;

	TTF_CloseFont(all->font);
	all->font=NULL;
	TTF_Quit();
	if(all->temp->npoints)
		free(all->temp->vertex);
	if(all->temp->neighbors)
		free(all->temp->neighbors);
	free(all->temp);
	all->temp = NULL;
	i = 0;
	while (i < 9)
		SDL_FreeSurface(all->labels[i++].surf);
	i = 0;
	while (i < BUTTONS)
		free(all->buttons[i++].title);

}

int		main(int av, char **ac)
{
	t_engine	engine;
	t_all		all;

	arg_check(&engine, &all, av, ac);
	init_all(&all);
	init_engine(&engine, &all);
	general_init(&engine);
	setup_window_icon(&engine);
	load_texture(&all);
	load_img(&engine, "wall1.png", 0);
	load_img(&engine, "wall2.png", 1);
	load_img(&engine, "wall3.png", 2);
	load_img(&engine, "floor1.png", 3);
	load_img(&engine, "ceil1.png", 4);
	load_img(&engine, "sky1.png", 5);
	game_loop(&engine, &all);
	clean(&engine);
	clean_all(&all);
	return (0);
}
