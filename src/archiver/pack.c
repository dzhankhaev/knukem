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
#include "editor.h"

int		fill_heads(char *files, char *src_dir, t_archiver *arch)
{
	int				fd;
	char			*buf;
	char			*file_name;
	char			*sub;

	file_name = (char*)malloc(arch->max_title_len + 1);
	if ((fd = open(files, O_RDONLY)) < 1)
		return (0);
	while (get_next_line(fd, &buf))
	{
		sub = ft_strjoin(src_dir, buf);
		stat(sub, &arch->sb);
		ft_bzero(file_name, arch->max_title_len - 8);
		ft_strcpy(file_name, buf);
		write(arch->fd_out_file, file_name, arch->max_title_len - 8);
		write(arch->fd_out_file, &arch->sb.st_size, 4);
		write(arch->fd_out_file, &arch->pos_start_byte, 4);
		arch->pos_start_byte += arch->sb.st_size + 1;
		ft_strdel(&sub);
		ft_strdel(&buf);
	}
	ft_strdel(&file_name);
	ft_strdel(&buf);
	close(fd);
	return (1);
}

int		fill_body(t_archiver *arch, int i)
{
	int				cur_pos;
	int				fd;

	read(arch->fd_out_file, &(arch->pre), sizeof(t_pack_pre));
	cur_pos = lseek(arch->fd_out_file, ((lseek(arch->fd_out_file, 0,
												SEEK_CUR) >> 3) + 1) << 3, 0);
	arch->head.file_name = (char*)malloc(arch->pre.len_field - 8);
	while (++i < arch->pre.num_of_file)
	{
		read(arch->fd_out_file, arch->head.file_name, arch->pre.len_field - 8);
		read(arch->fd_out_file, &(arch->head.len), 8);
		arch->buf[1] = ft_strjoin(arch->src_dir, arch->head.file_name);
		fd = open(arch->buf[1], O_RDONLY);
		ft_strdel(&arch->buf[1]);
		arch->buf[0] = (char*)malloc(arch->head.len);
		read(fd, arch->buf[0], arch->head.len);
		close(fd);
		lseek(arch->fd_out_file, arch->head.start_byte, 0);
		write(arch->fd_out_file, arch->buf[0], arch->head.len);
		free(arch->buf[0]);
		cur_pos += arch->pre.len_field;
		lseek(arch->fd_out_file, cur_pos, 0);
	}
	free(arch->head.file_name);
	return (1);
}

void	write_top_infiles(t_archiver *arch)
{
	if ((arch->fd_out_file = open(arch->output_file, O_RDWR | O_TRUNC | O_CREAT,
																	999)) < 0)
		exit_error(ENOENT);
	write(arch->fd_out_file, "knukem\0\0", 8);
	write(arch->fd_out_file, &arch->max_title_len, sizeof(arch->max_title_len));
	write(arch->fd_out_file, &arch->num_files, sizeof(arch->num_files));
	write(arch->fd_out_file, "start\0\0\0", 8);
	arch->pos_start_byte = arch->max_title_len * arch->num_files +
		lseek(arch->fd_out_file, 0, SEEK_CUR) + sizeof(arch->pos_start_byte);
	arch->pos_start_byte = (((arch->pos_start_byte >> 3) + 1) << 3) + 1;
	write(arch->fd_out_file, &arch->pos_start_byte, sizeof(int));
	lseek(arch->fd_out_file, ((lseek(arch->fd_out_file, 0, SEEK_CUR) >> 3)
																+ 1) << 3, 0);
}

void	max_len_filename(char *files, t_archiver *arch)
{
	int				fd;
	char			*buf;

	buf = NULL;
	if ((fd = open(files, O_RDONLY)) < 0)
		exit_error(0);
	while (get_next_line(fd, &buf))
	{
		if (ft_strlen(buf) > arch->max_title_len)
			arch->max_title_len = ft_strlen(buf);
		arch->num_files++;
		ft_strdel(&buf);
	}
	arch->max_title_len += sizeof(int) + sizeof(int) + 1;
	close(fd);
}

int		pack_files(char *files, char *output_file, char *src_dir)
{
	t_archiver arch;

	ft_bzero(&arch, sizeof(t_archiver));
	arch.output_file = output_file;
	max_len_filename(files, &arch);
	write_top_infiles(&arch);
	fill_heads(files, src_dir, &arch);
	lseek(arch.fd_out_file, 0, SEEK_SET);
	fill_body(&arch, -1);
	close(arch.fd_out_file);
	crc_xor(arch.output_file, 0);
	return (1);
}
