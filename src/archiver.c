/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archiver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:05:43 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 06:12:20 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "archiver.h"
#include <sys/errno.h>
#include <string.h>

u_char			crc_xor(char *file, int check)
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
	while (++i < sb.st_size)
		ret ^= buf[i];
	if (check == 1)
		ret = (buf[i] == ret) ? 1 : 0;
	else
		write(fd, &ret, 1);
	ft_strdel(&buf);
	close(fd);
	return (ret);
}

void			exit_error(void)
{
	ft_putendl(strerror(errno));
	exit(errno);
}

int				main(int argc, char **argv)
{
	if (argc == 4)
	{
		pack_files(argv[1], argv[2]);
		crc_xor(argv[2], 0);
		if ((crc_xor(argv[2], 1)) == 1)
			unpack_files(argv[2], argv[3]);
	}
	return (0);
}
