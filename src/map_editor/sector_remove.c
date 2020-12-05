#include "editor.h"

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