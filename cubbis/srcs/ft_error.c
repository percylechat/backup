/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:31:55 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/22 19:09:08 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_quit_map(t_main *t_m, char *str)
{
	int i;

	i = 0;
	ft_putstr_fd(str, 1);
	free(t_m->tex_n);
	free(t_m->tex_s);
	free(t_m->tex_w);
	free(t_m->tex_e);
	free(t_m->tex_sprite);
	free(t_m->map);
	while (i < t_m->line + 1)
		free(t_m->maptab[i++]);
	free(t_m->maptab);
	if (t_m->sprite_spot)
		free(t_m->sprite_spot);
	exit(0);
}

int		error_handling_start(int argc, char **argv)
{
	if (argc > 3 || argc < 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments", 1);
		return (0);
	}
	else if (strstr(argv[1], ".cub") == NULL)
	{
		ft_putstr_fd("Error\nWrong map extension", 1);
		return (0);
	}
	else if (argc == 3 && ft_issave(argv[2]) != 1)
	{
		ft_putstr_fd("Error\nWrong option", 1);
		return (0);
	}
	return (1);
}

void	error_sanity_check(t_main *t_m)
{
	ft_putstr_fd("Error\nIncomplete map data.", 1);
	if (t_m->tex_n)
		free(t_m->tex_n);
	if (t_m->tex_s)
		free(t_m->tex_s);
	if (t_m->tex_w)
		free(t_m->tex_w);
	if (t_m->tex_e)
		free(t_m->tex_e);
	if (t_m->tex_sprite)
		free(t_m->tex_sprite);
	free(t_m->map);
	exit(0);
}

void	error_color(t_main *t_m, char c)
{
	if (t_m->color_floor.r == 500 && c == 'F')
		ft_putstr_fd("Error\nFloor color missing", 1);
	else if (t_m->color_ceiling.r == 500 && c == 'C')
		ft_putstr_fd("Error\nCeiling color missing", 1);
	else
		ft_putstr_fd("Error\nColors should be separated by commas, \
each value between 0 and 255", 1);
	if (t_m->tex_n != NULL)
		free(t_m->tex_n);
	if (t_m->tex_s != NULL)
		free(t_m->tex_s);
	if (t_m->tex_w != NULL)
		free(t_m->tex_w);
	if (t_m->tex_e != NULL)
		free(t_m->tex_e);
	if (t_m->tex_sprite != NULL)
		free(t_m->tex_sprite);
	if (t_m->map != NULL)
		free(t_m->map);
	exit(0);
}

void	error_res(t_main *t_m)
{
	if (t_m->res_w == -1 || t_m->res_h == -1)
		ft_putstr_fd("Error\nResolution missing", 1);
	else
		ft_putstr_fd("Error\nResolution can't be negative", 1);
	if (t_m->tex_n != NULL)
		free(t_m->tex_n);
	if (t_m->tex_s != NULL)
		free(t_m->tex_s);
	if (t_m->tex_w != NULL)
		free(t_m->tex_w);
	if (t_m->tex_e != NULL)
		free(t_m->tex_e);
	if (t_m->tex_sprite != NULL)
		free(t_m->tex_sprite);
	if (t_m->map)
		free(t_m->map);
	exit(0);
}
