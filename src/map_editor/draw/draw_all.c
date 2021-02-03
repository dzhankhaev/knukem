/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:31:12 by sisidra           #+#    #+#             */
/*   Updated: 2020/11/27 13:31:42 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_sector_info(t_sdl *sdl, int n, t_all *all)
{
	SDL_Surface *tmp;
	char		*num;
	char		*t;
	SDL_Rect	area;

	tmp = NULL;
	area = (SDL_Rect){W - 105, 5, 100, 25};
	num = ft_itoa(n);
	t = ft_strjoin("s e c t o r ", num);
	ft_memdel((void*)&num);
	tmp = get_text_surface(t, all->font, YELLOW);
	ft_memdel((void*)&t);
	draw_texture(sdl->screen, area, tmp);
	SDL_FreeSurface(tmp);
}

void	draw_area(t_sdl *sdl, t_all *all)
{
	t_xy		c;

	c = (t_xy){(all->area.w / 2) % all->step, (all->area.h / 2) % all->step};
	draw_fill_rect(all, all->area, BLACK);
	draw_grid(all, &all->area, all->step);
	if (all->num_sectors)
		draw_map(all->sectors, all);
	if (all->buttons[NEW_SECT].state == 1)
		draw_circle(sdl, (t_xy){all->point.x * all->step + c.x + all->area.x,
			all->point.y * all->step + c.y + all->area.y}, 2, WHITE);
	if (all->temp.npoints > 0 && all->buttons[0].state == 1)
		draw_temp(all, sdl, &all->temp, all->delta);
	if (all->player.sector != -1)
		draw_player(all, sdl, &all->player, &c);
}

void	draw_all(t_all *all, t_sdl *sdl, t_button *btn)
{
	all->delta.x = all->area.x + all->area.w / 2 -
		(round(all->mapsize.x / 2) * all->step) + all->d.x * all->step;
	all->delta.y = all->area.y + all->area.h / 2 -
		(round(all->mapsize.y / 2) * all->step) + all->d.y * all->step;
	draw_area(sdl, all);
	draw_ui(all, sdl, btn);
	if (all->swap_num != -1)
		draw_sector_info(sdl, all->swap_num, all);
}
