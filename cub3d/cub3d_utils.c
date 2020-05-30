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
		data_t->direction = 90;
	if (data_t->orientation == 'E')
		data_t->direction = 0;
	if (data_t->orientation == 'W')
		data_t->direction = 180;
	if (data_t->orientation == 'S')
		data_t->direction = 270;
}
