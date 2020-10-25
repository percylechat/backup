/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 16:14:46 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/14 13:01:49 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_step(t_raycast *t_r, t_main *t_m)
{
	if (t_r->ray_x < 0)
	{
		t_r->step_x = -1;
		t_r->side_x = (t_m->position_x - t_r->map_x) * t_r->delta_x;
	}
	else
	{
		t_r->step_x = 1;
		t_r->side_x = (t_r->map_x + 1.0 - t_m->position_x) * t_r->delta_x;
	}
	if (t_r->ray_y < 0)
	{
		t_r->step_y = -1;
		t_r->side_y = (t_m->position_y - t_r->map_y) * t_r->delta_y;
	}
	else
	{
		t_r->step_y = 1;
		t_r->side_y = (t_r->map_y + 1.0 - t_m->position_y) * t_r->delta_y;
	}
}

void	check_intersec(t_raycast *t_r, t_main *t_m, t_sprite *t_s)
{
	if (t_r->side_x < t_r->side_y)
	{
		t_r->side_x += t_r->delta_x;
		t_r->map_x += t_r->step_x;
		t_r->side = 0;
	}
	else
	{
		t_r->side_y += t_r->delta_y;
		t_r->map_y += t_r->step_y;
		t_r->side = 1;
	}
	if (check_for_obstacle(t_r->map_x, t_r->map_y, t_m, t_s) > 0)
		t_r->hit = 1;
}

void	init_raycast(t_main *t_m, t_raycast *t_r, t_sprite *t_s, int i)
{
	t_r->hit = 0;
	t_r->map_x = (int)t_m->position_x;
	t_r->map_y = (int)t_m->position_y;
	t_r->camerax = 2 * i / t_m->res_w - 1;
	t_r->ray_x = t_m->direction_x + t_m->camera_x * t_r->camerax;
	t_r->ray_y = t_m->direction_y + t_m->camera_y * t_r->camerax;
	if (t_r->ray_y == 0)
		t_r->delta_x = 0;
	else
		t_r->delta_x = (t_r->ray_x == 0) ? 1 : fabs(1 / t_r->ray_x);
	if (t_r->ray_x == 0)
		t_r->delta_y = 0;
	else
		t_r->delta_y = (t_r->ray_y == 0) ? 1 : fabs(1 / t_r->ray_y);
	check_step(t_r, t_m);
	while (t_r->hit == 0)
		check_intersec(t_r, t_m, t_s);
	if (t_r->side == 0)
		t_r->wall_dist = (t_r->map_x - t_m->position_x + (1 -
t_r->step_x) / 2) / t_r->ray_x;
	else
		t_r->wall_dist = (t_r->map_y - t_m->position_y + (1 -
t_r->step_y) / 2) / t_r->ray_y;
}

void	raycasting(t_main *t_m)
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
		t_m->wall_size = (int)(t_m->res_h / t_r->wall_dist);
		calc_texture(t_m, t_r, i);
		t_s->buffer[i] = t_r->wall_dist;
		t_m->wall_size = 0;
		i += 1;
	}
	if (t_s->is_sprite > 0)
		print_sprite(t_m, t_s);
	free(t_s->buffer);
}
