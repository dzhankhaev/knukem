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
||||||| 1784372
=======
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
>>>>>>> master
