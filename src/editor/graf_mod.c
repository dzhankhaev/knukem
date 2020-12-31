#include "engine.h"
#include "utilits.h"

void			graf_memalloc(t_engine *engine, int sectorno, int i)
{
	t_graf *graf;

	graf = &engine->graf[sectorno];
	graf->g_num++;
	//выделяем память
	graf->wall = (int *)realloc(graf->wall, sizeof(int) * graf->g_num);
	graf->z = (float *)realloc(graf->z, sizeof(float) * graf->g_num);
	graf->coord = (t_fline *)realloc(graf->coord, sizeof(t_fline)
												  * graf->g_num);
	graf->txno = (int *)realloc(graf->txno, sizeof(int) * graf->g_num);
	//заносим необходимые данные
	graf->sectorno = sectorno;
	graf->txno[graf->g_num - 1] = engine->edit.txno == -1 ? 1 : engine->edit.txno;
	graf->wall[graf->g_num - 1] = i;
	graf->z[graf->g_num - 1] = engine->player.where.z;
	graf->coord[graf->g_num - 1] =
			(t_fline){engine->sectors[sectorno].vertex[i].x,
					  engine->sectors[sectorno].vertex[i + 1].x,
					  engine->sectors[sectorno].vertex[i].y,
					  engine->sectors[sectorno].vertex[i + 1].y,
					  graf->txno[graf->g_num - 1]};
}

void			create_coord(t_engine *engine, int sectorno)
{
	t_graf	*graf;
	float	angle;
	t_xy	a;
	t_xy	b;

	graf = &engine->graf[sectorno];
	//проекция
	a = point_proection(graf->coord[graf->g_num - 1],
						(t_xyz){engine->player.where.x,
								engine->player.where.y, 0});
	angle = get_vec_angle(graf->coord[graf->g_num - 1].x1
						  - graf->coord[graf->g_num - 1].x0,
						  graf->coord[graf->g_num - 1].y1
						  - graf->coord[graf->g_num - 1].y0,1,0);
	//прокладывание отрезка вдоль стены
	a.x -= engine->player.where.x;
	a.y -= engine->player.where.y;
	b.x = a.x + 1 * cosf(angle);
	b.y = a.y + 1 * sinf(angle);
	a.x += engine->player.where.x;
	a.y += engine->player.where.y;
	b.x += engine->player.where.x;
	b.y += engine->player.where.y;
	graf->coord[graf->g_num - 1] = (t_fline){a.x, b.x, a.y, b.y,
									graf->coord[graf->g_num - 1].color};
}

void			graf_mod(t_engine *engine, int sectorno, int i)
{
	if (engine->edit.mod_w != -1 && engine->edit.graf == 2)
	{
		engine->edit.graf = 0;
		if (engine->sectors[sectorno].neighbors[i] <= -1)
		{
			graf_memalloc(engine, sectorno, i);
			create_coord(engine, sectorno);
		}
	}
	if (engine->edit.graf == 3)
	{
		free(engine->graf[sectorno].coord);
		free(engine->graf[sectorno].z);
		free(engine->graf[sectorno].wall);
		free(engine->graf[sectorno].txno);
		engine->graf[sectorno].coord = 0;
		engine->graf[sectorno].z = 0;
		engine->graf[sectorno].wall = 0;
		engine->graf[sectorno].txno = 0;
		engine->graf[sectorno].sectorno = -1;
		engine->graf[sectorno].g_num = 0;
		engine->edit.graf = 0;
	}
}