#include "editor.h"

int *sorted_insert(int *line, int n, int *k)
{
    int i;
    int len;

    len = *k + 1;
    i = 1;
    while(i < len)
        if(line[i++] == n)
            return(line);
    *k = *k + 1;
    line = ft_realloc(line, sizeof(int) * (++len));
    i = 1;
    while(line[i] < n && i < len - 1)
        i++;
    while (len > i)
    {
        line[len -1 ] = line[len - 2];
        len--;
    }
    line[i] = n;
    return(line);
}

int *get_x(t_sect *sectors, int num, int y, int *line)
{
    int i;
    int j;
    int k;

    k = 0;
    i = 0;
    line[0] = k;
    while (i < num)
    {
        j = 0;
        while (j < sectors[i].npoints)
        {
            if (sectors[i].vertex[j].y == y)
                line = sorted_insert(line, (int)sectors[i].vertex[j].x, &k);
            j++;
        }
        i++;
    }
    line[0] = k;
    return (line);
}

int    **get_vertexes(t_all *all)
{
    int         y;
    int         **yx;
    
    y = 0;
    yx = (int**)malloc((all->max_coord.y + 1) * sizeof(int*));
    while(y <= all->max_coord.y)
    {
        yx[y] = (int*)malloc(sizeof(int));
        yx[y] = get_x(all->sectors, all->num_sectors, y, yx[y]);
        y++;
    }
    return(yx);
}

void    normalize(t_sect *sectors, int num, t_all *all)
{
    int i;
    int j;

    i = 0;
    while(i < num)
    {
        j = 0;
        while (j <= sectors[i].npoints)
        {
            sectors[i].vertex[j].x += (all->min_coord.x < 0) ? -all->min_coord.x : all->min_coord.x;
            sectors[i].vertex[j].y += (all->min_coord.y < 0) ? -all->min_coord.y : all->min_coord.y;
            j++;
        }
        i++;
    }
    all->player.where.x += (all->min_coord.x < 0) ? -all->min_coord.x : all->min_coord.x;
    all->player.where.y += (all->min_coord.y < 0) ? -all->min_coord.y : all->min_coord.y;
    all->max_coord.x += (all->min_coord.x < 0) ? -all->min_coord.x : 0;
    all->max_coord.y += (all->min_coord.y < 0) ? -all->min_coord.y : 0;
    all->min_coord.x += (all->min_coord.x < 0) ? -all->min_coord.x : 0;
    all->min_coord.y += (all->min_coord.y < 0) ? -all->min_coord.y : 0;

}

int get_order_num(t_xy coord, int **vert)
{
    int x;
    int y;
    int ret;
    ret = y = 0;

    while(y < coord.y)
        ret += vert[y++][0];
    x =  1;
    while(vert[y][x] < coord.x && x < vert[y][0])
    {
        ret += 1;
        x++;
    }

    return(ret);
}

float	vector_cross_product1(float x0, float y0, float x1, float y1)
{
	return ((x0) * (y1) - (x1) * (y0));
}

// С какой стороны от линии находится точка. Возвращает <0, 0, >0
float			point_side1(float px, float py, t_xy vert, t_xy vert1)
{
	return (vector_cross_product1(vert1.x - vert.x, vert1.y - vert.y,
								 px - vert.x, py - vert.y));
}

void    write_sprites(t_sprites *sprites, int fd)
{
    int i, j;
    char *array[5] = {"gun", "enemy", "aid", "bazooka", "player"};
    t_xyz *temp;

    i = 0;
    while(i < 4)
    {
        
        j = 0;
        while(j < sprites->buttons[i].num)
        {
            temp = sprites->buttons[i].sprite_coords;
            ft_putstr_fd(array[i], fd);
            ft_putchar_fd('\t', fd);
            ft_putnbr_fd((int)temp[j].x, fd);
            ft_putchar_fd('\t', fd);
            ft_putnbr_fd((int)temp[j].y, fd);
            ft_putchar_fd('\t', fd);
            ft_putnbr_fd((int)temp[j].z, fd);
            ft_putchar_fd('\n', fd);
            j++;
        }
        i++;
    }
}


int write_map(char *name, t_all *all)
{
    // для корректной работы, fd должен быть открыт как-то так open("new_map.txt", O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
    int     **vert;//массив вершин, где номер строки - координата y, первое значение в строке - 
    //количество вершин, далее - координаты x вершин.
    if (all->min_coord.x < 0 || all->min_coord.y < 0)
        normalize(all->sectors, all->num_sectors, all);
    vert = get_vertexes(all);
    int i, j, fd;

    fd = open("new_map.txt", O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);

    i = 0;
    j = 0;
    while( i <= all->max_coord.y)
    {
        j = 1;
        if (vert[i][0] != 0)
        {
            ft_putstr_fd("vertex\t", fd);
            ft_putnbr_fd(i, fd);
            ft_putstr_fd("\t", fd);
            while(j <= vert[i][0])
            {
                ft_putchar_fd(' ', fd);
                ft_putnbr_fd(vert[i][j], fd);
                j++;
            }
            ft_putchar_fd('\n', fd);
        }
        i++;
    }

    i = 0;
    j = 0;

    while(i < all->num_sectors)
    {
        //while (j < all->sectors[i].npoints)
          //  printf("y = %d, x = %d ", i, (int)all->sectors[i].vertex[j++].x);
        ft_putstr_fd("sector\t", fd);
        ft_putnbr_fd((int)all->sectors[i].floor, fd);
        ft_putchar_fd(' ', fd);
        ft_putnbr_fd((int)all->sectors[i].ceil, fd);
        ft_putchar_fd('\t', fd);
        
        j = 1;
        while(j < all->sectors[i].npoints)
        {
            ft_putnbr_fd(get_order_num(all->sectors[i].vertex[j], vert), fd);
            ft_putchar_fd(' ', fd);
            j++;
        }
        ft_putnbr_fd(get_order_num(all->sectors[i].vertex[0], vert), fd);
        ft_putchar_fd('\t', fd);
        j = 0;
        while (j < all->sectors[i].npoints)
        {
            ft_putnbr_fd(all->sectors[i].neighbors[j], fd);
            ft_putchar_fd(' ', fd);
            j++;
        }
        i++;
        ft_putchar_fd('\n', fd);
    }
    ft_putstr_fd("player\t", fd);
    ft_putnbr_fd((int)all->player.where.x, fd);
    ft_putchar_fd(' ', fd);
    ft_putnbr_fd((int)all->player.where.y, fd);
    ft_putchar_fd(' ', fd);
    ft_putnbr_fd((int)all->player.where.z, fd);
    ft_putchar_fd(' ', fd);
    ft_putnbr_fd(all->player.sector, fd);
    ft_putchar_fd('\n', fd);

    ft_memdel((void*)vert);

    write_sprites(&all->sprites, fd);

    
    ///********test*********////
    
    return (0);
}