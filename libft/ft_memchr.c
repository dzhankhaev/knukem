/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 19:01:16 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/27 20:32:13 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned long int	i;
	unsigned char		cc;
	unsigned char		*refs;

	refs = (unsigned char *)s;
	i = 0;
	cc = c;
	while (i < n)
	{
		if (refs[i] == cc)
			return (refs + i);
		i++;
	}
	return (NULL);
}
||||||| 1784372
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:29:23 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	d;
	unsigned char	*p;

	i = 0;
	d = (unsigned char)c;
	p = (unsigned char*)s;
	while (i < n)
	{
		if (p[i++] == d)
			return (p + i - 1);
	}
	return (NULL);
}
>>>>>>> master
