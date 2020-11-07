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
SDL_Surface	*get_text_surface(t_all *all, char *name, SDL_Rect target, SDL_Color color)
{
    SDL_Surface *text;
	int 		shift;
	int 		x;
    
	shift = 10 * ft_strlen(name);
    //text = SDL_CreateRGBSurface(1, target.w, target.h, 32 , 255, 255, 0, 0);
    if(!(text=TTF_RenderText_Blended(all->font, name, color)))
        printf("text printing error!\n");
	return(text);
}

int             load_buttons(t_all *all, t_button *buttons)
{
    int i;

    buttons[0].dstrect = (SDL_Rect){WIDTH/16, 50, WIDTH/8, 50};
    buttons[0].title = ft_strdup("NEW SECTOR");
    // buttons[0].texture = get_text_surface(all, "NEW SECTOR", buttons[0].dstrect, BLACK);
    buttons[1].dstrect = (SDL_Rect){WIDTH/16, 125, WIDTH/8, 50};
    buttons[1].title = ft_strdup("SET PLAYER");
    // buttons[1].texture = get_text_surface(all, "SET PLAYER", buttons[1].dstrect, BLACK);
    buttons[2].dstrect = (SDL_Rect){25, 300, 50, 50};
    buttons[2].title = ft_strdup(" - ");
    buttons[2].color = WHITE;// buttons[2].texture = get_text_surface(all, " - ", buttons[2].dstrect, WHITE);
    buttons[3].dstrect = (SDL_Rect){(WIDTH / 4 - 4) - 75, 300, 50, 50};
    buttons[3].title = ft_strdup(" + ");
    buttons[3].color = WHITE;// buttons[3].texture = get_text_surface(all, " + ", buttons[3].dstrect, WHITE);
    buttons[4].dstrect = (SDL_Rect){25, 500, 50, 50};
    buttons[4].title = ft_strdup(" - ");
    buttons[4].color = WHITE;// buttons[4].texture = get_text_surface(all, " - ", buttons[2].dstrect, WHITE);
    buttons[5].dstrect = (SDL_Rect){(WIDTH / 4 - 4) - 75, 500, 50, 50};
    buttons[5].title = ft_strdup(" + ");
    buttons[5].color = WHITE;//texture = get_text_surface(all, " + ", buttons[3].dstrect, WHITE);
    i = 0;
    while(i < 4)
        buttons[i++].state = 0;
    return (1);
}

int             load_labels(t_all *all, t_labels *labels)
{
    labels[0].dst = (SDL_Rect){WIDTH/16, 225, WIDTH/8, 50};
    labels[0].surf = get_text_surface(all, "SHOW FLOORS", labels[0].dst, BLACK);
    labels[1].dst = (SDL_Rect){WIDTH/16, 375, WIDTH/8, 50};
    labels[1].surf = get_text_surface(all, "FROM", labels[1].dst, BLACK);
    labels[2].dst = (SDL_Rect){WIDTH/16, 575, WIDTH/8, 50};
    labels[2].surf = get_text_surface(all, "TO", labels[2].dst, BLACK);
    labels[3].dst = (SDL_Rect){WIDTH/16, 375, WIDTH/8, 50};
    labels[3].surf = get_text_surface(all, "FLOOR HEIGHT", labels[3].dst, BLACK);
    labels[4].dst = (SDL_Rect){WIDTH/16, 575, WIDTH/8, 50};
    labels[4].surf = get_text_surface(all, "CEIL HEIGHT", labels[4].dst, BLACK);
    return(1);
}


int             load_texture(t_all *all)
{
    if(!(all->texture = get_texture("plain.bmp", all->sdl)))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(all->player.picture = get_texture("player.bmp", all->sdl)))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(load_buttons(all, all->buttons) == 1))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(load_labels(all, all->labels) == 1))
        error_and_close(__FILE__, __FUNCTION__);
    return (0);
}