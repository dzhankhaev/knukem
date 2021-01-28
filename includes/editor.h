/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 06:30:07 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/07 22:28:14 by ecelsa           ###   ########.fr       */
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

typedef struct			s_fline
{
	float				x0;
	float				x1;
	float				y0;
	float				y1;
	Uint32				color;
}						t_fline;

typedef struct	    s_sdl
{
    SDL_Window	    *window;
    SDL_Surface		*screen;
}				    t_sdl;

typedef struct      s_xyint
{
    int           x;
    int           y;
}                   t_xyint;

typedef struct      s_xy
{
    float           x;
    float           y;
}                   t_xy;

typedef struct	s_xyz
{
    float		x;
    float		y;
    float		z;
}				t_xyz;

typedef struct			s_graf
{
	int					g_num;		//	количество граффити в секторе
	float				*z;			//	высота
	t_fline				*coord;		//	вектор
	int					*wall;		//	номер стены сектора
}						t_graf;

typedef struct		s_sect
{
    float			floor;
    float			ceil;
    t_xy			*vertex;		//	Координаты всех вершин данного сектора, причем первая координаты дублируется в конце
    int				*neighbors;		//	Номера всех соседей данного сектора
    unsigned		npoints;		//	Количество соседей
    int				door;			//	-1 не является дверью. Остальное показывает насколько дверь закрыта
    float			oldf;			//	уровень пола, если сектор является дверью
    int				txf;
    int				txc;
    int				txw0;
    int				txw1;
    t_graf			graf;

}					t_sect;


typedef struct      s_button
{
    
    SDL_Rect        dstrect;
    char			*title;
    SDL_Color		color;
    int             state;
    SDL_Surface		*texture;
}                   t_button;

typedef struct  s_settings
{
    int         inventory;
    int         speed;
    int         gravity;
    int         ammo;
}               t_settings;


typedef	struct	s_player
{
    t_xyz		where;
    t_xyz		velocity;		//	вектор скорости движения
    SDL_Surface	*picture;
    int			picked;
    float		angle;			//	угол поворота
    float		anglesin;		//	синус угла поворота
    float		anglecos;		//	косинус угла поворота
    float		vangle;			//	угол вертикального поворота
    int 		sector;			//	текущий сектор
    int			wsad[4];		//	ключи передвижения. 1 - движение, 0 - его отсутстие
    int			falling;		//	1 - игрок падает, 0 - не падает. Игрок может падать вверх. Если 1, будет применено ускорение
    int			flying;			//	флаг = 1 только если игрок летит вверх или вниз. ФЛАГ НЕ ОПРЕДЕЛЯЕТ НАХОДИТСЯ ИГРОК В РЕЖИМЕ ПОЛЕТА ИЛИ НЕТ
    int			ground;			//	грок стоит на земле
    int			stand;
    float		eyeheight;		//	текущая высота камеры
    float		speed;			//	текущая максимальная скорость
    float		move_speed;		//	Максимальная скорость
    int			deep_sh;		//	затенение
    SDL_Event	event;
    int			game_mode;		//	1 создатель, 0 игрок
    t_settings  settings;
    int			cur_inv;		//	Сколько мест в инвентаре занято
    int			cur_am;			//	Сколько патронов имеется
    int			shot;			//	0 ничего, 1 выстрел
}				t_player;

typedef	struct s_labels
{
    SDL_Surface		*surf;
    SDL_Rect		dst;
}				t_labels;

typedef struct      s_all
{
    t_player        player;// переменная игрока.
    int				swap_num;
    int             fin_sect;
    t_xy			delta; // дельта области редактирования
    t_xy			d; // дельта сдвига карты
    t_sect          *sectors;//массив с данными о секторах
    t_sect			*temp;
    int				num_sectors;//количество секторов
    int 			step;//шаг (масштаб)
    TTF_Font		*font;
    t_labels		labels[9];
    t_xy			draw_floors;//уровни отрисовки этажей
    t_xy			set_floors;//установка высоты нового сектора
    t_xyint			point;//координаты ближайшей точки курсора
    t_xyz			mouse;//координаты мыши
    t_xyz			mapsize;//размер карты в исходной СИ
    t_xy			min_coord;
    t_xy			max_coord;
    SDL_Rect        area;//область редактирования
    SDL_Surface     *texture;//текстура-подложка
    int				threed;
    t_button        buttons[BUTTONS];//кнопки
    t_sdl           sdl;//
    char			*name;
}                   t_all;

void	            init_all(t_all *all); // инициализируем модули
void                error_and_close(const char *file, const char *function); // аварийное завершение программы
void                on_event(t_all *all, SDL_Event *event); //обработка событий
void				map_click(t_all *all, SDL_MouseButtonEvent *event);
int					load_map(char *name, t_all *all); // загрузка карты
int                 load_texture(t_all *all);// звгрузка текстур
int					load_buttons(t_button *btn);
void                draw_all(t_all *all, t_sdl *sdl, t_button *btn);//отрисовка
int					write_map(t_all *all);
void				draw_temp(t_all *all, t_sdl *sdl, t_sect *temp, t_xy delta);//несохраненный сектор
void                draw_player(t_all *all, t_sdl *sdl, t_player *player, t_xy *c);
void				draw_map(t_sect *sect, t_all *all);
void				draw_grid(t_all *all, SDL_Rect *area, int step);
void    			draw_texture(SDL_Surface *screen, SDL_Rect area, SDL_Surface *txt);
void    			draw_fill_rect(t_all *all, SDL_Rect area, SDL_Color color);
void				draw_rect(t_all *all, SDL_Rect area, SDL_Color color, int border);
void				draw_line(t_all *all, t_xy *start, t_xy *fin, SDL_Color color);
void				draw_circle(t_sdl *sdl, t_xy coord, int r, SDL_Color color);
void				draw_ui(t_all *all, t_sdl *sdl, t_button *btn);
void    			new_sector(t_all *all, t_sect *temp, int x, int y);
int                 get_neighbours(t_sect *sector, t_all 	*all, int n);
float				point_side1(float px, float py, t_xy vert, t_xy vert1);
int					check_sector(t_sect *sect);
int                 inside_sector(t_xyint point, t_sect *sector);
int					which_sector(t_all *all, t_sect *sectors, t_xyz where);
int                 *which_sectors(t_all *all, t_sect *sectors, t_xyz where);
void				remove_sector(t_all *all, t_sect *sectors);
SDL_Surface			*get_text_surface(char *name, TTF_Font *font, SDL_Color color);
void       			put_pxl(SDL_Surface *screen, SDL_Color col, int x, int y);
SDL_Surface			*get_texture2(char *file);
void				init_floors(t_sect *sectors, int num);
void				normalize(t_sect *sectors, int num, t_all *all);
int					**get_vertexes(t_all *all);
int					get_order_num(t_xy coord, int **vert);
int                 is_intersectred(t_xy v11, t_xy v12, t_xy v21, t_xy v22);
int                 ispointincube(t_xyz point, t_xyz cubecenter, t_xyz borders, float centerzoffset);
int                 print_message(t_all *all, SDL_Color color, char *text, int delay);
void				new_map(char *name);

# endif