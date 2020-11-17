#include "editor.h"

int		revert_sector(t_sect *sect)
{
	t_xy *temp;
	int i;

	i = 0;
	if(!(temp = (t_xy*)malloc(sizeof(t_xy) * sect->npoints)))
		exit(0);
	while(i < sect->npoints)
	{
		temp[i] = sect->vertex[sect->npoints - i];
		i++;
	}
	temp[i] = temp[0];
	free(sect->vertex);
	sect->vertex = temp;
	return 0;
}

int		get_clockwise_order_sector(t_sect *sect)
{
	int			res;
	int			i;
	int			num;
	t_xy	vertex1;
	t_xy	vertex2;

	res = 0;
	i = 0;
	while (i < sect->npoints)
	{
		vertex1 = sect->vertex[i];
		vertex2 = sect->vertex[i + 1];
		res += (vertex2.x - vertex1.x) * (vertex2.y + vertex1.y);
		i++;
	}
	return (res > 0 ? 0 : 1);
}

int		check_sector_order(t_sect *sect)
{
	if(!(get_clockwise_order_sector(sect)))
		revert_sector(sect);
	return (0);
}

void    del_neighbour(int *arr, int len, int num)
{
    int i;

    i = 0;
    while (i < len)
    {
        if(arr[i] == num)
            arr[i] = -1;
        i++;
    }
}

void    drop_neighbors(t_sect *sectors, int *neighbors, int num, int del)
{
    int i;
    int index;

    i = 0;
    while (i < num)
    {
        if(neighbors[i] > -1)
        {
            index = neighbors[i];
            del_neighbour(sectors[index].neighbors, sectors[index].npoints, del);
        }
        i++;
    }
}

void    remove_sector(t_all *all, t_sect *sectors)
{
    t_sect *del;
    int *temp;/// записать соседейй сюда, удалить сектор, пройтись по этим секторам для поиска соседей. 

    del = &all->sectors[all->swap_num];
    if(all->swap_num != -1)
    {
        drop_neighbors(all->sectors, del->neighbors, del->npoints, all->swap_num);
        free(all->sectors[all->swap_num].vertex);
        free(all->sectors[all->swap_num].neighbors);
		if (all->num_sectors > 1 && all->swap_num != all->num_sectors - 1)
        {
            all->sectors[all->swap_num] = all->sectors[all->num_sectors - 1];
            //free(all->sectors[all->swap_num].neighbors);
            //get_neighbours(&all->sectors[all->swap_num], all, all->num_sectors);
        }
        all->num_sectors -= 1;
        get_neighbours(&all->sectors[all->swap_num], all, all->swap_num);
        all->swap_num = -1;
    }
}