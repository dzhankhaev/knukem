/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:32:47 by sisidra           #+#    #+#             */
/*   Updated: 2020/11/27 13:32:49 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		write_sect_vert(t_all *all, int **vert, int i, int fd)
{
	unsigned int	j;

	ft_putstr_fd("sector\t", fd);
	ft_putnbr_fd((int)all->sectors[i].oldf, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd((int)all->sectors[i].ceil, fd);
	ft_putchar_fd('\t', fd);
	j = 1;
	while (j < all->sectors[i].npoints)
	{
		ft_putnbr_fd(get_order_num(all->sectors[i].vertex[j], vert), fd);
		ft_putchar_fd(' ', fd);
		j++;
	}
}

void		write_graffity(t_sect *sect, int fd)
{
	int j;

	j = 0;
	while ((int)j < sect->graf.g_num)
	{
		ft_putnbr_fd(sect->graf.wall[j], fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd((int)(sect->graf.z[j] * 1024.f), fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd((int)(sect->graf.coord[j].x0 * 1024.f), fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd((int)(sect->graf.coord[j].x1 * 1024.f), fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd((int)(sect->graf.coord[j].y0 * 1024.f), fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd((int)(sect->graf.coord[j].y1 * 1024.f), fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd((int)(sect->graf.coord[j].color), fd);
		ft_putchar_fd(' ', fd);
		j++;
	}
}

void		write_texture(t_sect *sect, int fd)
{
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(sect->door, fd);
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(sect->txf, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(sect->txc, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(sect->txw0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(sect->txw1, fd);
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(sect->graf.g_num, fd);
	ft_putchar_fd('\t', fd);
}

void		write_sectors(t_all *all, int **vert, int fd)
{
	int				i;
	unsigned int	j;

	i = 0;
	while (i < all->num_sectors)
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
		write_texture(&all->sectors[i], fd);
		write_graffity(&all->sectors[i], fd);
		i++;
		ft_putchar_fd('\n', fd);
	}
	ft_putstr_fd("final sector\t", fd);
	ft_putnbr_fd(all->fin_sect, fd);
	ft_putchar_fd('\n', fd);
}
