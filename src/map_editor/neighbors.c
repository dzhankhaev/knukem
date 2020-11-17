#include "editor.h"

int check_match(t_sect  *sect, t_xyz coord, t_xy *temp, int sect_num)
{
    int n;

    n = (int)coord.z; 
    if (coord.x == temp[n - 1].x && coord.y == temp[n - 1].y)
        sect->neighbors[n - 1] = sect_num;
    else if (coord.x == temp[n + 1].x && coord.y == temp[n + 1].y)
        sect->neighbors[n] = sect_num;
    else if (coord.x == temp[sect->npoints - 1].x
        && coord.y == temp[sect->npoints - 1].y)
        sect->neighbors[sect->npoints - 1] = sect_num;
    else
        return (0);
    return (1);
}

int		height_intersection(int x, int y, t_xy h)
{
	if ((x >= (int)h.x && x <= (int)h.y) || (y > (int)h.x && y <= (int)h.y) || 
		((int)h.x >= x && (int)h.x <= y) || ((int)h.y >= y && (int)h.y <= y))
		return(1);
	return 0;
}

int		is_neighbor(t_all *all, t_xy coord, t_xy coord2, t_xy height, int self)
{
	int i;
	int j;
	t_xy	*temp;

	i = 0;
	while(i < all->num_sectors - 1)
	{
		j = 0;
		temp = all->sectors[i].vertex;
        if (height_intersection(all->sectors[i].floor, all->sectors[i].ceil, height) && i != self)
            while (j < all->sectors[i].npoints)
            {
                if(coord.x == temp[j].x && coord.y == temp[j].y)
                {

                    if (check_match(&all->sectors[i], (t_xyz){coord2.x, coord2.y,  j},
                        temp, self))
                        return(i);
                }
                j++;
            }
        i++;
	}
	return (-1);
}

void	get_neighbours(t_sect *sector, t_all 	*all, int self)
{
	int i;
    t_xy h;
	int n;
 
	if (all->num_sectors == 1)
	{
		n = sector->npoints;
		sector->neighbors = (int*)malloc(sizeof(int) * n);
		while(--n >= 0)
			sector->neighbors[n] = -1;
	}
	else
	{
        h = (t_xy){sector->floor, sector->ceil};
		n = sector->npoints;
		sector->neighbors = (int*)malloc(sizeof(int) * n);
        i = 0;
		while(i < sector->npoints - 1)
		{
			sector->neighbors[i] = is_neighbor(all, sector->vertex[i], sector->vertex[i + 1], h, self);
			i++;
		}
		sector->neighbors[i] = is_neighbor(all, sector->vertex[i], sector->vertex[0], h, self);
	}
}