#include "get_next_line.h"
int     bsn(char *buffer)
{
    int     i;
    if (!buffer)
       return (0);
    i = 0;
    while (buffer[i] != '\0')
    {
        if (buffer[i] == '\n')
            return (i);
        i++;
    }
    return (i);
}
int      ft_strlen(const char *s)
{
    int  i;
    if (!s)
       return (0);
    i = 0;
    while (s[i] != '\0')
        i++;
    return (i);
}
//int     ft_check_mem(char *mem)
//{
// if (mem == NULL)
// {
//    if (!(mem = malloc((sizeof(char)))))
//       return (-1);
//    mem[0] = '\0';
// }
// return (0);
//}
int             get_next_line(int fd, char **line)
{
   static char *memory = NULL;
    ssize_t     read_bytes;
    char        buffer[BUFFER_SIZE + 1];
    read_bytes = 1;
    if (fd < 0)
       return (-1);
// if ((ft_check_mem(memory)) == (-1))
//    return (-1);
    if (memory == NULL)
    {
        if (!(memory = malloc((sizeof(char)))))
            return (-1);
        memory[0] = '\0';
    }
   while (read_bytes > 0 && new_line(memory) != 1)
   {
      read_bytes = read(fd, buffer, BUFFER_SIZE);
      buffer[read_bytes] = '\0';
      memory = ft_copy(memory, buffer);
   }
   if (read_bytes < 0)
      return (-1);
   if (!((*line) = get_line(memory)))
      return (-1);
   if (read_bytes == 0 && (memory[0] == '\0' || ft_strlen(memory) == bsn(memory)))
   {
      free(memory);
      memory = 0;
      return (0);
   }
   memory = ft_mem_copy(memory, read_bytes);
   return (1);
}






