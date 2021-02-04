/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 05:55:33 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/06 06:05:32 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "archiver.h"

int		fill_heads(int out_fd, int st_byte, char *files, int size_head)
{
	int				fd;
	char			*buf;
	char			*file_name;
	struct stat		sb;

	file_name = (char*)malloc(size_head + 1);
	if ((fd = open(files, O_RDONLY)) < 1)
		return (0);
	while (get_next_line(fd, &buf))
	{
		stat(buf, &sb);
		ft_bzero(file_name, size_head - 8);
		ft_strcpy(file_name, buf);
		write(out_fd, file_name, size_head - 8);
		write(out_fd, &sb.st_size, 4);
		write(out_fd, &st_byte, 4);
		st_byte += sb.st_size + 1;
		ft_strdel(&buf);
	}
	ft_strdel(&file_name);
	ft_strdel(&buf);
	close(fd);
	return (1);
}

int		fill_body(int fd_w, int i)
{
	t_pack_pre		pre;
	int				cur_pos;
	int				fd;
	char			*buf;
	t_pack_head		head;

	read(fd_w, &pre, sizeof(t_pack_pre));
	cur_pos = lseek(fd_w, ((lseek(fd_w, 0, SEEK_CUR) >> 3) + 1) << 3, 0);
	head.file_name = (char*)malloc(sizeof(char) * (pre.len_field - 8));
	while (++i < pre.num_of_file)
	{
		read(fd_w, head.file_name, pre.len_field - 8);
		read(fd_w, &head.len, 8);
		fd = open(head.file_name, O_RDONLY);
		buf = (char*)malloc(head.len);
		read(fd, buf, head.len);
		close(fd);
		lseek(fd_w, head.start_byte, 0);
		write(fd_w, buf, head.len);
		free(buf);
		cur_pos += pre.len_field;
		lseek(fd_w, cur_pos, 0);
	}
	free(head.file_name);
	return (1);
}

int		write_top_infiles(char *output_file, int max_len, int lens, int *start)
{
	int			fd_w;

	fd_w = 0;
	if ((fd_w = open(output_file, O_RDWR | O_TRUNC | O_CREAT, 999)) < 0)
		exit_error();
	write(fd_w, "knukem\0\0", 8);
	write(fd_w, &max_len, sizeof(max_len));
	write(fd_w, &lens, sizeof(lens));
	write(fd_w, "start\0\0\0", 8);
	*start = max_len * lens + lseek(fd_w, 0, SEEK_CUR) + sizeof(start);
	*start = (((*start >> 3) + 1) << 3) + 1;
	write(fd_w, start, sizeof(int));
	lseek(fd_w, ((lseek(fd_w, 0, SEEK_CUR) >> 3) + 1) << 3, 0);
	return (fd_w);
}

int		max_len_filename(char *files, int *lens)
{
	int		max_len;
	int		fd;
	char	*buf;

	*lens = 0;
	buf = NULL;
	max_len = 0;
	if ((fd = open(files, O_RDONLY)) < 0)
		exit_error();
	while (get_next_line(fd, &buf))
	{
		max_len = (ft_strlen(buf) > max_len) ? ft_strlen(buf) : max_len;
		(*lens)++;
		ft_strdel(&buf);
	}
	max_len += sizeof(int) + sizeof(int) + 1;
	close(fd);
	return (max_len);
}

int		pack_files(char *files, char *output_file)
{
	int		fd;
	int		max_len;
	int		lens;
	int		start;

	lens = 0;
	max_len = 0;
	start = 0;
	max_len = max_len_filename(files, &lens);
	fd = write_top_infiles(output_file, max_len, lens, &start);
	fill_heads(fd, start, files, max_len);
	lseek(fd, 0, SEEK_SET);
	fill_body(fd, -1);
	close(fd);
	crc_xor(output_file, 0);
	return (1);
}
