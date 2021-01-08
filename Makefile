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

NAME :=	doom-nukem

HEADERS := engine.h\
	utilits.h\
	events.h\


SRC := main.c\
	run_queue.c\
	init.c\
	lighting.c\
	transform_wall.c\
	cut_wall.c\
	manage_data.c\
	game_loop.c\
<<<<<<< HEAD
	pack.c\
	unpack.c
||||||| 7c04a9a
=======
	key_events/keys_manager.c\
	key_events/event_edit.c\
	key_events/event_movement.c\
	editor/real_time_edit.c\
	movement/move.c\
	movement/fall.c\
	utilits/math/determine_intersection.c\
    utilits/math/mathf.c\
    utilits/math/intersection_point.c\
    utilits/math/rotates.c\
    utilits/math/perspective_transform.c\
    utilits/swap.c\
    utilits/utilits.c\
    utilits/exit_options.c\
    utilits/load_img.c\
	render/minimap.c\
	render/render_hplane.c\
	render/render_sky.c\
	render/render_scene.c\
	render/ceil_and_floor_init.c\
	render/wall/perspective_init.c\
	render/wall/render_wall.c\
	render/wall/wall_tx_init.c\
	render/line/render_line.c\
	render/line/render_vline.c\
	render/line/render_hline.c\
>>>>>>> master

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