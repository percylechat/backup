#include "cub3d.h"

//called by get_content in file_handling.c
//creates appropriate integrer for ceiling and floor colors.

unsigned int		color_pixel(int r, int g, int b)
{
	return ((unsigned int)b + (unsigned int)(r<<16) + (unsigned int)(g<<8));
}

int		get_blue(char *line, int i)
{
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		i++;
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == ',')
		i++;
	else
		return (-1);
	return (ft_atoi(&line[i]));
}

int		get_green(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]) != 0)
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == ',')
		i++;
	else
		return (-1);
	return (ft_atoi(&line[i]));
}

void	error_color(data_t *data_t)
{
	ft_putstr_fd("Error\nColors should be separated by commas, each value between 0 and 255", 1);
	if (data_t->tex_N)
		free(data_t->tex_N);
	if (data_t->tex_S)
		free(data_t->tex_S);
	if (data_t->tex_W)
		free(data_t->tex_W);
	if (data_t->tex_E)
		free(data_t->tex_E);
	if (data_t->tex_sprite)
		free(data_t->tex_sprite);
	exit(0);
}

void	get_color(char *line, int i, data_t *data_t)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi(&line[i + 1]);
	g = get_green(line, i + 1);
	b = get_blue(line, i + 1);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		error_color(data_t);
		return;
	}
	if (line[i] == 'C')
		data_t->color_ceiling = color_pixel(r, g, b);
	if (line[i] == 'F')
		data_t->color_floor = color_pixel(r, g, b);
}
