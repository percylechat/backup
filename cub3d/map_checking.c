#include "cub3d.h"

//check if map is valid (surrounded by walls)

int		check_N(data_t *data_t, int i)
{
	while (data_t->map[i])
	{
		if (data_t->map[i] == '1')
			return (1);
		i -= (data_t->line + 1);
	}
	return (0);
}

int		check_S(data_t *data_t, int i)
{
	while (data_t->map[i])
	{
		if (data_t->map[i] == '1')
			return (1);
		i += (data_t->line + 1);
	}
	return (0);
}

int		check_W(data_t *data_t, int i)
{
	while (data_t->map[i] != '\n')
	{
		if (data_t->map[i] == '1')
			return (1);
		i--;
	}
	return (0);
}

int		check_E(data_t *data_t, int i)
{
	while (data_t->map[i] != '\n')
	{
		if (data_t->map[i] == '1')
			return (1);
		i++;
	}
	return (0);
}

//fixes some map stuff, check if for each blank space (0) there is a wall for every direction, then create a double array for map.
void	check_map(data_t *data_t)
{
	int x;
	int y;

	x = 0;
	y = 0;
	// data_t->line -= 2;
	// ft_memmove((void *)&data_t->map[0], (void *)&data_t->map[1], data_t->line * (data_t->column + 1));
	// // data_t->map[data_t->line * (data_t->column + 1)] = '\0';
	// while (data_t->map[i])
	// {
	// 	if (data_t->map[i] == '0')
	// 	{
	// 		if ((check_N(data_t, i) + check_S(data_t, i) + check_E(data_t, i) + check_W(data_t, i)) != 4)
	// 		{
	// 			write(1, "ERROR, fail map", 15);
	// 			return;
	// 		}
	// 	}
	// 	else if (data_t->map[i] == 'W' || data_t->map[i] == 'N' ||
	// 	data_t->map[i] == 'S' || data_t->map[i] == 'E')
	// 	{
	// 		data_t->orientation = data_t->map[i];
	// 		data_t->position_x = i % (data_t->column + 1);
	// 		data_t->position_y = (i / (data_t->column + 1));
	// 		give_angle(data_t);
	// 		printf("%d %d\n", data_t->position_x, data_t->position_y);
	// 	}
	// 	i++;
	// }
	// transform_map(data_t);
	data_t->maptab = ft_split_map(data_t);
	// printf("%s\n", data_t->maptab[0]);
	while (y < data_t->line)
	{
		while (x < data_t->column_size[y])
		{
			// if (data_t->maptab[y][x] == '0')
			// {
			// 	if ((check_N(data_t, i) + check_S(data_t, i) + check_E(data_t, i) + check_W(data_t, i)) != 4)
			// 	{
			// 		write(1, "ERROR, fail map", 15);
			// 		return;
			// 	}
			// }
			if (data_t->maptab[y][x] == 'W' || data_t->maptab[y][x] == 'N' || data_t->maptab[y][x] == 'S' || data_t->maptab[y][x] == 'E')
			{
				data_t->orientation = data_t->maptab[y][x];
				data_t->position_x = x;
				data_t->position_y = y;
				give_angle(data_t);
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	*ft_memcpy_line(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*buffer_d;
	char	*buffer_s;

	// printf("%d\n", (int)n);
	if ((dst == src) || (!dst && !src) || !n)
		return ((void *)dst);
	buffer_s = (char *)src;
	buffer_d = dst;
	i = 0;
	while (i < n)
	{
		// printf("%c\n", buffer_s[i]);
		buffer_d[i] = buffer_s[i];
		i++;
	}
	buffer_d[i] = '\0';
	// printf("linememcpy: %s\n", dst);
	return ((void *)dst);
}

char		**ft_split_map(data_t *data_t)
{
	int		i;
	int		j;
	int		k;
	char *test;

	j = 0;
	k = 0;
	i = 0;
	if (!(data_t->maptab = malloc(sizeof(char *) * (data_t->line + 1))))
		return (NULL);
	while (k < data_t->line)
	{
		test = ft_memcpy_line(&data_t->maptab[k], &data_t->map[i], data_t->column_size[k]);
		// while (j < data_t->column_size[k])
		// {
		// 	data_t->maptab[k][j] = data_t->map[i];
		// 	j++;
		// 	i++;
		// }
		// printf("test: %s\n", test);
		data_t->maptab[k] = ft_strdup(test);
		// printf("test2: %s\n", data_t->maptab[k]);
		i += data_t->column_size[k];
		k++;
	}
	data_t->maptab[k] = NULL;
	return (data_t->maptab);
}

//creates double array for map and put it in struct.
// void	transform_map(data_t *data_t)
// {
// 	int i;
// 	int j;
// 	int k;
//
// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	if (!(data_t->maptab = malloc(sizeof(char *) * data_t->line + 1)))
// 		return;
// 	while (i < data_t->line + 1)
// 	{
// 		if (!(data_t->maptab[i] = malloc(sizeof(char*) * data_t->column + 1)))
// 			return;
// 		while (data_t->map[k] != '\n')
// 		{
// 			data_t->maptab[i][j] = data_t->map[k];
// 			j++;
// 			k++;
// 		}
// 		data_t->maptab[i][j] = '\0';
// 		j = 0;
// 		k++;
// 		i++;
// 	}
// 	data_t->maptab[i][j] = '\0';
// }
