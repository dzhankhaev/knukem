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

int	mode_switch(t_all *all, int mode)
{
	SDL_Surface *temp;

	if (all->player.where.z != -1 && mode)
	{
		all->threed = 1;
		normalize(all->sectors, all->num_sectors, all);
		temp = get_text_surface(all, "Entering 3D!", all->font, RED);
		draw_texture(all->sdl->screen, (SDL_Rect){W/2 - 175, H/2 - 25, 300, 50}, temp);
		SDL_UpdateWindowSurface(all->sdl->window);
		SDL_Delay(1000);
		SDL_FreeSurface(temp);
	}
	else if (all->player.where.z == -1)
	{
		temp = get_text_surface(all, "Set player!", all->font, RED);
		draw_texture(all->sdl->screen, (SDL_Rect){W/2 - 175, H/2 - 25, 300, 50}, temp);
		SDL_UpdateWindowSurface(all->sdl->window);
		SDL_Delay(1000);
		SDL_FreeSurface(temp);
	}
	return(1);
}

void	key_press(t_all *all)
{
	const Uint8	*keystate;

	keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_E])
		mode_switch(all, 1);
	else if (keystate[SDL_SCANCODE_DELETE])
		remove_sector(all, all->sectors);
	else if (keystate[SDL_SCANCODE_TAB] && mode_switch(all, 0))
		write_map("new", all);
	else if (keystate[SDL_SCANCODE_RIGHT])
		all->d.x += 1;
	else if (keystate[SDL_SCANCODE_LEFT])
		all->d.x -= 1;//(all->step > 1) ? 1 : 0;
	else if (keystate[SDL_SCANCODE_I])
		all->iso = (all->iso == 0) ? 1 : 0;
	else if (keystate[SDL_SCANCODE_UP])
		all->d.y -= 1;
	else if (keystate[SDL_SCANCODE_DOWN])
		all->d.y += 1;
}

void		level_buttons(t_all *all, t_button *buttons, SDL_MouseButtonEvent *event)
{
	int i;
	int	dx;
	int	dy;
	int	count;


	i = 2;
	count = (all->buttons[NEW_SECT].state == 1 || \
		all->swap_num >= 0) ? BUTTONS : BUTTONS - 4;
	while(i < count)
	{
		dx = event->x - buttons[i].dstrect.x;
		dy = event->y - buttons[i].dstrect.y;
		if(all->mouse.z == 1)
			if(dx > 0 && dy > 0 && dx < buttons[i].dstrect.w && dy < buttons[i].dstrect.h)
				buttons[i].state = buttons[i].state == 1 ? 0 : 1;
		i++;
	}
}

void	button_click(t_all *all, t_button *buttons, SDL_MouseButtonEvent *event, int i)
{
	int	dx;
	int	dy;

	while(i < BUTTONS - 8)
	{
		dx = event->x - buttons[i].dstrect.x;
		dy = event->y - buttons[i].dstrect.y;
		if(all->mouse.z == 1)
		{
			if(dx > 0 && dy > 0 && dx < buttons[i].dstrect.w && dy < buttons[i].dstrect.h)
				buttons[i].state = buttons[i].state == 1 ? 0 : 1;
			else
				buttons[i].state = 0;
			all->swap_num = -1;
		}
		else if(all->mouse.z == 0)
		{
			if(dx > 0 && dy > 0 && dx < buttons[i].dstrect.w && dy < buttons[i].dstrect.h &&
			buttons[i].state != 1)
				buttons[i].color = GREY;
			else
				buttons[i].color = WHITE;
		}
		i++;
	}
	// all->player.picked = buttons[1].state == 1 ? 1 : 0;
}

void	closest_point(t_all *all, t_xyint point)
{
	t_xy	   c;

	c = (t_xy){(all->area.w / 2) % all->step, (all->area.h / 2) % all->step};
	if(all->player.picked != -1)
	{
		all->point.x = ((float)point.x - all->area.x - c.x) / all->step;
		all->point.y = ((float)point.y - all->area.y - c.y) / all->step;
	}
	else
	{
		all->point.x = round(((float)point.x - all->area.x - c.x) / all->step);
		all->point.y = round(((float)point.y - all->area.y - c.y) / all->step);
	}
	
}

void	sprite_click(t_all *all, t_button *buttons, SDL_MouseButtonEvent *event, int i)
{
	int	dx;
	int	dy;

	while(i < 5)
	{
		dx = event->x - buttons[i].dstrect.x;
		dy = event->y - buttons[i].dstrect.y;
		if(all->mouse.z == 1)
		{
			if(dx > 0 && dy > 0 && dx < buttons[i].dstrect.w && dy < buttons[i].dstrect.h)
				buttons[i].state = buttons[i].state == 1 ? 0 : 1;
			else
				buttons[i].state = 0;
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
			all->mouse = (t_xyz){event->x - temp->x, event->y - temp->y};//пишем координаты мыши на карте
			map_click(&all->mouse, all, event);
		}
	}
	else if (event->x < W * 0.25 && event->y < H * 0.2)
		button_click(all, all->buttons, event, 0); // обработка кликов на панели управления
	/*
	else if (event->x < W * 0.25 && event->y < H * 0.5 && event->y > \
			H * 0.2 && !all->buttons[NEW_SECT].state)
область для патронов, скорости и др.........................
			*/
	else
		level_buttons(all, all->buttons, event);//проверка нажатий кнопок + и -
}

void	on_event(t_all *all, SDL_Event *event)
{
	if (event->key.type == SDL_KEYDOWN)
		key_press(all); // обработка событий клавиатуры
	else if (event->button.type == SDL_MOUSEBUTTONDOWN)
		all->mouse.z = 1;
	else if (event->button.type == SDL_MOUSEBUTTONUP)
		all->mouse.z = 0;
	on_mouse(all, &event->button); // обаботка событий мыши
}

