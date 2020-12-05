#include "editor.h"

void	draw_sprite_picked(t_all *all, t_sdl *sdl, t_sprites *sprites, t_xy *c)
{
	SDL_Rect loc;

	// if (sp.picked == 0)
	// 	loc = (SDL_Rect){(player->where.x * all->step) + all->delta.x - all->step/2,
	// 	 (player->where.y * all->step) + all->delta.y - all->step/2,
	//  		 all->step, all->step};
	if (sprites->picked != -1)
    {
		loc = (SDL_Rect){all->point.x * all->step + c->x - all->step/2 + all->area.x,
			 all->point.y * all->step + c->y - all->step/2 + all->area.y, all->step, all->step};
	    draw_texture(sdl, loc, sprites->buttons[sprites->picked].texture);
    }
}

void    draw_sprite(t_all *all, SDL_Surface *texture, t_xyz *coords, int num)
{
    SDL_Rect loc;
    int i;

    i = 0;
    while(i < num)
    {
        loc = (SDL_Rect){(coords[i].x * all->step) + all->delta.x - all->step/2,
            (coords[i].y * all->step) + all->delta.y - all->step/2,
                all->step, all->step};
        if(all->sectors[(int)coords[i].z].floor >= all->draw_floors.x)
            draw_texture(all->sdl, loc, texture);
        i++;
    }
}

void    draw_sprites(t_all *all, t_sprites *sprites)
{
    draw_sprite(all, sprites->buttons[0].texture, sprites->aids, sprites->num_aids);
    draw_sprite(all, sprites->buttons[1].texture, sprites->guns, sprites->num_aids);
    draw_sprite(all, sprites->buttons[2].texture, sprites->enemies, sprites->num_aids);
    draw_sprite(all, sprites->buttons[3].texture, sprites->bazookas, sprites->num_aids);
    draw_sprite(all, sprites->buttons[4].texture, &sprites->where_player, 1);
}

void    add_sprite(t_all *all, int x, int y, int num)
{
    t_xyz   *coords;

    coords = all->sprites.buttons[num].sprite_coords;
    if(num == PLAYER)
        coords[0] = (t_xyz){x, y, all->draw_floors.x};
}