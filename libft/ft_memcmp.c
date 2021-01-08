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
||||||| 1784372
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:55:54 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char*)s1;
	p2 = (unsigned char*)s2;
	if (!n)
		return (0);
	while (i < n - 1)
	{
		if (p1[i] != p2[i])
			break ;
		i++;
	}
	return (p1[i] - p2[i]);
}
>>>>>>> master
