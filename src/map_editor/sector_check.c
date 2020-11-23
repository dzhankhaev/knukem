#include "editor.h"

int		check_sector_shape(t_sect *sect)
{
	t_xy *temp;
	int i;
	float side;

	i = 0;
	temp = sect->vertex;
	while (i < sect->npoints - 1)
	{
		side = point_side1(temp[i + 1].x, temp[i + 1].y, temp[i], temp[i + 2]);
		if (side > 0)
			return 0;
		i++;
	}
	side = point_side1(temp[0].x, temp[0].y, temp[i], temp[1]);
	if (side > 0)
			return 0;
	return 1;
}

int		revert_sector(t_sect *sect)
{
	t_xy *temp;
	int i;

	i = 0;
	if(!(temp = (t_xy*)malloc(sizeof(t_xy) * sect->npoints)))
		exit(0);
	while(i < sect->npoints)
	{
		temp[i] = sect->vertex[sect->npoints - i];
		i++;
	}
	temp[i] = temp[0];
	free(sect->vertex);
	sect->vertex = temp;
	return 0;
}

int		check_sector_order(t_sect *sect)
{
	int			res;
	int			i;
	int			num;
	t_xy	vertex1;
	t_xy	vertex2;

	res = 0;
	i = 0;
	while (i < sect->npoints)
	{
		vertex1 = sect->vertex[i];
		vertex2 = sect->vertex[i + 1];
		res += (vertex2.x - vertex1.x) * (vertex2.y + vertex1.y);
		i++;
	}
	return (res > 0 ? 0 : 1);
}

int		check_sector(t_sect *sect)
{
	if(!(check_sector_order(sect)))
		revert_sector(sect);
	check_sector_shape(sect);
	return (0);
}