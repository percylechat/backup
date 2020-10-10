/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:33:29 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/10 18:40:01 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*new_buffer(char *buffer, char *reste)
{
	char *temp;

	if (reste[0] != '\0')
	{
		temp = ft_strdup(buffer);
		free(buffer);
		buffer = ft_strjoin(reste, temp);
		free(temp);
		reste[0] = '\0';
	}
	return (buffer);
}

char	*ft_run(char *reste, char *buffer, char **line)
{
	int		bs;
	char	*temp;
	char	*sub;

	bs = ft_custom_strchr(buffer);
	free(reste);
	if (bs == 0)
	{
		reste = ft_substr(buffer, bs + 1, (ft_strlen(&buffer[bs + 1])));
		if (!(*line = malloc(1)))
			return (NULL);
		*line[0] = '\0';
	}
	else if (bs != -1 && bs != 0)
	{
		reste = ft_substr(buffer, bs + 1, (ft_strlen(&buffer[bs + 1])));
		temp = ft_strdup(*line);
		sub = ft_substr(buffer, 0, bs);
		*line = ft_strjoin(temp, sub);
		free(temp);
		free(sub);
	}
	else
		reste = ft_strdup(buffer);
	return (reste);
}

char	*ulti_run(char *reste, char **line, int bs)
{
	char	*temp;
	char	*temp1;

	temp = ft_strdup(*line);
	temp1 = ft_substr(reste, 0, bs);
	free(*line);
	*line = ft_strjoin(temp, temp1);
	free(temp);
	temp = ft_substr(reste, bs + 1, (ft_strlen(&reste[bs + 1])));
	free(reste);
	reste = ft_strdup(temp);
	free(temp1);
	free(temp);
	return (reste);
}

char	*ft_run_end(char *reste, char **line)
{
	int		bs;
	char	*temp;

	bs = ft_custom_strchr(reste);
	if (bs == 0)
	{
		temp = ft_substr(reste, bs + 1, (ft_strlen(&reste[bs + 1])));
		free(reste);
		reste = ft_strdup(temp);
		*line = malloc(1);
		*line[0] = '\0';
		free(temp);
	}
	else if (bs != -1 && bs != 0)
		reste = ulti_run(reste, line, bs);
	else
	{
		temp = ft_strdup(*line);
		free(*line);
		*line = ft_strjoin(temp, reste);
		free(reste);
		reste = NULL;
		free(temp);
	}
	return (reste);
}

int		get_next_line(int fd, char **line)
{
	char		*buffer;
	int			res;
	static char	*reste = NULL;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || !(buffer = malloc(sizeof(char) *
BUFFER_SIZE + 1)))
		return (-1);
	*line = NULL;
	if (!reste)
	{
		reste = malloc(1);
		reste[0] = '\0';
	}
	while ((res = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[res] = '\0';
		buffer = new_buffer(buffer, reste);
		reste = ft_run(reste, buffer, line);
		if (ft_custom_strchr(buffer) != -1)
		{
			free(buffer);
			return (1);
		}
	}
	free(buffer);
	while ((reste = ft_run_end(reste, line)) != NULL)
		return (1);
	free(reste);
	return (0);
}
