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
#include "archiver.h"

void	arg_check(t_engine *engine, t_all *all, int av, char **ac)
{
	int fd;
	struct stat		sb;
	char			*sub_name;
	
	int i = stat(ac[1], &sb);
	ft_bzero(engine, sizeof(*engine));
	engine->player.game_mode = 1;
	if (av == 1)
	{
		all->threed = 1;
		if (stat("default.map", &sb) == 0 && !S_ISDIR(sb.st_mode))
		{
			unpack_files("default.map", "");
			all->src_dir = ft_strdup("textures/");
		}
		else if ((stat("textures", &sb) == 0) && (S_ISDIR(sb.st_mode)))
		{
			all->src_dir = ft_strdup("textures/");
		}
		else
			exit_error();
		// all->name = ft_strdup("new_map.txt");
		// new_map(all->name);
	}
	else if (av == 2 && (stat(ac[1], &sb) == 0))
	{
		if (!S_ISDIR(sb.st_mode))
		{
			unpack_files(ac[1], "");
			all->src_dir = ft_strdup("textures/");
		}
		else if ((stat(ac[1], &sb) == 0) && (S_ISDIR(sb.st_mode)))
			all->src_dir = ft_strdup(ac[1]);
		else
			exit_error();
	}
	else if (av == 3)
	{
		if (ac[2][0] == 'g' && ac[2][1] == '\0')
		{
			unpack_files(ac[1], "");
			all->src_dir = ft_strdup("textures/");
			engine->player.game_mode = 0;
		}
		else
			exit(0);
	}
	else
		exit_error();
	sub_name = ft_strjoin(all->src_dir, "map.txt");
	all->name = ft_strdup(sub_name);
	free(sub_name);
}

void	clean_all(t_all *all)
{
	int i;

	free(all->name);
	TTF_CloseFont(all->font);
	all->font=NULL;
	TTF_Quit();
	if(all->temp.npoints)
		free(all->temp.vertex);
	if(all->temp.neighbors)
		free(all->temp.neighbors);
	i = 0;
	while (i < 9)
		SDL_FreeSurface(all->labels[i++].surf);
	i = 0;
	while (i < BUTTONS)
		free(all->buttons[i++].title);

}

void	load_tx(t_engine *engine, char *name)
{
	char		*line;
	int			fd;
	int			i;

	if (!(fd = open(name, O_RDONLY)))
		exc(__FILE__, __FUNCTION__);
	i = 0;
	while (get_next_line(fd, &line))
	{
		load_img(engine, line, i++);
		free(line);
	}
	if (i != 10)
	{
		fd = 0;
		while (fd < i)
			SDL_FreeSurface(engine->img[fd++].tx);
		exc(__FILE__, __FUNCTION__);
	}
	load_img(engine, "textures/icon.png", 10);
	close(fd);
	SDL_SetWindowIcon(engine->window, engine->img[10].tx);
}

int		main(int av, char **ac)
{
	t_engine	engine;
	t_all		all;
	char		*sub;

	// pack_files("textures/files","map1.map");
	arg_check(&engine, &all, av, ac);
	init_engine(&engine, &all);
	sub = ft_strjoin(all.src_dir, "nmap.txt");
	load_tx(&engine, sub);
	free(sub);
	init_all(&all);
	general_init(&engine, &all);
	game_loop(&engine, &all);
	clean(&engine);
	clean_all(&all);
	SDL_Quit();
	exit(0);
}
