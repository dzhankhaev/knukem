/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 19:01:16 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/26 14:30:14 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned long int	i;
	unsigned char		cc;
	unsigned char		*refdst;
	unsigned char		*refsrc;

	cc = c;
	refdst = (unsigned char *)dst;
	refsrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		refdst[i] = refsrc[i];
		if (refdst[i] == cc)
			return (refdst + i + 1);
		i++;
	}
	return (NULL);
}
