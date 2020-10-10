/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:10:47 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/10 18:17:23 by budal-bi         ###   ########.fr       */
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

void	give_angle_EW(data_t *data_t)
{
	data_t->direction_y = 0;
	data_t->camera_x = 0;
	if (data_t->orientation == 'E')
	{
		data_t->direction_x = 1;
		data_t->camera_y = 2 * atan(0.66/1.0);
	}
	else
	{
		data_t->direction_x = -1;
		data_t->camera_y = -(2 * atan(0.66/1.0));
	}
}

void	give_angle(data_t *data_t)
{
	if (data_t->orientation == 'E' || data_t->orientation == 'W')
	{
		give_angle_EW(data_t);
		return ;
	}
	data_t->direction_x = 0;
	data_t->camera_y = 0;
	if (data_t->orientation == 'N')
	{
		data_t->direction_y = -1;
		data_t->camera_x = 2 * atan(0.66/1.0);
	}
	else
	{
		data_t->direction_y = 1;
		data_t->camera_x = -(2 * atan(0.66/1.0));
	}
}

int		check_for_obstacle(int x, int y, data_t *data_t, t_sprite *t_sprite)
{
	if (x < 0 || y < 0 || x > data_t->column_size[y] || y >= data_t->line)
		return (0);
	if (data_t->maptab[y][x] == '1')
		return (1);
	if (data_t->maptab[y][x] == '2')
	{
		t_sprite->is_sprite = 1;
		return (0);
	}
	else
		return (0);
}

int		new_image(data_t *data_t)
{
	if ((data_t->mlx_img = mlx_new_image(data_t->mlx_prog, data_t->res_w,
data_t->res_h)) == NULL)
	{
		ft_quit_map(data_t, "Error\nFailed to create image");
		return (0);
	}
	data_t->img.content = mlx_get_data_addr(data_t->mlx_img ,
&data_t->img.bits_per_pixel, &data_t->img.size_line, &data_t->img.endian);
	return (1);
}
