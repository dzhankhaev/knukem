NAME = libft.a
SRC = ./
INCLUDE = libft.h 
LIB = get_next_line c_mod c_arg c_add c_sub c_set c_sqr c_pow ft_swap\
		ft_lstmap ft_lstiter ft_lstadd ft_lstnew ft_lstdelone ft_lstdel\
		ft_atoi ft_bzero ft_isalpha ft_isascii ft_isdigit ft_itoa ft_toupper\
		ft_tolower ft_isprint ft_isalnum ft_memalloc ft_memdel ft_memset\
		ft_memchr ft_memcmp ft_memcpy ft_memccpy ft_memmove ft_strclr\
		ft_strdup ft_strdel ft_striter ft_striteri ft_strjoin ft_strcat\
		ft_strchr ft_strnew ft_strrchr ft_strlcat ft_strncmp ft_strnstr\
		ft_strstr ft_strncat ft_strcmp ft_strcpy ft_strlen ft_strequ\
		ft_strmap ft_strmapi ft_strncpy ft_strnequ ft_strsplit ft_strsub\
		ft_strtrim ft_putchar ft_putchar_fd ft_putnbr ft_putnbr_fd ft_putstr\
		ft_putstr_fd ft_putendl ft_putendl_fd ft_realloc
FILES = $(patsubst %, %.o, $(LIB))

all: $(NAME)

$(LIB):
	gcc -Wall -Werror -Wextra -c $(patsubst %.o, $(SRC)%.c, $(NAME)) -I $(INCLUDE) -o $@ -c $<

$(NAME): $(FILES)
	ar rc $(NAME) $(FILES);
	ranlib $(NAME);

clean:
	rm  -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
