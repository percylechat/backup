/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking_dir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 19:03:00 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/25 11:16:21 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_rotate(t_main *t_m)
{
	if (t_m->direction_x > 1)
		t_m->direction_x = ((t_m->direction_x - 1) - 1) * -1;
	if (t_m->direction_y > 1)
		t_m->direction_y = ((t_m->direction_y - 1) - 1) * -1;
	if (t_m->direction_x < -1)
		t_m->direction_x = ((t_m->direction_x + 1) + 1) * -1;
	if (t_m->direction_y < -1)
		t_m->direction_y = ((t_m->direction_y + 1) + 1) * -1;
}

int		check_n(t_main *t_m, int x, int y)
{
	while (y >= 0)
	{
		if (!t_m->maptab[y][x])
			return (0);
		else
		{
			if (t_m->maptab[y][x] == '1')
				return (1);
		}
		y--;
	}
	return (0);
}

int		check_s(t_main *t_m, int x, int y)
{
	while (y < t_m->line)
	{
		if (!t_m->maptab[y][x])
			return (0);
		else
		{
			if (t_m->maptab[y][x] == '1')
				return (1);
		}
		y++;
	}
	return (0);
}

int		check_w(t_main *t_m, int x, int y)
{
	while (x >= 0)
	{
		if (!t_m->maptab[y][x])
			return (0);
		else
		{
			if (t_m->maptab[y][x] == '1')
				return (1);
		}
		x--;
	}
	return (0);
}

int		check_e(t_main *t_m, int x, int y)
{
	while (x < t_m->column_size[y])
	{
		if (!t_m->maptab[y][x])
			return (0);
		else
		{
			if (t_m->maptab[y][x] == '1')
				return (1);
		}
		x++;
	}
	return (0);
}
