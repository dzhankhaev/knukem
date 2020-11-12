#include "editor.h"

void	key_press(t_all *all)
{
	const Uint8	*keystate;

	keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_ESCAPE])
	{
		//SDL_DestroyTexture(all->texture);
    	SDL_DestroyWindow(all->sdl->window);
	    SDL_Quit();
		free(all->sectors);
		free(all->sdl);
		free(all);
		exit(0);
	}
	else if (keystate[SDL_SCANCODE_TAB])
		write_map("new", all);
	else if (keystate[SDL_SCANCODE_RIGHT])
		all->step += 1;
	else if (keystate[SDL_SCANCODE_LEFT])
		all->step -= (all->step > 1) ? 1 : 0;
	else if (keystate[SDL_SCANCODE_I])
		all->iso = (all->iso == 0) ? 1 : 0;
	else if (keystate[SDL_SCANCODE_UP])
		all->set_floors.x += 1;
	else if (keystate[SDL_SCANCODE_DOWN])
		all->set_floors.y += 1;
}

void		level_buttons(t_all *all, t_button *buttons, SDL_MouseButtonEvent *event)
{
	int i;
	int	dx;
	int	dy;

	i = 2;
	while(i < BUTTONS)
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

	while(i < BUTTONS - 4)
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
	all->player.picked = buttons[1].state == 1 ? 1 : 0;
}

// t_xyz	coordinator(t_all *all, int x, int y, t_xyz rot)
// {
// 	t_xyz temp;
// 	int z;

// 	temp.x = x / all->step - (all->area.w/all->step/2 - all->mapsize.x/2);
// 	temp.y = y / all->step - (all->area.h/all->step/2 - all->mapsize.y/2);
// 	temp.z = z / all->step + all->mapsize.z;
// 	return(temp);
// }

void	closest_point(t_all *all, t_xyint point, t_xyz mouse)
{
	t_xy	   c;

	c = (t_xy){(all->area.w / 2) % all->step, (all->area.h / 2) % all->step};
	if(all->player.picked)
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

void	on_mouse(t_all *all, SDL_MouseButtonEvent *event)
{
	SDL_Rect	*temp;
	int			x;
	int			y;

	x = all->mouse.x;
	y = all->mouse.y;
	temp = &all->area;

	if (event->x >= temp->x && event->x <= (temp->x + temp->w) &&
			event->y >= temp->y && event->y <= (temp->y + temp->h))
	{
		SDL_GetMouseState(&all->point.x, &all->point.y);
		closest_point(all, all->point, all->mouse);
		if (all->mouse.z == 1)
		{
			all->mouse = (t_xyz){event->x - temp->x, event->y - temp->y};//пишем координаты мыши на карте
			map_click(&all->mouse, all);
		}
	}
	else if (event->x < WIDTH / 4 && event->y < HEIGHT / 4)
		button_click(all, all->buttons, event, 0); // обработка кликов на панели управления
	else
		level_buttons(all, all->buttons, event);
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

/* дописать 
1 - удаление сектора
2 - сдвиг координат
3 - бэкграунд через имадж
4 - вывод в файл
5 - чтение файла
6 - подключение движка
7 - выбор текстуры */