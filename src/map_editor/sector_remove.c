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

    if(all->swap_num != -1)
    {
        del = &sectors[all->swap_num];
        drop_neighbors(all->sectors, del->neighbors, del->npoints, all->swap_num);
        free(del->vertex);
        free(del->neighbors);
        if (del->graf.g_num > 0)
        {
            free(del->graf.coord);
            free(del->graf.z);
            free(del->graf.wall);
        }
		if (all->num_sectors > 1 && all->swap_num != all->num_sectors - 1)
            sectors[all->swap_num] = sectors[all->num_sectors - 1];
        if (all->swap_num == all->player.sector)
            all->player.sector = -1;
        all->num_sectors -= 1;
        get_neighbours(&sectors[all->swap_num], all, all->swap_num);
        all->fin_sect = all->swap_num == all->fin_sect ? -1 : all->fin_sect;
        all->swap_num = -1;
    }
}