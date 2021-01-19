#include "editor.h"

void    write_vertexes(t_all *all, int **vert, int fd)
{
    int i, j;
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
}

void    write_sect_vert(t_all *all, int **vert, int i, int fd)
{
    int j;

    ft_putstr_fd("sector\t", fd);
    ft_putnbr_fd((int)all->sectors[i].oldf, fd);
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
}

void    write_sectors(t_all *all, int **vert, int fd)
{
    int i;
    int j;

    i = 0;
    while(i < all->num_sectors)
    {
        write_sect_vert(all, vert, i, fd);
        ft_putnbr_fd(get_order_num(all->sectors[i].vertex[0], vert), fd);
        ft_putchar_fd('\t', fd);
        j = 0;
        while (j < all->sectors[i].npoints)
        {
            ft_putnbr_fd(all->sectors[i].neighbors[j], fd);
            ft_putchar_fd(' ', fd);
            j++;
        }
        ft_putchar_fd('\t', fd);
        ft_putnbr_fd(all->sectors[i].door, fd);
		ft_putchar_fd('\t', fd);
		ft_putnbr_fd(all->sectors[i].txf, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(all->sectors[i].txc, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(all->sectors[i].txw0, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(all->sectors[i].txw1, fd);
		i++;
        ft_putchar_fd('\n', fd);
    }
}

static void		write_player(t_all *all, int fd)
{
	ft_putstr_fd("player\t", fd);
	ft_putnbr_fd((int)all->player.where.x, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd((int)all->player.where.y, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(all->player.sector, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(all->player.settings.inventory, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(all->player.settings.speed, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(all->player.settings.ammo, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(all->player.settings.gravity, fd);
	ft_putchar_fd('\n', fd);
}

int				write_map(char *name, t_all *all)
{
    int fd;// для корректной работы, fd должен быть открыт как-то так open("new_map.txt", O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
    int **vert;//массив вершин, где номер строки - координата y, первое значение в строке - 
                                                //количество вершин, далее - координаты x вершин.
    if (all->min_coord.x < 0 || all->min_coord.y < 0)
        normalize(all->sectors, all->num_sectors, all);
    vert = get_vertexes(all);

    fd = open("new_map.txt", O_TRUNC | O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);

    write_vertexes(all, vert, fd);
    write_sectors(all, vert, fd);
	write_player(all, fd);
    ft_memdel((void*)vert);
    return (0);
}