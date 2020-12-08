#include "engine.h"
#include "utilits.h"

static t_xy	normi_sprite(t_xy where, t_player player)
{
	t_xy		sprite;

	sprite.x = where.x - player.where.x;
	sprite.y = where.y - player.where.y;
	return (sprite);
}

t_xy			rotate_sprite(t_xyz sprite, t_player player, SDL_Color color)
{
	t_xy	w;
	t_xy	wall;

	wall = normi_sprite((t_xy){sprite.x, sprite.y}, player);
	w = wall;
	wall.x = w.x * player.anglecos + w.y * player.anglesin;
	wall.y = -w.x * player.anglesin + w.y * player.anglecos;
	return (wall);
}

static t_xyz	vrotate2(t_xyz p, float vangle) //используется для обработки вертикального угла взгляда
{
	p.z = p.z + p.x * vangle;
	return (p);
}

t_xy			perspective_transform2(t_xy w, float z, float vangle,
							   int color)
{
	t_xy	wall;
	t_xyz	p0;
	t_xyz	p1;

	p0 = vrotate2((t_xyz){w.x, w.y, z}, vangle);
	wall.x = (int)((W >> 1) + p0.y / p0.x * (W >> 1));
	wall.y = (int)((H >> 1) + p0.z / p0.x * (H >> 1));

	return (wall);
}



void render_sprite(t_engine *engine)
{
    t_xyz sprite;
    t_xy res;
    t_xy res2;
    t_line ret;
    t_all temp;

    sprite = (t_xyz){3, 7, 0};
    t_xy line;

    temp.sdl = &(t_sdl){engine->window, engine->screen}; 

    line = rotate_sprite(sprite, engine->player, GREEN);
    res = perspective_transform2(line, 0, engine->player.vangle, 0x000000);
    res2 = perspective_transform2(line, 10, engine->player.vangle, 0x000000);
    ret = (t_line){res.x, res2.x, res.y, res2.y, 0x000000};
    // draw_line(&temp, &res, &res2, BLACK);
	printf("%f\n", engine->player.vangle);
	draw_fill_rect(&temp, (SDL_Rect){res.x, res.y, 10, 300}, GREEN);
}