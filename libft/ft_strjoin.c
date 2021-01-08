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
