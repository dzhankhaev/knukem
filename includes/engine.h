#ifndef ENGINE_H
# define ENGINE_H
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <SDL2/SDL.h>
# include <SDL2_image/SDL_image.h>
//# include <SDL2_ttf/SDL_ttf.h>
//# include <SDL2_mixer/SDL_mixer.h>
/*
 * ЗАКОММЕНТИРУЙ, ЕСЛИ НЕ КОМПИЛИТСЯ! Временное решение
 */
/*# include <SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include <SDL_mixer.h>*/

# define W 1920
# define H 1080
# define MAX_QUEUE 64				//	максимальная длина очереди секторов
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
# define MOVE_SPEED 0.2f			//	[0.1;**]
# define DFALL_SPEED -0.11f			//	изменение скорости при падении на живот
# define DSIT_SPEED -0.07f			//	изменение скорости при приседе
# define DSPRINT_SPEED 0.1f			//	изменение скорости при беге
# define VSPEED 0.5f				//	вертикальная начальная скорость
# define VACCEL 0.05f				//	вертикальное ускорение
# define CAMERA_DY -0.007f			//	чувствительность по оси Y
# define CAMERA_DX 0.01f			//	чувствительность по оси X
# define VLIMIT 2.5f				//	Граница вертикального поворота

typedef struct	q_queue
{
	int			sectorno;	//	номер сектора
	int			x0;			//	границы отображения этого сектора
	int			x1;			//	равны границам портала, из которого попали в этот сектор
	int			psec;		//	номер сектора, из которого пришли
}				t_queue;

typedef struct	s_delta		//	для алгоритма брезенхема
{
	int			dx;
	int			dy;
	int			error;
	int			derror;
}				t_delta;

typedef struct	s_line		//	стена для экранных координат
{
	int			x0;
	int			x1;
	int			y0;
	int			y1;
	Uint32		color;
}				t_line;

typedef struct	s_fline		//	стена для вычислений
{
	float		x0;
	float		x1;
	float		y0;
	float		y1;
	Uint32		color;
}				t_fline;

typedef struct	s_xy
{
	float		x;
	float		y;
}				t_xy;

typedef struct	s_xyz
{
	float		x;
	float		y;
	float		z;
}				t_xyz;

typedef struct	s_sector
{
	float		floor;
	float		ceil;
	t_xy		*vertex;		//	Координаты всех вершин данного сектора, причем первая координата дублируется в конце
	int 		*neighbors;		//	Номера всех соседей данного сектора, им соответствуют вершины i, i+1
	int 		npoints;		//	Количество соседей
}				t_sector;

typedef	struct	s_player
{
	t_xyz		where;			//	текущая позиция
	t_xyz		velocity;		//	вектор скорости движения
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
	SDL_Event	event;
}				t_player;

typedef struct	s_minimap
{
	t_xy		point;				//центр миникарты
	unsigned	scale;				//масштаб миникарты
	t_line		player_vertical;	//стрелка игрока
	t_line		player_horizontal;	//стрелка игрока
	t_line		borders;			//границы отображения миникарты
	int			mod;				//режим миникарты
}				t_minimap;

typedef struct	s_edit
{
	int			hchange[4];			//	модификаторы
	int 		mod_s;				//	 этот сектор будет модифицирован
	int			mod;				//	режим модификатора !не используется!
}				t_edit;

typedef struct	s_img
{
	SDL_Surface	*tx;
	char		name[15];
}				t_img;

typedef struct	s_engine
{
	SDL_Window	*window;
	SDL_Surface	*screen;
	t_minimap	minimap;
	t_edit		edit;
	t_line		borders;			//	границы отображения (установлены во всё окно)
	t_player	player;
	t_sector	*sectors;			//	считанная карта
	int 		num_sectors;		//	количество секторов в карте
	t_queue		*queue;				//	очередь секторов
	t_queue		*future;			//	указатель заполнения
	t_queue		*present;			//	указатель считывания
	int 		max_queue;
	int 		close_request;
	t_fline		wall;
	t_fline		w;
	int			tline[W];
	int			bline[W];
	t_img		img[1];
}				t_engine;


void			init_engine(t_engine *engine);
void			general_init(t_engine *engine);
void			load_data(t_engine *engine);
void			unload_data(t_engine *engine);
void			game_loop(t_engine *engine);
int 			transform_wall(t_engine *engine, int i);
void			render_wall(t_engine *engine, int sectorno, int neighbor);
t_fline			cut_wall(t_fline wall, t_xy i1, t_xy i2);						//разрезает стену для попадания в fov
void			minimap(t_engine *engine, t_xy v0, t_xy v1, Uint32 color);			//рисуется отдельно для каждой стены
void			minimap_cut(t_engine *engine, t_xy v0, t_xy v1, Uint32 color);		//показывает только то, что в поле зрения
void			render_minimap_hud(t_minimap minimap, SDL_Surface *screen);		//рисуется один раз на кадр
void			run_queue(t_engine *engine);
int				check_repeat(t_engine *engine, int sectorno, int neighbor);
void			render_line(t_line p, SDL_Surface *screen, t_line borders);		//линия в пределах указанных границ
void			render_vline(SDL_Surface *screen, t_line p);			//вертикальная линия сверху вниз
void			move(t_engine *engine);
void			fall(t_player *player, t_sector *sectors);
Uint32			deep_shading(t_engine *engine, t_line wall, int x);			//модификатор освещения в зависимости от дальности
Uint32			get_shadow(Uint32 z, Uint32 color);								//применить модификатор освещения
void			real_time_edit(t_engine *engine);

#endif