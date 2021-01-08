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
