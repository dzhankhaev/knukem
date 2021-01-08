/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:51:24 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/28 22:17:53 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *srch)
{
	unsigned int	i;
	unsigned int	f;

	if (*srch == 0)
		return ((char*)str);
	f = 0;
	i = 0;
	while (str[f] != '\0')
	{
		if (str[f] == srch[i])
		{
			while (str[f + i] == srch[i] && srch[i] != '\0')
				i++;
			if (srch[i] == '\0')
				return ((char*)&str[f]);
			else
				i = 0;
		}
		f++;
	}
	return (NULL);
}
||||||| 1784372
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 23:01:09 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (to_find[0] == '\0')
		return ((char*)str);
	while (str[i] != '\0')
	{
		if (to_find[0] == str[i])
		{
			j = 1;
			while (to_find[j] != '\0' && str[i + j] == to_find[j])
				j++;
			if (to_find[j] == '\0')
				return ((char*)&str[i]);
		}
		i++;
	}
	return (0);
}
>>>>>>> master
