#include "editor.h"

t_xy   which_sprite(t_all *all, t_sprites *sprites, t_xyz where)
{
    int i;
    int j;
    t_xyz temp;

    i = 0;
    while(i < 4)
    {
        j = 0;
        while(j < sprites->buttons[i].num)
        {
            temp = sprites->buttons[i].sprite_coords[j];
            if(where.x == temp.x && where.y == temp.y && where.z == temp.z)
                return((t_xy){i, j});
            j++;
        }
        i++;
    }
    return (t_xy){-1, -1};
}

int     which_sector(t_all *all, t_sect *sectors, t_xyz where)
{
    int i;
    int p;

    int j;
    i = 0;
    p = 0;
    while(i < all->num_sectors)
    {
        j = 0;
        if(where.z == all->sectors[i].oldf)
            while(j < all->sectors[i].npoints)
            {
                p = point_side1(where.x, where.y, sectors[i].vertex[j], sectors[i].vertex[j + 1]);
                if (p < 0)
                    break;
                j++;
            }
        if(p > 0)
            return(i);
        i++;
    }
    return (-1);
}