#include "editor.h"

void    del_sprites(t_all *all, t_sprites *sprites, int sect_num)
{
    int i;
    int j;
    int sprite_sector;

    i = 0;
    sprite_sector = -1;
    while(i <= 4)
    {
        j = 0;
        while(j < sprites->buttons[i].num)
        {
            sprite_sector = which_sector(all, all->sectors, sprites->buttons[i].sprite_coords[j]);
            if(sprite_sector == sect_num)
            {
                sprite_remove(all, sprites, (t_xy){i, j});
                printf("del sect = %d sprite sect = %d\n", sect_num, sprite_sector);
            }
            j++;
        }
        i++;
    }
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

    del = &all->sectors[all->swap_num];
    if(all->swap_num != -1)
    {
        del_sprites(all, &all->sprites, all->swap_num);
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