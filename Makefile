CLEAR_LINE	:= \033[2K
BEGIN_LINE	:= \033[A
RESET_FORM	:= \033[0m
RED_FONT	:= \033[1;31m
GREEN_FONT	:= \033[1;32m
YELLOW_FONT	:= \033[1;33m
BLUE_FONT	:= \033[1;34m
VIOLET_FONT	:= \033[1;35m
CYAN_FONT	:= \033[1;36m
WHITE_FONT	:= \033[1;37m

NAME :=	d-k3d

HEADERS := engine.h\
	arg_defines.h\
	math_utilits.h\


SRC := main.c\
	run_queue.c\
	init_engine.c\
	move.c\
	transform_wall.c\
	cut_wall.c\
	keys_manager.c\
	manage_data.c\
	game_loop.c\
	math_utilits/determine_intersection.c\
    math_utilits/mathf.c\
    math_utilits/intersection_point.c\
    math_utilits/rotate_wall.c\
	render/minimap.c\
	render/line/render_line.c\
	render/line/render_line_with_angle.c\
#	ft_col_dec.c\
#	ft_render_walls.c\


OBJ := $(SRC:.c=.o)

SRCDIR := src
OBJDIR := obj

HEADERSP := $(addprefix includes/, $(HEADERS))
SRCP :=		$(addprefix $(SRCDIR)/, $(SRC))
OBJP :=		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
ONLYDIR :=	$(foreach dir, $(OBJP), $(shell dirname $(dir)))

FLAG :=  -g #-Wall -Werror -Wextra

PWD := $(shell pwd)
FRAMEWORKSDIR := $(PWD)/frameworks
INC := -I includes
SDL := -F $(FRAMEWORKSDIR) -framework SDL2 -framework SDL2_ttf -framework SDL2_image -framework SDL2_mixer -Wl -rpath $(FRAMEWORKSDIR)

TOTAL_FILES := $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell find $(PWD)/obj/ -type f 2> /dev/null | wc -l | sed -e 's/ //g')

all : $(NAME)

$(NAME) : $(OBJP)
			@gcc $(SDL) $(FLAG) $(OBJP) $(INC) $(LIB) -o $(NAME)
			@echo "$(CLEAR_LINE)$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Finished compilation. Output file : $(VIOLET_FONT)$(PWD)/$(NAME)$(RESET_FORM)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERSP)
			@mkdir -p $(ONLYDIR)
			@gcc -c $(FLAG) -F $(FRAMEWORKSDIR) $(INC) $< -o $@
			@echo "$(CLEAR_LINE)$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Compiling file [$(VIOLET_FONT)$<$(COL_YELLOW)]. ($(CURRENT_FILES) / $(TOTAL_FILES))$(RESET_FORM)$(BEGIN_LINE)"


clean :
			@rm -rf $(OBJDIR)
			@echo "$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Removed $(VIOLET_FONT)object files.$(RESET_FORM)"

fclean :	clean
			@rm -rf $(NAME)
			@echo "$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Removed $(VIOLET_FONT)$(NAME)$(RESET_FORM)"

re :		fclean all