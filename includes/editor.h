#ifndef EDITOR_H
# define EDITOR_H


//# include "../SDL/SDL.h"
//# include "../SDL/SDL_ttf.h"
# include <SDL2_ttf/SDL_ttf.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

# define MAP_WIDTH 11
# define MAP_HEIGHT 11
# define MAP_ELEMENTS 4
# define WIDTH 1920
# define HEIGHT 1080
# define FPS 200
# define PICT_HEIGHT 50
# define PICT_WIDTH 90
// # define OBJECTS (MAP_HEIGHT * MAP_WIDTH)
# define BUTTONS 6
# define FUNC_BUT 2
# define OBJ_SIDE 57
# define EYE_HEIGHT 6

# define GREY (SDL_Color){150, 150, 150, 255}
# define BLACK (SDL_Color){0, 0, 0, 255}
# define WHITE (SDL_Color){255, 255, 255, 255}
# define RED (SDL_Color){255, 0, 0, 255}
# define BLUE (SDL_Color){0, 0, 255, 255}
# define GREEN (SDL_Color){0, 255, 0, 255}
# define LAZUR (SDL_Color){54, 209, 183, 255}

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

typedef struct      s_sect
{
	float		floor;
	float		ceil;
	t_xy		*vertex;		//	Координаты всех вершин данного сектора, причем первая координаты дублируется в конце
	int		 *neighbors;		//	Номера всех соседей данного сектора
	unsigned	npoints; //	Количество соседей
			
}                   t_sect;


typedef struct      s_button
{
    SDL_Surface		*texture;
    SDL_Rect        dstrect;
	SDL_Color		color;
    int             state;
	char			*title;
}                   t_button;
/*
typedef struct      s_edit
{
    int             function;
	t_xyz			coord;
	t_sect			new_sector;
}                   t_edit;

typedef	struct	s_player
{
	t_xyz		where;			//	Current position
	t_xyz		velocity;
	SDL_Surface	*picture;
	int			picked;
	int			sect;
}				t_player;
*/
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


typedef struct      s_all
{
    t_player        player;// переменная игрока.
    // t_sect          *swap;//указатель на выбранный сектор
    t_sect          *sectors;//массив с данными о секторах
	t_sect			*temp;
    unsigned int    num_sectors;//количество секторов
	int 			step;//шаг (масштаб)
	int 			iso;
	SDL_Color		color;
	TTF_Font		*font;
	t_labels		labels[5];
	// float			angle;//угол поворота
	// t_xyz			rot;//
	t_xy			draw_floors;
	t_xy			set_floors;
	t_xyint			point;//координаты ближайшей точки курсора
    t_xyz			mouse;//координаты мыши на area
	t_xyz			mapsize;//размер карты в исходной СИ
	t_xy			min_coord;
	t_xy			max_coord;
    SDL_Rect        area;//область редактирования
    SDL_Surface     *texture;//текстура-подложка
	int				threed;

    t_button        buttons[BUTTONS];//кнопки
//    t_edit			edit;//
    t_sdl           *sdl;//
}                   t_all;

void	            init_all(t_all *all); // инициализируем модули
void                error_and_close(const char *file, const char *function); // аварийное завершение программы
void                on_event(t_all *all, SDL_Event *event); //обработка событий
void				map_click(t_xyz *mouse, t_all *all);
int					load_map(char *name, t_all *all); // загрузка карты
int                 load_texture(t_all *all);// звгрузка текстур
int					load_buttons(t_all *all, t_button *btn);
void                draw_all(t_all *all, t_sdl *sdl, t_button *btn);//отрисовка
int					write_map(char *name, t_all *all);
void				draw_player(t_all *all, t_sdl *sdl, t_player *player, t_xy *c);
void				draw_grid(t_all *all, SDL_Rect *area, int step);
void    			draw_texture(t_sdl *sdl, SDL_Rect area, SDL_Surface *txt);
void    			draw_fill_rect(t_all *all, SDL_Rect area, SDL_Color color);
void				draw_line(t_all *all, t_xyz *start, t_xyz *fin, SDL_Color color);
void				draw_circle(t_sdl *sdl, t_xy coord, int r, SDL_Color color);
void				draw_labels(t_all *all, t_labels *labels, int i);
void				draw_digits(t_sdl *sdl, t_all *all, int x, int y);
void				get_neighbours(t_sect *sector, t_all 	*all, int n);
SDL_Surface			*get_text_surface(t_all *all, char *name, SDL_Rect target, SDL_Color color);
void       			put_pxl(t_sdl *sdl, SDL_Color col, int x, int y);


# endif
