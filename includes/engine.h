#ifndef ENGINE_H
# define ENGINE_H
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
<<<<<<< HEAD
# include <SDL.h>
//# include <SDL2_ttf/SDL_ttf.h>
// # include <SDL2_image/SDL_image.h>
||||||| 7c04a9a
# include <SDL2/SDL.h>
//# include <SDL2_ttf/SDL_ttf.h>
//# include <SDL2_image/SDL_image.h>
=======
# include <SDL2/SDL.h>
# include <SDL_image.h>
//# include <SDL2_image/SDL_image.h>
//# include <SDL2_ttf/SDL_ttf.h>
>>>>>>> master
//# include <SDL2_mixer/SDL_mixer.h>
/*
 * ЗАКОММЕНТИРУЙ, ЕСЛИ НЕ КОМПИЛИТСЯ! Временное решение
 */
/*# include <SDL.h>*/
# include <SDL_ttf.h> 
# include <SDL_image.h>
// # include <SDL_mixer.h>

<<<<<<< HEAD
//# define W 1920
//# define H 1080
# define W 400
# define H 600
# define CUR_SECT engine->player.sector

# define NEAR_Z 1e-4f				//TODO что это?
# define FAR_Z 5					//TODO что это?
# define NEAR_SIDE 1e-5f
# define FAR_SIDE 20.f
# define floor_diff 10
# define EyeHeight 6				//camera height
# define DuckHeight 2.5				//camera height when crouching
# define HeadMargin 1				//how much room above before the head hits the ceiling
# define KneeHeight 2				//how tall obj are those can be walked over without jumping
# define hfov (0.73f * H)			//horizontal FOV
# define vfov (.2f * H)				//vertical FOV
# define PLAYER engine.player
# define SECTORS engine.sectors
# define Yaw(y, z) (y + z * engine->player.yaw)		// calculate yaw angle between y and z values (поворот игрока)

typedef struct	q_queue_obj
{
	int			sectorno;	//номер сектора
	int			size_x1;		//
	int			size_x2;		//
}				t_queue_obj;

typedef struct	s_delta
||||||| 7c04a9a
//# define W 1920
//# define H 1080
# define W 1280
# define H 720
# define CUR_SECT engine->player.sector

# define NEAR_Z 1e-4f				//TODO что это?
# define FAR_Z 5					//TODO что это?
# define NEAR_SIDE 1e-5f
# define FAR_SIDE 20.f
# define floor_diff 10
# define EyeHeight 6				//camera height
# define DuckHeight 2.5				//camera height when crouching
# define HeadMargin 1				//how much room above before the head hits the ceiling
# define KneeHeight 2				//how tall obj are those can be walked over without jumping
# define hfov (0.73f * H)			//horizontal FOV
# define vfov (.2f * H)				//vertical FOV
# define PLAYER engine.player
# define SECTORS engine.sectors
# define Yaw(y, z) (y + z * engine->player.yaw)		// calculate yaw angle between y and z values (поворот игрока)

typedef struct	q_queue_obj
{
	int			sectorno;	//номер сектора
	int			size_x1;		//
	int			size_x2;		//
}				t_queue_obj;

typedef struct	s_delta
=======
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
>>>>>>> master
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

typedef struct	s_ixyz
{
	int 		x;
	int 		y;
	int 		z;
}				t_ixyz;

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
	int			deep_sh;		//	затенение
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
	int			hchange[4];			//	модификаторы высоты пола и потолка
	int 		mod_s;				//	этот сектор будет модифицирован											}
	int			mod_w;				//	эта стена будет модифицирована											 }текстуры
	int			mod_tx;				//	1 - пол, 2 - потолок, 3 - нижняя линия раздела, 4 - верхняя, 0 - стена	}
	int			txno;				//	эту текстуру назначим
	int			mod;				//	режим модификатора !не используется!
}				t_edit;

typedef struct	s_img
{
	SDL_Surface	*tx;
	char		name[15];
	int			n;
}				t_img;

typedef struct	s_temp
{
	int			txx;		//	текстура по Х
	int			z;			//	Глубина (для затенения)
	int			x;			//	текущий х
	int			x0;			//	начальный х
	int			x1;			//	конечный х
	int 		oy[4];		//	текущая точка в перспективе до обрезания по краям экрана (origin)
	int			y[4];		//	текущая точка в перспективе. 0 потолок, 1 пол, 2 потолок соседа и верхняя линия раздела, 3 пол соседа и нижняя линия раздела
	t_line		wall[4];	//	координаты стены в перспективе. 0 потолок, 1 пол, 2 потолок соседа и верхняя линия раздела, 3 пол соседа и нижняя линия раздела
	t_line		w;			//	координаты стены до обрезания по лучам видимости
	t_fline		l;			//	короткая запись engine->wall
}				t_temp;

typedef struct	s_temp2
{
	int			y_top;
	int			y_bot;
	float		z;			//высота
	int			txx;		//текстура по х
	int 		txy;		//текстура по у
	float		mapx;		//координаты пикселя на карте
	float		mapy;		//
	float		cosx;		//с учетом mapx (mapx вычисляется один раз на столбец)
	float		sinx;
	float		pcos;		//для игрока
	float		psin;
	SDL_Surface	*tx;
}				t_temp2;

typedef struct	s_vplane
{
	int 		minx;//минимальная координата X области
	int 		maxx;//максимальная координата X области
	int 		topy[W];//верхняя координата
	int 		boty[W];//нижняя координата
	float		z;
}				t_vplane;

typedef struct	s_engine
{
	SDL_Window	*window;
	SDL_Surface	*screen;
	t_minimap	minimap;
	t_edit		edit;
	t_line		borders;			//	границы отображения (установлены во всё окно)
	t_player	player;
<<<<<<< HEAD
	t_sector	*sectors;		//	считанная карта
	unsigned	num_sectors;	//	количество секторов в карте
	t_queue_obj		queue[32];
	t_queue_obj		*future;
	t_queue_obj		*present;
	unsigned	max_queue;
	unsigned	close_request;
	int 		tmp;
	int			w;				//размер окна
	int			h;				//размер окна
||||||| 7c04a9a
	t_sector	*sectors;		//	считанная карта
	unsigned	num_sectors;	//	количество секторов в карте
	t_queue_obj		queue[32];
	t_queue_obj		*future;
	t_queue_obj		*present;
	unsigned	max_queue;
	unsigned	close_request;
	int 		tmp;
=======
	t_sector	*sectors;			//	считанная карта
	int 		num_sectors;		//	количество секторов в карте
	t_queue		*queue;				//	очередь секторов
	t_queue		*future;			//	указатель заполнения
	t_queue		*present;			//	указатель считывания
	int 		max_queue;
	int 		close_request;
	t_fline		wall;				//	текущая стена со всеми преобразованиями
	t_fline		ow;					//	текущая стена без отрезания частей, не попавших в кадр
	int			tline[W];			//	верхняя линия раздела
	int			bline[W];			//	нижняя линия раздела
	int			yctop[W];			//	экранные y потолка
	int			ycbot[W];			//	экранные y потолка
	int			yftop[W];			//	экранные y пола
	int			yfbot[W];			//	экранные y пола
	t_vplane	vpfloor;			//	таблица для заполнения пола
	t_vplane	vpceil;				//	таблица для заполнения потолка
	int			u0;					//	начало и конец текстуры с учетом чати стены, которая не попала в кадр
	int			u1;					//
	t_temp		rend_wall;			//используется в rendel_Wall тобы обойти норму
	t_temp2		rend_plane;			//используется при рендеринге пола и потолка
	t_img		img[10];
>>>>>>> master
}				t_engine;


void			init_engine(t_engine *engine);
void			general_init(t_engine *engine);
void			load_data(t_engine *engine);
void			unload_data(t_engine *engine);
void			game_loop(t_engine *engine);
int 			transform_wall(t_engine *engine, int i);
void			render_scene(t_engine *engine, int sectorno, int neighbor);
void			ceil_and_floor_init(t_engine *engine);
void			render_wall(t_engine *engine, int neighbor, t_ixyz t);
t_line			get_op1(t_temp *a);
t_line			get_op2(t_temp *a);
t_line			get_op3(t_temp *a);
void			init_ceil_floor(t_engine *engine, t_sector sector, t_line *wall);
void			init_wall(t_engine *engine, t_sector sector, t_line *wall);
t_fline			cut_wall(t_fline wall, t_xy i1, t_xy i2);						//разрезает стену для попадания в fov
void			minimap(t_engine *engine, t_xy v0, t_xy v1, Uint32 color);			//рисуется отдельно для каждой стены
void			minimap_cut(t_engine *engine, t_xy v0, t_xy v1, Uint32 color);		//показывает только то, что в поле зрения
void			render_minimap_hud(t_minimap minimap, SDL_Surface *screen);		//рисуется один раз на кадр
void			run_queue(t_engine *engine);
int				check_repeat(t_engine *engine, int sectorno, int neighbor);
void			render_line(t_line p, SDL_Surface *screen, t_line borders);		//линия в пределах указанных границ
void			render_vline(t_engine *engine, t_line p, t_line op, int texture_n);			//вертикальная линия сверху вниз
void			render_hline(t_engine *engine, int y, int xbegin, int xend);
void			move(t_engine *engine);
void			fall(t_player *player, t_sector *sectors);
Uint32			deep_shading(t_engine *engine, t_line wall, int x);			//модификатор освещения в зависимости от дальности
Uint32			get_shadow(Uint32 z, Uint32 color);								//применить модификатор освещения
void			real_time_edit(t_engine *engine);
void			render_hplane(t_engine *engine, t_vplane *p, int txno);
void			render_sky(t_engine *engine);

#endif