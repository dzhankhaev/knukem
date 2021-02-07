/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map_sector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/12 19:53:26 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	sector0(int fd)
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

void	sector1(int fd)
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

void	enders(int fd)
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
