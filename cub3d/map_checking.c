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
	data_t->line -= 2;
	ft_memmove((void *)&data_t->map[0], (void *)&data_t->map[1], data_t->line * (data_t->column + 1));
	// data_t->map[data_t->line * (data_t->column + 1)] = '\0';
	while (data_t->map[i])
	{
		if (data_t->map[i] == '0')
		{
			if ((check_N(data_t, i) + check_S(data_t, i) + check_E(data_t, i) + check_W(data_t, i)) != 4)
			{
				write(1, "ERROR", 5);
				return;
			}
		}
		else if (data_t->map[i] == 'W' || data_t->map[i] == 'N' ||
		data_t->map[i] == 'S' || data_t->map[i] == 'E')
		{
			data_t->orientation = data_t->map[i];
			data_t->position_x = i % (data_t->column + 1);
			data_t->position_y = (i / (data_t->column + 1));
			give_angle(data_t);
		}
		i++;
	}
	transform_map(data_t);
}

//creates double array for map and put it in struct.
void	transform_map(data_t *data_t)
{
	char **map;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	if (!(map = malloc(sizeof(char*) * data_t->line + 1)))
		return;
	while (i < data_t->line + 1)
	{
		if (!(map[i] = malloc(sizeof(char*) * data_t->column + 1)))
			return;
		while (data_t->map[k] != '\n')
		{
			map[i][j] = data_t->map[k];
			j++;
			k++;
		}
		map[i][j] = '\0';
		j = 0;
		k++;
		i++;
	}
	data_t->maptab = map;
}
