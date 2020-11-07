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

int		is_neighbor(t_all *all, t_xy coord, t_xy coord2, int floor)
{
	int i;
	int j;
	t_xy	*temp;

	i = 0;
	while(i < all->num_sectors - 1)
	{
		j = 0;
		temp = all->sectors[i].vertex;
        if(floor >= all->sectors[i].floor && floor <= all->sectors[i].ceil)
            while (j < all->sectors[i].npoints)
            {
                if(coord.x == temp[j].x && coord.y == temp[j].y)
                {

                    if (check_match(&all->sectors[i], (t_xyz){coord2.x, coord2.y,  j},
                        temp, all->num_sectors - 1))
                        return(i);
                }
                j++;
            }
            i++;
	}
	return (-1);
}

void	get_neighbours(t_sect *sector, t_all 	*all, int n)
{
	int i;
    int h;
 
	if (n == 1)
	{
		n = sector->npoints;
		sector->neighbors = (int*)malloc(sizeof(int) * n);
		while(--n >= 0)
			sector->neighbors[n] = -1;
	}
	else
	{
        h = sector->floor;
		n = sector->npoints;
		sector->neighbors = (int*)malloc(sizeof(int) * n);
        i = 0;
		while(i < sector->npoints - 1)
		{
			sector->neighbors[i] = is_neighbor(all, sector->vertex[i], sector->vertex[i + 1], h);
			i++;
		}
		sector->neighbors[i] = is_neighbor(all, sector->vertex[i], sector->vertex[0], h);
	}
}