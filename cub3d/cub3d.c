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

int	check_for_obstacle(int x, int y, data_t *data_t)
{
	//add option 2 sprites
	printf("x: %d y: %d\n", x, y);
	x /= BLOC_SIZE;
	y /= BLOC_SIZE;
	// printf("x: %d y: %d\n", x, y);
	if (data_t->map[(y * (data_t->column)) + x] == '1')
		return (1);
	else
		return (0);
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
	// printf("%s", data_t->map);
	new_screen(data_t);
	// print_minimap(data_t);
	// mlx_hook(data_t->mlx_win, KEYPRESS, KEYPRESSMASK, &ft_keyboard_press, data_t);
	// mlx_hook(data_t->mlx_win, KEYRELEASE, KEYRELEASEMASK, &ft_keyboard_release, data_t);
	// mlx_loop(data_t->mlx_prog);
	sleep (2);
	printf("column %d\n", data_t->column);
	printf("line %d\n", data_t->line);
	printf("%s\n", data_t->tex_N);
	printf("%s", data_t->map);
	printf("%d\n", data_t->wall_size);
	return (0);
}
