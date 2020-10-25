/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:14:51 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/22 18:52:24 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_quit(t_main *t_m)
{
	int i;

	i = 0;
	free(t_m->tex_n);
	free(t_m->tex_s);
	free(t_m->tex_w);
	free(t_m->tex_e);
	free(t_m->tex_sprite);
	free(t_m->map);
	while (i < t_m->line + 1)
		free(t_m->maptab[i++]);
	free(t_m->maptab);
	free(t_m->sprite_spot);
	mlx_destroy_image(t_m->mlx_prog, t_m->mlx_img);
	mlx_destroy_image(t_m->mlx_prog, t_m->n_tex.address);
	mlx_destroy_image(t_m->mlx_prog, t_m->s_tex.address);
	mlx_destroy_image(t_m->mlx_prog, t_m->e_tex.address);
	mlx_destroy_image(t_m->mlx_prog, t_m->w_tex.address);
	mlx_destroy_window(t_m->mlx_prog, t_m->mlx_win);
	free(t_m->mlx_prog);
	exit(0);
}

int		launch_img(t_main *t_m)
{
	if (new_image(t_m) == 0)
	{
		ft_quit_map(t_m, "Error\nCannot open new image");
		return (0);
	}
	t_m->n_tex = get_tex_n(t_m);
	t_m->s_tex = get_tex_s(t_m);
	t_m->e_tex = get_tex_e(t_m);
	t_m->w_tex = get_tex_w(t_m);
	t_m->sp_tex = get_tex_sp(t_m);
	if (t_m->n_tex.address == NULL || t_m->s_tex.address == NULL ||
t_m->e_tex.address == NULL || t_m->w_tex.address == NULL ||
t_m->sp_tex.address == NULL)
	{
		ft_quit_map(t_m, "Error\nCannot open texture");
		return (0);
	}
	return (1);
}

int		launch_mlx(t_main *t_m, int argc, char **argv)
{
	if ((t_m->mlx_prog = mlx_init()) == NULL)
	{
		ft_quit_map(t_m, "Error\nFailed to launch Xserver");
		return (0);
	}
	check_res(t_m);
	if (argc == 3 && ft_issave(argv[2]) == 1)
	{
		if (launch_img(t_m) == 0)
			return (0);
		ft_save(t_m);
		return (0);
	}
	if (launch_img(t_m) == 0)
		return (0);
	if ((t_m->mlx_win = mlx_new_window(t_m->mlx_prog, t_m->res_w, t_m->res_h,
"Cub3D")) == NULL)
	{
		ft_quit_map(t_m, "Error\nFailed to create window");
		return (0);
	}
	return (1);
}

void	init_values(t_main *t_m)
{
	t_m->tot_sprite = 0;
	t_m->sprite_spot = NULL;
	t_m->tex_e = NULL;
	t_m->tex_w = NULL;
	t_m->tex_n = NULL;
	t_m->tex_s = NULL;
	t_m->tex_sprite = NULL;
	t_m->res_w = -1;
	t_m->res_h = -1;
	t_m->position_x = 0;
	t_m->color_ceiling.r = 500;
	t_m->color_floor.r = 500;
	t_m->map = NULL;
	t_m->column = 0;
	t_m->line = 0;
}

int		main(int argc, char **argv)
{
	t_main	t_m[1];

	if (error_handling_start(argc, argv) == 0)
		return (0);
	init_values(t_m);
	if (file_handling(argv[1], t_m) == 1)
		return (0);
	check_map(t_m);
	if (launch_mlx(t_m, argc, argv) == 0)
		return (0);
	if (t_m->position_x == 0)
	{
		ft_quit_map(t_m, "Error\nNo player detected on map");
		return (0);
	}
	raycasting(t_m);
	mlx_put_image_to_window(t_m->mlx_prog, t_m->mlx_win, t_m->mlx_img, 0, 0);
	mlx_hook(t_m->mlx_win, KEYPRESS, KEYPRESSMASK, ft_keyboard_press, &t_m);
	mlx_hook(t_m->mlx_win, 17, 1 << 17, ft_quit, &t_m);
	mlx_hook(t_m->mlx_win, 15, 1 << 16, minimize, &t_m);
	mlx_loop(t_m->mlx_prog);
	ft_quit(t_m);
	return (0);
}
