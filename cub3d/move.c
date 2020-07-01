#include "cub3d.h"

void ft_move_updown(data_t *data_t, int m)
{
	printf("%d\n", data_t->position_x);
	printf("%d\n", data_t->position_y);
	// printf("%c\n", data_t->map[]);
	if (m == 0)
	{
        data_t->position_y--;
        data_t->map[((data_t->column + 1) * (data_t->position_y)) + (data_t->position_x)] = 'N';
        data_t->map[((data_t->column + 1) * (data_t->position_y + 1)) + (data_t->position_x)] = '0';
	}
	else
	{
        data_t->position_y++;
        data_t->map[((data_t->column + 1) * (data_t->position_y)) + (data_t->position_x)] = 'N';
        data_t->map[((data_t->column + 1) * (data_t->position_y - 1)) + (data_t->position_x)] = '0';
	}
	write(1, "ok", 2);
}

void ft_move_leftright(data_t *data_t, int m)
{
	printf("%d\n", data_t->position_x);
	printf("%d\n", data_t->position_y);
	// printf("%c\n", data_t->map[]);
	if (m == 0)
	{
        data_t->position_x--;
        data_t->map[((data_t->column + 1) * (data_t->position_y)) + (data_t->position_x)] = 'N';
        data_t->map[((data_t->column + 1) * (data_t->position_y)) + (data_t->position_x + 1)] = '0';
	}
	else
	{
        data_t->position_x++;
        data_t->map[((data_t->column + 1) * (data_t->position_y)) + (data_t->position_x)] = 'N';
        data_t->map[((data_t->column + 1) * (data_t->position_y)) + (data_t->position_x - 1)] = '0';
	}
	write(1, "ok", 2);
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
	// else if (key == KEY_A)
	// 	ft_rotate(data_t, 1);
	// else if (key == KEY_E)
	// 	ft_rotate(data_t, 0);
	else
		write(1, "fail", 4);
	// mlx_destroy_image(data_t->mlx_prog, data_t->mlx_win);
	// data_t->mlx_img = mlx_new_image(data_t->mlx_prog, data_t->res_w, data_t->res_h);
		printf("%s", data_t->map);
	// mlx_clear_window(data_t->mlx_prog, data_t->mlx_win);
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
