/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:21:50 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/12 15:55:03 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	color_pixel(int r, int g, int b)
{
	return ((unsigned int)b + (unsigned int)(r << 16) + (unsigned int)(g << 8));
}

int				get_blue(char *line, int i)
{
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		i++;
	while (ft_isdigit(line[i]) == 0)
		i++;
	while (ft_isdigit(line[i]) != 0)
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == ',')
		i++;
	else
		return (-1);
	return (ft_atoi(&line[i]));
}

int				get_green(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]) != 0)
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == ',')
		i++;
	else
		return (-1);
	return (ft_atoi(&line[i]));
}

void			get_color(char *line, int i, t_main *t_m)
{
	int	r;
	int	g;
	int	b;

	b = ft_atoi(&line[i + 1]);
	g = get_green(line, i + 1);
	r = get_blue(line, i + 1);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		error_color(t_m);
		return ;
	}
	if (line[i] == 'C')
	{
		t_m->color_ceiling.r = r;
		t_m->color_ceiling.g = g;
		t_m->color_ceiling.b = b;
	}
	if (line[i] == 'F')
	{
		t_m->color_floor.b = b;
		t_m->color_floor.g = g;
		t_m->color_floor.r = r;
	}
}
