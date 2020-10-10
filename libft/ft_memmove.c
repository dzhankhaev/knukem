/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 14:40:56 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*p1;

	i = 0;
	p = (unsigned char*)dst;
	p1 = (unsigned char*)src;
	if (p == p1)
		return (dst);
	if (p > p1)
	{
		while (len--)
			*(p + len) = *(p1 + len);
	}
	else
	{
		while (i < len)
		{
			*(p++) = *(p1++);
			i++;
		}
	}
	return (dst);
}
