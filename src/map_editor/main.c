#include "editor.h"
#include "engine.h"

void	apply_changes(t_all *all, t_button *btn)
{
	int		i;
	t_xy	*temp;

	temp = btn[0].state == 0 ? &all->draw_floors : &all->set_floors;
	i = 2;
	while (i < BUTTONS)
	{
		if (btn[i].state == 1)
			break;
		i++;
	}
	if (i - 2 == 0)
		temp->x -= 1;
	else if (i - 2 == 1)
	{
		temp->y += temp->x == temp->y ? 1 : 0;
		temp->x += 1;
	}
	else if (i - 2 == 2)
	{
		temp->x -= temp->y == temp->x ? 1 : 0;
		temp->y -= 1;
	}
	else if (i - 2 == 3)
		temp->y += 1;
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
		apply_changes(all, all->buttons);
		if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP || event.type == SDL_MOUSEMOTION
			|| event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_LockSurface(all->sdl->screen);
			ft_bzero((void*)all->sdl->screen->pixels, (size_t)(4 * W * H));
			draw_all(all, all->sdl, all->buttons);
			event.type = 0; // отрисовка
			SDL_UnlockSurface(all->sdl->screen);
			SDL_UpdateWindowSurface(all->sdl->window);
			SDL_FreeSurface(all->sdl->screen);
		}
	}
}

int main_editor(t_engine *engine, char *name, t_all *all)
{
//    t_all           *all;
	
//	if(ac > 2)
//	{
//		printf("Enter correct map name or new map name!\n");
//		exit(0);
//	}
    init_all(all); // инициализация всех модулей
	printf("level z = %d\n", (int)all->draw_floors.y);
//	if (load_map(name, all) != 0)
//		error_and_close(__FILE__, __FUNCTION__);
	if (load_texture(all) != 0)
		error_and_close(__FILE__, __FUNCTION__); //загрузка текстур
	//draw_texture(all->sdl->renderer, (SDL_Rect){0,0, WIDTH, HEIGHT}, all->texture);
	
	interact(all);// основная функция взаимодействия
//	write_map(av[1], all);
	engine->sectors = all->sectors;
	engine->player.where = all->player.where;
	engine->player.sector = all->player.sector;
	return (0);
}
