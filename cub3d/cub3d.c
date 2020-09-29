#include "cub3d.h"

int 	ft_issave(char *txt)
{
	if (txt[0] != '-' || txt[1] != '-' || txt[2] != 's' || txt[3] != 'a' || txt[4] != 'v' || txt[5] != 'e')
		return (0);
	return (1);
}

//beginning of an error handling protocol. Called in Main.
int	error_handling_start(int argc, char **argv)
{
	if (argc > 3 || argc < 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments", 1);
		return (0);
	}
	else if (strstr(argv[1], ".cub") == NULL)
	{
		ft_putstr_fd("Error\nWrong map extension", 1);
		return (0);
	}
	else if (argc == 3 && ft_issave(argv[2]) != 1)
	{
		ft_putstr_fd("Error\nWrong option", 1);
		return (0);
	}
	return (1);
}

//Called by drawRays3d in raycasting.c
//check in the map if the coordonates contain a wall or not. To be improved with sprite detection.
int	check_for_obstacle(int x, int y, data_t *data_t, t_sprite *t_sprite)
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

void		ft_quit(data_t *data_t)
{
	mlx_destroy_image(data_t->mlx_prog, data_t->mlx_img);
	mlx_destroy_window(data_t->mlx_prog, data_t->mlx_win);
	exit(0);
}

int 	launch_mlx(data_t *data_t)
{
	if ((data_t->mlx_prog = mlx_init()) == NULL)
	{
		ft_quit_map(data_t, "Error\nFailed to launch Xserver");
		return (0);
	}
	if ((data_t->mlx_win = mlx_new_window(data_t->mlx_prog, data_t->res_w, data_t->res_h, "Cub3D")) == NULL)
	{
		ft_quit_map(data_t, "Error\nFailed to create window");
		return (0);
	}
	if ((data_t->mlx_img = mlx_new_image(data_t->mlx_prog, data_t->res_w, data_t->res_h)) == NULL)
	{
		ft_quit_map(data_t, "Error\nFailed to create image");
		return (0);
	}
}

// IS main
// first initialize image, then starts controls loop.
int		main(int argc, char **argv)
{
	data_t	data_t[256];

	if (error_handling_start(argc, argv) == 0)
		return (0);
	file_handling(argv[1], data_t);
	check_map(data_t);
	if (launch_mlx(data_t) == 0)
		return (0);
	drawRays3d(data_t);
	mlx_hook(data_t->mlx_win, KEYPRESS, KEYPRESSMASK, &ft_keyboard_press, data_t);
	mlx_hook(data_t->mlx_win, KEYRELEASE, KEYRELEASEMASK, &ft_keyboard_release, data_t);
	mlx_loop(data_t->mlx_prog);
	return (0);
}
