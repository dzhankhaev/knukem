#ifndef PARSE_WAD
# define PARSE_WAD

# include "engine.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define RMASK	0xff0000
# define GMASK	0xff00
# define BMASK	0xff
# define AMASK	0xff000000

typedef struct	s_patch
{
	unsigned short	width;
	unsigned short	height;
	unsigned short	l_offset;
	unsigned short	r_offsrt;
	int				*columnofs;
	unsigned char	**colum;
	unsigned char	*mem;
	size_t			size_patch;
	int				type;
	char			name[8];
	SDL_Surface		*surface;
}				t_patch;

typedef struct	s_directory
{
	int		filepos;
	int		size;
	char	name[8];
}				t_directory;

typedef struct	s_wad
{
	char			identification[4];
	unsigned int	numlumps;
	unsigned int	mem_start;
	t_directory		dir;
	t_patch			patch;
	unsigned char	colormap[14][255*3];
	int				fd;
	int				fr;
	// unsigned char	*colormap;
}				t_wad;

typedef struct	s_value
{
	int		ammo;
	int		health;
	int		arms;
	int		armor;
	int		bull[2];
	int		shel[2];
	int		rckt[2];
	int		cell[2];
}				t_value;

typedef struct	s_pars_colum
{
	int			*pixel;
	int			x;
	int			i;
	int			col;
	int			index;
	int			size;
}				t_pars_colum;

t_patch			*init_patch(t_wad *wad);
// void			free_patch(t_patch *patch);
void			pars_patch(t_patch *patch);
t_patch			*load_patch(char *name_file, char *name_dir);

#endif