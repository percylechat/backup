#include "cub3d.h"

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
