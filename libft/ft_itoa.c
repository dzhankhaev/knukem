/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:29:21 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/30 16:39:46 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_get_int_len(long long int nb)
{
	int n;

	n = 0;
	if (nb == 0)
		return (1);
	if (nb == -2147483648)
		return (11);
	if (nb < 0)
	{
		nb *= -1;
		n++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		++n;
	}
	return (n);
}

char			*ft_itoa(int n)
{
	char			*s;
	int				len;
	long long int	nb;

	nb = n;
	len = ft_get_int_len(nb);
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len--] = '\0';
	if (nb < 0)
	{
		nb *= -1;
		s[0] = '-';
	}
	if (nb == 0)
		return (ft_strdup("0"));
	while (nb > 0)
	{
		s[len] = (nb % 10) + 48;
		nb /= 10;
		len--;
	}
	return (s);
}
