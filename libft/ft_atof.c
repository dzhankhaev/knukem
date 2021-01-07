/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:58:48 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/07 20:31:30 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_atof_sub(int *i, char *line, double *f)
{
	int		j;

	j = 10;
	while (line[*i] && line[*i] >= '0' && line[*i] <= '9')
	{
		*f *= 10;
		*f += line[*i] - '0';
		++(*i);
	}
	if (line[*i] && line[*i] == '.')
	{
		++(*i);
		while (line[*i] && line[*i] >= '0' && line[*i] <= '9')
		{
			*f += (double)(line[*i] - '0') / j;
			j *= 10;
			++(*i);
		}
	}
}

double		ft_atof(char *num)
{
	double		f;
	int			i;
	int			flag;
	char		*line;

	i = 0;
	f = 0.0;
	if (num)
	{
		line = ft_strtrim(num);
		flag = 1;
		if (line[i] && line[i] == '-')
		{
			flag = -1;
			i++;
		}
		ft_atof_sub(&i, line, &f);
		free(line);
		return (f * flag);
	}
	return (0);
}