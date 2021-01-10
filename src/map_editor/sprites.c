#include "editor.h"

void    sprite_remove(t_all *all, t_sprites *sprites, t_xy pos)
{
    int i;
    int j;
    t_xyz *coords;
    printf("i = %dj = %d\n", (int)pos.x, (int)pos.y);

    if(pos.x == 4)
    {
        all->player.where = (t_xyz){-1, -1, -1};
        all->player.sector = -1;
        return ;
    }
    i = pos.x;
    j = pos.y;
    coords = sprites->buttons[i].sprite_coords;
    while(j + 1 < sprites->buttons[i].num)
    {
        coords[j] = coords[j + 1];
        j++;
    }
    coords = ft_realloc((void*)coords, --sprites->buttons[i].num);
}

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

void    draw_sprite(t_all *all, t_button *sprite, int type)
{
    SDL_Rect    loc;
    t_xyz       *coords;
    SDL_Surface *texture;
    int         i;

    coords = sprite->sprite_coords;
    texture = sprite->texture;
    i = 0;
    while(i < sprite->num)
    {
        loc = (SDL_Rect){(coords[i].x * all->step) + all->delta.x - all->step/2,
            (coords[i].y * all->step) + all->delta.y - all->step/2,
                all->step, all->step};
        if(all->sectors[(int)coords[i].z].floor >= all->draw_floors.x  && loc.x > all->area.x)
        {
            if(all->sprites.swap.x == type && all->sprites.swap.y == i)
                draw_circle(all->sdl, (t_xy){loc.x + all->step/2, loc.y + all->step/2}, all->step/2, YELLOW);
            draw_texture(all->sdl, loc, texture);
        }
        i++;
    }
}

void    draw_sprites(t_all *all, t_sprites *sprites)
{
    draw_sprite(all, &sprites->buttons[GUN], GUN);
    draw_sprite(all, &sprites->buttons[ENEMY], ENEMY);
    draw_sprite(all, &sprites->buttons[AID], AID);
    draw_sprite(all, &sprites->buttons[BAZOOKA], BAZOOKA);
    draw_sprite(all, &sprites->buttons[PLAYER], PLAYER);
}

void    add_sprite(t_all *all, int x, int y, int type)
{
    t_xyz   *coords;
    int sect;

    coords = all->sprites.buttons[type].sprite_coords;
    if(type == PLAYER && (sect = which_sector(all, all->sectors, (t_xyz){x, y, all->draw_floors.x})) != -1)
    {
        coords[0] = (t_xyz){x, y, all->draw_floors.x};
        all->player.sector = sect;
    }
    else if((sect = which_sector(all, all->sectors, (t_xyz){x, y, all->draw_floors.x})) != -1)
    {
        coords = ft_realloc(coords, sizeof(t_xyz) * (++all->sprites.buttons[type].num));
        coords[all->sprites.buttons[type].num - 1] = (t_xyz){x, y, all->draw_floors.x};
        all->sprites.buttons[type].sprite_coords = coords;
    }
    else
    {
        printf("öut of sector\n");
    }
    
    
}