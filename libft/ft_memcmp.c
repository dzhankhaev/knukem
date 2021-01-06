/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 20:26:02 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/27 20:34:30 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned long int	i;
	int					c;
	unsigned char		*refs1;
	unsigned char		*refs2;

	i = 0;
	c = 0;
	refs1 = (unsigned char *)s1;
	refs2 = (unsigned char *)s2;
	while (i < n)
	{
		if (refs1[i] != refs2[i])
		{
			c = refs1[i] - refs2[i];
			break ;
		}
		if (refs1[i] == refs2[i])
			i++;
	}
	return (c);
}
