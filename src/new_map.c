/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/12 19:53:26 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	vertex(int fd)
{
	ft_putstr_fd("vertex\t", fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(4, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(16, fd);
	ft_putchar_fd('\n', fd);
	ft_putstr_fd("vertex\t", fd);
	ft_putnbr_fd(9, fd);
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(4, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(16, fd);
	ft_putchar_fd('\n', fd);
}

static void	sector0(int fd)
{
	int	i;

	ft_putstr_fd("sector\t", fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(10, fd);
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(2, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(5, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(4, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(1, fd);
	ft_putchar_fd(' ', fd);
	ft_putchar_fd('\t', fd);
	i = -1;
	while (++i < 3)
	{
		ft_putnbr_fd(-1, fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putnbr_fd(1, fd);
	ft_putchar_fd(' ', fd);
}

static void	sector1(int fd)
{
	int	i;

	ft_putstr_fd("sector\t", fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(10, fd);
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(4, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(3, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(1, fd);
	ft_putchar_fd(' ', fd);
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	i = -1;
	while (++i < 3)
	{
		ft_putnbr_fd(-1, fd);
		ft_putchar_fd(' ', fd);
	}
}

static void enders(int fd)
{
	int	i;

	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(-1, fd);
	ft_putchar_fd('\t', fd);
	i = -1;
	while (++i < 4)
	{
		ft_putnbr_fd(1, fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd('\n', fd);
}

static void	player(int fd)
{
	ft_putstr_fd("final sector\t", fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd('\n', fd);
	ft_putstr_fd("player\t", fd);
	ft_putnbr_fd(3, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(3, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(1, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(50, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(10, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(50, fd);
	ft_putchar_fd(' ', fd);
}

void		new_map(char *name)
{
	int	fd;

	fd = open(name, O_TRUNC | O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
	if (fd == -1)
		exit(0);
	vertex(fd);
	sector0(fd);
	enders(fd);
	sector1(fd);
	enders(fd);
	player(fd);
	close(fd);
}
