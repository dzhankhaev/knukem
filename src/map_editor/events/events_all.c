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

void	level_buttons(t_all *all, t_button *btns, SDL_MouseButtonEvent *event)
{
	int i;
	int	dx;
	int	dy;
	int	count;

	i = 2;
	count = (all->buttons[NEW_SECT].state == 1 || \
		all->swap_num >= 0) ? BUTTONS : BUTTONS - 4;
	while (i < count)
	{
		dx = event->x - btns[i].dstrect.x;
		dy = event->y - btns[i].dstrect.y;
		if (all->mouse.z == 1)
			if (dx > 0 && dy > 0 && dx < btns[i].dstrect.w && dy < \
					btns[i].dstrect.h)
				btns[i].state = btns[i].state == 1 ? 0 : 1;
		i++;
	}
}

void	button_click(t_all *all, t_button *bt, SDL_MouseButtonEvent *event, \
	int i)
{
	int	dx;
	int	dy;

	while (i < BUTTONS - 8)
	{
		dx = event->x - bt[i].dstrect.x;
		dy = event->y - bt[i].dstrect.y;
		if (all->mouse.z == 1)
		{
			if (dx > 0 && dy > 0 && dx < bt[i].dstrect.w && dy < \
					bt[i].dstrect.h)
				bt[i].state = bt[i].state == 1 ? 0 : 1;
			else
				bt[i].state = 0;
			all->swap_num = -1;
		}
		else if (all->mouse.z == 0)
			bt[i].color = (dx > 0 && dy > 0 && dx < bt[i].dstrect.w && dy < \
				bt[i].dstrect.h && bt[i].state != 1) ? GREY : WHITE;
		i++;
	}
	all->player.picked = bt[1].state == 1 ? 1 : 0;
}

void	sprite_click(t_all *all, t_button *btns, SDL_MouseButtonEvent *event, \
	int i)
{
	int			dx;
	int			dy;
	SDL_Rect	target;

	while (i < 5)
	{
		target = btns[i].dstrect;
		dx = event->x - target.x;
		dy = event->y - target.y;
		if (all->mouse.z == 1)
		{
			if (dx > 0 && dy > 0 && dx < target.w && dy < target.h)
				btns[i].state = btns[i].state == 1 ? 0 : 1;
			else
				btns[i].state = 0;
		}
		i++;
	}
}

void	on_mouse(t_all *all, SDL_MouseButtonEvent *event)
{
	SDL_Rect	*temp;

	temp = &all->area;
	if (event->x >= temp->x && event->x <= (temp->x + temp->w) &&
			event->y >= temp->y && event->y <= (temp->y + temp->h))
	{
		SDL_GetMouseState(&all->point.x, &all->point.y);
		closest_point(all, all->point);
		if (all->mouse.z == 1)
		{
			all->mouse = (t_xyz){event->x - temp->x, event->y - temp->y, 0};
			map_click(all, event);
		}
	}
	else if (event->x < W * 0.25 && event->y < H * 0.2)
		button_click(all, all->buttons, event, 0);
	else
		level_buttons(all, all->buttons, event);
}

void	on_event(t_all *all, SDL_Event *event)
{
	if (event->type == SDL_QUIT)
	{
		if (mode_switch(all, 0))
			all->threed = 2;
	}
	else if (event->key.type == SDL_KEYDOWN)
		key_press(all);
	else if (event->button.type == SDL_MOUSEBUTTONDOWN)
		all->mouse.z = 1;
	else if (event->button.type == SDL_MOUSEBUTTONUP)
		all->mouse.z = 0;
	else if (event->wheel.type == SDL_MOUSEWHEEL)
	{
		if (event->wheel.y < 0)
			all->step -= all->step > 10 ? 2 : 0;
		else if (event->wheel.y > 0)
			all->step += all->step < 50 ? 2 : 0;
	}
	on_mouse(all, &event->button);
}
