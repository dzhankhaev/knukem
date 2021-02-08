/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 05:59:22 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 06:03:44 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "archiver.h"

int				make_dir(char *file_name)
{
	char	**split;
	int		arr_len;
	char	*sub[2];
	int		i;

	i = -1;
	split = ft_strsplit(file_name, '/');
	if ((arr_len = ft_arrlen((void**)split)) > 1)
	{
		sub[0] = ft_strjoin((file_name[0] == '/') ? "/" : "", split[0]);
		sub[1] = NULL;
		while (++i < arr_len - 1)
		{
			mkdir(sub[0], 0777);
			ft_strdel(&sub[1]);
			sub[1] = ft_strjoin(sub[0], "/");
			ft_strdel(&sub[0]);
			sub[0] = ft_strjoin(sub[1], split[i + 1]);
		}
		ft_strdel(&sub[0]);
		ft_strdel(&sub[1]);
		ft_free_split(split);
	}
	return (1);
}

int				create_file(int fd_in, t_pack_head head, char *file_name)
{
	int			fd;
	char		*buf;

	buf = NULL;
	make_dir(file_name);
	if ((fd = open(file_name, O_RDWR | O_TRUNC | O_CREAT, 999)) < 0)
		exit_error(0);
	buf = (char*)malloc(head.len);
	lseek(fd_in, head.start_byte, 0);
	read(fd_in, buf, head.len);
	write(fd, buf, head.len);
	close(fd);
	ft_strdel(&buf);
	return (1);
}

int				crate_files_from_pack(t_pack_pre pre, int fd_in,
													char *dst_dir, int cur_pos)
{
	t_pack_head	head;
	int			i;
	char		*sub;
	int			fd_files;

	sub = ft_strjoin(dst_dir, "files");
	if ((fd_files = open(sub, O_RDWR | O_TRUNC | O_CREAT, 999)) < 0)
		exit_error(0);
	ft_strdel(&sub);
	head.file_name = (char*)malloc(sizeof(char) * (pre.len_field - 8));
	i = -1;
	while (++i < pre.num_of_file)
	{
		read(fd_in, head.file_name, pre.len_field - 8);
		read(fd_in, &head.len, 8);
		sub = ft_strjoin(dst_dir, head.file_name);
		ft_putendl_fd(head.file_name, fd_files);
		create_file(fd_in, head, sub);
		ft_strdel(&sub);
		cur_pos += pre.len_field;
		lseek(fd_in, cur_pos, 0);
	}
	ft_strdel(&head.file_name);
	close(fd_files);
	return (0);
}

int				unpack_files(char *file, char *dst_dir)
{
	int			fd_in;
	t_pack_pre	pre;
	int			cur_pos;
	char		*sub;
	char		*cur_dst_dir;

	if (!crc_xor(file, 1))
		exit_error(ENOEXEC);
	cur_dst_dir = ft_strjoin(dst_dir, ((dst_dir[ft_strlen(dst_dir) - 1] == '/')
									|| ft_strlen(dst_dir) == 0) ? "" : "/");
	sub = ft_strjoin(cur_dst_dir, "files");
	make_dir(sub);
	ft_strdel(&sub);
	fd_in = open(file, O_RDONLY);
	read(fd_in, &pre, sizeof(t_pack_pre));
	cur_pos = lseek(fd_in, ((lseek(fd_in, 0, SEEK_CUR) >> 3) + 1) << 3, 0);
	crate_files_from_pack(pre, fd_in, cur_dst_dir, cur_pos);
	ft_strdel(&cur_dst_dir);
	return (1);
}
