#include "editor.h"



void	draw_sector_info(t_sect sect, t_sdl *sdl, int n, t_all *all)
{
	SDL_Surface *tmp;
	char		*str;
	char		*num;
	SDL_Rect	area;

	tmp = NULL;
	str = NULL;
	num = NULL;
	area = (SDL_Rect){W - 105, 25, 100 ,30};
	num = ft_itoa(n);
	tmp = get_text_surface(all, ft_strjoin("sector ", num), area, YELLOW);
	draw_texture(sdl, area, tmp);
	SDL_FreeSurface(tmp);
	free(num);
	area = (SDL_Rect){W - 105, 55, 100 ,30};
	num = ft_itoa(sect.floor);
	tmp = get_text_surface(all, ft_strjoin("floor  ", num), area, YELLOW);
	draw_texture(sdl, area, tmp);
	SDL_FreeSurface(tmp);
	free(num);
	area = (SDL_Rect){W - 105, 85, 100 ,30};
	num = ft_itoa(sect.ceil);
	tmp = get_text_surface(all, ft_strjoin("ceil   ", num), area, YELLOW);
	draw_texture(sdl, area, tmp);
	SDL_FreeSurface(tmp);
	free(num);
}




void	draw_area(t_sdl *sdl, t_all *all)
{
	t_xy	   c;

	c = (t_xy){(all->area.w / 2) % all->step, (all->area.h / 2) % all->step};
	draw_fill_rect(all, all->area, BLACK);
	draw_grid(all, &all->area, all->step);
	draw_map(sdl, all->sectors, all);
	if (!all->player.picked)
		draw_circle(all->sdl, (t_xy){all->point.x * all->step + c.x + all->area.x, 
			all->point.y * all->step + c.y + all->area.y}, 2, WHITE);
	if (all->temp->npoints > 0)
		// draw_sector(all->temp, all, all->color);
	 	draw_temp(all, sdl, all->temp, all->delta); /// uncomment to defeat segfault
	draw_player(all, sdl, &all->player, &c);
}

void	draw_all(t_all *all, t_sdl *sdl, t_button *btn)
{
	Uint32 state;

	all->delta.x = all->area.x + all->area.w/2 - 
		(round(all->mapsize.x/2) * all->step) + all->d.x * all->step;
	all->delta.y = all->area.y + all->area.h/2 - 
		(round(all->mapsize.y/2) * all->step) + all->d.y * all->step;
	draw_area(sdl, all);
	draw_ui(all, sdl, btn);
	if(all->swap_num != -1)
		draw_sector_info(all->sectors[all->swap_num], sdl, all->swap_num, all);

}
