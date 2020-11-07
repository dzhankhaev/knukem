#include "editor.h"

void	draw_labels(t_all *all, t_labels label[5], int i)
{
	int l;

	l = i == 0 ? 2 : 4;
	while(i <= l)
	{
		draw_texture(all->sdl->renderer, label[i].dst, label[i].surf);
		i++;
	}
}

void	draw_digits(SDL_Renderer *rnd, t_all *all, int x, int y)
{
	SDL_Surface *tmp;
	SDL_Rect	area[2];

	tmp = NULL;
	if (all->buttons[0].state == 1)
	{
		x = (int)all->set_floors.x;
		y = (int)all->set_floors.y;
	}
	area[0] = (SDL_Rect){WIDTH/16, 250, WIDTH/8, 150};
	area[1] = (SDL_Rect){WIDTH/16, 450, WIDTH/8, 150};
	tmp = get_text_surface(all, ft_itoa(x), area[0], BLUE);
	draw_texture(rnd, area[0], tmp);
	SDL_FreeSurface(tmp);
	tmp = get_text_surface(all, ft_itoa(y), area[1], BLUE);
	draw_texture(rnd, area[1], tmp);
	SDL_FreeSurface(tmp);
}

void	draw_player(t_all *all, SDL_Renderer *rnd, t_player *player, t_xy *c)
{
	SDL_Rect loc;

	if (all->player.picked == 0)
	//(temp->vertex[j].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step)
		loc = (SDL_Rect){(player->where.x * all->step) + all->area.w/2 - (round(all->mapsize.x/2) * all->step) - all->step/2,
		 (player->where.y * all->step) + all->area.h/2 - (round(all->mapsize.y/2) * all->step) - all->step/2,
	 		 all->step, all->step};
	else if (all->player.picked == 1)
		loc = (SDL_Rect){all->point.x * all->step + c->x - all->step/2,
			 all->point.y * all->step + c->y - all->step/2, all->step, all->step};
	draw_texture(rnd, loc, player->picture);

	// SDL_RenderCopy(rnd, player->picture, NULL, &loc);
}

void	draw_grid(t_all *all, SDL_Rect *area, int step)
{
	t_xy	c;

	c = (t_xy){(area->w / 2) % step, (area->h / 2) % step};
	all->color = (SDL_Color){255, 255, 255, 70};
	while (c.x <= area->w)
	{
		draw_line(all, &(t_xyz){c.x, 0, 0}, &(t_xyz){c.x, area->h}, all->color);
		c.x += step;
	}
	c.x = 0;
	while (c.y <= area->h)
	{
		draw_line(all, &(t_xyz){c.x, c.y, 0}, &(t_xyz){area->w, c.y}, all->color);
		c.y += step;
	}
}