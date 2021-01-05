/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archiver.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/05 18:29:56 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "libft.h"
#include <errno.h>

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