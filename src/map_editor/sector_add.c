#include "editor.h"

int		is_intersectred(t_xy v11, t_xy v12, t_xy v21, t_xy v22)
{
	t_xy c1;
	t_xy c2;

	c1 = (t_xy){point_side1(v11.x, v11.y, v21, v22), 
		point_side1(v12.x, v12.y, v21, v22)};
	c2 = (t_xy){point_side1(v21.x, v21.y, v11, v12), 
		point_side1(v22.x, v22.y, v11, v12)};
	c1.x = c1.x >= 0 ? 1 : -1;
	c1.y = c1.y >= 0 ? 1 : -1;
	c2.x = c2.x >= 0 ? 1 : -1;
	c2.y = c2.y >= 0 ? 1 : -1;
	if (c1.x + c1.y + c2.x + c2.y == 0)
		return 1;
	return 0;
}

int		check_intersections(t_sect *sect)
{
	int i, j;
	t_xy *v;
	
	i = 0;
	v = sect->vertex;
	while(i < sect->npoints)
	{
		j = i + 2;
		while(j < sect->npoints)
		{
			if (is_intersectred(v[i], v[i + 1], v[j], v[j + 1]))
				return 1;
			j++;
		}
		i++;
	}
	return 0;
}

void    validate_sector(t_sect *sect, t_all *all)
{
    check_sector(sect);
	get_neighbours(sect, all, all->num_sectors - 1);
	if (check_intersections(sect))
	{
		all->swap_num = all->num_sectors - 1; 
		remove_sector(all, sect);
	}
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
		all->sectors[all->num_sectors - 1].oldf = all->temp->floor;
		all->sectors[all->num_sectors - 1].ceil = all->temp->ceil; 
		all->sectors[all->num_sectors - 1].door = -1;
		all->sectors[all->num_sectors - 1].txf = 1;
		all->sectors[all->num_sectors - 1].txc = 1;
		all->sectors[all->num_sectors - 1].txw0 = 1;
		all->sectors[all->num_sectors - 1].txw1 = 1;
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