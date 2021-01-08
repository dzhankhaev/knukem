/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:33:40 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/30 14:09:26 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_minus(char c)
{
	if (c == '-')
		return (-1);
	else if (c == '+')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	int				i;
	int				n;
	long long int	res;

	i = 0;
	n = 1;
	res = 0;
	while (str[i] == '\t' || str[i] == '\b' || str[i] == '\f' || str[i] == ' '
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (check_minus(str[i]))
		n = check_minus(str[i]);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str == 0)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] <= '9' && str[i] >= '0')
			res = (res * 10) + str[i] - 48;
		else
			return (res * n);
		i++;
	}
	return (res * n);
}
||||||| 1784372
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 13:25:00 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_atoi(const char *str)
{
	int						i;
	unsigned long long int	nbr;
	int						neg;

	i = 0;
	nbr = 0;
	neg = 1;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\f' ||
			str[i] == '\r' || str[i] == ' ' || str[i] == '\n')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i++] - '0');
		if (nbr != (nbr * 10 / 10))
			return (neg == 1 ? -1 : 0);
	}
	return (neg * nbr);
}
>>>>>>> master
