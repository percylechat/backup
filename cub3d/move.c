#include "cub3d.h"

void	check_move(data_t *data_t, double temp, double tempbis)
{
	printf(" new x %d\n", (int)data_t->position_x);
	printf(" new y %d\n", (int)data_t->position_y);
	printf(" x %d\n", (int)temp);
	printf(" y %d\n", (int)tempbis);
	//BONUS
	if (check_for_obstacle(data_t->position_x, data_t->position_y, data_t) == 1)
	{
		data_t->position_x =  temp;
		data_t->position_y = tempbis;
	}
	if ((int)data_t->position_x != (int)temp || (int)data_t->position_y != (int)tempbis)
	{
		data_t->map[(int)data_t->position_y * (data_t->column + 1) + (int)data_t->position_x] = data_t->orientation;
		data_t->map[(int)tempbis * (data_t->column + 1) + (int)temp] = '0';
	}
}

void ft_move_updown(data_t *data_t, int m)
{
	// printf("%f\n", data_t->position_x);
	// printf("%f\n", data_t->position_y);
	// printf("%c\n", data_t->map[]);
	double temp;
	double tempbis;

	temp = data_t->position_x;
	tempbis = data_t->position_y;
	if (m == 0)
	{
		data_t->position_x -= data_t->direction_x * (0.5);
		data_t->position_y -= data_t->direction_y * (0.5);
	}
	else
	{
		data_t->position_x += data_t->direction_x * (0.5);
		data_t->position_y += data_t->direction_y * (0.5);
	}
	check_move(data_t, temp, tempbis);
	// write(1, "ok", 2);
}

void ft_move_leftright(data_t *data_t, int m)
{
	// printf("%f\n", data_t->position_x);
	// printf("%f\n", data_t->position_y);
	// printf("%c\n", data_t->map[]);
	double temp;
	double tempbis;

	temp = data_t->position_x;
	tempbis = data_t->position_y;
	if (m == 0)
	{
		data_t->position_x += data_t->direction_y * (0.5);
		data_t->position_y += data_t->direction_x * (0.5);
	}
	else
	{
		data_t->position_x -= data_t->direction_y * (0.5);
		data_t->position_y -= data_t->direction_x * (0.5);
	}
	check_move(data_t, temp, tempbis);
	write(1, "ok", 2);
}

void	ft_rotate(data_t *data_t, int m)
{
	double temp;

	if (m == 1)
	{
		temp = data_t->direction_x;
		data_t->direction_x = data_t->direction_x * cos(0.5) - data_t->direction_y * sin(0.5);
		data_t->direction_y = temp * sin(0.5) + data_t->direction_y * cos(0.5);
		temp = data_t->camera_x;
		data_t->camera_x = data_t->camera_x * cos(0.5) - data_t->camera_y * sin(0.5);
		data_t->camera_y = temp * sin(0.5) + data_t->camera_y * cos(0.5);
	}
	else
	{
		temp = data_t->direction_x;
		data_t->direction_x = data_t->direction_x * cos(-0.5) - data_t->direction_y * sin(-0.5);
		data_t->direction_y = temp * sin(-0.5) + data_t->direction_y * cos(-0.5);
		temp = data_t->camera_x;
		data_t->camera_x = data_t->camera_x * cos(-0.5) - data_t->camera_y * sin(-0.5);
		data_t->camera_y = temp * sin(-0.5) + data_t->camera_y * cos(-0.5);
	}
}

void ft_keyboard_press(int key, data_t *data_t)
{
	printf("%d\n", key);
	if (key == KEY_S)
		ft_move_updown(data_t, 0);
	else if (key == KEY_Z)
		ft_move_updown(data_t, 1);
    else if (key == KEY_Q)
        ft_move_leftright(data_t, 0);
    else if (key == KEY_D)
        ft_move_leftright(data_t, 1);
	else if (key == KEY_A)
		ft_rotate(data_t, 1);
	else if (key == KEY_E)
		ft_rotate(data_t, 0);
	else
		write(1, "fail", 4);
	// mlx_destroy_image(data_t->mlx_prog, data_t->mlx_win);
	// data_t->mlx_img = mlx_new_image(data_t->mlx_prog, data_t->res_w, data_t->res_h);
		printf("%s", data_t->map);
	// mlx_clear_window(data_t->mlx_prog, data_t->mlx_win);
	print_black(data_t);
	drawRays3d(data_t);
	print_minimap(data_t);
}

void ft_keyboard_release(int key, data_t *data_t)
{
	if (key == KEY_S)
		return ;
	else
		return ;
}
