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
	get_texture(data_t);
}

void	get_texture(data_t *data_t)
{
	data_t->img_N = mlx_xpm_to_image(data_t->mlx_prog, *data_t->tex_N, (int)BLOC_SIZE, (int)BLOC_SIZE);
	mlx_put_image_to_window(data_t->mlx_prog, data_t->mlx_win ,data_t->img_N, 64, 64);
}
