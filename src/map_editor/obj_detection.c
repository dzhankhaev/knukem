#include "editor.h"

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