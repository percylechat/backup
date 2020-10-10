#include "cub3d.h"

void	get_res(char *line, int i, data_t *data_t)
{
	data_t->res_w = ft_atoi(&line[i + 1]);
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		i++;
	data_t->res_h = ft_atoi(&line[i]);
	if (data_t->res_w < 200)
		data_t->res_w = 200;
	if (data_t->res_h < 200)
		data_t->res_h = 200;
}

void 	fill_map(char *line, data_t *data_t)
{
	char	*temp;

	if (line[0] != '\0' && line[0] != '\n')
	{
		if (data_t->line == 0)
		{
			data_t->map = ft_strdup(line);
			data_t->column = ft_strlen(line);
		}
		else
		{
			temp = ft_strdup(data_t->map);
			free(data_t->map);
			data_t->map = ft_strjoin(temp, line);
			free(temp);
			if (ft_strlen(line) > data_t->column)
				data_t->column = ft_strlen(line);
		}
		data_t->column_size[data_t->line] = ft_strlen(line);
		data_t->line++;
	}
}

void	get_content(char *line, data_t *data_t)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'C' || line[i] == 'F')
		get_color(line, i, data_t);
	else if (line[i] == 'R')
		get_res(line, i, data_t);
	else if (line[i] == 'N')
		data_t->tex_N = ft_strtrim(&line[i + 2], " ");
	else if (line[i] == 'W')
		data_t->tex_W = ft_strtrim(&line[i + 2], " ");
	else if (line[i] == 'E')
		data_t->tex_E = ft_strtrim(&line[i + 2], " ");
	else if (line[i] == 'S' && line[i + 1] == 'O')
		data_t->tex_S = ft_strtrim(&line[i + 2], " ");
	else if (line[i] == 'S')
		data_t->tex_sprite = ft_strtrim(&line[i + 1], " ");
	else
		fill_map(line, data_t);
}

//WARNING absolut path
void	file_handling(char *name, data_t *data_t)
{
	int		fd;
	char	*line;

	data_t->column = 0;
	data_t->line = 0;
	if ((fd = open(name, O_RDONLY)) == -1)
	{
		ft_putstr_fd("Error\nCan't open map file", 1);
		return ;
	}
	while (get_next_line(fd, &line) != 0)
	{
		if (line)
		get_content(line, data_t);
		free(line);
	}
	if (line != NULL)
		get_content(line, data_t);
	free(line);
	close(fd);
}
