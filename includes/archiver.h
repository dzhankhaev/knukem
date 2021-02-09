/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archiver.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/02/09 03:02:33 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARCHIVER_H
# define ARCHIVER_H

# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include "libft.h"
# include <errno.h>

typedef struct		s_pack_pre
{
	char	name[8];
	int		len_field;
	int		num_of_file;
	char	start[8];
	int		start_byte;
}					t_pack_pre;

typedef struct		s_pack_head
{
	char		*file_name;
	int			len;
	int			start_byte;
}					t_pack_head;

typedef struct		s_archiver
{
	int				fd_out_file;
	int				max_title_len;
	int				num_files;
	int				pos_start_byte;
	char			*output_file;
	char			*src_dir;
	char			*buf[2];
	struct stat		sb;
	t_pack_pre		pre;
	t_pack_head		head;

}					t_archiver;

unsigned char		crc_xor(char *file, int check);
void				exit_error(int error);
int					unpack_files(char *file, char *dst_dir);
int					pack_files(char *files, char *output_file, char *src_dir);

#endif
