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
||||||| 1784372
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 19:00:42 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*p;
	char	*p1;

	i = 0;
	if (dst == src)
		return (dst);
	p = (char*)dst;
	p1 = (char*)src;
	while (i < n)
	{
		*(p + i) = *(p1 + i);
		i++;
	}
	return (dst);
}
>>>>>>> master
