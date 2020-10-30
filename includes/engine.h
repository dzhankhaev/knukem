#ifndef ENGINE_H
# define ENGINE_H
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <SDL2/SDL.h>
//# include <SDL2_ttf/SDL_ttf.h>
//# include <SDL2_image/SDL_image.h>
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
# define FLOOR_DIFF 20				//	Отображать на миникарте секторы с разницой в высоте не более floor_diff
# define WALL_COLOR 0xDDDDDD		//	Цвета по умолчанию
# define FLOOR_COLOR 0x4F3B0D
# define CEIL_COLOR 0x0D384F
# define EDGE_COLOR 0xFF4444		//	цвет портала
# define TOP_COLOR 0xDDDDDD			//	верхняя линия раздела
# define BOT_COLOR 0xAAAAAA			//	нижняя линия раздела
# define EYE_HEIGHT 6				//	высота камеры
# define SIT_HEIGHT 2.5				//	изменение высоты камеры при приседе
# define FALL_HEIGHT 5				//	изменение высоты камеры при ползании
# define HEAD_HEIGHT 1				//	прибавить к высоте игрока для проверки коллизии при перемещении под объект
# define KNEE_HEIGHT 2				//	высота объекта, которую можно перешагивать
# define ACCELERATION_PLUS 0.6f		//	множитель ускорения (увеличит)
# define ACCELERATION_MINUS 0.8f	//	множитель ускорения (уменьшит)
# define MAX_SPEED 0.2f				//	[0.1;**]
# define VSPEED 0.5f				//	вертикальная начальная скорость

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
	unsigned	color;
}				t_line;

typedef struct	s_fline		//	стена для вычислений
{
	float		x0;
	float		x1;
	float		y0;
	float		y1;
	unsigned	color;
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
	t_xyz		velocity;		//	вектор движения
	float		angle;			//	угол поворота
	float		anglesin;		//	синус угла поворота
	float		anglecos;		//	косинус угла поворота
	float		vangle;			//	угол вертикального поворота
	int 		sector;			//	текущий сектор
	int			wsad[4];		//	ключи передвижения. 1 - движение, 0 - его отсутстие
	int			cntrl;			//	присед
	int			ground;
	int			falling;		//	1 - игрок падает, 0 - не падает. Так же используется при приседании
	int			ducking;		//	приседание. 1 - есть, 0 - нет
	int			pushing;		//	приложена ли сила к игроку
	float		acceleration;	//	текущее ускорение игрока
	float		eyeheight;		//	текущая высота камеры
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

typedef struct	s_engine
{
	SDL_Window	*window;
	SDL_Surface	*screen;
	t_minimap	minimap;
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
	int			tline[W];
	int			bline[W];
}				t_engine;


int				init_engine(t_engine *engine);
void			load_data(t_engine *engine);
void			unload_data(t_engine *engine);
void			game_loop(t_engine *engine);
void			keys_manager(t_engine *engine);
void			clean_up(t_engine *engine);
void			draw(t_engine *engine);
int 			transform_wall(t_engine *engine, int i);
void			render_wall(t_engine *engine, int sectorno, int neighbor);
t_fline			cut_wall(t_fline wall, t_xy i1, t_xy i2);						//разрезает стену для попадания в fov
void			minimap(t_engine *engine, t_xy v0, t_xy v1, int color);			//рисуется отдельно для каждой стены
void			minimap_cut(t_engine *engine, t_xy v0, t_xy v1, int color);		//показывает только то, что в поле зрения
void			render_minimap_hud(t_minimap minimap, SDL_Surface *screen);		//рисуется один раз на кадр
void			run_queue(t_engine *engine);
int				check_repeat(t_engine *engine, int sectorno, int neighbor);
void			render_line(t_line p, SDL_Surface *screen, t_line borders);		//линия в пределах указанных границ
void			render_vline(t_line p, SDL_Surface *screen);					//вертикальная линия сверху вниз
void			move(t_engine *engine);
void			fall(t_player *player, t_sector *sectors);
int				color_distance(t_engine *engine, t_line wall, int x);			//модификатор освещения в зависимости от дальности
unsigned		get_shadow(int z, unsigned color);								//применить модификатор освещения

#endif