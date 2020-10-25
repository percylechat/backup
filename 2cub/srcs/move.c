/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:16:54 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/14 12:16:26 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_move(t_main *t_m, double temp, double tempbis)
{
	char spot;

	if ((int)t_m->position_x != (int)temp || (int)t_m->position_y !=
(int)tempbis)
	{
		spot = t_m->maptab[(int)t_m->position_y][(int)t_m->position_x];
		t_m->maptab[(int)t_m->position_y][(int)t_m->position_x] =
t_m->orientation;
		t_m->maptab[(int)tempbis][(int)temp] = spot;
	}
}

void	ft_move_updown(t_main *t_m, int m)
{
	double temp;
	double tempbis;

	temp = t_m->position_x;
	tempbis = t_m->position_y;
	if (m == 1)
	{
		t_m->position_x -= t_m->direction_x * (0.5);
		t_m->position_y -= t_m->direction_y * (0.5);
	}
	else if (m == 0)
	{
		t_m->position_x += t_m->direction_x * (0.5);
		t_m->position_y += t_m->direction_y * (0.5);
	}
	check_move(t_m, temp, tempbis);
}

void	ft_move_leftright(t_main *t_m, int m)
{
	double temp;
	double tempbis;

	temp = t_m->position_x;
	tempbis = t_m->position_y;
	if (m == 1)
	{
		t_m->position_x += t_m->camera_x * (0.5);
		t_m->position_y += t_m->camera_y * (0.5);
	}
	else
	{
		t_m->position_x -= t_m->camera_x * (0.5);
		t_m->position_y -= t_m->camera_y * (0.5);
	}
	check_move(t_m, temp, tempbis);
}

void	ft_rotate(t_main *t_m, int m)
{
	double temp;

	temp = t_m->direction_x;
	if (m == 0)
	{
		t_m->direction_x = t_m->direction_x * cos(0.5) - t_m->direction_y *
sin(0.5);
		t_m->direction_y = temp * sin(0.5) + t_m->direction_y * cos(0.5);
		temp = t_m->camera_x;
		t_m->camera_x = t_m->camera_x * cos(0.5) - t_m->camera_y * sin(0.5);
		t_m->camera_y = temp * sin(0.5) + t_m->camera_y * cos(0.5);
	}
	else
	{
		t_m->direction_x = t_m->direction_x * cos(-0.5) - t_m->direction_y *
sin(-0.5);
		t_m->direction_y = temp * sin(-0.5) + t_m->direction_y * cos(-0.5);
		temp = t_m->camera_x;
		t_m->camera_x = t_m->camera_x * cos(-0.5) - t_m->camera_y * sin(-0.5);
		t_m->camera_y = temp * sin(-0.5) + t_m->camera_y * cos(-0.5);
	}
	check_rotate(t_m);
}

int		ft_keyboard_press(int key, t_main *t_m)
{
	if (key == KEY_S)
		ft_move_updown(t_m, 0);
	else if (key == KEY_Z)
		ft_move_updown(t_m, 1);
	else if (key == KEY_Q)
		ft_move_leftright(t_m, 0);
	else if (key == KEY_D)
		ft_move_leftright(t_m, 1);
	else if (key == KEY_A)
		ft_rotate(t_m, 1);
	else if (key == KEY_E)
		ft_rotate(t_m, 0);
	else if (key == KEY_ESC)
		ft_quit(t_m);
	mlx_destroy_image(t_m->mlx_prog, t_m->mlx_img);
	if (new_image(t_m) == 0)
	{
		ft_quit_map(t_m, "Error\nFailed to create image");
		return (0);
	}
	raycasting(t_m);
	mlx_put_image_to_window(t_m->mlx_prog, t_m->mlx_win, t_m->mlx_img, 0, 0);
	return (0);
}
