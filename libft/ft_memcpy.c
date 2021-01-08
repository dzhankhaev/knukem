/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 23:05:19 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/29 22:54:48 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*redst;
	unsigned char	*resrc;

	redst = (unsigned char *)dst;
	resrc = (unsigned char *)src;
	if (dst == NULL && src == NULL && n)
		return (NULL);
	i = 0;
	while (i < n)
	{
		redst[i] = resrc[i];
		i++;
	}
	return (dst);
}
