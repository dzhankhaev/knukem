#include "editor.h"

static void	vertex(int fd)
{
	ft_putstr_fd("vertex\t", fd);
	ft_putnbr_fd(1, fd);
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(1, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(6, fd);
	ft_putchar_fd('\n', fd);
	ft_putstr_fd("vertex\t", fd);
	ft_putnbr_fd(6, fd);
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(1, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(6, fd);
	ft_putchar_fd('\n', fd);
}

static void	sector2(int fd)
{
	ft_putstr_fd("sector\t", fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(10, fd);
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(1, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(3, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(2, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putchar_fd('\t', fd);
}

static void	sector(int fd)
{
	int	i;

	sector2(fd);
	i = -1;
	while (++i < 4)
	{
		ft_putnbr_fd(-1, fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(-1, fd);
	ft_putchar_fd('\t', fd);
	i = -1;
	while (++i < 4)
	{
		ft_putnbr_fd(1, fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd('\n', fd);
}

void		new_map()
{
	int	fd;

	fd = open("new_map.txt", O_TRUNC | O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
	vertex(fd);
	sector(fd);
	ft_putstr_fd("player\t", fd);
	ft_putnbr_fd(3, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(3, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(1, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(50, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(10, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(50, fd);
	ft_putchar_fd(' ', fd);
	close(fd);
}