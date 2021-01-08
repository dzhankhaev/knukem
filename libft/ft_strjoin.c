/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 22:49:08 by sisidra           #+#    #+#             */
/*   Updated: 2019/09/29 21:10:34 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	count;
	unsigned int	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char*)s1) + ft_strlen((char*)s2);
	if (!(str = (char*)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	count = 0;
	while (s1[count] != '\0')
	{
		str[count] = s1[count];
		count++;
	}
	i = 0;
	while (count < len)
	{
		str[count] = s2[i];
		count++;
		i++;
	}
	str[count] = '\0';
	return (str);
}
||||||| 1784372
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:30:43 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 16:11:24 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s1[i] || s2[j])
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
>>>>>>> master
