#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "libft.h"
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

typedef struct		s_files
{
	char	file_name[24];
	int 	size_block;
	int		start_byte;
}					t_files;


void		check_folder(char *file_name)
{
	char			**arr;
	int				len;
	int				i;
	struct stat		sb;
	char			*sub_line;
	char			*line;
	int				fd = S_IRWXU | S_IRWXG | S_IRWXO;
	int chmodd, mkdirr;

	(void)sb;
	// sub_line = ft_strtrim(file_name);
	sub_line = NULL;
	line = NULL;
	arr = ft_strsplit(file_name, '/');
	len = ft_arrlen((void**)arr);
	i = 0;
	if (len > 1)
	{
		// ft_strdel(&line);
		line = ft_strdup(arr[i++]);
		if ((fd = open(line, O_RDONLY)) < 0)
			if ((chmodd = chmod(line, 0777)) < 0)
				mkdirr = mkdir(line, 0777);
	}
	while (i < len - 1)
	{
		ft_strdel(&sub_line);
		sub_line = ft_strjoin(line, "/");
		ft_strdel(&line);
		line = ft_strjoin(sub_line, arr[i]);
		if ((fd = open(line, O_RDONLY)) < 0)
			if ((chmodd = chmod(line, 0777)) < 0)
				mkdirr = mkdir(line, 0777);
		i++;
	}
	sub_line = ft_strjoin(line, "/");
	ft_strdel(&sub_line);
	sub_line = ft_strjoin(line,arr[i]);
}

void		pack(char *filename_out)
{
	struct stat		sb;
	char			file_name[21];
	char			*line;
	int				fd;
	unsigned char	size;
	int				i;
	t_files			*top;

	size = 0;
	memcpy(file_name, "textur/", 14);
	if ((fd = open("textur/files", O_RDONLY)))
	{
		while ((get_next_line(fd, &line)))
			size++;
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
			free(line);
		}
		close(fd);
		
		fd = open(filename_out,O_RDWR|O_TRUNC|O_CREAT,999);
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
		close(fd);
	}
}

void		unpack();

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		check_folder(argv[1]);
		// pack(argv[1]);
	}
	else
	{
		ft_putstr("Not filename for out pack\n");
	}
	

	return 0;
}
