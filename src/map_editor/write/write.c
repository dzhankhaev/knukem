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
#include "archiver.h"

void		write_vertexes(t_all *all, int **vert, int fd)
{
	int	i;
	int	j;

	i = 0;
	while (i <= all->max_coord.y)
	{
		j = 1;
		if (vert[i][0] != 0)
		{
			ft_putstr_fd("vertex\t", fd);
			ft_putnbr_fd(i, fd);
			ft_putstr_fd("\t", fd);
			while (j <= vert[i][0])
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

static void	write_player(t_all *all, int fd)
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

int			write_map(t_all *all)
{
	int		i;
	int		fd;
	int		**vert;
	char	*sub;

	if (all->min_coord.x < 0 || all->min_coord.y < 0)
		normalize(all->sectors, all->num_sectors, all);
	vert = get_vertexes(all);
	fd = open(all->name, O_TRUNC | O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
	write_vertexes(all, vert, fd);
	write_sectors(all, vert, fd);
	write_player(all, fd);
	i = 0;
	while (i <= all->max_coord.y)
	{
		free(vert[i]);
		i++;
	}
	free(vert);
	sub = ft_strjoin(all->src_dir, "files");
	pack_files(sub, "map.map", all->src_dir);
	free(sub);
	return (0);
}
