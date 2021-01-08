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
		ft_putstr_fd ft_putendl ft_putendl_fd ft_realloc ft_free_split ft_arrlen\
		ft_atof
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
||||||| 1784372
=======
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/06 16:49:32 by dgruyere          #+#    #+#              #
#    Updated: 2020/11/12 14:38:18 by ecelsa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strzero.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_strnlen.c ft_min.c ft_max.c ft_swap.c ft_lstsize.c ft_strrev.c get_next_line.c ft_free_split.c ft_arrlen.c

O_FILES = ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o ft_memchr.o ft_memcmp.o ft_strlen.o ft_strdup.o ft_strcpy.o ft_strncpy.o ft_strcat.o ft_strncat.o ft_strlcat.o ft_strchr.o ft_strrchr.o ft_strstr.o ft_strnstr.o ft_strcmp.o ft_strncmp.o ft_atoi.o ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o ft_memalloc.o ft_memdel.o ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o ft_strtrim.o ft_strsplit.o ft_itoa.o ft_putchar.o ft_putstr.o ft_putendl.o ft_putnbr.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_strzero.o ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o ft_lstmap.o ft_strnlen.o ft_min.o ft_max.o ft_swap.o ft_lstsize.o ft_strrev.o ft_free_split.o ft_arrlen.o get_next_line.o

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):	$(SRCS) libft.h
			gcc -g -Wall -Wextra -Werror -c $(SRC)
			ar rc $(NAME) $(O_FILES)
			ranlib $(NAME)

clean:
	/bin/rm -f $(O_FILES)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
>>>>>>> master
