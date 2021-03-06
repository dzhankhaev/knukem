UNAME_S := $(shell uname -s)

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
	editor.h\
	archiver.h


SRC := main.c\
	run_queue.c\
	init.c\
	init_engine.c\
	hud.c\
	hud_sub.c\
	lighting.c\
	transform_wall.c\
	cut_wall.c\
	game_loop.c\
	draw.c\
	new_map.c\
	new_map_sector.c\
	loader/manage_data.c\
	loader/load_sector.c\
	animations/do_door_anim.c\
	animations/start_door_anim.c\
	animations/check_door_anim.c\
	key_events/keys_manager.c\
	key_events/event_edit.c\
	key_events/event_movement.c\
	key_events/keyboard_event.c\
	editor/door_mod.c\
	editor/real_time_edit.c\
	editor/graf_mod.c\
	editor/delete_one_graf.c\
	editor/tx_mod.c\
	movement/move.c\
	movement/fall.c\
	utilits/math/determine_intersection.c\
    utilits/math/mathf.c\
    utilits/math/mathf2.c\
    utilits/math/intersection_point.c\
    utilits/math/rotates.c\
    utilits/math/perspective_transform.c\
    utilits/swap.c\
    utilits/utilits.c\
    utilits/exit_options.c\
    utilits/load_img.c\
    utilits/anim_delete.c\
    utilits/ispointincube.c\
	render/minimap.c\
	render/render_hplane.c\
	render/render_scene.c\
	render/render_cross.c\
	render/ceil_and_floor_init.c\
	render/graf_proccesing.c\
	render/wall/render_wall.c\
	render/wall/perspective_init.c\
	render/wall/wall_tx_init.c\
	render/line/render_line.c\
	render/line/render_vline.c\
	render/line/render_hline.c\
	map_editor/main.c\
	map_editor/draw/digits.c\
	map_editor/draw/draw_ui.c\
	map_editor/draw/draw_map.c\
	map_editor/draw/draw_map_obj.c\
	map_editor/draw/draw_all.c\
	map_editor/draw/drawing_utils.c\
	map_editor/errors.c\
	map_editor/events/events_all.c\
	map_editor/events/events_key.c\
	map_editor/events/events_map.c\
	map_editor/events/events_processing.c\
	map_editor/init.c\
	map_editor/texture.c\
	map_editor/texture2.c\
	map_editor/write/prewrite.c\
	map_editor/write/normalize.c\
	map_editor/write/write.c\
	map_editor/write/write_sectors.c\
	map_editor/pixels.c\
	map_editor/math.c\
	map_editor/sector/sector_check.c\
	map_editor/sector/sector_check_2.c\
	map_editor/sector/sector_remove.c\
	map_editor/sector/sector_neighbors.c\
	map_editor/sector/sector_add.c\
	map_editor/obj_detection.c\
	archiver/archiver.c\
	archiver/pack.c\
	archiver/unpack.c


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

ifeq ($(UNAME_S),Linux)
    SDL := -I SDL2/SDL.h -lSDL2 -lSDL2_ttf -lSDL2_image
endif
ifeq ($(UNAME_S),Darwin)
    SDL := -F $(FRAMEWORKSDIR) -framework SDL2 -framework SDL2_ttf -framework SDL2_image -framework SDL2_mixer -Wl -rpath $(FRAMEWORKSDIR)
endif

TOTAL_FILES := $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell find $(PWD)/obj/ -type f 2> /dev/null | wc -l | sed -e 's/ //g')

FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft -lm -l pthread

all : $(FT_LIB) $(NAME)

$(FT_LIB):
	@make -C $(FT)

$(NAME) : $(OBJP)
			@gcc $(FLAG) $(OBJP) $(FT_INC) $(FT_LNK) $(INC) $(SDL)  $(LIB) -o $(NAME)
			@echo "$(CLEAR_LINE)$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Finished compilation. Output file : $(VIOLET_FONT)$(PWD)/$(NAME)$(RESET_FORM)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERSP)
			@mkdir -p $(ONLYDIR)
			@gcc -c $(FLAG) $(FT_INC) -F $(FRAMEWORKSDIR)  $(INC) $< -o $@
			@echo "$(CLEAR_LINE)$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Compiling file [$(VIOLET_FONT)$<$(COL_YELLOW)]. ($(CURRENT_FILES) / $(TOTAL_FILES))$(RESET_FORM)$(BEGIN_LINE)"


clean :
			@rm -rf $(OBJDIR)
			@echo "$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Removed $(VIOLET_FONT)object files.$(RESET_FORM)"
			make -C $(FT) clean

fclean :	clean
			@rm -rf $(NAME)
			@echo "$(BLUE_FONT)[$(NAME)] $(YELLOW_FONT)Removed $(VIOLET_FONT)$(NAME)$(RESET_FORM)"
			make -C $(FT) fclean
re :		fclean all