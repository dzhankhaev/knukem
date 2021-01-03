#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "libft.h"
#include <errno.h>
/**
**	список файлов
**	сколько их?
**	записать в фаил в начале сколько файлов (инт)
**	16 символов имя файла + int адрес сектора(4 + 20 * количество файлов)
**	
**
**
**
**/

/*загрузка игры из карты*/
// проверить сушествует ли каталог? создать
// распаковать в каталог все файлы
// выполнить загрузку всех файлов текстур все что надо
// затереть созданый каталог и внутринности


/*создание карты*/
// распаковать дефолтный архив в дирректорию либо прочитать дирректорию, найти там фаил с перечнем файлов
// сгенерировать карту и перенаправить в фаил
// упаковать все в один фаил с определенным названием
// подчистить за собой

typedef struct		s_files
{
	char			file_name[22];
	int 			size_block;
	int				start_byte;
	struct s_files	*next;
}					t_files;

int		new_t_files(char *file_name, int size_block, t_files **top)
{
	t_files			*tmp;

	if (*top == NULL)
	{
 		*top = (t_files*)malloc(sizeof(t_files));
		**top = (t_files){.start_byte = 8, .size_block = size_block, .next = NULL};
		ft_strncpy((*top)->file_name, file_name, sizeof((*top)->file_name));
	}
	else
	{
		tmp = *top;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_files*)malloc(sizeof(t_files));
		*tmp->next = (t_files){.start_byte = tmp->start_byte +
			tmp->size_block + 1, .size_block = size_block, .next = NULL};
		ft_strncpy(tmp->file_name, file_name, sizeof(tmp->file_name));
	}
	return (1);
}

int		free_t_files(t_files **t_files_list)
{
	t_files		*tmp;
	t_files		*sub;

	tmp = *t_files_list;
	while (tmp != NULL)
	{
		sub = tmp->next;
		// free(tmp->file_name);
		*tmp = (t_files){.size_block = 0, .start_byte = 0};
		ft_bzero(&tmp->file_name, sizeof(tmp->file_name));
		free(tmp);
		tmp = NULL;
		tmp = sub;
	}
	*t_files_list = NULL;
	return (1);
}

void		check_folder(char *dir_name)
{
	char			**arr;
	int				len;
	int				i;
	char			*sub_line;
	char			*line;
	int				fd;

	sub_line = NULL;
	line = NULL;
	sub_line = ft_strtrim(dir_name);
	len = (sub_line[ft_strlen(sub_line) - 1] == '/') ? 0 : -1;
	ft_strdel(&sub_line);
	arr = ft_strsplit(dir_name, '/');
	len += ft_arrlen((void**)arr);
	i = 0;
	sub_line = ft_strdup(arr[i]);
	while (i < len && len > 0)
	{
		ft_strdel(&line);
		line = ft_strjoin(sub_line, (i == 0) ? "" : arr[i]);
		ft_strdel(&sub_line);
		sub_line = ft_strjoin(line, "/");
		if ((fd = open(line, O_RDONLY)) < 0)
		{
			if (chmod(line, 0777) < 0)
				mkdir(line, 0777);
		}
		else
			close(fd);
		i++;
	}
	ft_strdel(&sub_line);
	ft_strdel(&line);
	ft_free_split(arr);
}

//какую папку, в какой фаил упаковать

void		pack(char *dir_src, char *filename_out)
{
	struct stat		sb;
	char			file_name[21];
	char			*line;
	int				fd;
	unsigned char	size;
	int				i;
	char			*sub_pt;
	t_files			*top;

	size = 0;
	memcpy(file_name, ".tmp/", 14);
	sub_pt = file_name + 5;
	line = ft_strjoin(dir_src, (dir_src[ft_strlen(dir_src) - 1] == '/') ? "files" : "/files");
	if ((fd = open(line, O_RDONLY)))
	{
		ft_strdel(&line);
		while ((get_next_line(fd, &line)))
		{
			size++;
			ft_strdel(&line);
		}
			printf("%i\n",size);
		top = (t_files*)malloc(sizeof(t_files) * size);
		lseek(fd, 0, 0);
		i = -1;
		while ((get_next_line(fd, &line)))
		{
			i++;
			memcpy(file_name + 5, line, 14);
			if (stat(file_name, &sb) != -1)
			{
				if (!(sb.st_mode & S_IFDIR))
				{
					strcpy(top[i].file_name, file_name);
					top[i].size_block = sb.st_size;
					if (i == 0)
						top[i].start_byte = size * sizeof(t_files) + 8;
					else
						top[i].start_byte = top[i - 1].start_byte + top[i - 1].size_block + 1;
				}
			}
			ft_strdel(&line);
		}
		close(fd);
		// line = ft_strjoin(dir_src, filename_out);
		fd = open(filename_out,O_RDWR|O_TRUNC|O_CREAT,999);
		ft_strdel(&line);
		lseek(fd,7,0);
		write(fd, &size, 1);
		i = -1;
		while(++i < size)
		{
			lseek(fd, 8 + i * sizeof(t_files), 0);
			write(fd, &top[i], sizeof(t_files));
			int fdo;
			fdo = open(top[i].file_name,O_RDONLY);
			char	buf[1024];
			int		fr;
			lseek(fd, top[i].start_byte, 0);
			while ((fr = read(fdo, buf, sizeof(buf))))
				write(fd, buf, fr);
			close(fdo);
			printf("file name '%s' size-%i start-%i\n",top[i].file_name,top[i].size_block,top[i].start_byte);
		}
		free(top);
		close(fd);
	}
}

int			ft_file_lines(char *filename)
{
	int				lines;
	int				fd;
	char			*line;
	// t_files			*top;

	fd = 0;
	lines = 0;
	if ((fd = open(filename, O_RDONLY)))
	{
		while (get_next_line(fd, &line))
		{
			++lines;
			free(line);
		}
		close(fd);
	}
	else
		return (-1);
	return (lines);
}

// fill_t_files(t_files *top, intlen, )
// {
// 	while(++i < size)
// 		{
// 			lseek(fd, 8 + i * sizeof(t_files), 0);
// 			write(fd, &top[i], sizeof(t_files));
// 			int fdo;
// 			fdo = open(top[i].file_name,O_RDONLY);
// 			char	buf[1024];
// 			int		fr;
// 			lseek(fd, top[i].start_byte, 0);
// 			while ((fr = read(fdo, buf, sizeof(buf))))
// 				write(fd, buf, fr);
// 			close(fdo);
// 			printf("file name '%s' size-%i start-%i\n",top[i].file_name,top[i].size_block,top[i].start_byte);
// 		}
// }

// void		dir_to_outfile(char *src_dir, char *output_filename)
// {
// 	int			fd;
// 	char		*files;
// 	char		*line;
// 	t_files		*top;
// 	int i;
	
// 	if ((i = ft_file_lines(output_filename)) > 0)
// 	{
// 		top = (t_files*)malloc(sizeof(t_files) * i);
// 		// files = ft_strjoin(src_dir, "/files");
// 		fill_t_files(top, i, output_filename);
// 		fd = open(files,O_RDONLY);
// 	}
// }

void		unpack();

// int main(int argc, char **argv)
// {
// 	// int fd;
// 	// pid_t pid;
// 	t_files		*top;
// 	t_files		*tmp;
// 	int			fd;
// 	int			fd_sub;
// 	int			len;
// 	char		*line;

// 	top = NULL;
// 	free_t_files(&top);
// 	new_t_files("PISFA0.png", 2033, &top);
// 	new_t_files("PISGA0.png", 2631, &top);
// 	new_t_files("PISGB0.png", 3292, &top);
// 	new_t_files("PISGC0.png", 3098, &top);
// 	tmp = top;
// 	fd = open("out_file.map", O_RDWR|O_TRUNC|O_CREAT,999);
// 	len = ft_file_lines("textur/files");
// 	write(fd, &(len), 4);
// 	lseek(fd, 8, 0);
// 	//fill head
// 	{
// 		while (tmp)
// 		{
// 			write(fd, tmp, sizeof(t_files) + ft_strlen(tmp->file_name));
// 			tmp = tmp->next;
// 		}	
// 	}
// 	tmp = top;
// 	while (tmp)
// 	{
// 		if ((fd_sub = open(tmp->file_name, O_RDONLY)))
// 		{
// 			lseek(fd, tmp->start_byte, 0);
// 			line = (char*)malloc(tmp->size_block + 1);
// 			read(fd_sub, line, tmp->size_block);
// 			ft_putstr_fd(line, fd);
// 			ft_strdel(&line);
// 			close(fd_sub);
// 		}
// 		tmp = tmp->next;
// 	}
// 	close(fd);
// 	free_t_files(&top);
// 	// char *bla[] = {"" ,"!!!" , "arg2" , NULL};
// 	// // int ret;

// 	// pid = fork();
// 	// if (pid == 0)
// 	// {
// 	// 	execve("run.sh", bla, NULL);
// 	// 	exit (0);
// 	// }
// 	// if (argc == 2)
// 	// {
// 	// 	fd = open(argv[1], O_RDONLY);
// 	// 	check_folder(argv[1]);
// 	// 	pack(argv[1], "out_file");
// 	// 	close(fd);
// 	// 	// pack(argv[1]);
// 	// }
// 	// else
// 	// {
// 	// 	ft_putstr("Not filename for out pack\n");
// 	// }
// 	return 0;
// }



/*
	1.получить фаил со списом файлов
	1.1 открывается?
	1.2 читается?
	2.читаем по строчно именя(относительный или полный путь до файлов)
	2.1 открывается? читается?	2.2 читаем в ** размер/ имя /	
	2.3 пишем в шапку в слудуюшую область, имя / размер / начало блока

	Опеределить максимальную длинну файла
	[старт текст][размер шапки блока[длинна имени + \0 + 4байта размер файла]][колиество блоков][[имя файла][длинна блока][старт блока]]
	[8 байт]
*/

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
		ft_strdel(&buf);
		cur_pos += pre.len_field;
		lseek(fd_w, cur_pos, 0);
	}
	ft_strdel(&head.file_name);
	return(1);
}

int		fill_heads(int out_fd, int start_byte, char *files, int size_head)
{
	int				fd;
	char			*buf;
	struct stat		sb;

	fd = open(files, O_RDONLY);
	while (get_next_line(fd, &buf))
	{
		stat(buf, &sb);
		write(out_fd, buf, size_head - 8);
		write(out_fd, &sb.st_size, 4);
		write(out_fd, &start_byte, 4);
		start_byte += sb.st_size + 1;
		ft_strdel(&buf);
	}
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
	printf("ok\n");
	while (get_next_line(fd, &buf))
	{
		max_len = (ft_strlen(buf) > max_len) ? ft_strlen(buf) : max_len;
		lens++;
		ft_strdel(&buf);
	}
	close(fd);
	if ((fd_w = open(output_file,O_RDWR|O_TRUNC|O_CREAT,999)) < 1)
		return (0);
	max_len+= sizeof(int) + sizeof(int);
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

	mkdir(dst_dir, 0777);
	sub = ft_strjoin(dst_dir,"textur");
	mkdir(sub, 0777);
	ft_strdel(&sub);
	fd_in = open(file, O_RDONLY);
	read(fd_in, &pre, sizeof(t_pack_pre));
	cur_pos = lseek(fd_in, ((lseek(fd_in, 0, SEEK_CUR) >> 3) + 1) << 3, 0);
	head.file_name = (char*)malloc(sizeof(char) * (pre.len_field - 8));
	i = -1;
	while (++i < pre.num_of_file)
	{
		read(fd_in, head.file_name, pre.len_field - 8);
		read(fd_in, &head.len, 8);
		sub = ft_strjoin(dst_dir, head.file_name);
		fd = open(sub,O_RDWR|O_TRUNC|O_CREAT,999);
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
	return(1);
}

int main(int argc, char const *argv[])
{
	pack_files("textur/files", "map_1");
	unpack_files("map_1", "");
	return 0;
}
