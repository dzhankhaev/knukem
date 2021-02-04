/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:32:47 by sisidra           #+#    #+#             */
/*   Updated: 2020/11/27 13:32:49 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

SDL_Surface		*get_texture(char *file, t_all *all)
{
	SDL_Surface	*surface;
	char		*dir;

	dir = ft_strjoin(all->src_dir, file);
	if (!(surface = SDL_LoadBMP(dir)))
		error_and_close(__FILE__, __FUNCTION__);
	free(dir);
	return (surface);
}

int				extra_buttons(t_button *buttons)
{
	buttons[6] = (t_button){(SDL_Rect){W / 4 - 150, H * 0.15, 50, 50},\
		ft_strdup(" - "), WHITE, 0, NULL};
	buttons[7] = (t_button){(SDL_Rect){W / 4 - 50, H * 0.15, 50, 50},\
		ft_strdup(" + "), WHITE, 0, NULL};
	buttons[8] = (t_button){(SDL_Rect){W / 4 - 150, H * 0.21, 50, 50},\
		ft_strdup(" - "), WHITE, 0, NULL};
	buttons[9] = (t_button){(SDL_Rect){W / 4 - 50, H * 0.21, 50, 50},\
		ft_strdup(" + "), WHITE, 0, NULL};
	buttons[10] = (t_button){(SDL_Rect){W / 4 - 150, H * 0.27, 50, 50},\
		ft_strdup(" - "), WHITE, 0, NULL};
	buttons[11] = (t_button){(SDL_Rect){W / 4 - 50, H * 0.27, 50, 50},\
		ft_strdup(" + "), WHITE, 0, NULL};
	buttons[12] = (t_button){(SDL_Rect){W / 4 - 150, H * 0.33, 50, 50},\
		ft_strdup(" - "), WHITE, 0, NULL};
	buttons[13] = (t_button){(SDL_Rect){W / 4 - 50, H * 0.33, 50, 50},\
		ft_strdup(" + "), WHITE, 0, NULL};
	buttons[14] = (t_button){(SDL_Rect){25, H * 0.46, 50, 50},\
		ft_strdup(" - "), WHITE, 0, NULL};
	buttons[15] = (t_button){(SDL_Rect){(W / 4 - 4) - 75, H * 0.46, 50, 50},\
		ft_strdup(" + "), WHITE, 0, NULL};
	buttons[16] = (t_button){(SDL_Rect){25, H * 0.58, 50, 50},\
		ft_strdup(" - "), WHITE, 0, NULL};
	buttons[17] = (t_button){(SDL_Rect){(W / 4 - 4) - 75, H * 0.58, 50, 50},\
		ft_strdup(" + "), WHITE, 0, NULL};
	return (0);
}

int				load_buttons(t_button *buttons)
{
	int i;

	buttons[0] = (t_button){(SDL_Rect){W / 16, H * 0.01, W / 8, 50},\
		ft_strdup("NEW SECTOR"), WHITE, 0, NULL};
	buttons[1] = (t_button){(SDL_Rect){W / 16, H * 0.07, W / 8, 50},\
		ft_strdup("SET PLAYER"), WHITE, 0, NULL};
	buttons[2] = (t_button){(SDL_Rect){25, H * 0.75, 50, 50},\
		ft_strdup(" - "), WHITE, 0, NULL};
	buttons[3] = (t_button){(SDL_Rect){(W / 4 - 4) - 75, H * 0.75, 50, 50},\
		ft_strdup(" + "), WHITE, 0, NULL};
	buttons[4] = (t_button){(SDL_Rect){25, H * 0.86, 50, 50},\
		ft_strdup(" - "), WHITE, 0, NULL};
	buttons[5] = (t_button){(SDL_Rect){(W / 4 - 4) - 75, H * 0.86, 50, 50},\
		ft_strdup(" + "), WHITE, 0, NULL};
	extra_buttons(buttons);
	i = 0;
	while (i < BUTTONS)
		buttons[i++].state = 0;
	return (1);
}

int				load_labels(t_all *all, t_labels *labels)
{
	labels[FLOOR].dst = (SDL_Rect){W / 16, H * 0.4, W / 8, 50};
	labels[FLOOR].surf = get_text_surface("FLOOR HEIGHT", all->font, BLACK);
	labels[CEIL].dst = (SDL_Rect){W / 16, H * 0.52, W / 8, 50};
	labels[CEIL].surf = get_text_surface("CEIL HEIGHT", all->font, BLACK);
	labels[SHOW].dst = (SDL_Rect){W / 16, H * 0.68, W / 8, 50};
	labels[SHOW].surf = get_text_surface("SHOW FLOORS", all->font, BLACK);
	labels[FROM].dst = (SDL_Rect){W / 16 + W / 96, H * 0.81, W / 10, 30};
	labels[FROM].surf = get_text_surface("FROM", all->font, BLACK);
	labels[TO].dst = (SDL_Rect){W / 11, H * 0.92, W / 16, 30};
	labels[TO].surf = get_text_surface("TO", all->font, BLACK);
	labels[INVENTORY].dst = (SDL_Rect){15, H * 0.17, W / 10, 30};
	labels[INVENTORY].surf = get_text_surface("INV.size", all->font, BLACK);
	labels[SPEED].dst = (SDL_Rect){15, H * 0.23, W / 10, 30};
	labels[SPEED].surf = get_text_surface("SPEED", all->font, BLACK);
	labels[GRAVITY].dst = (SDL_Rect){15, H * 0.29, W / 10, 30};
	labels[GRAVITY].surf = get_text_surface("GRAVITY", all->font, BLACK);
	labels[AMMO].dst = (SDL_Rect){15, H * 0.35, W / 10, 30};
	labels[AMMO].surf = get_text_surface("AMMO", all->font, BLACK);
	return (1);
}

int				load_texture(t_all *all)
{
	if (!(load_buttons(all->buttons) == 1))
		error_and_close(__FILE__, __FUNCTION__);
	if (!(load_labels(all, all->labels) == 1))
		error_and_close(__FILE__, __FUNCTION__);
	if (!(all->player.picture = get_texture("player.bmp", all)))
		error_and_close(__FILE__, __FUNCTION__);
	return (0);
}
