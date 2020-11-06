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
	render/rotate.c\
	render/minimap.c\
	render/line/render_line.c\
	render/line/render_line_with_angle.c\
	math_utilits/vector_operations.c\
	math_utilits/mathf.c\
	fill_queue.c\
	init_engine.c\
	move.c\
	keys_manager.c\
	manage_data.c\
	game_loop.c\

SRCDASH := hud.c $(filter-out main.c, $(SRC))
SRCARCH := archiver.c $(filter-out main.c, $(SRC))

OBJ := $(SRC:.c=.o)

SRCDIR := src
OBJDIR := obj

HEADERSP := $(addprefix includes/, $(HEADERS))
SRCP :=		$(addprefix $(SRCDIR)/, $(SRC))
OBJP :=		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
SRCPD :=	$(addprefix $(SRCDIR)/, $(SRCDASH))
OBJPD :=	$(addprefix $(OBJDIR)/, $(SRCDASH:.c=.o))
SRCAR :=	$(addprefix $(SRCDIR)/, $(SRCARCH))
OBJAR :=	$(addprefix $(OBJDIR)/, $(SRCARCH:.c=.o))
ONLYDIR :=	$(foreach dir, $(OBJP), $(shell dirname $(dir)))

FLAG :=  -g -Wall #-Werror -Wextra

PWD := $(shell pwd)
FRAMEWORKSDIR := $(PWD)/frameworks
INC := -I includes -I ./libft -I./frameworks/SDL2.framework/Headers/ -I./frameworks/SDL2_image.framework/Headers/ -I./frameworks/SDL2_ttf.framework/Headers/
SDL := -F $(FRAMEWORKSDIR) -framework SDL2 -framework SDL2_ttf -framework SDL2_image -framework SDL2_mixer -Wl -rpath $(FRAMEWORKSDIR)

TOTAL_FILES := $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell find $(PWD)/obj/ -type f 2> /dev/null | wc -l | sed -e 's/ //g')

all : $(NAME)

$(NAME) : $(OBJP)
			@gcc $(SDL) $(FLAG) $(OBJP) $(INC) $(LIB)  -L./libft -lft  -o $(NAME)
			@echo "$(CLEAR_LINE)$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Finished compilation. Output file : $(VIOLET_FONT)$(PWD)/$(NAME)$(RESET_FORM)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERSP)
			@mkdir -p $(ONLYDIR)
			@gcc -c $(FLAG)-F $(FRAMEWORKSDIR) $(INC) $< -o $@
			@echo "$(CLEAR_LINE)$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Compiling file [$(VIOLET_FONT)$<$(COL_YELLOW)]. ($(CURRENT_FILES) / $(TOTAL_FILES))$(RESET_FORM)$(BEGIN_LINE)"

dash : $(OBJPD)
			@gcc $(SDL) $(FLAG) $(OBJPD)  $(INC) $(LIB)  -L./libft -lft  -o $@
			@echo "$(CLEAR_LINE)$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Finished compilation. Output file : $(VIOLET_FONT)$(PWD)/$@$(RESET_FORM)"

arch : $(OBJAR)
			@gcc $(SDL) $(FLAG) $(OBJAR)  $(INC) $(LIB)  -L./libft -lft  -o $@
			@echo "$(CLEAR_LINE)$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Finished compilation. Output file : $(VIOLET_FONT)$(PWD)/$@$(RESET_FORM)"


clean :
			@rm -rf $(OBJDIR)
			@echo "$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Removed $(VIOLET_FONT)object files.$(RESET_FORM)"

fclean :	clean
			@rm -rf $(NAME)
			@echo "$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Removed $(VIOLET_FONT)$(NAME)$(RESET_FORM)"

re :		fclean all