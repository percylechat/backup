#include "cub3d.h"

//check if map is valid (surrounded by walls)

int		check_N(data_t *data_t, int x, int y)
{
	while (y >= 0)
	{
		if (data_t->maptab[y][x] == '1')
			return (1);
		y--;
	}
	return (0);
}

int		check_S(data_t *data_t, int x, int y)
{
	while (y < data_t->line)
	{
		if (data_t->maptab[y][x] == '1')
			return (1);
		y++;
	}
	return (0);
}

int		check_W(data_t *data_t, int x, int y)
{
	while (x >= 0)
	{
		if (data_t->maptab[y][x] == '1')
			return (1);
		x--;
	}
	return (0);
}

int		check_E(data_t *data_t, int x, int y)
{
	while (x < data_t->column_size[y])
	{
		if (data_t->maptab[y][x] == '1')
			return (1);
		x++;
	}
	return (0);
}

void	sprite_roundup(data_t *data_t, int x, int y)
{
	char	*add;
	char *temp;

	if (!(add = malloc(sizeof(char) * 3)))
		return;
	add[0] = y;
	add[1] = x;
	add[2] = '\0';
	data_t->tot_sprite += 1;
	if (data_t->sprite_spot)
	{
		temp = ft_strjoin(data_t->sprite_spot, add);
		free(data_t->sprite_spot);
		data_t->sprite_spot = ft_strdup(temp);
	}
	else
	{
		data_t->sprite_spot = ft_strdup(add);
		temp = NULL;
	}
	free(temp);
}


//fixes some map stuff, check if for each blank space (0) there is a wall for every direction, then create a double array for map.
void	check_map(data_t *data_t)
{
	int x;
	int y;

	x = 0;
	y = 0;
	data_t->maptab = ft_split_map(data_t);
	while (y < data_t->line)
	{
		while (x < data_t->column_size[y])
		{
			if (data_t->maptab[y][x] == '0')
			{
				if ((check_N(data_t, x, y) + check_S(data_t, x, y) + check_E(data_t, x, y) + check_W(data_t, x, y)) != 4)
				{
					write(1, "ERROR, fail map", 15);
					return;
				}
			}
			if (data_t->maptab[y][x] == 'W' || data_t->maptab[y][x] == 'N' || data_t->maptab[y][x] == 'S' || data_t->maptab[y][x] == 'E')
			{
				if ((check_N(data_t, x, y) + check_S(data_t, x, y) + check_E(data_t, x, y) + check_W(data_t, x, y)) != 4)
				{
					write(1, "ERROR, fail map", 15);
					return;
				}
				data_t->orientation = data_t->maptab[y][x];
				data_t->position_x = x + 0.5;
				data_t->position_y = y + 0.5;
				give_angle(data_t);
			}
			if (data_t->maptab[y][x] == '2')
				sprite_roundup(data_t, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}
