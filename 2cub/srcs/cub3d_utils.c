/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:10:47 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/12 15:54:30 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_issave(char *txt)
{
	if (txt[0] != '-' || txt[1] != '-' || txt[2] != 's' || txt[3] != 'a' ||
txt[4] != 'v' || txt[5] != 'e')
		return (0);
	return (1);
}

void	give_angle_ew(t_main *t_m)
{
	t_m->direction_y = 0;
	t_m->camera_x = 0;
	if (t_m->orientation == 'E')
	{
		t_m->direction_x = 1;
		t_m->camera_y = 2 * atan(0.66 / 1.0);
	}
	else
	{
		t_m->direction_x = -1;
		t_m->camera_y = -(2 * atan(0.66 / 1.0));
	}
}

void	give_angle(t_main *t_m)
{
	if (t_m->orientation == 'E' || t_m->orientation == 'W')
	{
		give_angle_ew(t_m);
		return ;
	}
	t_m->direction_x = 0;
	t_m->camera_y = 0;
	if (t_m->orientation == 'N')
	{
		t_m->direction_y = -1;
		t_m->camera_x = 2 * atan(0.66 / 1.0);
	}
	else
	{
		t_m->direction_y = 1;
		t_m->camera_x = -(2 * atan(0.66 / 1.0));
	}
}

int		check_for_obstacle(int x, int y, t_main *t_m, t_sprite *t_sp)
{
	if (x < 0 || y < 0 || x > t_m->column_size[y] || y >= t_m->line)
		return (0);
	if (t_m->maptab[y][x] == '1')
		return (1);
	if (t_m->maptab[y][x] == '2')
	{
		t_sp->is_sprite = 1;
		return (0);
	}
	else
		return (0);
}

int		new_image(t_main *t_m)
{
	if ((t_m->mlx_img = mlx_new_image(t_m->mlx_prog, t_m->res_w, t_m->res_h)) ==
	NULL)
	{
		ft_quit_map(t_m, "Error\nFailed to create image");
		return (0);
	}
	t_m->img.content = mlx_get_data_addr(t_m->mlx_img, &t_m->img.bits_per_pixel,
	&t_m->img.sl, &t_m->img.endian);
	return (1);
}
