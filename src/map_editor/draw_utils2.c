#include "editor.h"

void	draw_labels(t_all *all, t_labels label[5], int i)
{
	int l;

	l = i == 0 ? 2 : 4;
	while(i <= l)
	{
		draw_texture(all->sdl, label[i].dst, label[i].surf);
		i++;
	}
}

void	draw_digits(t_sdl *sdl, t_all *all, int x, int y)
{
	SDL_Surface *tmp;
	SDL_Rect	area[2];

	tmp = NULL;
	if (all->buttons[0].state == 1)
	{
		x = (int)all->set_floors.x;
		y = (int)all->set_floors.y;
	}
	area[0] = (SDL_Rect){W/16, 250, W/8, 150};
	area[1] = (SDL_Rect){W/16, 450, W/8, 150};
	tmp = get_text_surface(all, ft_itoa(x), area[0], BLUE);
	draw_texture(sdl, area[0], tmp);
	SDL_FreeSurface(tmp);
	tmp = get_text_surface(all, ft_itoa(y), area[1], BLUE);
	draw_texture(sdl, area[1], tmp);
	SDL_FreeSurface(tmp);
}

void	draw_player(t_all *all, t_sdl *sdl, t_player *player, t_xy *c)
{
	SDL_Rect loc;

	if (all->player.picked == 0)
	//(temp->vertex[j].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step)
		loc = (SDL_Rect){(player->where.x * all->step) + all->delta.x - all->step/2,
		 (player->where.y * all->step) + all->delta.y - all->step/2,
	 		 all->step, all->step};
	else if (all->player.picked == 1)
		loc = (SDL_Rect){all->point.x * all->step + c->x - all->step/2 + all->area.x,
			 all->point.y * all->step + c->y - all->step/2 + all->area.y, all->step, all->step};
	draw_texture(sdl, loc, player->picture);
}

void	draw_grid(t_all *all, SDL_Rect *area, int step)
{
	t_xy	c;

	c = (t_xy){area->x + (area->w / 2) % step, area->y + (area->h / 2) % step};
	while (c.x <= area->x + area->w)
	{
		draw_line(all, &(t_xy){c.x, 0}, &(t_xy){c.x, area->h}, GREY);
		c.x += step;
	}
	c.x = area->x;
	while (c.y <= area->y + area->h)
	{
		draw_line(all, &c, &(t_xy){area->x + area->w, c.y}, GREY);
		c.y += step;
	}
}