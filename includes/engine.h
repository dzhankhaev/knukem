#ifndef ENGINE_H
# define ENGINE_H
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
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

# define W 1800
# define H 950
# define CUR_SECT engine->player.sector //текущий сектор
# define MAX_QUEUE 32					//максимальная длина очереди секторов
# define HFOV 1.2211f				//горизонтальный фов в радианах (70)
//вычисленные заранее координаты конечной точки луча видимости. Подробнее в transform_wall.c
# define RAY_POINT_X 40.968075f			//50.f * cosf(HFOV/2)
# define RAY_POINT_Y 28.663858f			//50.f * sinf(HFOV/2)
# define K 0.7f						//Коэффицент уравнения прямой y = kx. Применяется к лучам видимости. Подробнее в transform_wall.c
# define floor_diff 10				//Отображать на миникарте секторы с разницой в высоте не более floor_diff
# define EyeHeight 6				//высота камеры
# define DuckHeight 2.5				//высота камеры при приседе
# define HeadMargin 1				//how much room above before the head hits the ceiling
# define KneeHeight 2				//how tall obj are those can be walked over without jumping
# define acceleration_plus 0.6f		//множитель ускорения (увеличит)
# define acceleration_minus 0.8f	//множитель ускорения (уменьшит)

typedef struct	q_queue
{
	int			sectorno;	//номер сектора
	int			size_x1;		//
	int			size_x2;		//
}				t_queue;

typedef struct	s_delta
{
	int			dx;
	int			dy;
	int			error;
	int			derror;
}				t_delta;

typedef struct	s_line
{
	int			x0;
	int			x1;
	int			y0;
	int			y1;
	int			color;
}				t_line;

typedef struct	s_fline
{
	float			x0;
	float			x1;
	float			y0;
	float			y1;
	int			color;
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
	int 		*neighbors;		//	Номера всех соседей данного сектора
	unsigned	npoints;		//	Количество соседей
}				t_sector;

typedef	struct	s_player
{
	t_xyz		where;			//	текущая позиция
	t_xyz		velocity;		//	вектор движения
	float		angle;			//	угол поворота
	float		anglesin;		//	синус угла поворота
	float		anglecos;		//	косинус угла поворота
	float		temp_yaw;		//TODO WTF
	float		yaw;			//	and player angle when looking up and down
	unsigned	sector;			//	текущий сектор
	int			wsad[4];		//	ключи передвижения. 1 - движение, 0 - его отсутстие
	float		move_vec[2];
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
}				t_minimap;

typedef struct	s_engine
{
	SDL_Window	*window;
	SDL_Surface	*screen;
	t_minimap	minimap;
	t_line		borders;			//границы отображения (установлены во всё окно)
	t_player	player;
	t_sector	*sectors;		//	считанная карта
	unsigned	num_sectors;	//	количество секторов в карте
	t_queue		queue[MAX_QUEUE];
	t_queue		*future;
	t_queue		*present;
	unsigned	max_queue;
	unsigned	close_request;
	t_fline		wall;
}				t_engine;


int				init_engine(t_engine *engine);
void			load_data(t_engine *engine);
void			unload_data(t_engine *engine);
void			game_loop(t_engine *engine);
void			move_player(float dx, float dy, t_engine *engine);
void			keys_manager(t_engine *engine);
void			clean_up(t_engine *engine);
void			draw(t_engine *engine);
void			transform_wall(t_engine *engine, int i);						//
t_fline			cut_wall(t_fline wall, t_xy i1, t_xy i2);						//разрезает стену для попадания в fov
void			minimap(t_engine *engine, t_xy v0, t_xy v1, int color);			//рисуется отдельно для каждой стены
void			minimap_cut(t_engine *engine, t_xy v0, t_xy v1, int color);		//показывает только то, что в поле зрения
void			render_minimap_hud(t_minimap minimap, SDL_Surface *screen);		//рисуется один раз на кадр
void			run_queue(t_engine *engine);
void			render_line(t_line p, SDL_Surface *screen, t_line borders);
void			angle_less_than_45_1(t_line p, SDL_Surface *screen, t_line borders);
void			angle_more_than_45_1(t_line p, SDL_Surface *screen, t_line borders);
void			angle_less_than_45_2(t_line p, SDL_Surface *screen, t_line borders);
void			angle_more_than_45_2(t_line p, SDL_Surface *screen, t_line borders);
void			move(t_engine *engine);

#endif