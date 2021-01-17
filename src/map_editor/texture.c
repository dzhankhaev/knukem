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

SDL_Surface     *get_texture2(char *file)
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

SDL_Surface	*get_text_surface(char *name, TTF_Font *font, SDL_Color color)
{
    SDL_Surface *text;
    if(!(text = TTF_RenderText_Blended(font, name, color)))
        error_and_close(__FILE__, __FUNCTION__);
	  return(text);
}

int             extra_buttons(t_all *all, t_button *buttons)
{    
    buttons[6] = (t_button){(SDL_Rect){W / 4 - 150, H * 0.15, 50, 50},\
		ft_strdup(" - "), WHITE};//inventory
    buttons[7] = (t_button){(SDL_Rect){W / 4 - 50, H * 0.15, 50, 50},\
		ft_strdup(" + "), WHITE};//inventory
    buttons[8] = (t_button){(SDL_Rect){W / 4 - 150, H * 0.21, 50, 50},\
		ft_strdup(" - "), WHITE};//speed
    buttons[9] = (t_button){(SDL_Rect){W / 4 - 50, H * 0.21, 50, 50},\
		ft_strdup(" + "), WHITE};//speed
    buttons[10] = (t_button){(SDL_Rect){W / 4 - 150, H * 0.27, 50, 50},\
		ft_strdup(" - "), WHITE};//gravity
    buttons[11] = (t_button){(SDL_Rect){W / 4 - 50, H * 0.27, 50, 50},\
		ft_strdup(" + "), WHITE};//gravity
    buttons[12] = (t_button){(SDL_Rect){W / 4 - 150, H * 0.33, 50, 50},\
		ft_strdup(" - "), WHITE};//ammo
    buttons[13] = (t_button){(SDL_Rect){W / 4 - 50, H * 0.33, 50, 50},\
		ft_strdup(" + "), WHITE};//ammo
    buttons[14] = (t_button){(SDL_Rect){25, H * 0.46, 50, 50},\
		ft_strdup(" - "), WHITE};
    buttons[15] = (t_button){(SDL_Rect){(W / 4 - 4) - 75, H * 0.46, 50, 50},\
		ft_strdup(" + "), WHITE};
    buttons[16] = (t_button){(SDL_Rect){25, H * 0.58, 50, 50},\
		ft_strdup(" - "), WHITE};
    buttons[17] = (t_button){(SDL_Rect){(W / 4 - 4) - 75, H * 0.58, 50, 50},\
		ft_strdup(" + "), WHITE};
	  
    return 0;
}

int             load_buttons(t_all *all, t_button *buttons)
{
    int i;

	buttons[0] = (t_button){(SDL_Rect){W / 16, H * 0.01, W / 8, 50},\
		ft_strdup("NEW SECTOR")};
    buttons[1] = (t_button){(SDL_Rect){W/16, H * 0.07, W/8, 50},\
		ft_strdup("SET PLAYER")};
    buttons[2] = (t_button){(SDL_Rect){25, H * 0.75, 50, 50},\
		ft_strdup(" - "), WHITE};
    buttons[3] = (t_button){(SDL_Rect){(W / 4 - 4) - 75, H * 0.75, 50, 50},\
		ft_strdup(" + "), WHITE};
    buttons[4] = (t_button){(SDL_Rect){25, H * 0.86, 50, 50},\
		ft_strdup(" - "), WHITE};
    buttons[5] = (t_button){(SDL_Rect){(W / 4 - 4) - 75, H * 0.86, 50, 50},\
		ft_strdup(" + "), WHITE};
    extra_buttons(all, buttons);
    i = 0;
    while(i < BUTTONS)
        buttons[i++].state = 0;
    return (1);
}

int             load_labels(t_all *all, t_labels *labels)
{
    labels[FLOOR].dst = (SDL_Rect){W / 16, H * 0.4, W / 8, 50};
    labels[FLOOR].surf = get_text_surface("FLOOR HEIGHT", all->font, BLACK);
    labels[CEIL].dst = (SDL_Rect){W / 16, H * 0.52, W / 8, 50};
    labels[CEIL].surf = get_text_surface("CEIL HEIGHT", all->font, BLACK);
    labels[SHOW].dst = (SDL_Rect){W / 16, H * 0.68, W / 8, 50};
    labels[SHOW].surf = get_text_surface("SHOW FLOORS", all->font, BLACK);
    labels[FROM].dst = (SDL_Rect){W / 16 + W / 96, H * 0.81 , W / 10, 30};
    labels[FROM].surf = get_text_surface("FROM", all->font, BLACK);
    labels[TO].dst = (SDL_Rect){W / 11 , H * 0.92, W / 16, 30};
    labels[TO].surf = get_text_surface("TO", all->font, BLACK);
    labels[INVENTORY].dst = (SDL_Rect){15, H * 0.17, W / 10, 30};
    labels[INVENTORY].surf = get_text_surface("INV.size", all->font, BLACK);
    labels[SPEED].dst = (SDL_Rect){15, H * 0.23, W / 10, 30};
    labels[SPEED].surf = get_text_surface("SPEED", all->font, BLACK);
    labels[GRAVITY].dst = (SDL_Rect){15, H * 0.29 , W / 10, 30};
    labels[GRAVITY].surf = get_text_surface("GRAVITY", all->font, BLACK);
    labels[AMMO].dst = (SDL_Rect){15 , H * 0.35, W / 10, 30};
    labels[AMMO].surf = get_text_surface("AMMO", all->font, BLACK);
    
    return(1);

}

int             load_texture(t_all *all)
{
    if(!(load_buttons(all, all->buttons) == 1))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(load_labels(all, all->labels) == 1))
        error_and_close(__FILE__, __FUNCTION__);
    if(!(all->player.picture = get_texture("player.bmp", all->sdl)))
        error_and_close(__FILE__, __FUNCTION__);

    return (0);
}