/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archiver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:05:43 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/07 17:10:49 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "archiver.h"
#include <sys/errno.h>
#include <string.h>

unsigned char	crc_xor(char *file, int check)
{
	char			ret;
	int				fd;
	int				i;
	char			*buf;
	struct stat		sb;

	ret = 0xff;
	i = -1;
	stat(file, &sb);
	fd = open(file, O_RDWR);
	buf = (char*)malloc(sb.st_size);
	read(fd, buf, sb.st_size);
	sb.st_size -= (check == 1) ? 1 : 0;
	while (++i < sb.st_size - check * 3)
		ret ^= buf[i];
	if (check == 1)
		ret = (buf[i + 3] == ret) ? 1 : 0;
	else
	{
		write(fd, "crc", 3);
		write(fd, &ret, 1);
	}
	ft_strdel(&buf);
	close(fd);
	return (ret);
}

void			exit_error(int error)
{
	if (error != 0)
		errno = error;
	ft_putendl(strerror(errno));
	exit(errno);
}
