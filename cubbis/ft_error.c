/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:31:55 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/12 16:33:19 by budal-bi         ###   ########.fr       */
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
	if (t_m->mlx_prog)
		free(t_m->mlx_prog);
	if (t_m->mlx_win)
		free(t_m->mlx_win);
	if (t_m->mlx_img)
		free(t_m->mlx_img);
	exit(0);
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

void	error_color(t_main *t_m)
{
	ft_putstr_fd("Error\nColors should be separated by commas, each value \
between 0 and 255", 1);
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
	exit(0);
}
