#include "cub3d.h"


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

void	give_angle(data_t *data_t)
{
	if (data_t->orientation == 'N')
		data_t->direction = 90;
	if (data_t->orientation == 'E')
		data_t->direction = 0;
	if (data_t->orientation == 'W')
		data_t->direction = 180;
	if (data_t->orientation == 'S')
		data_t->direction = 270;
}

void	check_map(data_t *data_t)
{
	int	i;

	i = 0;
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
			data_t->position_x = i % (data_t->line + 1);
			data_t->position_y = (i / data_t->line);
			give_angle(data_t);
		}
		i++;
	}
	data_t->sub_position_x = 32;
	data_t->sub_position_y = 32;
}
