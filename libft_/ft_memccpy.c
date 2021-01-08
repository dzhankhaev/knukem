/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 19:44:37 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*p1;
	unsigned char	*pmem;

	p1 = (unsigned char*)src;
	pmem = (unsigned char*)ft_memchr(src, c, n);
	if (pmem)
	{
		ft_memcpy(dst, src, pmem - p1 + 1);
		return (dst + (pmem - p1 + 1));
	}
	ft_memcpy(dst, src, n);
	return (NULL);
}
