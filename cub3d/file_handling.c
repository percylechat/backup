#include "cub3d.h"

//functions reads map infos and put them in struct.

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

void 	fill_map(char *line, data_t *data_t)
{
	if (line[0] != '\0' && line[0] != '\n')
	{
		if (data_t->line == 0)
		{
			data_t->map = ft_strdup(line);
			data_t->column = ft_strlen(line);
		}
		else
		{
			data_t->map = ft_strjoin(data_t->map, line);
			if (ft_strlen(line) > data_t->column)
				data_t->column = ft_strlen(line);
		}
		data_t->column_size[data_t->line] = ft_strlen(line);
		data_t->line++;
	}
}

//Called by file_handling
//dispatch line acquired by get_next_line to subordinates functions according to beginning of line.
//also deletes spaces because the subject indicates so.
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
		data_t->tex_N = ft_strdup(ft_strtrim(&line[i + 2], " "));
	else if (line[i] == 'W')
		data_t->tex_W = ft_strdup(ft_strtrim(&line[i + 2], " "));
	else if (line[i] == 'E')
		data_t->tex_E = ft_strdup(ft_strtrim(&line[i + 2], " "));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		data_t->tex_S = ft_strdup(ft_strtrim(&line[i + 2], " "));
	else if (line[i] == 'S')
		data_t->tex_sprite = ft_strdup(ft_strtrim(&line[i + 1], " "));
	else
		fill_map(line, data_t);
}

// called by main
// first open file with infos, then copy information in struct bit by bit.
//WARNING absolut path
void	file_handling(char *name, data_t *data_t)
{
	int		fd;
	char	*line;

	data_t->column = 0;
	data_t->line = 0;
	if ((fd = open("/home/budal-bi/Workspace/C/cub3d/map.cub", O_RDONLY)) == -1)
	{
		perror("test");
		write(1, "ERROR: can't open file", 22);
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
