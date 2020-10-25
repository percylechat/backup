/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:24:25 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/23 12:17:50 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_res(char *line, int i, t_main *t_m, t_gnl *t_g)
{
	t_m->res_w = ft_atoi(&line[i + 1]);
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		i++;
	t_m->res_h = ft_atoi(&line[i]);
	if (t_m->res_w <= 0 || t_m->res_h <= 0)
	{
		end_gnl(t_g);
		error_res(t_m);
		return (1);
	}
	return (0);
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

int		get_content(char *line, t_main *t_m, t_gnl *t_g)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R')
		return (get_res(line, i, t_m, t_g));
	else if (line[i] == 'C' || line[i] == 'F')
		return (get_color(line, i, t_m));
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
	return (0);
}

int		ft_custom_strchr(const char *s)
{
	int		i;

	i = 0;
	if (!s || s == NULL)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		file_handling(char *name, t_main *t_m)
{
	t_gnl	t_g[1];

	t_g->line = NULL;
	t_g->deb = 0;
	t_g->fd = open(name, O_RDONLY, O_NOFOLLOW);
	if ((t_g->fd == -1) || (!(t_g->buffer = malloc(sizeof(char) * BS + 1))))
	{
		ft_putstr_fd("Error\nCan't open map file", 1);
		return (1);
	}
	t_g->res = read(t_g->fd, t_g->buffer, BS);
	if (t_g->res <= 0)
	{
		ft_putstr_fd("Error\nCan't open map file", 1);
		end_gnl(t_g);
		return (1);
	}
	t_g->buffer[t_g->res] = '\0';
	if (go_line(t_g, t_m) == 1)
		return (1);
	end_gnl(t_g);
	return (0);
}
