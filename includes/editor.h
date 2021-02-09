/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 06:30:07 by ecelsa            #+#    #+#             */
/*   Updated: 2021/02/09 03:05:38 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# ifdef __linux__
#  include "SDL2/SDL.h"
#  include "SDL2/SDL_ttf.h"
#  include "SDL2/SDL_image.h"
# elif __APPLE__
#  include <SDL2/SDL.h>
#  include <SDL2_ttf/SDL_ttf.h>
#  include <SDL2_image/SDL_image.h>
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define W 1200
# define H 700
# define FPS 200
# define PICT_HEIGHT 50
# define PICT_WIDTH 90
# define BUTTONS 18
# define FUNC_BUT 2
# define OBJ_SIDE 57
# define EYE_HEIGHT 6

# define GREY (SDL_Color){70, 70, 70, 255}
# define BLACK (SDL_Color){0, 0, 0, 255}
# define WHITE (SDL_Color){255, 255, 255, 255}
# define RED (SDL_Color){255, 0, 0, 255}
# define BLUE (SDL_Color){0, 0, 255, 255}
# define GREEN (SDL_Color){0, 255, 0, 255}
# define LAZUR (SDL_Color){54, 209, 183, 255}
# define YELLOW (SDL_Color){255, 255, 33, 255}
# define ORANGE (SDL_Color){255, 128, 0, 255}

# define NEW_SECT 0

# define FLOOR 0
# define CEIL 1
# define SHOW 2
# define FROM 3
# define TO 4
# define INVENTORY 5
# define SPEED 6
# define GRAVITY 7
# define AMMO 8

typedef struct		s_fline
{
	float			x0;
	float			x1;
	float			y0;
	float			y1;
	Uint32			color;
}					t_fline;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Surface		*screen;
}					t_sdl;

typedef struct		s_xyint
{
	int				x;
	int				y;
}					t_xyint;

typedef struct		s_xy
{
	float			x;
	float			y;
}					t_xy;

typedef struct		s_xyz
{
	float			x;
	float			y;
	float			z;
}					t_xyz;

typedef struct		s_graf
{
	int				g_num;
	float			*z;
	t_fline			*coord;
	int				*wall;
	int				*u;
}					t_graf;

typedef struct		s_sect
{
	float			floor;
	float			ceil;
	t_xy			*vertex;
	int				*neighbors;
	unsigned		npoints;
	int				door;
	float			oldf;
	int				txf;
	int				txc;
	int				txw0;
	int				txw1;
	t_graf			graf;
}					t_sect;

typedef struct		s_button
{
	SDL_Rect		dstrect;
	char			*title;
	SDL_Color		color;
	int				state;
	SDL_Surface		*texture;
}					t_button;

typedef struct		s_settings
{
	int				inventory;
	int				speed;
	int				gravity;
	int				ammo;
}					t_settings;

typedef	struct		s_player
{
	t_xyz			where;
	t_xyz			velocity;
	SDL_Surface		*picture;
	int				picked;
	float			angle;
	float			anglesin;
	float			anglecos;
	float			vangle;
	int				sector;
	int				wsad[4];
	int				falling;
	int				flying;
	int				ground;
	int				stand;
	float			eyeheight;
	float			speed;
	float			move_speed;
	int				deep_sh;
	SDL_Event		event;
	int				game_mode;
	t_settings		settings;
	int				cur_inv;
	int				cur_am;
	int				shot;
}					t_player;

typedef	struct		s_labels
{
	SDL_Surface		*surf;
	SDL_Rect		dst;
}					t_labels;

typedef struct		s_all
{
	t_player		player;
	int				swap_num;
	int				fin_sect;
	t_xy			delta;
	t_xy			d;
	t_sect			*sectors;
	t_sect			temp;
	int				num_sectors;
	int				step;
	TTF_Font		*font;
	t_labels		labels[9];
	t_xy			draw_floors;
	t_xy			set_floors;
	t_xyint			point;
	t_xyz			mouse;
	t_xyz			mapsize;
	t_xy			min_coord;
	t_xy			max_coord;
	SDL_Rect		area;
	SDL_Surface		*texture;
	int				threed;
	t_button		buttons[BUTTONS];
	t_sdl			sdl;
	char			*name;
	char			*src_dir;
	char			*src_map;
}					t_all;

void				init_all(t_all *all);
void				error_and_close(const char *file, const char *function);
void				on_event(t_all *all, SDL_Event *event);
void				map_click(t_all *all, SDL_MouseButtonEvent *event);
int					load_map(char *name, t_all *all);
int					load_texture(t_all *all);
int					load_buttons(t_button *btn);
int					check_sect_intersect(t_all *all, int num, t_xy one,
																	t_xy two);
void				check_vert(t_all *all, int *x, int *y, t_sect *temp);
void				draw_all(t_all *all, t_sdl *sdl, t_button *btn);
void				draw_digits(t_sdl *sdl, t_all *all, int x, int y);
void				draw_setting_digits(t_all *all, t_settings *settings);
int					write_map(t_all *all);
void				draw_temp(t_all *all, t_sdl *sdl, t_sect *temp, t_xy delta);
void				draw_player(t_all *all, t_sdl *sdl, t_player *player,
																	t_xy *c);
void				draw_map(t_sect *sect, t_all *all);
void				draw_grid(t_all *all, SDL_Rect *area, int step);
void				draw_texture(SDL_Surface *screen, SDL_Rect area,
															SDL_Surface *txt);
void				draw_fill_rect(t_all *all, SDL_Rect area, SDL_Color color);
void				draw_rect(t_all *all, SDL_Rect area, SDL_Color color,
																	int border);
void				draw_line(t_all *all, t_xy *start, t_xy *fin,
															SDL_Color color);
void				draw_label(t_all *all, char *name, SDL_Rect area,
															SDL_Color color);
void				draw_circle(t_sdl *sdl, t_xy coord, int r, SDL_Color color);
void				draw_ui(t_all *all, t_sdl *sdl, t_button *btn);
void				draw_sector(t_sect *sect, t_all *all, SDL_Color color,
																	t_xy delta);
void				processing(t_all *all);
int					is_vector_equal(t_xy a0, t_xy a1, t_xy b0, t_xy b1);
void				new_sector(t_all *all, t_sect *temp, int x, int y);
int					get_neighbours(t_sect *sector, t_all *all, int n);
float				point_side1(float px, float py, t_xy vert, t_xy vert1);
int					check_sector(t_sect *sect);
int					inside_sector(t_xyint point, t_sect *sector);
int					which_sector(t_all *all, t_sect *sectors, t_xyz where);
int					which_sector_p(t_all *all, t_sect *sectors, t_xyz where);
int					*which_sectors(t_all *all, t_sect *sectors, t_xyz where);
void				remove_sector(t_all *all, t_sect *sectors);
SDL_Surface			*get_text_surface(char *name, TTF_Font *font,
															SDL_Color color);
void				put_pxl(SDL_Surface *screen, SDL_Color col, int x, int y);
t_xy				get_coords(t_all *all);
void				init_floors(t_sect *sectors, int num);
void				normalize(t_sect *sectors, int num, t_all *all);
int					**get_vertexes(t_all *all);
int					get_order_num(t_xy coord, int **vert);
int					is_intersectred(t_xy v11, t_xy v12, t_xy v21, t_xy v22);
int					doors_close(t_all *all);
void				key_press(t_all *all);
int					print_message(t_all *all, SDL_Color color, char *text,
																	int delay);
void				new_map(char *name);
void				closest_point(t_all *all, t_xyint point);
void				write_sectors(t_all *all, int **vert, int fd);
int					mode_switch(t_all *all, int mode);
void				sector0(int fd);
void				sector1(int fd);
void				enders(int fd);

#endif
