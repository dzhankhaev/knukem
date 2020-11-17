#include "editor.h"

void    new_sector(t_all *all, int x, int y)
{
    int i = 0;

	all->min_coord.x = x < all->min_coord.x ? x : all->min_coord.x;
	all->min_coord.y = y < all->min_coord.y ? y : all->min_coord.y;
	all->max_coord.x = x > all->max_coord.x ? x : all->max_coord.x;
	all->max_coord.y = y > all->max_coord.y ? y : all->max_coord.y;
    all->temp->vertex = ft_realloc(all->temp->vertex, (++all->temp->npoints) * sizeof(t_xy));
	all->temp->vertex[all->temp->npoints - 1] = (t_xy){x, y};
	if (all->temp->vertex[0].x == x && all->temp->vertex[0].y == y && all->temp->npoints != 1)
	{
		all->sectors = ft_realloc(all->sectors, ++(all->num_sectors) * sizeof(t_sect));
		all->sectors[all->num_sectors - 1].vertex = malloc(sizeof(t_xy) * all->temp->npoints);
		all->sectors[all->num_sectors - 1].npoints = all->temp->npoints;
		all->sectors[all->num_sectors - 1].floor = all->temp->floor;
		all->sectors[all->num_sectors - 1].ceil = all->temp->ceil; 
		while( i < all->temp->npoints)
		{
			all->sectors[all->num_sectors - 1].vertex[i] = all->temp->vertex[i];
			i++;
		}
		all->sectors[all->num_sectors - 1].npoints--;
		get_neighbours(&all->sectors[all->num_sectors -1], all, all->num_sectors);
		ft_memdel((void*)&all->temp->vertex);
		all->temp->npoints = 0;
	}
}

void	select_sector(t_all *all, int x, int y)
{
	t_xyz	where;

	where = (t_xyz){x, y, all->draw_floors.x};
	all->swap_num = which_sector(all, all->sectors, where);
	printf("%f\n",all->draw_floors.x);
	// else
		// all->swap = NULL;
	
}

void	map_click(t_xyz *mouse, t_all *all)
{
	int x;
	int y;

	x = all->point.x - all->d.x - ((all->area.w/(2 * all->step)) - round(all->mapsize.x/2));
	y = all->point.y - all->d.y - ((all->area.h/(2 * all->step)) - round(all->mapsize.y/2));
	if(all->buttons[0].state == 1)
	{
		all->temp->floor = all->set_floors.x;
        all->temp->ceil = all->set_floors.y;
		all->temp->neighbors = NULL;
        new_sector(all, x, y);
	}
    else if(all->buttons[1].state == 1)
    {
		all->player.where = (t_xyz){x, y, all->draw_floors.x + EYE_HEIGHT};
    	all->player.sector = which_sector(all, all->sectors, all->player.where);
		all->player.picked = 0;
		all->buttons[1].state = 0;
		all->buttons[1].color = WHITE;
	}
	else
		select_sector(all, x, y);
}
