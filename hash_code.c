#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static char	*copy_n_chars(const char *str, int n)
{
	char	*a;
	int		i;

	a = (char *)malloc(sizeof(char) * (n + 1));
	if (!a)
		return (0);
	i = 0;
	while (i < n)
	{
		a[i] = str[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main(int av, char **ac)
{
	char buf[9000];
	if (av == 2)
	{
		int fd = open(ac[1], O_RDONLY);
		int i = (int)read(fd, buf, 9000);
		unsigned char *map = copy_n_chars(buf, i);
		printf("%lu\n", hash(map));
	}
		
	return (0);
}
