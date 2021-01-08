#include "engine.h"
#include "utilits.h"

int	imin(int a, int b)
{
	return (((a) < (b)) ? (a) : (b));
}

int	imax(int a, int b)
{
	return (((a) > (b)) ? (a) : (b));
}

float clamp(float a, float min, float max)
{
	return fminf(fmaxf(a, min), max);
}

int iclamp(int a, int min, int max)
{
	return imin(imax(a, min), max);
}

/*
 * checks whether a point is inside cube
 * point - point coordinates
 * cubecenter - center coordinates
 * borders - borders coordinates
 * centeroffset - center offset (z axis)
 */
int ispointincube(t_xyz point, t_xyz cubecenter, t_xyz borders, float centerzoffset)
{
    return ((cubecenter.x + borders.x > point.x & point.x > cubecenter.x - borders.x)
            && (cubecenter.y + borders.y > point.y & point.y > cubecenter.y - borders.y)
            && (cubecenter.z + centerzoffset + borders.z > point.z & point.z > cubecenter.z + centerzoffset - borders.z));
}

Uint32		get_pixel_color(SDL_Surface *surface, int x, int y)
{
	Uint8	*p;
	Uint32	rgb;

	p = (Uint8 *)(surface->pixels + y * surface->pitch
				  + (x * surface->format->BytesPerPixel));
	rgb = p[2] << 16 | p[1] << 8 | p[0];
	return (rgb);
}