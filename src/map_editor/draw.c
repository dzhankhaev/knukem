#include "editor.h"

void	isometric(t_all *all, t_sect *sect, t_xyz *start, t_xyz rot)
{
	t_xyz temp;

	rot = (t_xyz){(M_PI / 25 * rot.x), (M_PI / 25 * rot.y), (M_PI / 135 * rot.z) * -1};
	temp.y = all->area.h/2 + start->y * cos(rot.x) + start->z * sin(rot.x);
	temp.z = -(start->y * sin(rot.x)) + start->z * cos(rot.x);
	start->y = temp.y;
	start->z = temp.z;
	temp.x = all->area.w/2 + start->x * cos(rot.y) + start->z * sin(rot.y);
	temp.z = -(start->x * sin(rot.y)) + start->z * cos(rot.y);
	start->x = temp.x;
	start->z = temp.z;
	start->x -= all->area.w/2;
	start->y -= all->area.h/4; 

}

void	draw_wall(t_all *all, t_sect *sect, int j, t_xyz *vertex)
{
	t_xyz f;

	f = (t_xyz){sect->vertex[j].x * all->step + (all->step * 5),
				sect->vertex[j].y * all->step + (all->step * 6), sect->ceil * all->step/2};
	//isometric(all, sect, &f, all->rot);
	//if (sect->floor == 0)
		draw_line(all, vertex, &f, all->color);
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
		while (j < temp->npoints)
		{
			s = (t_xyz){(temp->vertex[j].x * all->step) + all->area.w/2 - (round(all->mapsize.x/2) * all->step) + all->area.x,
				(temp->vertex[j].y * all->step) + all->area.h/2 - (round(all->mapsize.y/2) * all->step) + all->area.y, 0};
					// (temp->floor - all->mapsize.z/4) * all->step/2};
			f = (t_xyz){(temp->vertex[j + 1].x * all->step) + all->area.w/2 - (round(all->mapsize.x/2) * all->step)+ all->area.x,
				(temp->vertex[j + 1].y * all->step) + all->area.h/2 - (round(all->mapsize.y/2) * all->step)+ all->area.y, 0};
					// (temp->floor - all->mapsize.z/4) * all->step/2};
			if (all->iso)
			{
				isometric(all, temp, &s, (t_xyz){10, 1, 1});
				isometric(all, temp, &f, (t_xyz){10, 1, 1});
			}
			all->color = (temp->neighbors[j] == -1 && j < temp->npoints) ? RED : BLUE;
			if (temp->floor >= all->draw_floors.x && temp->floor <= all->draw_floors.y)
			{
				draw_line(all, &s, &f, &all->sectors[i] == all->swap ? YELLOW : all->color);
				draw_circle(sdl, (t_xy){s.x, s.y}, 2, GREEN);
			}
			j++;
		}
		i++;
	}
}



void	draw_temp(t_all *all, t_sdl *sdl, t_sect *temp)
{
	t_xyz	s;
	t_xyz	f;
	int j = 0;
	int x = all->point.x - (all->area.w/(2 * all->step) - (all->mapsize.x/2));
	int y = all->point.y - (all->area.h/(2 * all->step) - (all->mapsize.y/2));

	while (j < temp->npoints)
	{
		if(j == temp->npoints - 1)
		{
			s = (t_xyz){(temp->vertex[j].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step) + all->area.x,
			(temp->vertex[j].y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step) + all->area.y, 0};
				// (temp->floor - all->mapsize.z/4) * all->step/2};
			f = (t_xyz){(x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step) + all->area.x,
			(y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step) + all->area.y, 0};
				// (temp->floor - all->mapsize.z/4) * all->step/2};
		}
		else
		{		// printf(" %d,%d", (int)temp->vertex[j].x, (int)temp->vertex[j].y);
			s = (t_xyz){(temp->vertex[j].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step) + all->area.x,
				(temp->vertex[j].y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step) + all->area.y,
					(temp->floor - all->mapsize.z/4) * all->step/2};
			f = (t_xyz){(temp->vertex[j + 1].x * all->step) + all->area.w/2 - (all->mapsize.x/2 * all->step) + all->area.x,
				(temp->vertex[j + 1].y * all->step) + all->area.h/2 - (all->mapsize.y/2 * all->step) + all->area.y,
					(temp->floor - all->mapsize.z/4) * all->step/2};
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
	if (all->temp->npoints != 0)
	 	draw_temp(all, sdl, all->temp);
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
	draw_area(sdl, all);
	draw_fill_rect(all, (SDL_Rect){4, 4, WIDTH / 4 - 8, HEIGHT - 8}, LAZUR);
	i = btn[0].state == 1 ? 3 : 0;
	draw_labels(all, all->labels, i);
	draw_digits(sdl, all, all->draw_floors.x, all->draw_floors.y);
	draw_buttons(all, sdl, btn);
}
