#include "editor.h"
#include "engine.h"

int		button_pressed(int i, t_button *buttons)
{
	while(i < BUTTONS)
	{
		if(buttons[i].state)
			break;
		i++;
	}
	return (i);
}

void	apply_changes(t_all *all, t_button *btn, int i)
{
	t_xy	*temp;
	
	i = button_pressed(i, btn);
	temp = i < 14 ? &all->draw_floors : &all->set_floors;
	if ((i - 2 == 0 || i - 14 == 0) && temp->x > 0)
		temp->x -= 1;
	else if ((i - 2 == 1 || i - 14 == 1) && temp->y < 200)
	{
		temp->y += temp->x == temp->y ? 1 : 0;
		temp->x += 1;
	}
	else if ((i - 2 == 2 || i - 14 == 2) && temp->y > 0)
	{
		temp->x -= temp->y == temp->x ? 1 : 0;
		temp->y -= 1;
	}
	else if ((i - 2 == 3 || i - 14 == 3) && temp->y < 200)
		temp->y += 1;
}

void	sector_change(t_all *all, t_sect *sectors, int num)
{
	int i;

	i = button_pressed(14, all->buttons);
	if (i - 14 == 0 && sectors[num].floor > 0)
		sectors[num].oldf = sectors[num].floor -= 1;
	else if (i - 14 == 1 && sectors[num].floor < 200)
	{
		sectors[num].ceil += sectors[num].floor == sectors[num].ceil ? 1 : 0;
		sectors[num].oldf = sectors[num].floor += 1;
	}
	else if (i - 14 == 2 && sectors[num].ceil > 0)
	{
		sectors[num].oldf = sectors[num].floor -=\
			(sectors[num].floor == sectors[num].ceil ? 1 : 0);
		sectors[num].ceil -= 1;
	}
	else if (i - 14 == 3 && sectors[num].ceil < 200)
		sectors[num].ceil += 1;
	if (sectors[num].ceil - sectors[num].floor < 6)
		all->player.sector = -1;
}

void	game_setting_values(t_settings *set, t_button *btns)
{
	int i;

	i = button_pressed(6, btns);
	if (i == 6 && set->inventory > 1)
		set->inventory--;
	else if (i == 7 && set->inventory < 9)
		set->inventory++;
	else if (i == 8 && set->speed > 10)
		set->speed -= 10;
	else if (i == 9 && set->speed < 100)
		set->speed += 10;
	else if (i == 10 && set->gravity > 10)
		set->gravity -= 10;
	else if (i == 11 && set->gravity < 100)
		set->gravity += 10;
	else if (i == 12 && set->ammo > 0)
		set->ammo -= 5;
	else if (i == 13 && set->ammo < 30)
		set->ammo += 5;
}

void    interact(t_all *all)
{
	SDL_Event		event;
	Uint32			cur_time;
	Uint32			last_time;

	while ((last_time = SDL_GetTicks()) && all->threed == 0)
	{
		while (SDL_PollEvent(&event)) // отслеживаем события
		{
			on_event(all, &event); // обработчик событий
			cur_time = SDL_GetTicks();
			if (cur_time - last_time > FPS)
				break ;
		}
		if(all->swap_num == -1)
		{
			apply_changes(all, all->buttons, 2);
			game_setting_values(&all->player.settings, all->buttons);
		}
		else
			sector_change(all, all->sectors, all->swap_num);
		
		if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP || event.type == SDL_MOUSEMOTION
			|| event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN || all->on)
		{
			SDL_LockSurface(all->sdl->screen);
			ft_bzero((void*)all->sdl->screen->pixels, (size_t)(4 * W * H));
			draw_all(all, all->sdl, all->buttons);
			event.type = 0; // отрисовка
			SDL_UnlockSurface(all->sdl->screen);
			SDL_UpdateWindowSurface(all->sdl->window);
			SDL_FreeSurface(all->sdl->screen);
		}
		all->on = 0;
	}
}

int main_editor(t_engine *engine, t_all *all)
{
	if (&engine->player == &all->player)
		printf("YY\n");
    init_all(all); // инициализация всех модулей
	// printf("level z = %d\n", (int)all->draw_floors.y);
	if (load_texture(all) != 0)
		error_and_close(__FILE__, __FUNCTION__); //загрузка текстур
	interact(all);// основная функция взаимодействия
	engine->sectors = all->sectors;
	engine->player.where = all->player.where;
	engine->player.sector = all->player.sector;
	engine->player.settings = all->player.settings;
	engine->player.move_speed = ((float)engine->player.settings.speed / 100.f)
								* 0.3f + MOVE_SPEED;
	engine->player.speed = engine->player.move_speed;
	engine->num_sectors = all->num_sectors;
	return (0);
}
