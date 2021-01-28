/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:29:37 by ecelsa            #+#    #+#             */
/*   Updated: 2021/01/12 19:29:16 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# include <math.h>
# include "editor.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/stat.h>

# define MAX_QUEUE 64
//вычисленные заранее координаты конечной точки лучей видимости для фов 90. Подробнее в transform_wall.c
# define RAY_POINT_X 35.f			//	50.f * cosf(HFOV/2)
# define RAY_POINT_Y 35.f			//	50.f * sinf(HFOV/2)
# define K 1.f						//	Коэффицент уравнения прямой y = kx. Применяется к лучам видимости. Подробнее в transform_wall.c
# define FLOOR_DIFF 12				//	Отображать на миникарте секторы с разницой в высоте не более floor_diff
# define DEEP_SHADING 6.f			//	Модификатор затенения
# define WALL_COLOR 0xDDDDDD		//	Цвета по умолчанию
# define FLOOR_COLOR 0x4F3B0D
# define CEIL_COLOR 0x0D384F
# define EDGE_COLOR 0xFF4444		//	цвет портала
# define TOP_COLOR 0xDDDDDD			//	верхняя линия раздела
# define BOT_COLOR 0xAAAAAA			//	нижняя линия раздела
# define EYE_HEIGHT 6				//	высота камеры
# define DSIT_HEIGHT 2.5			//	изменение высоты камеры при приседе
# define DFALL_HEIGHT 5				//	изменение высоты камеры при ползании
# define HEAD_HEIGHT 1				//	прибавить к высоте игрока для проверки коллизии при перемещении под объект
# define KNEE_HEIGHT 2				//	высота объекта, которую можно перешагивать
# define ACCELERATION_PLUS 0.6f		//	ускорение. плюс при ускорении
# define ACCELERATION_MINUS 0.8f	//	ускорение. минус при торможении
# define MOVE_SPEED 0.1f			//	[0.1;**]
# define DFALL_SPEED -0.11f			//	изменение скорости при падении на живот
# define DSIT_SPEED -0.07f			//	изменение скорости при приседе
# define DSPRINT_SPEED 0.1f			//	изменение скорости при беге
# define VSPEED 0.5f				//	вертикальная начальная скорость
# define VACCEL 0.05f				//	вертикальное ускорение
# define CAMERA_DY -0.007f			//	чувствительность по оси Y
# define CAMERA_DX 0.01f			//	чувствительность по оси X
# define VLIMIT 2.5f				//	Граница вертикального поворота
# define WEAPON_SPRITE_NUM 1		//	Количество спрайтов оружия

typedef struct	s_hud
{
	SDL_Surface		*scr;
	SDL_Rect		rect;
	int				health;
	int				weapon;
	int				face;
	SDL_Surface		*hud;
	SDL_Surface		*arms;
	SDL_Surface		*pis[6];
	SDL_Surface		*num_h[11];
	SDL_Surface		*num_wp_g[10];
	SDL_Surface		*num_wp_y[10];
	SDL_Surface		*face_s[3];
}				t_hud;

typedef struct	s_inp_hud
{
	int				health;
	int				buttons;
	int				weapons;
	int				curr_weap;
	int				ammo[6];
	int				face;
	int				fire;
	int 			flag;
}				t_inp_hud;


typedef struct			s_queue
{
	int					sectorno;	//	номер сектора
	int					x0;			//	границы отображения этого сектора
	int					x1;			//	равны границам портала, из которого попали в этот сектор
	int					psec;		//	номер сектора, из которого пришли
}						t_queue;

typedef struct			s_delta		//	для алгоритма брезенхема
{
	int					dx;
	int					dy;
	int					error;
	int					derror;
}						t_delta;

typedef struct			s_line		//	стена для экранных координат
{
	int					x0;
	int					x1;
	int					y0;
	int					y1;
	Uint32				color;
}						t_line;

typedef struct			s_ixyz
{
	int 				x;
	int 				y;
	int 				z;
}						t_ixyz;

typedef struct			s_minimap
{
	t_xy				point;				//центр миникарты
	unsigned			scale;				//масштаб миникарты
	t_line				player_vertical;	//стрелка игрока
	t_line				player_horizontal;	//стрелка игрока
	t_line				borders;			//границы отображения миникарты
	int					mod;				//режим миникарты
}						t_minimap;

typedef struct			s_edit
{
	int					hchange[4];			//	модификаторы высоты пола и потолка
	int 				mod_s;				//	этот сектор будет модифицирован											}
	int					mod_w;				//	эта стена будет модифицирована											 }текстуры
	int					mod_tx;				//	0 - пол, 1 - потолок, 2 - стена, 3 - нижняя линия раздела, 4 - верхняя, }
	int					txno;				//	эту текстуру назначим
	int					graf;				//	0 ничего, 1 режим граффити, 2 поставить граффити, 3 удалить граффити
	int					graf_wall;
	int					door;				//	0 ничего, 1 назначить/удалить дверь, 2 закрыть, 3 открыть
	int					mod;				//
}						t_edit;

typedef struct			s_img
{
	SDL_Surface			*tx;
}						t_img;

typedef struct			s_temp
{
	int					txx;		//	текстура по Х
	int					z;			//	Глубина (для затенения)
	int					x;			//	текущий х
	int					x0;			//	начальный х
	int					x1;			//	конечный х
	int 				oy[6];		//	текущая точка в перспективе до обрезания по краям экрана (origin)
	int					y[8];		//	текущая точка в перспективе. 0 потолок, 1 пол, 2 потолок соседа и верхняя линия раздела, 3 пол соседа и нижняя линия раздела
	t_line				wall[8];	//	координаты стены в перспективе. 0 потолок, 1 пол, 2 потолок соседа и верхняя линия раздела, 3 пол соседа и нижняя линия раздела
	t_line				w;			//	координаты стены до обрезания по лучам видимости
	t_fline				l;			//	короткая запись engine->wall
}						t_temp;

typedef struct			s_temp2
{
	int					y_top;
	int					y_bot;
	float				z;			//высота
	int					txx;		//текстура по х
	int 				txy;		//текстура по у
	float				mapx;		//координаты пикселя на карте
	float				mapy;		//
	float				cosx;		//с учетом mapx (mapx вычисляется один раз на столбец)
	float				sinx;
	float				pcos;		//для игрока
	float				psin;
	SDL_Surface			*tx;
}						t_temp2;

typedef struct			s_vplane
{
	int					minx;//минимальная координата X области
	int					maxx;//максимальная координата X области
	int					topy[W];//верхняя координата
	int					boty[W];//нижняя координата
	float				z;
	int					s;		//сектор
}						t_vplane;

//структура для каждого врага
typedef struct			s_weapon_sprites
{
	int					visible; //TODO
	t_xyz				where; //текущая позиция
	t_xyz				translated_where;
	t_xyz				rotated_where;
	t_xyz				fin_transformed_where;
	int					sector; //текущий сектор
	//float 				angle;
	//int 				height;
	SDL_Surface			*texture; //массив текстур для этого спрайта
	SDL_Rect			dstrect;
	double 				dist;
	t_fline				cut_sprite_where;
	t_fline				cut_translated_where;
	t_fline				cut_rotated_where;
	t_fline				fov_cut_rotated_where;
	t_fline				cut_fin_transformed_where;
	double				width;
	double				height;
	//int 				*sprite[3];
}						t_weapon_sprites;

typedef struct			s_sprites1
{
	t_weapon_sprites	*weapon_sprite;
}						t_sprites1;

typedef struct			s_engine
{
	SDL_Window			*window;
	SDL_Surface			*screen;
	t_minimap			minimap;
	t_edit				edit;
	t_line				borders;			//	границы отображения (установлены во всё окно)
	t_player			player;
	t_sect				*sectors;				//	считанная карта
	int 				num_sectors;		//	количество секторов в карте
	t_queue				*queue;				//	очередь секторов
	t_queue				*future;			//	указатель заполнения
	t_queue				*present;			//	указатель считывания
	int 				max_queue;
	int 				close_request;
	t_fline				wall;				//	текущая стена со всеми преобразованиями
	t_fline				ow;					//	текущая стена без отрезания частей, не попавших в кадр
	int					tline[W];			//	верхняя линия раздела
	int					bline[W];			//	нижняя линия раздела
	int					danimbuf[30];		//	очередь анимаций дверей. Шаг = 2, первое значение сектор, второе вид анимации
	t_vplane			vpfloor;			//	таблица для заполнения пола
	t_vplane			vpceil;				//	таблица для заполнения потолка
	int					u0;					//	начало и конец текстуры с учетом части стены, которая не попала в кадр
	int					u1;					//
	t_temp				rend_wall;			//используется в rendel_Wall тобы обойти норму
	t_temp2				rend_plane;			//используется при рендеринге пола и потолка
	t_img				img[11];
	t_sprites1			*sprites1;
	t_hud				hud;
	t_inp_hud			hud_inp;				//для задачи параметров отрисовки HUD
}						t_engine;

void					init_engine(t_engine *engine, t_all *all);
void					general_init(t_engine *engine);
void					load_data(t_engine *engine, t_all *all);
void					unload_data(t_engine *engine);
void					game_loop(t_engine *engine, t_all *all);
int						transform_wall(t_engine *engine, t_fline *wall);
void					render_scene(t_engine *engine, int sectorno, int neighbor, int i);
void					ceil_and_floor_init(t_engine *engine);
void					render_wall(t_engine *engine, int neighbor, t_ixyz t);
t_line					get_op1(t_temp *a);
t_line					get_op2(t_temp *a);
t_line					get_op3(t_temp *a);
void					init_ceil_floor(t_engine *engine, t_sect sector, t_line *wall);
void					init_wall(t_engine *engine, t_sect sector, t_line *wall);
t_fline					cut_wall(t_fline wall, t_xy i1, t_xy i2);						//разрезает стену для попадания в fov
void					minimap(t_engine *engine, t_xy v0, t_xy v1, Uint32 color);			//рисуется отдельно для каждой стены
void					render_minimap_hud(t_minimap *minimap, SDL_Surface *screen);		//рисуется один раз на кадр
void					run_queue(t_engine *engine);
int						check_repeat(t_engine *engine, int sectorno, int neighbor);
void					render_line(t_line p, SDL_Surface *screen, t_line borders);		//линия в пределах указанных границ
void					render_vline(t_engine *engine, t_line p, t_line op, int texture_n);			//вертикальная линия сверху вниз
void					render_hline(t_engine *engine, int y, int xbegin, int xend);
void					move(t_engine *engine);
void					fall(t_player *player, t_sect *sectors);
Uint32					deep_shading(t_engine *engine, t_line wall, int x);			//модификатор освещения в зависимости от дальности
Uint32					get_shadow(Uint32 z, Uint32 color);								//применить модификатор освещения
void					real_time_edit(t_engine *engine);
void					render_cross(t_engine *engine);
void					render_hplane(t_engine *engine, t_vplane *p, int txno);
int						main_editor(t_engine *engine, t_all *all);
void					graf_proccesing(t_engine *engine, int sectorno, int i);
void					graf_mod(t_engine *engine, int sectorno, int i);
void					delete_one_graf(t_engine *engine, int sectorno);
t_ixyz					tx_wall_mod(t_engine *engine, int sectorno, int i);
t_ixyz					tx_plane_mod(t_engine *engine, int sectorno);
void					door_mod(t_engine *engine, int neighbor, int i);
void					door_anim(t_engine *engine);
void					start_door_anim(t_engine *engine, int sec, int nei, 
	unsigned int i);
// void					put_hud(SDL_Surface *scr, t_inp_hud *inp);
void					put_hud(t_engine *engine);
void					load_surfaces(const char *dirs, t_hud *hud_);
int						check_door_anim(t_engine *engine, int door);
void					keyboard_event(t_engine *engine, t_player *player,
					t_edit *edit);

#endif
