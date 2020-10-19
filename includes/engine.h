#ifndef ENGINE_H
# define ENGINE_H
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <SDL.h>
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
	t_xyz		where;			//	Current position
	t_xyz		velocity;		//	Current motion vector
	float		angle;			//	Looking towards
	float		anglesin;		//	and sin()
	float		anglecos;		//	and cos()
	float		temp_yaw;		//TODO WTF
	float		yaw;			//	and player angle when looking up and down
	unsigned	sector;			//	текущий сектор
	int			wsad[4];		//	ключи передвижения. 1 - движение, 0 - его отсутстие
	float		move_vec[2];
	int			ground;
	int			falling;		//	1 - игрок падает, 0 - не падает. Так же используется при приседании
	int			moving;
	int			ducking;		//	приседание. 1 - есть, 0 - нет
	int			pushing;
	float		acceleration;
	float		eyeheight;
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
	t_queue_obj		queue[32];
	t_queue_obj		*future;
	t_queue_obj		*present;
	unsigned	max_queue;
	unsigned	close_request;
	int 		tmp;
	int			w;				//размер окна
	int			h;				//размер окна
}				t_engine;


int				init_engine(t_engine *engine);
void			load_data(t_engine *engine);
void			unload_data(t_engine *engine);
void			game_loop(t_engine *engine);
void			move_player(float dx, float dy, t_engine *engine);
void			keys_manager(t_engine *engine);
void			clean_up(t_engine *engine);
void			draw(t_engine *engine);

t_xy			rot_z(t_xy p, float angle);
void			minimap(t_engine *engine, t_xy v0, t_xy v1, int color);
void			fill_queue(t_engine *engine, unsigned s);
void			render_line(t_line p, SDL_Surface *screen, t_line borders);
void			angle_less_than_45_1(t_line p, SDL_Surface *screen, t_line borders);
void			angle_more_than_45_1(t_line p, SDL_Surface *screen, t_line borders);
void			angle_less_than_45_2(t_line p, SDL_Surface *screen, t_line borders);
void			angle_more_than_45_2(t_line p, SDL_Surface *screen, t_line borders);
float			point_side(float px, float py, t_xy vert, t_xy vert1);
t_xy			determine_intersection_point(float *arg);
int				determine_box_intersection(float *arg);
int				clamp(int a, int min, int max);
void			move(t_engine *engine);

#endif