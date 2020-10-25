/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:57:53 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/23 12:10:09 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_roundup(t_main *t_m, int x, int y)
{
	char	*add;
	char	*temp;

	if (!(add = malloc(sizeof(char) * 3)))
		return ;
	add[0] = y;
	add[1] = x;
	add[2] = '\0';
	t_m->tot_sprite += 1;
	if (t_m->sprite_spot == NULL)
	{
		t_m->sprite_spot = ft_strdup(add);
		temp = NULL;
	}
	else
	{
		temp = ft_strjoin(t_m->sprite_spot, add);
		free(t_m->sprite_spot);
		t_m->sprite_spot = ft_strdup(temp);
	}
	free(temp);
	free(add);
}

int		init_map(t_main *t_m, int y, int x)
{
	if (((check_n(t_m, x, y) + check_s(t_m, x, y) + check_e(t_m, x, y) +
check_w(t_m, x, y)) != 4 && t_m->maptab[y][x] != '1' &&
t_m->maptab[y][x] != ' ') || (t_m->maptab[y][x] != '0' &&
t_m->maptab[y][x] != 'W' && t_m->maptab[y][x] != 'N' &&
t_m->maptab[y][x] != 'S' && t_m->maptab[y][x] != 'E' &&
t_m->maptab[y][x] != '2' && t_m->maptab[y][x] != '1' &&
t_m->maptab[y][x] != ' '))
		return (-1);
	if (t_m->maptab[y][x] == 'W' || t_m->maptab[y][x] == 'N' ||
t_m->maptab[y][x] == 'S' || t_m->maptab[y][x] == 'E')
	{
		t_m->orientation = t_m->maptab[y][x];
		t_m->position_x = x + 0.5;
		t_m->position_y = y + 0.5;
		give_angle(t_m);
	}
	if (t_m->maptab[y][x] == '2')
		sprite_roundup(t_m, x, y);
	return (0);
}

int		sanity_check(t_main *t_m)
{
	if (t_m->color_ceiling.r == 500)
	{
		error_color(t_m, 'C');
		return (1);
	}
	if (t_m->color_floor.r == 500)
	{
		error_color(t_m, 'F');
		return (1);
	}
	if (!t_m->res_w || !t_m->res_h || !t_m->tex_s || !t_m->tex_e ||
!t_m->tex_n || !t_m->tex_w || !t_m->tex_sprite || !t_m->map ||
!t_m->color_floor.b || !t_m->color_ceiling.b)
		return (1);
	if (t_m->res_w == -1 || t_m->res_h == -1)
	{
		error_res(t_m);
		return (1);
	}
	return (0);
}

void	check_map(t_main *t_m)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (sanity_check(t_m) != 0)
	{
		error_sanity_check(t_m);
		return ;
	}
	t_m->maptab = ft_split_map(t_m);
	while (y < t_m->line)
	{
		while (x < t_m->column_size[y])
		{
			if (init_map(t_m, y, x) != 0)
			{
				ft_quit_map(t_m, "Error\nInvalid map");
				return ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
