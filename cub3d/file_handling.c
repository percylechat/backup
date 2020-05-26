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

void	fix_line(data_t *data_t, int k)
{
	char	*temp;
	int		i;
	char	*tempbis;

	i = 0;
	if (!(temp = malloc(sizeof(char) * ((data_t->column - k) + 1))))
		return ;
	while (i < data_t->column - k)
	{
		temp[i] = ' ';
		i++;
	}
	temp[i] = '\0';
	tempbis = ft_strjoin(data_t->map, temp);
	free (data_t->map);
	data_t->map = strdup(tempbis);
	free(tempbis);
}

void	fix_lines_before(data_t *data_t, int k)
{
	int		i;
	int		j;
	int		m;
	char	*temp;

	i = 0;
	j = 0;
	m = k - data_t->column;
	if (!(temp = malloc(sizeof(char) * ((k + 1) * data_t->line))))
		return ;
	while (data_t->map[i])
	{
		if (data_t->map[i] == '\n')
		{
			while (m > 0)
			{
				m--;
				temp[j++] = ' ';
			}
		m = k - data_t->column;
		}
	temp[j++] = data_t->map[i++];
	}
	temp[j] = '\0';
	free(data_t->map);
	data_t->map = ft_strdup(temp);
	free(temp);
}

void	fill_map(char *line, data_t *data_t)
{
	int		k;
	char	*temp;

	k = ft_strlen(line);
	if (k == 1 && line[0] == '\n')
		return;
	if (k > data_t->column)
	{
		if (data_t->line > 0)
			fix_lines_before(data_t, k);
		data_t->column = k;
	}
	if (data_t->line == 0)
		data_t->map = ft_strdup(line);
	else
	{
		temp = ft_strdup(data_t->map);
		free (data_t->map);
		data_t->map = ft_strjoin_map(temp, line);
		free(temp);
	}
	if (data_t->column > k)
		fix_line(data_t, k);
	data_t->line++;
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
}
