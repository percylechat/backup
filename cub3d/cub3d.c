#include "cub3d.h"

//beginning of an error handling protocol. Called in Main.
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

//Called by drawRays3d in raycasting.c
//check in the map if the coordonates contain a wall or not. To be improved with sprite detection.
int	check_for_obstacle(int x, int y, data_t *data_t)
{
		// write(1, "ok", 2);
	// printf("x: %d y:%d\n", x, y);
	if (x < 0 || y < 0 || x > data_t->column_size[y] || y >= data_t->line)
		return (0);
	if (data_t->maptab[y][x] == '1')
		return (1);
	else
		return (0);
}

// IS main
// first initialize image, then starts controls loop.
int		main(int argc, char **argv)
{
	data_t	data_t[256];

int i = 0;

	if (error_handling_start(argc, argv) == 0)
		return (0);
	file_handling(argv[1], data_t);
		printf("map :%s\n", data_t->map);
		// printf("%d\n", data_t->line);
		// printf("%d\n", data_t->column);
	check_map(data_t);
	// while (data_t->maptab[i])
	// printf("tab :%s\n", data_t->maptab[0]);
	if ((data_t->mlx_prog = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data_t->mlx_win = mlx_new_window(data_t->mlx_prog, data_t->res_w, data_t->res_h, "Cub3D")) == NULL)
		return (EXIT_FAILURE);
	data_t->mlx_img = mlx_new_image(data_t->mlx_prog, data_t->res_w, data_t->res_h);
	drawRays3d(data_t);
	mlx_hook(data_t->mlx_win, KEYPRESS, KEYPRESSMASK, &ft_keyboard_press, data_t);
	mlx_hook(data_t->mlx_win, KEYRELEASE, KEYRELEASEMASK, &ft_keyboard_release, data_t);
	mlx_loop(data_t->mlx_prog);
	return (0);
}
