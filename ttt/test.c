/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 20:21:33 by ecelsa            #+#    #+#             */
/*   Updated: 2020/11/04 20:29:47 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		bla(int i)
{
	return (i);
}

void	test(void)
{
	static int		i = 0;

	i++;
}

int		main(int argc, char const *argv[])
{
	test();
	test();
	test();
	return (0);
}
