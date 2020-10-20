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


# define PATHCES_COL 14

# define STBAR	"STBAR"

/**
** жизни / броня / патроны
**/
# define STTNUM 0
# define STTNUM_COL 11

# define STTNUM0 0
# define STTNUM1 1
# define STTNUM2 2
# define STTNUM3 3
# define STTNUM4 4
# define STTNUM5 5
# define STTNUM6 6
# define STTNUM7 7
# define STTNUM8 8
# define STTNUM9 9
# define STTPRCNT 10

/**
**	Когда нет оружия
**/

# define STGNUM 1
# define STGNUM_COL 11

# define STGNUM0 0
# define STGNUM1 1
# define STGNUM2 2
# define STGNUM3 3
# define STGNUM4 4
# define STGNUM5 5
# define STGNUM6 6
# define STGNUM7 7
# define STGNUM8 8
# define STGNUM9 9
# define STTMINUS 10

/**
** когда есть оружие
**/

# define STYNUM 2
# define STYNUM_COL 10

# define STYSNUM0 0
# define STYSNUM1 1
# define STYSNUM2 2
# define STYSNUM3 3
# define STYSNUM4 4
# define STYSNUM5 5
# define STYSNUM6 6
# define STYSNUM7 7
# define STYSNUM8 8
# define STYSNUM9 9

/**
** Мордаха просто смотрит за мышкой в зависимости от хр
** 0 - вправо / 1 - прямо / 2 - влево
**/

# define STFST 3
# define STFST_COL 15

# define STFST00 0
# define STFST01 1
# define STFST02 2

# define STFST10 3
# define STFST11 4
# define STFST12 5

# define STFST20 6
# define STFST21 7
# define STFST22 8

# define STFST30 9
# define STFST31 10
# define STFST32 11

# define STFST40 12
# define STFST41 13
# define STFST42 14

/**
** недовольная мордаха смотрит по сторонам
**/

# define STFT 4
# define STFT_COL 10

# define STFTL00 0
# define STFTR00 1

# define STFTL10 2
# define STFTR10 3

# define STFTL20 4 
# define STFTR20 5

# define STFTL30 6
# define STFTR30 7

# define STFTL40 8
# define STFTR40 9


/**
** Мордаха "злой"
**/

# define SRFEVL	5
# define SRFEVL_COL	5

# define STFEVL0 0
# define STFEVL1 1
# define STFEVL2 2
# define STFEVL3 3
# define STFEVL4 4

/**
** Мордаха "больно"
**/

#define STFOUCH 6
#define STFOUCH_COL 5

# define STFOUCH0 0
# define STFOUCH1 1
# define STFOUCH2 2
# define STFOUCH3 3
# define STFOUCH4 4

/**
** Мордаха "убил"
**/

#define STFKILL 7
#define STFKILL_COL 5

# define STFKILL0 0
# define STFKILL1 1
# define STFKILL2 2
# define STFKILL3 3
# define STFKILL4 4

/**
**  Пулемет 0,1 - огонь / 2,3 - сам пулемет
**/

# define CHGF 8
# define CHGF_COL 4

# define CHGFA0 0
# define CHGFB0 1

# define CHGGA0 2
# define CHGGB0 3

/**
**	ружье 
**/

# define SHTF 9
# define SHTF_COL 6

# define SHTFA0 0
# define SHTFB0 1

# define SHTGA0 2
# define SHTGB0 3
# define SHTGC0 4
# define SHTGD0 5

/**
**	Бензопила
**/

# define SAW 10
# define SAW_COL 4

# define SAWGA0 0
# define SAWGB0 1
# define SAWGC0 2
# define SAWGD0 3

/**
**	Кастет
**/

# define PUNG 11
# define PUNG_COL 4

# define PUNGA0 0
# define PUNGB0 1
# define PUNGC0 2
# define PUNGD0 3

/**
**	Пистолет
**/

# define PIS 12
# define PIS_COL 6

# define PISFA0 0
# define PISGA0 1
# define PISGB0 2
# define PISGC0 3
# define PISGD0 4
# define PISGE0 5

/**
**	Хз че за оружие
**/

# define MIS 13
# define MIS_COL 14

# define MISFA0 0
# define MISFB0 1
# define MISFC0 2
# define MISFD0 3

# define MISGA0 4
# define MISGB0 5

# define MISLA1 6
# define MISLA5 7
# define MISLA6A4 8
# define MISLA7A3 9
# define MISLA8A2 10
# define MISLB0 11
# define MISLC0 12
# define MISLD0 13

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

typedef struct	s_sub_hud
{
	t_patch		*patch;
	SDL_Rect	rect;
	SDL_Surface	*scr;
}				t_sub_hud;

typedef struct	s_hud
{
	char		colormap[14][256*3];
	t_sub_hud	**patches;
}				t_hud;

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