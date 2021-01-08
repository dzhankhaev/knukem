/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgruyere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:36:56 by dgruyere          #+#    #+#             */
/*   Updated: 2020/07/19 15:37:30 by dgruyere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		len;
	char	buf;
	int		i;

	i = 0;
	len = ft_strlen(str);
	while (len - 1 > i)
	{
		buf = str[len - 1];
		str[len - 1] = str[i];
		str[i] = buf;
		len--;
		i++;
	}
	return (str);
}
