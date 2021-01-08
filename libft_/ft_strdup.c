/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:10:47 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/18 02:43:58 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
		i++;
	if (!(dest = (char*)malloc(sizeof(char) * (i + 1))) || (src == NULL))
		return (NULL);
	dest[i] = '\0';
	while (i-- > 0)
		dest[i] = src[i];
	return (dest);
}
