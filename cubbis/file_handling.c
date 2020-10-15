/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:24:25 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/14 16:21:54 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_res(char *line, int i, t_main *t_m)
{
	t_m->res_w = ft_atoi(&line[i + 1]);
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		i++;
	t_m->res_h = ft_atoi(&line[i]);
	if (t_m->res_w < 200)
		t_m->res_w = 200;
	if (t_m->res_h < 200)
		t_m->res_h = 200;
}

void	fill_map(char *line, t_main *t_m)
{
	char	*temp;

	if (line[0] != '\0' && line[0] != '\n')
	{
		if (t_m->line == 0)
		{
			t_m->map = ft_strdup(line);
			t_m->column = ft_strlen(line);
		}
		else
		{
			temp = ft_strdup(t_m->map);
			free(t_m->map);
			t_m->map = ft_strjoin(temp, line);
			free(temp);
			if (ft_strlen(line) > t_m->column)
				t_m->column = ft_strlen(line);
		}
		t_m->column_size[t_m->line] = ft_strlen(line);
		t_m->line++;
	}
}

void	get_content(char *line, t_main *t_m)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'C' || line[i] == 'F')
		get_color(line, i, t_m);
	else if (line[i] == 'R')
		get_res(line, i, t_m);
	else if (line[i] == 'N')
		t_m->tex_n = ft_strtrim(&line[i + 2], " ");
	else if (line[i] == 'W')
		t_m->tex_w = ft_strtrim(&line[i + 2], " ");
	else if (line[i] == 'E')
		t_m->tex_e = ft_strtrim(&line[i + 2], " ");
	else if (line[i] == 'S' && line[i + 1] == 'O')
		t_m->tex_s = ft_strtrim(&line[i + 2], " ");
	else if (line[i] == 'S')
		t_m->tex_sprite = ft_strtrim(&line[i + 1], " ");
	else
		fill_map(line, t_m);
}

void	file_handling(char *name, t_main *t_m)
{
	int		fd;
	char	*line;
	int		check;

	t_m->column = 0;
	t_m->line = 0;
	if ((fd = open(name, O_RDONLY)) == -1)
	{
		ft_putstr_fd("Error\nCan't open map file", 1);
		return ;
	}
	while ((check = get_next_line(fd, &line)) != 0 && check != -1)
	{
		if (line)
			get_content(line, t_m);
		free(line);
	}
	if (check == -1)
		return ;
	if (line != NULL)
		get_content(line, t_m);
	free(line);
	close(fd);
}
