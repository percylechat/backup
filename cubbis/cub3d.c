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
	int i;

	i = 0;
	free(data_t->tex_N);
	free(data_t->tex_S);
	free(data_t->tex_W);
	free(data_t->tex_E);
	free(data_t->tex_sprite);
	free(data_t->map);
	while (i < data_t->line + 1)
		free(data_t->maptab[i++]);
	free(data_t->maptab);
	if (data_t->sprite_spot)
		free(data_t->sprite_spot);
	mlx_destroy_image(data_t->mlx_prog, data_t->mlx_img);
	mlx_destroy_image(data_t->mlx_prog, data_t->N_tex.address);
	mlx_destroy_image(data_t->mlx_prog, data_t->S_tex.address);
	mlx_destroy_image(data_t->mlx_prog, data_t->E_tex.address);
	mlx_destroy_image(data_t->mlx_prog, data_t->W_tex.address);
	mlx_destroy_window(data_t->mlx_prog, data_t->mlx_win);
	free(data_t->mlx_prog);
	exit(0);
}

int		new_image(data_t *data_t)
{
	if ((data_t->mlx_img = mlx_new_image(data_t->mlx_prog, data_t->res_w, data_t->res_h)) == NULL)
	{
		ft_quit_map(data_t, "Error\nFailed to create image");
		return (0);
	}
	data_t->img.content = mlx_get_data_addr(data_t->mlx_img ,&data_t->img.bits_per_pixel, &data_t->img.size_line, &data_t->img.endian);
	return (1);
}

int 	launch_mlx(data_t *data_t)
{
	int rh;
	int rw;

	if ((data_t->mlx_prog = mlx_init()) == NULL)
	{
		ft_quit_map(data_t, "Error\nFailed to launch Xserver");
		return (0);
	}
	// mlx_get_screen_size(data_t->mlx_prog, &rw, &rh);
	// if (data_t->res_w > rw)
		// data_t->res_w = rw;
	// if (data_t->res_h > rh)
		// data_t->res_h = rh;
	if ((data_t->mlx_win = mlx_new_window(data_t->mlx_prog, data_t->res_w, data_t->res_h, "Cub3D")) == NULL)
	{
		ft_quit_map(data_t, "Error\nFailed to create window");
		return (0);
	}
	if (new_image(data_t) == 0)
		return (0);
	data_t->N_tex = get_tex_N(data_t);
	if (data_t->N_tex.address == NULL)
	{
		ft_quit_map(data_t, "Error\nCannot open North texture");
		return (0);
	}
	data_t->S_tex = get_tex_S(data_t);
	if (data_t->S_tex.address == NULL)
	{
		ft_quit_map(data_t, "Error\nCannot open South texture");
		return (0);
	}
	data_t->E_tex = get_tex_E(data_t);
	if (data_t->E_tex.address == NULL)
	{
		ft_quit_map(data_t, "Error\nCannot open East texture");
		return (0);
	}
	data_t->W_tex = get_tex_W(data_t);
	if (data_t->W_tex.address == NULL)
	{
		ft_quit_map(data_t, "Error\nCannot open West texture");
		return (0);
	}
	return (1);
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
	if (argc == 3 && ft_issave(argv[2]) == 1)
	{
		ft_save(data_t);
		return (0);
	}
	mlx_hook(data_t->mlx_win, KEYPRESS, KEYPRESSMASK, ft_keyboard_press, &data_t);
	// mlx_hook(data_t->mlx_win, KEYRELEASE, KEYRELEASEMASK, &ft_keyboard_release, &data_t);
	mlx_loop(data_t->mlx_prog);
	return (0);
}
