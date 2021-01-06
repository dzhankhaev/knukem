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
