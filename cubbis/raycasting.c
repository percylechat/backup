/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 16:14:46 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/11 16:19:52 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_step(t_raycast *t_r, data_t *t_m)
{
	if (t_r->ray_x < 0)
	{
		t_r->stepX = -1;
		t_r->sideDistX = (t_m->position_x - t_r->mapX) * t_r->deltaDistX;
	}
	else
	{
		t_r->stepX = 1;
		t_r->sideDistX = (t_r->mapX + 1.0 - t_m->position_x) * t_r->deltaDistX;
	}
	if (t_r->ray_y < 0)
	{
		t_r->stepY = -1;
		t_r->sideDistY = (t_m->position_y - t_r->mapY) * t_r->deltaDistY;
	}
	else
	{
		t_r->stepY = 1;
		t_r->sideDistY = (t_r->mapY + 1.0 - t_m->position_y) * t_r->deltaDistY;
	}
}

void	check_intersec(t_raycast *t_r, data_t *t_m, t_sprite *t_s)
{
	if (t_r->sideDistX < t_r->sideDistY)
	{
		t_r->sideDistX += t_r->deltaDistX;
		t_r->mapX += t_r->stepX;
		t_r->side = 0;
	}
	else
	{
		t_r->sideDistY += t_r->deltaDistY;
		t_r->mapY += t_r->stepY;
		t_r->side = 1;
	}
	if (check_for_obstacle(t_r->mapX, t_r->mapY, t_m, t_s) > 0)
		t_r->hit = 1;
}

void	init_raycast(data_t *t_m, t_raycast *t_r, t_sprite *t_s, int i)
{
	t_r->hit = 0;
	t_r->mapX = (int)t_m->position_x;
	t_r->mapY = (int)t_m->position_y;
	t_r->camerax = 2 * i / t_m->res_w - 1;
	t_r->ray_x = t_m->direction_x + t_m->camera_x * t_r->camerax;
	t_r->ray_y = t_m->direction_y + t_m->camera_y * t_r->camerax;
	t_r->deltaDistX = (t_r->ray_y == 0) ? 0 : ((t_r->ray_x == 0) ? 1 : fabs(1 / t_r->ray_x));
	t_r->deltaDistY = (t_r->ray_x == 0) ? 0 : ((t_r->ray_y == 0) ? 1 : fabs(1 /
t_r->ray_y));
	check_step(t_r, t_m);
	while (t_r->hit == 0)
		check_intersec(t_r, t_m, t_s);
	if (t_r->side == 0)
		t_r->perpWallDist = (t_r->mapX - t_m->position_x + (1 -
t_r->stepX) / 2) / t_r->ray_x;
	else
		t_r->perpWallDist = (t_r->mapY - t_m->position_y + (1 -
t_r->stepY) / 2) / t_r->ray_y;
}

void	raycasting(data_t *t_m)
{
	int			i;
	t_raycast	t_r[1];
	t_sprite	t_s[1];

	i = 0;
	t_s->is_sprite = 0;
	if (!(t_s->buffer = malloc(sizeof(float*) * t_m->res_w + 1)))
	{
		ft_quit_map(t_m, "ERROR\nInsufficient memory");
		return ;
	}
	while (i <= t_m->res_w)
	{
		init_raycast(t_m, t_r, t_s, i);
		t_m->wall_size = (int)(t_m->res_h / t_r->perpWallDist);
		calc_texture(t_m, t_r, i);
		t_s->buffer[i] = t_r->perpWallDist;
		t_m->wall_size = 0;
		i += 1;
	}
	if (t_s->is_sprite > 0)
		print_sprite(t_m, t_s);
	free(t_s->buffer);
	mlx_put_image_to_window(t_m->mlx_prog, t_m->mlx_win, t_m->mlx_img, 0, 0);
}
