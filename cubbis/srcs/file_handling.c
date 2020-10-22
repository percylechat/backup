/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:24:25 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/22 15:21:20 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	end_gnl(t_gnl *t_g)
{
	write(1, "errgnl", 6);
	free(t_g->line);
	free(t_g->buffer);
	// free(t_g->reste);
	close(t_g->fd);
	return ;
}

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

	// printf("line; %s\n", line);
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

int	get_content(char *line, t_main *t_m, t_gnl *t_g)
{
	int		i;

	i = 0;
	printf("line: %s\n", line);
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R')
		return (get_res(line, i, t_m, t_g));
	else if (line[i] == 'C' || line[i] == 'F')
		return (get_color(line, i, t_m));//, t_g));
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

void	file_handling(char *name, t_main *t_m)
{
	t_gnl	t_g[1];
	int		check;
	int res;

	t_g->reste = NULL;
	t_g->line = NULL;
	if ((t_g->fd = open(name, O_RDONLY, O_NOFOLLOW)) == -1)
	{
		ft_putstr_fd("Error\nCan't open map file", 1);
		return ;
	}
	if (!(t_g->buffer = malloc(sizeof(char) * BS + 1)))
		return;
	res = read(t_g->fd, t_g->buffer, BS);
	if (res == -1)
		return ;
	if (res == 0)
		return ;
	t_g->buffer[res] = '\0';
	int i = 0;
	// int j = 0;
	while (i < res)
	{
		int end = ft_custom_strchr(&t_g->buffer[i]);
		printf("envoi: %d %d\n", i, end + i);
		if (end > 0)
		{
			free(t_g->line);
			t_g->line = ft_substr(t_g->buffer, i, end);
			check = get_content(t_g->line, t_m, t_g);
			if (check == 1)
			{
				end_gnl(t_g);
				return ;
			}
			i += end + 1;
		}
		else if (end == -1)
		{
			free(t_g->line);
			t_g->line = ft_strdup(t_g->buffer);
			i = res;
		}
		else
			i += end + 1;
		// printf("%d %d %d",i, end, res);
	}
	end_gnl(t_g);
}




	// while ((check = get_next_line(t_g->fd, t_g)) > 0)
	// {
	// 	if (t_g->line)
	// 	{
	// 		res = get_content(t_g->line, t_m, t_g);
	// 		if (res == 1)
	// 			return ;
	// 	}
	// }
	// if (check == -1)
	// {
	// 	free(t_g->line);
	// 	return ;
	// }
	// if (t_g->line != NULL)
	// 	get_content(t_g->line, t_m, t_g);
	// write(1, "lol", 3);
	// end_gnl(t_g);
	// if (!(line = malloc(sizeof(char) * BS + 1)))
	// {
	// 	ft_putstr_fd("Error\nInsufficient memory", 1);
	// 	return;
	// }
	// if ((check = read(fd, line, BS)) <= 0)
	// {
	// 	ft_putstr_fd("Error\nEmpty file", 1);
	// 	return ;
	// }
	// while (line[j])
	// {
	// 	while (k == 0)
	// 		k = ft_custom_strchr(line);
	// 	if (k == -1)
	// 	{
	// 		free(line);
	// 		close(fd);
	// 		return ;
	// 	}
	// 	line[k] = '\0';
	// 	if (get_content(ft_substr(line, j, k), t_m) == 1)
	// 	{
	// 		free(line);
	// 		close(fd);
	// 		return ;
	// 	}
	// 	line[k] = '\n';
	// 	temp = ft_substr(line, k + 1, BS + 1 - k);
	// 	free(line);
	// 	line = ft_strdup(temp);
	// 	free(temp);
	// 	j = k;
	// }
// }
