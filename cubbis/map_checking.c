/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:57:53 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/10 18:57:55 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_roundup(data_t *data_t, int x, int y)
{
	char	*add;
	char *temp;

	if (!(add = malloc(sizeof(char) * 3)))
		return;
	add[0] = y;
	add[1] = x;
	add[2] = '\0';
	data_t->tot_sprite += 1;
	if (!data_t->sprite_spot)
	{
		data_t->sprite_spot = ft_strdup(add);
		temp = NULL;
	}
	else
	{
		temp = ft_strjoin(data_t->sprite_spot, add);
		free(data_t->sprite_spot);
		data_t->sprite_spot = ft_strdup(temp);
	}
	free(temp);
	free(add);
}

int 	init_map(data_t *data_t, int y, int x)
{
	if (((check_N(data_t, x, y) + check_S(data_t, x, y) + check_E(data_t, x, y)
+ check_W(data_t, x, y)) != 4 && data_t->maptab[y][x] != '1' &&
data_t->maptab[y][x] != ' ') || (data_t->maptab[y][x] != '0' &&
data_t->maptab[y][x] != 'W' && data_t->maptab[y][x] != 'N' &&
data_t->maptab[y][x] != 'S' && data_t->maptab[y][x] != 'E' &&
data_t->maptab[y][x] != '2' && data_t->maptab[y][x] != '1' &&
data_t->maptab[y][x] != ' '))
		return (-1);
	if (data_t->maptab[y][x] == 'W' || data_t->maptab[y][x] == 'N' ||
data_t->maptab[y][x] == 'S' || data_t->maptab[y][x] == 'E')
	{
		data_t->orientation = data_t->maptab[y][x];
		data_t->position_x = x + 0.5;
		data_t->position_y = y + 0.5;
		give_angle(data_t);
	}
	if (data_t->maptab[y][x] == '2')
		sprite_roundup(data_t, x, y);
	return (0);
}

int		sanity_check(data_t *data_t)
{
	if (!data_t->res_w || !data_t->res_h || !data_t->tex_S || !data_t->tex_E ||
!data_t->tex_N || !data_t->tex_W || !data_t->tex_sprite || !data_t->map ||
!data_t->color_floor.r || !data_t->color_ceiling.r)
		return (1);
	return (0);
}

void	check_map(data_t *data_t)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (sanity_check(data_t) != 0)
	{
		error_sanity_check(data_t);
		return;
	}
	data_t->maptab = ft_split_map(data_t);
	while (y < data_t->line)
	{
		while (x < data_t->column_size[y])
		{
			if (init_map(data_t, y, x) != 0)
			{
				ft_quit_map(data_t, "Error\nInvalid map");
				return;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
