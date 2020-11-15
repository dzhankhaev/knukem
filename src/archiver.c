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
	char	file_name[24];
	int 	size_block;
	int		start_byte;
}					t_files;


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

void		pack(char *dir_src, char *filename_out)
{
	struct stat		sb;
	char			file_name[21];
	char			*line;
	int				fd;
	unsigned char	size;
	int				i;
	t_files			*top;

	size = 0;
	memcpy(file_name, dir_src, 14);
	line = ft_strjoin(dir_src, (dir_src[ft_strlen(dir_src) - 1] == '/') ? "files" : "/files");
	if ((fd = open(line, O_RDONLY)))
	{
		ft_strdel(&line);
		while ((get_next_line(fd, &line)))
		{
			ft_strdel(&line);
			size++;
		}
			printf("%i\n",size);
		top = (t_files*)malloc(sizeof(t_files) * size);
		lseek(fd, 0, 0);
		i = -1;
		while ((get_next_line(fd, &line)))
		{
			i++;
			memcpy(file_name + 7, line, 14);
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
		line = ft_strjoin(dir_src, filename_out);
		fd = open(line,O_RDWR|O_TRUNC|O_CREAT,999);
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

void		unpack();

int main(int argc, char **argv)
{
	int fd;
	pid_t pid;
	char *bla[] = {"" ,"!!!" , "arg2" , NULL};
	// int ret;

	pid = fork();
	if (pid == 0)
	{
		execve("run.sh", bla, NULL);
		exit (0);
	}
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		check_folder(argv[1]);
		pack(argv[1], "out_file");
		close(fd);
		// pack(argv[1]);
	}
	else
	{
		ft_putstr("Not filename for out pack\n");
	}
	return 0;
}
