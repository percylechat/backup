#include "cub3d.h"

//called by get_content in file_handling.c
//creates appropriate integrer for ceiling and floor colors.

int		color_pixel(int r, int g, int b)
{
	return (b + (r<<16) + (g<<8));
}

int		get_blue(char *line, int i)
{
	char	clr[5];
	int		j;

	j = 0;
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		i++;
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		i++;
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		clr[j++] = line[i++];
	if (j > 3)
	{
		write(1, "ERROR: wrong color input", 24);
		return (NULL);
	}
	clr[j] = '\0';
	return (ft_atoi(clr));
}

int		get_green(char *line, int i)
{
	char	clr[5];
	int		j;

	j = 0;
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		i++;
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		clr[j++] = line[i++];
	if (j > 3)
	{
		write(1, "ERROR: wrong color input", 24);
		return (NULL);
	}
	clr[j] = '\0';
	return (ft_atoi(clr));
}

int		get_red(char *line, int i)
{
	char	clr[5];
	int		j;

	j = 0;
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		clr[j++] = line[i++];
	if (j > 3)
	{
		write(1, "ERROR: wrong color input", 24);
		return (NULL);
	}
	clr[j] = '\0';
	return (ft_atoi(clr));
}

void	get_color(char *line, int i, data_t *data_t)
{
	int		r;
	int		g;
	int		b;

	r = get_red(line, i);
	g = get_green(line, i);
	b = get_blue(line, i);
	if (line[i] == 'C')
		data_t->color_ceiling = color_pixel(r, g, b);
	if (line[i] == 'F')
		data_t->color_floor = color_pixel(r, g, b);
}
