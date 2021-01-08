/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:39:16 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/27 22:58:06 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int un;

	un = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		un = n * -1;
	}
	else
		un = n;
	if ((un / 10) != 0)
		ft_putnbr_fd((un / 10), fd);
	ft_putchar_fd((un % 10) + '0', fd);
}
||||||| 1784372
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:21:22 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int m;

	m = (long int)n;
	if (m < 0)
	{
		m = 0 - m;
		ft_putchar_fd('-', fd);
	}
	if (m >= 10)
	{
		ft_putnbr_fd(m / 10, fd);
		ft_putnbr_fd(m % 10, fd);
	}
	else
		ft_putchar_fd(m + '0', fd);
}
>>>>>>> master
