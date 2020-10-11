/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking_dir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 19:03:00 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/11 15:34:48 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_n(data_t *t_m, int x, int y)
{
	while (y >= 0)
	{
		if (t_m->maptab[y][x] == '1')
			return (1);
		y--;
	}
	return (0);
}

int		check_s(data_t *t_m, int x, int y)
{
	while (y < t_m->line)
	{
		if (t_m->maptab[y][x] == '1')
			return (1);
		y++;
	}
	return (0);
}

int		check_w(data_t *t_m, int x, int y)
{
	while (x >= 0)
	{
		if (t_m->maptab[y][x] == '1')
			return (1);
		x--;
	}
	return (0);
}

int		check_e(data_t *t_m, int x, int y)
{
	while (x < t_m->column_size[y])
	{
		if (t_m->maptab[y][x] == '1')
			return (1);
		x++;
	}
	return (0);
}
