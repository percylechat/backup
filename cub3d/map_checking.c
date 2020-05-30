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

void	check_map(data_t *data_t)
{
	int	i;

	i = 0;
	ft_memmove((void *)&data_t->map[0], (void *)&data_t->map[1], 125);
	data_t->line -= 2;
	data_t->map[data_t->line * (data_t->column + 1)] = '\0';
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
			data_t->position_x = i % (data_t->line);
			data_t->position_y = (i / data_t->line);
			give_angle(data_t);
		}
		i++;
	}
	data_t->sub_position_x = 32;
	data_t->sub_position_y = 32;
}
