#include "cub3d.h"

int	error_handling_start(int argc, char **argv)
{
	if (strstr(argv[1], ".cub") == NULL)
	{
		write(1, "ERROR: wrong map extension", 26);
		return (0);
	}
	if (argc == 3 && argv[2] != "--save")
	{
		write(1, "ERROR: wrong arguments", 22);
		return (0);
	}
	return (1);
}

int	accurate_position(data_t *data_t, int i)
{
	if (i == 1)
		return ((data_t->position_x - 1) * 64 + data_t->sub_position_x);
	else if (i == 0)
		return ((data_t->position_y - 1) * 64 + data_t->sub_position_y);
}

int	check_for_obstacle(int x, int y, data_t *data_t)
{
	//add option 2 sprites
	x /= BLOC_SIZE;
	y /= BLOC_SIZE;
	// printf("x: %d y: %d\n", x, y);
	if (data_t->map[(y * (data_t->line + 1)) + x - 1] == '1')
		return (1);
	else
		return (0);
}

void ft_move_updown(data_t *data_t, int m)
{
	printf("%d\n", data_t->position_x);
	printf("%d\n", data_t->position_y);
	// printf("%c\n", data_t->map[]);
	if (m == 0)
	{
		if (data_t->position_y + 1 < data_t->line)
		{
			printf("%c\n", data_t->map[data_t->position_y * data_t->line + data_t->position_x]);
			printf("%c\n",data_t->map[data_t->position_y * data_t->line + data_t->position_x]);
			data_t->map[(data_t->position_y + 1) * data_t->line + data_t->position_x] = data_t->map[data_t->position_y * data_t->line + data_t->position_x];
			data_t->map[data_t->position_y * data_t->line + data_t->position_x] = '0';
			data_t->position_y++;
		}
	}
	else
	{
		data_t->map[(data_t->position_y - 1) * data_t->line + data_t->position_x] = data_t->map[data_t->position_y * data_t->line + data_t->position_x];
		data_t->map[data_t->position_y * data_t->line + data_t->position_x] = '0';
		data_t->position_y--;
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
	else
		write(1, "fail", 4);
	// mlx_destroy_image(data_t->mlx_prog, data_t->mlx_win);
	// data_t->mlx_img = mlx_new_image(data_t->mlx_prog, data_t->res_w, data_t->res_h);
		printf("%s", data_t->map);
	// mlx_clear_window(data_t->mlx_prog, data_t->mlx_win);
	// print_minimap(data_t);
}

void ft_keyboard_release(int key, data_t *data_t)
{
	if (key == KEY_S)
		return ;
	else if (key == KEY_Z)
		return ;
}

int		main(int argc, char **argv)
{
	data_t	data_t[256];

	if (error_handling_start(argc, argv) == 0)
		return (0);
	file_handling(argv[1], data_t);
	check_map(data_t);
	if ((data_t->mlx_prog = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data_t->mlx_win = mlx_new_window(data_t->mlx_prog, data_t->res_w, data_t->res_h, "Cub3D")) == NULL)
		return (EXIT_FAILURE);
	data_t->mlx_img = mlx_new_image(data_t->mlx_prog, data_t->res_w, data_t->res_h);
	printf("%s", data_t->map);
	// new_screen(data_t);
	// print_minimap(data_t);
	mlx_hook(data_t->mlx_win, KEYPRESS, KEYPRESSMASK, &ft_keyboard_press, data_t);
	mlx_hook(data_t->mlx_win, KEYRELEASE, KEYRELEASEMASK, &ft_keyboard_release, data_t);
	mlx_loop(data_t->mlx_prog);




	// sleep (6);
	printf("column %d\n", data_t->column);
	printf("line %d\n", data_t->line);
	printf("%s\n", data_t->tex_N);
	printf("%s", data_t->map);
	printf("%d\n", data_t->wall_size);
	return (0);
}
