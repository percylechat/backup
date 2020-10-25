/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:34:14 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/15 17:26:44 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		minimize(t_main *t_m)
{
	mlx_put_image_to_window(t_m->mlx_prog, t_m->mlx_win, t_m->mlx_img, 0, 0);
	return (0);
}

void	write_img(t_main *t_m, int fd)
{
	int				x;
	unsigned int	index;
	int				y;

	y = (int)t_m->res_h;
	while (y)
	{
		x = 0;
		while (x < t_m->res_w)
		{
			index = (y * t_m->img.sl + x * 4);
			write(fd, &t_m->img.content[index], 1);
			write(fd, &t_m->img.content[index + 1], 1);
			write(fd, &t_m->img.content[index + 2], 1);
			x++;
		}
		y--;
	}
}

void	init_save(t_main *t_m, t_save *t_s, int fd)
{
	t_s->one = 1;
	t_s->info = 54;
	t_s->bpp = 24;
	t_s->header = 40;
	t_s->zero = 0;
	t_s->h = (int)t_m->res_h;
	t_s->w = (int)t_m->res_w;
	t_s->size = t_s->info + (t_s->h * t_m->img.sl);
	write(fd, "BM", 2);
	write(fd, &t_s->size, sizeof(int));
	write(fd, &t_s->zero, sizeof(int));
	write(fd, &t_s->info, sizeof(int));
	write(fd, &t_s->header, sizeof(int));
}

int		ft_quit_save(t_main *t_m)
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
	free(t_m->mlx_prog);
	exit(0);
}

void	ft_save(t_main *t_m)
{
	int		fd;
	t_save	t_s[1];

	if ((fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0)
	{
		ft_quit(t_m);
		return ;
	}
	raycasting(t_m);
	init_save(t_m, t_s, fd);
	write(fd, &t_s->w, sizeof(int));
	write(fd, &t_s->h, sizeof(int));
	write(fd, &t_s->one, sizeof(short int));
	write(fd, &t_s->bpp, sizeof(short int));
	write(fd, &t_s->zero, sizeof(int));
	write(fd, &t_s->zero, sizeof(int));
	write(fd, &t_s->zero, sizeof(int));
	write(fd, &t_s->zero, sizeof(int));
	write(fd, &t_s->zero, sizeof(int));
	write(fd, &t_s->zero, sizeof(int));
	write_img(t_m, fd);
	close(fd);
	ft_quit_save(t_m);
}
