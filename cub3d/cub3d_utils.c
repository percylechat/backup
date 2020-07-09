#include "cub3d.h"

void	get_res(char *line, int i, data_t *data_t)
{
	char	res[5];
	char	res2[5];
	int		j;

	j = 0;
	while (ft_isdigit(line[i]) == 0)
		i++;
 	while (ft_isdigit(line[i]) != 0)
		res[j++] = line[i++];
	res[j] = '\0';
	data_t->res_w = ft_atoi(res);
	j = 0;
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		res2[j++] = line[i++];
	res[j] = '\0';
	data_t->res_h = ft_atoi(res2);
}

void	give_angle(data_t *data_t)
{
	if (data_t->orientation == 'N')
		data_t->direction_x = 0;
		data_t->direction_y = -1;
		data_t->camera_x = 2 * atan(0.66/1.0);
		data_t->camera_y = 0;
	if (data_t->orientation == 'E')
		data_t->direction_x = -1;
		data_t->direction_y = 0;
		data_t->camera_x = 0;
		data_t->camera_y = 2 * atan(0.66/1.0);
	if (data_t->orientation == 'W')
		data_t->direction_x = 1;
		data_t->direction_y = 0;
		data_t->camera_x = 0;
		data_t->camera_y = 2 * atan(0.66/1.0);
	if (data_t->orientation == 'S')
		data_t->direction_x = 0;
		data_t->direction_y = 1;
		data_t->camera_x = -(2 * atan(0.66/1.0));
		data_t->camera_y = 0;
}
