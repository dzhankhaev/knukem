/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:14:36 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/28 17:18:11 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *srch, size_t len)
{
	unsigned int	f;
	unsigned int	i;

	if (*srch == 0)
		return ((char*)str);
	f = 0;
	while (str[f] != '\0' && (size_t)f < len)
	{
		i = 0;
		if (str[f] == srch[i])
		{
			i++;
			while (srch[i] != '\0' && str[f + i] == srch[i] &&
											(size_t)(f + i) < len)
				++i;
			if (srch[i] == '\0')
				return ((char*)&str[f]);
		}
		++f;
	}
	return (0);
}
||||||| 1784372
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 13:54:56 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (to_find[0] == '\0')
		return ((char*)str);
	while (str[i] != '\0' && i < n)
	{
		if (to_find[0] == str[i])
		{
			j = 1;
			while (to_find[j] != '\0' && str[i + j] == to_find[j] &&
					(i + j) < n)
				j++;
			if (to_find[j] == '\0')
				return ((char*)&str[i]);
		}
		i++;
	}
	return (0);
}
>>>>>>> master
