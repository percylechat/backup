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
	int	i;

	i = 0;
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
	// 	}
	// 	i++;
	// }
	// transform_map(data_t);
	data_t->maptab = ft_split(data_t->map, '\n', data_t);
}

static int	ft_count(char const *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i + 1] == c)
			{
				i++;
			}
			j++;
		}
		i++;
	}
	return (j + 1);
}

static int	ft_clear(char const *str, char c, int i)
{
	int j;

	j = 0;
	while (str[i] != c && str[i])
	{
		j++;
		i++;
	}
	return (j);
}

char		**ft_split(char const *str, char c, data_t *data_t)
{
	int		i;
	int		j;
	int		k;

	j = 0;
	k = 0;
	i = 0;
	if (!(data_t->maptab = malloc(sizeof(char *) * (ft_count(str, c)))))
		return (NULL);
	while (str[i])
	{
		if (str[i] != c)
		{
			j = ft_clear(str, c, i);
			data_t->maptab[k] = ft_substr((char *)str, i, j);
			k++;
			i += (j - 1);
		}
		i++;
	}

	if (!(data_t->maptab[k] = malloc(1)))
		return (NULL);
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
