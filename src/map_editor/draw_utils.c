#include "editor.h"

void	draw_line(t_all *all, t_xyz *start, t_xyz *fin, SDL_Color color)
{
	float		dx;
	float		dy;
	int	l;
	int i;
	float x, y;

	SDL_SetRenderDrawColor(all->sdl->renderer, color.r, color.g, color.b, color.a);

	l = (int)fmax(abs((int)start->x - (int)fin->x), abs((int)start->y - (int)fin->y));
	dx = (fin->x - start->x) / l;
	dy = (fin->y - start->y) / l;
	x = (int)(start->x);
	y = (int)(start->y); 
	i = 0;

	while (i < l)
	{
		x = x + dx;
		y = y + dy;
		i++;
		SDL_RenderDrawPoint(all->sdl->renderer, (int)x, (int)y);
	} 	
}

void	draw_circle(SDL_Renderer *rnd, t_xy coord, int r, SDL_Color col)
{
	int 	i;
	float	angle;
	float dx;
	float dy;
	//printf("x:y = %d : %d\n", x, y);
	SDL_SetRenderDrawColor(rnd, col.r, col.g, col.b, col.a);
	while (r >= 0)
	{
		i = 0;
		while (i < 20)
		{
			angle = (2 * M_PI * i)/20;
			dx = r * cosf(angle);
			dy = r * sinf(angle);
			SDL_RenderDrawPoint(rnd, roundf(coord.x + dx), roundf(coord.y + dy));
			i++;
		}
		r--;
	}
}

void    draw_fill_rect(t_all *all, SDL_Rect area, SDL_Color color)
{
    int x;
    int y;

    SDL_SetRenderDrawColor(all->sdl->renderer, color.r, color.g, color.b, color.a);
    x = area.x;
    while (x < area.x + area.w)
    {
        y = area.y;
        while(y < area.y + area.h)
        {
            SDL_RenderDrawPoint(all->sdl->renderer, x, y);
            y++;
        }
        x++;
    }
}

Uint32		get_pixel_color1(SDL_Surface *surface, const int x,\
									const int y)
{
	Uint8	*p;
	Uint32	rgb;

	p = (Uint8 *)surface->pixels + y * surface->pitch + x
			* surface->format->BytesPerPixel;
	rgb = p[3] << 24 | p[2] << 16 | p[1] << 8 | p[0];
	return (rgb);
}

void    draw_texture(SDL_Renderer *rnd, SDL_Rect area, SDL_Surface *txt)
{
    float x;
    float y;
    Uint32 col;
	float kx, ky;
	
	kx = (float)txt->w / area.w;
	ky = (float)txt->h / area.h;
	
    y = 0;
    while(y < area.h)
    {
        x = 0;
        while(x < area.w)
        {
            col = get_pixel_color1(txt,kx*x, ky*y);
            SDL_SetRenderDrawColor(rnd, col >> 16, col >> 8, col, 255);
			if(col >> 24 != 0)
            	SDL_RenderDrawPoint(rnd, area.x + x, area.y + y);
			x++;
        }
		y++;
    }
}