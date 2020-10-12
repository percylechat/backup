/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:33:32 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/12 15:55:37 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	text_print(t_tex t_t, t_print *t_p, t_main *t_m, int index)
{
	t_p->texY = (int)t_p->texPos & ((int)BLOC_SIZE - 1);
	t_p->texPos += t_p->step;
	t_m->img.content[index + 3] = t_t.content[t_p->texX * 4 + t_t.sl *
t_p->texY + 3];
	t_m->img.content[index] = t_t.content[t_p->texX * 4 + t_t.sl * t_p->texY];
	t_m->img.content[index + 1] = t_t.content[t_p->texX * 4 + t_t.sl *
t_p->texY + 1];
	t_m->img.content[index + 2] = t_t.content[t_p->texX * 4 + t_t.sl *
t_p->texY + 2];
}

void	print_cf(t_main *t_m, int h, int i, int g)
{
	if (g == 1)
	{
		t_m->img.content[i * 4 + h * t_m->img.sl] = t_m->color_ceiling.r;
		t_m->img.content[i * 4 + h * t_m->img.sl + 1] = t_m->color_ceiling.g;
		t_m->img.content[i * 4 + h * t_m->img.sl + 2] = t_m->color_ceiling.b;
	}
	else
	{
		t_m->img.content[i * 4 + h * t_m->img.sl] = t_m->color_floor.r;
		t_m->img.content[i * 4 + h * t_m->img.sl + 1] = t_m->color_floor.g;
		t_m->img.content[i * 4 + h * t_m->img.sl + 2] = t_m->color_floor.b;
	}
}

void	print_wall(t_main *t_m, t_raycast *t_r, int i, t_print *t_p)
{
	t_tex	tex;
	int		h;
	int		index;

	h = 0;
	t_p->step = 1.0 * BLOC_SIZE / t_m->wall_size;
	t_p->texPos = (t_p->deb - t_m->res_h / 2 + t_m->wall_size / 2) * t_p->step;
	tex = choose_texture(t_m, t_r);
	while (h < t_m->res_h)
	{
		while (h < t_p->deb)
		{
			print_cf(t_m, h, i, 1);
			h++;
		}
		while (h > t_p->deb && h < t_p->end)
		{
			index = i * 4 + h * t_m->img.sl;
			text_print(tex, t_p, t_m, index);
			h++;
		}
		print_cf(t_m, h, i, 0);
		h++;
	}
}

void	calc_texture(t_main *t_m, t_raycast *t_r, int i)
{
	t_print t_p[1];

	t_p->deb = t_m->res_h / 2 - t_m->wall_size / 2;
	if (t_p->deb < 0)
		t_p->deb = 0;
	t_p->end = t_p->deb + t_m->wall_size;
	if (t_p->end > t_m->res_h)
		t_p->end = t_m->res_h;
	if (t_r->side == 0)
		t_p->wallX = t_m->position_y + t_r->perpWallDist *
t_r->ray_y;
	else
		t_p->wallX = t_m->position_x + t_r->perpWallDist *
t_r->ray_x;
	t_p->wallY = floor((t_p->wallX - floor(t_p->wallX)) *
BLOC_SIZE);
	t_p->wallX -= (int)t_p->wallX;
	t_p->texX = (int)(t_p->wallX * BLOC_SIZE);
	if (t_r->side == 0 && t_r->ray_x > 0)
		t_p->texX = BLOC_SIZE - t_p->texX - 1;
	if (t_r->side == 1 && t_r->ray_y < 0)
		t_p->texX = BLOC_SIZE - t_p->texX - 1;
	print_wall(t_m, t_r, i, t_p);
}
