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
// # define OBJECTS (MAP_HEIGHT * MAP_WIDTH)
# define BUTTONS 10
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

# define NEW_SECT 0
# define GUN 0
# define ENEMY 1
# define AID 2
# define BAZOOKA 3
# define PLAYER 4

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

}					t_sect;


typedef struct      s_button
{
    SDL_Surface		*texture;
    SDL_Rect        dstrect;
    SDL_Color		color;
    int             state;
    char			*title;
    t_xyz			*sprite_coords;
    int				num;
}                   t_button;

typedef	struct	s_player
{
    t_xyz		where;			//	текущая позиция
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
    float		eyeheight;		//	текущая высота камеры
    float		speed;			//	текущая максимальная скорость
    int			deep_sh;		//	затенение
    SDL_Event	event;
}				t_player;

typedef	struct s_labels
{
    SDL_Surface		*surf;
    SDL_Rect		dst;
}				t_labels;

typedef	struct	s_sprites
{
    t_button		buttons[5];
    // t_xyz			*enemies;
    // t_xyz			*aids;
    // t_xyz			*guns;
    // t_xyz			*bazookas;
    t_xyz			where_player;
    int				picked;
    t_xy			swap;
}				t_sprites;


typedef struct      s_all
{
    t_player        player;// переменная игрока.
    t_sect          *swap;//указатель на выбранный сектор
    int				on; // индикатор запуска редактора
    int				swap_num;
    t_xy			delta; // дельта области редактирования
    t_xy			d; // дельта сдвига карты
    t_sect          *sectors;//массив с данными о секторах
    t_sect			*temp;
    int				num_sectors;//количество секторов
    int 			step;//шаг (масштаб)
    int 			iso; //изометрия вкл/выкл
    SDL_Color		color;
    TTF_Font		*font;
    TTF_Font		*s_font;
    t_labels		labels[5];
    t_sprites		sprites;
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
    t_sdl           *sdl;//
}                   t_all;

void	            init_all(t_all *all); // инициализируем модули
void				add_sprite(t_all *all, int x, int y, int type);
void                error_and_close(const char *file, const char *function); // аварийное завершение программы
void                on_event(t_all *all, SDL_Event *event); //обработка событий
void				map_click(t_xyz *mouse, t_all *all, SDL_MouseButtonEvent *event);
int					load_map(char *name, t_all *all); // загрузка карты
int                 load_texture(t_all *all);// звгрузка текстур
int					load_buttons(t_all *all, t_button *btn);
void                draw_all(t_all *all, t_sdl *sdl, t_button *btn);//отрисовка
int					write_map(char *name, t_all *all);
void				draw_temp(t_all *all, t_sdl *sdl, t_sect *temp, t_xy delta);//несохраненный сектор
void				draw_map(t_sdl *sdl, t_sect *sect, t_all *all);
void				draw_sprite_picked(t_all *all, t_sdl *sdl, t_sprites *sprites, t_xy *c);
void				draw_grid(t_all *all, SDL_Rect *area, int step);
void    			draw_texture(t_sdl *sdl, SDL_Rect area, SDL_Surface *txt);
void    			draw_fill_rect(t_all *all, SDL_Rect area, SDL_Color color);
void				draw_rect(t_all *all, SDL_Rect area, SDL_Color color, int border);
void				draw_line(t_all *all, t_xy *start, t_xy *fin, SDL_Color color);
void				draw_circle(t_sdl *sdl, t_xy coord, int r, SDL_Color color);
void				draw_ui(t_all *all, t_sdl *sdl, t_button *btn);
void				draw_sprites(t_all *all, t_sprites *sprites);
void    			new_sector(t_all *all, int x, int y);
void				get_neighbours(t_sect *sector, t_all 	*all, int n);
float				point_side1(float px, float py, t_xy vert, t_xy vert1);
int					check_sector(t_sect *sect);
int					which_sector(t_all *all, t_sect *sectors, t_xyz where);
t_xy				which_sprite(t_all *all, t_sprites *sprites, t_xyz where);
void				remove_sector(t_all *all, t_sect *sectors);
SDL_Surface			*get_text_surface(t_all *all, char *name, TTF_Font *font, SDL_Color color);
void       			put_pxl(t_sdl *sdl, SDL_Color col, int x, int y);
void				sprite_remove(t_all *all, t_sprites *sprites, t_xy pos);
SDL_Surface			*get_texture2(char *file);
void				init_floors(t_sect *sectors, int num);
void				normalize(t_sect *sectors, int num, t_all *all);
int					**get_vertexes(t_all *all);
int					get_order_num(t_xy coord, int **vert);
int                 ispointincube(t_xyz point, t_xyz cubecenter, t_xyz borders, float centerzoffset);

# endif