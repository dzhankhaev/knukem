#include "editor.h"

void    validate_sector(t_sect *sect, t_all *all)
{
    check_sector(sect);
	get_neighbours(sect, all, all->num_sectors - 1);
	ft_memdel((void*)&all->temp->vertex);
}

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
		validate_sector(&all->sectors[all->num_sectors - 1], all);
		all->temp->npoints = 0;
	}
}