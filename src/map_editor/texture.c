#include "editor.h"

SDL_Surface     *get_texture(char *file, t_sdl *sdl)
{
	SDL_Surface		*surface;
    char            *dir;

    dir = (char*)malloc(sizeof(char) * (ft_strlen(file) + 10));
    dir = ft_strjoin("textures/", file);
	if(!(surface = SDL_LoadBMP(dir)))
        error_and_close(__FILE__, __FUNCTION__);
    free(dir);
    return(surface);
}
SDL_Surface	*get_text_surface(t_all *all, char *name, TTF_Font *font, SDL_Color color)
{
    SDL_Surface *text;
	int 		shift;
    
	shift = 15 * ft_strlen(name);
    //text = SDL_CreateRGBSurface(1, target.w, target.h, 32 , 255, 255, 0, 0);
    if(!(text = TTF_RenderText_Blended(font, name, color)))
        printf("text printing error!\n");
    // free(&name);
	return(text);
}

int             extra_buttons(t_all *all, t_button *buttons)
{
    buttons[6].dstrect = (SDL_Rect){25, H * 0.46, 50, 50};
    buttons[6].title = ft_strdup(" - ");
    buttons[6].color = WHITE;
    buttons[7].dstrect = (SDL_Rect){(W / 4 - 4) - 75, H * 0.46, 50, 50};
    buttons[7].title = ft_strdup(" + ");
    buttons[7].color = WHITE;
    buttons[8].dstrect = (SDL_Rect){25, H * 0.58, 50, 50};
    buttons[8].title = ft_strdup(" - ");
    buttons[8].color = WHITE;
    buttons[9].dstrect = (SDL_Rect){(W / 4 - 4) - 75, H * 0.58, 50, 50};
    buttons[9].title = ft_strdup(" + ");
    buttons[9].color = WHITE;
}

int             load_buttons(t_all *all, t_button *buttons)
{
    int i;

    buttons[0].dstrect = (SDL_Rect){W / 16, H * 0.01, W/8, 50};
    buttons[0].title = ft_strdup("NEW SECTOR");
    buttons[1].dstrect = (SDL_Rect){W/16, H * 0.1, W/8, 50};
    buttons[1].title = ft_strdup("SET SPRITE");
    buttons[2].dstrect = (SDL_Rect){25, H * 0.75, 50, 50};
    buttons[2].title = ft_strdup(" - ");
    buttons[2].color = WHITE;
    buttons[3].dstrect = (SDL_Rect){(W / 4 - 4) - 75, H * 0.75, 50, 50};
    buttons[3].title = ft_strdup(" + ");
    buttons[3].color = WHITE;
    buttons[4].dstrect = (SDL_Rect){25, H * 0.86, 50, 50};
    buttons[4].title = ft_strdup(" - ");
    buttons[4].color = WHITE;
    buttons[5].dstrect = (SDL_Rect){(W / 4 - 4) - 75, H * 0.86, 50, 50};
    buttons[5].title = ft_strdup(" + ");
    buttons[5].color = WHITE;
    extra_buttons(all, buttons);
    i = 0;
    while(i < BUTTONS)
        buttons[i++].state = 0;
    return (1);
}

int             load_labels(t_all *all, t_labels *labels)
{
    labels[0].dst = (SDL_Rect){W / 16, H * 0.4, W / 8, 50};
    labels[0].surf = get_text_surface(all, "FLOOR HEIGHT", all->font, BLACK);
    labels[1].dst = (SDL_Rect){W / 16, H * 0.52, W / 8, 50};
    labels[1].surf = get_text_surface(all, "CEIL HEIGHT", all->font, BLACK);
    labels[2].dst = (SDL_Rect){W / 16, H * 0.68, W / 8, 50};
    labels[2].surf = get_text_surface(all, "SHOW FLOORS", all->font, BLACK);
    labels[3].dst = (SDL_Rect){W / 16 + W / 96, H * 0.81 , W / 10, 30};
    labels[3].surf = get_text_surface(all, "FROM", all->font, BLACK);
    labels[4].dst = (SDL_Rect){W / 11 , H * 0.92, W / 16, 30};
    labels[4].surf = get_text_surface(all, "TO", all->font, BLACK);
    
    return(1);

}

int             load_sprites_pics(t_all *all, t_sprites *sprite)
{
    if(!(sprite->player->texture = get_texture("player.bmp", all->sdl)))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(sprite->gun->texture = get_texture("gun.bmp", all->sdl)))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(sprite->enemy->texture = get_texture("monster.bmp", all->sdl)))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(sprite->aid->texture = get_texture("aid.bmp", all->sdl)))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(sprite->bazooka->texture = get_texture("bazooka.bmp", all->sdl)))
        error_and_close(__FILE__, __FUNCTION__);
    sprite->gun->dstrect = (SDL_Rect){W / 28, H * 0.2, 50, 50};
    sprite->enemy->dstrect = (SDL_Rect){W / 10, H * 0.2, 50, 50};
    sprite->aid->dstrect = (SDL_Rect){W / 6, H * 0.2, 50, 50};
    sprite->bazooka->dstrect = (SDL_Rect){W / 28, H * 0.3, 50, 50};
    sprite->player->dstrect = (SDL_Rect){W / 10, H * 0.3, 50, 50};
    init_sprites(sprite);
    return(1);
}

void	alloc_sprites(t_sprites *sprites)
{
	int i;

	sprites->gun = (t_button*)malloc(sizeof(t_button));
	sprites->aid = (t_button*)malloc(sizeof(t_button));
	sprites->enemy = (t_button*)malloc(sizeof(t_button));
	sprites->bazooka = (t_button*)malloc(sizeof(t_button));
	sprites->player = (t_button*)malloc(sizeof(t_button));

	i = 0;
	while(i < 5)
	{
		if(&sprites->buttons[i] == NULL)
			error_and_close(__FILE__, __FUNCTION__);
		i++;
	}
}

int             load_texture(t_all *all)
{
    t_sprites *sprites;

    sprites = &all->sprites;
	alloc_sprites(&all->sprites);
    if(!(load_sprites_pics(all, &all->sprites) == 1))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(load_buttons(all, all->buttons) == 1))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(load_labels(all, all->labels) == 1))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(all->player.picture = get_texture("player.bmp", all->sdl)))
        error_and_close(__FILE__, __FUNCTION__);
    sprites->buttons[0] = *sprites->gun;
	sprites->buttons[1] = *sprites->enemy;
	sprites->buttons[2] = *sprites->aid;
	sprites->buttons[3] = *sprites->bazooka;
	sprites->buttons[4] = *sprites->player;

    return (0);
}