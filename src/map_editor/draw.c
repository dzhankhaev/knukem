#include "editor.h"

void	isometric(t_all *all, t_xy *s, t_xyz rot, float add)
{
	t_xyz temp;
	t_xyz start;

	start = (t_xyz){s->x, s->y, add};
	rot = (t_xyz){(M_PI / 25 * rot.x), (M_PI / 25 * rot.y), (M_PI / 135 * rot.z) * -1};
	temp.y = all->area.h/2 + start.y * cos(rot.x) + start.z * sin(rot.x);
	temp.z = -(start.y * sin(rot.x)) + start.z * cos(rot.x);
	s->y = temp.y;
	start.z = temp.z;
	temp.x = all->area.w/2 + start.x * cos(rot.y) + start.z * sin(rot.y);
	temp.z = -(start.x * sin(rot.y)) + start.z * cos(rot.y);
	s->x = temp.x;
	start.z = temp.z;
	s->x -= all->area.w/2;
	s->y -= all->area.h/4; 

}

void	draw_sector(t_sect *sect, t_all *all, SDL_Color color, t_xy delta)
{
	int		i;
	t_xy	s;
	t_xy	f;

	i = 0;
	while(i < sect->npoints)
	{
		s = (t_xy){(sect->vertex[i].x * all->step) + delta.x,
				(sect->vertex[i].y * all->step) + delta.y};
		f = (t_xy){(sect->vertex[i + 1].x * all->step) + delta.x,
				(sect->vertex[i + 1].y * all->step) + delta.y};
		if (all->iso)
		{
			isometric(all, &s, (t_xyz){10, 1, 0}, sect[i].floor - all->mapsize.z/4 * all->step/2);
			isometric(all, &f, (t_xyz){10, 1, 0}, sect[i].floor - all->mapsize.z/4 * all->step/2);
		}
		color = (sect->neighbors[i] < 0 && i < sect->npoints) ? RED : BLUE;
		if (sect->floor >= all->draw_floors.x && sect->floor <= all->draw_floors.y)
		{
			draw_line(all, &s, &f, &all->sectors[all->swap_num] == sect ? YELLOW : color);
			draw_circle(all->sdl, s, 2, GREEN);
		}
		i++;
	}
}

void	draw_map(t_sdl *sdl, t_sect *sect, t_all *all)
{
	int		i, j;
	t_xyz	s;
	t_xyz	f;
	t_sect *temp;

	i = 0;
	while(i < all->num_sectors)
	{
		j = 0;
		temp = &sect[i];
		draw_sector(temp, all, all->color, all->delta);
		i++;
	}
	if (all->swap_num != -1)
		draw_sector(&sect[all->swap_num], all, YELLOW, all->delta);
}



void	draw_temp(t_all *all, t_sdl *sdl, t_sect *temp, t_xy delta)
{
	t_xy	s;
	t_xy	f;
	int j = 0;
	int x = all->point.x - all->d.x - (all->area.w/(2 * all->step) - (all->mapsize.x/2));
	int y = all->point.y - all->d.y -(all->area.h/(2 * all->step) - (all->mapsize.y/2));

	while (j < temp->npoints)
	{
		if(j == temp->npoints - 1)
		{
			s = (t_xy){(temp->vertex[j].x * all->step) + delta.x, 
			(temp->vertex[j].y * all->step) + delta.y};
			f = (t_xy){(x * all->step) + delta.x, (y * all->step) + delta.y};
		}
		else
		{
			s = (t_xy){(temp->vertex[j].x * all->step) + delta.x,
				(temp->vertex[j].y * all->step) + delta.y};
			f = (t_xy){(temp->vertex[j + 1].x * all->step) + delta.x,
				(temp->vertex[j + 1].y * all->step) + delta.y};
		}
		draw_line(all, &s, &f, WHITE);
		j++;
	}
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

void	draw_buttons(t_all *all, t_sdl *sdl, t_button *btn)
{
	int i;

	i = 0;
	while (i < BUTTONS)
	{ 
		btn[i].color = btn[i].state == 1 ? RED : btn[i].color;
		
		btn[i].texture = get_text_surface(all, btn[i].title, btn[i].dstrect, btn[i].color);
		draw_texture(sdl, btn[i].dstrect, btn[i].texture);
		if (i >= 2)
		{
			btn[i].state = 0;
			btn[i].color = WHITE;
		}
		SDL_FreeSurface(btn[i].texture);
		i++;
    }
	
}

void	draw_all(t_all *all, t_sdl *sdl, t_button *btn)
{
    int			i;
	Uint32 state;

	all->delta.x = all->area.x + all->area.w/2 - 
		(round(all->mapsize.x/2) * all->step) + all->d.x * all->step;
	all->delta.y = all->area.y + all->area.h/2 - 
		(round(all->mapsize.y/2) * all->step) + all->d.y * all->step;
	draw_area(sdl, all);
	draw_fill_rect(all, (SDL_Rect){4, 4, W / 4 - 8, H - 8}, LAZUR);
	i = btn[0].state == 1 ? 3 : 0;
	draw_labels(all, all->labels, i);
	draw_digits(sdl, all, all->draw_floors.x, all->draw_floors.y);
	draw_buttons(all, sdl, btn);
}
