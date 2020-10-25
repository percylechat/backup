/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 12:05:49 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/23 12:18:43 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	end_gnl(t_gnl *t_g)
{
	free(t_g->line);
	free(t_g->buffer);
	close(t_g->fd);
	return ;
}

int		go_line(t_gnl *t_g, t_main *t_m)
{
	while (t_g->deb < t_g->res)
	{
		t_g->end = ft_custom_strchr(&t_g->buffer[t_g->deb]);
		if (t_g->end > 0)
		{
			free(t_g->line);
			t_g->line = ft_substr(t_g->buffer, t_g->deb, t_g->end);
			t_g->check = get_content(t_g->line, t_m, t_g);
			if (t_g->check == 1)
			{
				end_gnl(t_g);
				return (1);
			}
			t_g->deb += t_g->end + 1;
		}
		else if (t_g->end == -1)
		{
			free(t_g->line);
			t_g->line = ft_strdup(t_g->buffer);
			t_g->deb = t_g->res;
		}
		else
			t_g->deb += t_g->end + 1;
	}
	return (0);
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
