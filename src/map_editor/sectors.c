#include "editor.h"

// int		revert_sector(t_sector *sector, t_env *env)
// {
// 	int			i;
// 	int			index;
// 	int			j;
// 	int			*tmp;

// 	i = 1;
// 	j = 1;
// 	if (!(tmp = (int *)ft_memalloc(sizeof(int) * (sector->nb_vertices + 1))))
// 		return (ft_perror("Could not malloc revert sector tmp"));
// 	tmp[0] = sector->vertices[0];
// 	while (i < sector->nb_vertices)
// 	{
// 		if (env->editor.reverted)
// 			index = sector->nb_vertices - j;
// 		else
// 			index = j;
// 		tmp[i] = sector->vertices[index];
// 		i++;
// 		j++;
// 	}
// 	tmp[sector->nb_vertices] = tmp[0];
// 	free(sector->vertices);
// 	sector->vertices = tmp;
// 	return (0);
// }


// int		check_sector_order(t_env *env)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < env->nb_sectors)
// 	{
// 		j = 0;
// 		while (j < env->sectors[i].nb_vertices)
// 		{
// 			if (env->editor.dragged_vertex == env->sectors[i].vertices[j])
// 			{
// 				env->editor.reverted =
// 				get_clockwise_order_sector(env, i) ? 0 : 1;
// 				if (revert_sector(&env->sectors[i], env))
// 					return (-1);
// 				break ;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int		get_clockwise_order_sector(t_env *env, int index)
// {
// 	int			res;
// 	int			i;
// 	int			num;
// 	t_vertex	vertex1;
// 	t_vertex	vertex2;

// 	res = 0;
// 	i = 0;
// 	vertex2 = env->vertices[0];
// 	while (i < env->sectors[index].nb_vertices - 1)
// 	{
// 		num = env->sectors[index].vertices[i];
// 		vertex1 = env->vertices[num];
// 		num = env->sectors[index].vertices[i + 1];
// 		vertex2 = env->vertices[num];
// 		res += (vertex2.x - vertex1.x) * (vertex2.y + vertex1.y);
// 		i++;
// 	}
// 	vertex1 = vertex2;
// 	num = env->sectors[index].vertices[0];
// 	vertex2 = env->vertices[num];
// 	res += (vertex2.x - vertex1.x) * (vertex2.y + vertex1.y);
// 	return (res > 0 ? 0 : 1);
// }

void    del_neighbour(int *arr, int len, int num)
{
    int i;

    i = 0;
    while (i < len)
    {
        printf("neighbour %d is %d...\n", i, arr[i]);
        if(arr[i] == num)
        {
            arr[i] = -1;
            printf("sector clear\n");
			break ;
        }
        i++;
    }
}

void    drop_neighbors(t_sect *sectors, int *neighbors, int num, int del)
{
    int i;
    int index;

    i = 0;
    while (i < num)
    {
        if(neighbors[i] > -1)
        {
            index = neighbors[i];
            printf("checking sector: %d\n", neighbors[i]);
            del_neighbour(sectors[index].neighbors, sectors[index].npoints, del);
        }
        i++;
    }
}

void    remove_sector(t_all *all, t_sect *sectors)
{
    t_sect *del;

    del = &all->sectors[all->swap_num];
    if(all->swap_num != -1)
    {
        printf("sector to be removed: %d\n", all->swap_num);
        drop_neighbors(all->sectors, del->neighbors, del->npoints, all->swap_num);
        free(all->sectors[all->swap_num].vertex);
        free(all->sectors[all->swap_num].neighbors);
		if (all->num_sectors > 1 && all->swap_num != all->num_sectors - 1)
        	all->sectors[all->swap_num] = all->sectors[all->num_sectors - 1];
        all->num_sectors -= 1;
        all->swap_num = -1;
    }
}