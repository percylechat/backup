#include "cub3d.h"

// Called by get_content in file_handling.c
// extract resolution information and put it in struct
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

//called by ft_keyboard_press in move.c
//print black frame to reprint on without artefacts.
void	print_black(data_t *data_t)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < data_t->res_w)
	{
		while (i < data_t->res_h)
		{
			mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, j, i , (1+(1<<16)+(1<<8)));
			i++;
		}
		i = 0;
		j++;
	}
}

// Called by check_map in map_checking.c
// extract angle information in map and gives appropriates information in struct for raycasting.c
void	give_angle(data_t *data_t)
{
	if (data_t->orientation == 'N')
		data_t->direction_x = 0;
		data_t->direction_y = -1;
		data_t->camera_x = 2 * atan(0.66/1.0);
		data_t->camera_y = 0;
	if (data_t->orientation == 'E')
		data_t->direction_x = 1;
		data_t->direction_y = 0;
		data_t->camera_x = 0;
		data_t->camera_y = -(2 * atan(0.66/1.0));
	if (data_t->orientation == 'W')
		data_t->direction_x = -1;
		data_t->direction_y = 0;
		data_t->camera_x = 0;
		data_t->camera_y = 2 * atan(0.66/1.0);
	if (data_t->orientation == 'S')
		data_t->direction_x = 0;
		data_t->direction_y = 1;
		data_t->camera_x = -(2 * atan(0.66/1.0));
		data_t->camera_y = 0;
}
