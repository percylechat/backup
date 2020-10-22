/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:33:29 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/22 11:33:40 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_run(t_gnl *t_g)
{
	int		bs;

	bs = ft_chrlen(t_g->buffer, '\n');
	if (bs == 0)
	{
		t_g->reste = ft_substr(t_g->buffer, bs + 1, (ft_chrlen(&t_g->buffer[bs + 1], '\0')));
		t_g->line = NULL;
	}
	else if (bs != -1 && bs != 0)
	{
		t_g->reste = ft_substr(t_g->buffer, bs + 1, (ft_chrlen(&t_g->buffer[bs + 1], '\0')));
		t_g->line = ft_substr(t_g->buffer, 0, bs);
	}
	else
		t_g->line = ft_strdup(t_g->buffer);
	return (t_g->reste);
}
//
// char	*ulti_run(char *reste, char **line, int bs)
// {
// 	char	*temp;
// 	char	*temp1;
//
// 	temp = ft_strdup(*line);
// 	temp1 = ft_substr(reste, 0, bs);
// 	free(*line);
// 	*line = ft_strjoin(temp, temp1);
// 	free(temp);
// 	temp = ft_substr(reste, bs + 1, (ft_chrlen(&reste[bs + 1], '\0')));
// 	free(reste);
// 	reste = ft_strdup(temp);
// 	free(temp1);
// 	free(temp);
// 	return (reste);
// }
//
char	*ft_run_end(t_gnl *t_g)
{
	int		bs;

	bs = ft_chrlen(t_g->buffer, '\n');
	if (bs == 0)
	{
		t_g->reste = ft_substr(t_g->buffer, bs + 1, (ft_chrlen(&t_g->buffer[bs + 1], '\0')));
		t_g->line = NULL;
	}
	else if (bs != -1 && bs != 0)
	{
		t_g->reste = ft_substr(t_g->buffer, bs + 1, (ft_chrlen(&t_g->buffer[bs + 1], '\0')));
		t_g->line = ft_substr(t_g->buffer, 0, bs);
	}
	else
	{
		t_g->line = ft_strdup(t_g->buffer);
		t_g->reste = NULL;
	}
	return (t_g->reste);
}

int		ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_chrlen(const char *s, char c)
{
	int		i;

	i = 0;
	if (!s || s == NULL)
		return (-1);
	if (c == '\0')
	{
		while (s[i])
			i++;
		return (i);
	}
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		get_next_line(int fd, t_gnl *t_g)
{
	int			res;

	if (!(read(fd, t_g->reste, 0) == 0))
		return (-1);
	if ((res = read(fd, t_g->buffer, BS)) > 0)
	{
		t_g->buffer[res] = '\0';
		t_g->reste = ft_run(t_g);
		if (ft_chrlen(t_g->buffer, '\n') != -1)
			return (1);
	}
	free(t_g->buffer);
	t_g->buffer = ft_strdup(t_g->reste);
	free(t_g->reste);
	// free(t_g->line);
	while (t_g->reste != NULL)
	{
		t_g->reste = ft_run_end(t_g);
		// free(t_g->buffer);
		return (1);
	}
	return (0);
}
