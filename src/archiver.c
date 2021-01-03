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

u_char crc_xor(char *file, int check)
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
	while(++i < sb.st_size)
		ret ^= buf[i];
	if (check == 1)
		ret = (buf[i] == ret) ? 1 : 0;
	else
		write(fd, &ret, 1);
	ft_strdel(&buf);
	close(fd);
	return(ret);
}

int		fill_body(int fd_w)
{
	t_pack_pre	pre;
	int cur_pos;
	int fd;
	int i;
	char *buf;
	t_pack_head	head;

	lseek(fd_w, 0, SEEK_SET);
	read(fd_w, &pre, sizeof(t_pack_pre));
	cur_pos = lseek(fd_w, ((lseek(fd_w, 0, SEEK_CUR) >> 3) + 1) << 3, 0);
	head.file_name = (char*)malloc(sizeof(char) * (pre.len_field - 8));
	i = -1;
	while (++i < pre.num_of_file)
	{
		read(fd_w, head.file_name, pre.len_field - 8);
		read(fd_w, &head.len, 8);
		fd = open(head.file_name,O_RDONLY);
		buf = (char*)malloc(head.len);
		read(fd,buf,head.len);
		close(fd);
		lseek(fd_w, head.start_byte, 0);
		write(fd_w, buf,head.len);
		free(buf);
		cur_pos += pre.len_field;
		lseek(fd_w, cur_pos, 0);
	}
	free(head.file_name);
	return(1);
}

int		fill_heads(int out_fd, int start_byte, char *files, int size_head)
{
	int				fd;
	char			*buf;
	char			*file_name;
	struct stat		sb;

	file_name = (char*)malloc(size_head);
	fd = open(files, O_RDONLY);
	while (get_next_line(fd, &buf))
	{
		stat(buf, &sb);
		ft_bzero(file_name, size_head - 8);
		ft_strcpy(file_name, buf);
		write(out_fd, file_name, size_head - 8);
		write(out_fd, &sb.st_size, 4);
		write(out_fd, &start_byte, 4);
		start_byte += sb.st_size + 1;
		ft_strdel(&buf);
	}
	ft_strdel(&file_name);
	ft_strdel(&buf);	
	return(1);
}

int		pack_files(char *files, char *output_file)
{
	int fd_w;
	int fd;
	char *buf;
	int max_len;
	int lens;

	lens = 0;
	max_len = 0;
	if ((fd = open(files, O_RDONLY)) < 1)
		return(0);
	while (get_next_line(fd, &buf))
	{
		max_len = (ft_strlen(buf) > max_len) ? ft_strlen(buf) : max_len;
		lens++;
		ft_strdel(&buf);
	}
	close(fd);
	if ((fd_w = open(output_file,O_RDWR|O_TRUNC|O_CREAT,999)) < 1)
		return (0);
	max_len+= sizeof(int) + sizeof(int) + 1;
	write(fd_w, "knukem\0\0", 8);
	write(fd_w, &max_len, sizeof(max_len));
	write(fd_w, &lens, sizeof(lens));
	write(fd_w, "start\0\0\0",8);
	int start = max_len * lens + lseek(fd_w, 0, SEEK_CUR) + sizeof(start);
	start = (((start >> 3) + 1) << 3) + 1;
	write(fd_w, &start, sizeof(start));
	lseek(fd_w, ((lseek(fd_w, 0, SEEK_CUR) >> 3) + 1) << 3, 0);
	fill_heads(fd_w, start, files,max_len);
	fill_body(fd_w);
	close(fd_w);
	return(1);
}

int make_dir(char *file_name)
{
	char **split;
	int arr_len;
	char *sub[2];
	int i;

	i = -1;
	split = ft_strsplit(file_name,'/');
	if ((arr_len = ft_arrlen((void**)split)) > 1)
	{
		sub[0] = ft_strdup(split[0]);
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
	return(1);
}

int unpack_files(char *file, char *dst_dir)
{
	int fd_in;
	t_pack_pre	pre;
	int cur_pos;
	int fd;
	int i;
	char *buf;
	char *sub;
	t_pack_head	head;

	fd_in = open(file, O_RDONLY);
	read(fd_in, &pre, sizeof(t_pack_pre));
	cur_pos = lseek(fd_in, ((lseek(fd_in, 0, SEEK_CUR) >> 3) + 1) << 3, 0);
	head.file_name = (char*)malloc(sizeof(char) * (pre.len_field - 8));
	i = -1;
	while (++i < pre.num_of_file)
	{
		read(fd_in, head.file_name, pre.len_field - 8);
		read(fd_in, &head.len, 8);
		buf = ft_strjoin(dst_dir,
						(dst_dir[ft_strlen(dst_dir) - 1] == '/') ? "" : "/");
		sub = ft_strjoin(buf, head.file_name);
		ft_strdel(&buf);
		make_dir(sub);
		if ((fd = open(sub,O_RDWR|O_TRUNC|O_CREAT,999)) < 1)
			continue;
		ft_strdel(&sub);
		buf = (char*)malloc(head.len);
		lseek(fd_in, head.start_byte, 0);
		read(fd_in, buf,head.len);
		write(fd, buf,head.len);
		close(fd);
		ft_strdel(&buf);
		cur_pos += pre.len_field;
		lseek(fd_in, cur_pos, 0);
	}
	ft_strdel(&head.file_name);
	return(1);
}

int main(int argc, char const *argv[])
{
	// u_char ret;
	// pack_files("textur/files", "map_1");
	// ret = crc_xor("map_1", 0);
	if ((crc_xor("map_1", 1)) == 1)
		unpack_files("map_1", "tes");
	while(1);
	return 0;
}
