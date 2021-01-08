/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 22:24:14 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/29 21:07:19 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *s;

	if (size != 0)
	{
		s = (size_t*)malloc(sizeof(size_t) * size);
		if (s == NULL)
			return (NULL);
	}
	else
		return (NULL);
	ft_bzero(s, size);
	return (s);
}
||||||| 1784372
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:03:26 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *res;

	res = NULL;
	if ((res = (void*)malloc(size)))
		return (ft_memset(res, 0, size));
	else
		return (NULL);
}
>>>>>>> master
