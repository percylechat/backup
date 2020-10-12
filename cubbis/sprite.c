/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:22:42 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/12 15:55:34 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		*sort_sprite(int *temp)
{
	int i;
	int buf;

	i = 0;
	while (temp[i])
	{
		if (temp[i] < temp[i + 3] && temp[i + 3])
		{
			buf = temp[i];
			temp[i] = temp[i + 3];
			temp[i + 3] = buf;
			buf = temp[i + 1];
			temp[i + 1] = temp[i + 4];
			temp[i + 4] = buf;
			buf = temp[i + 2];
			temp[i + 2] = temp[i + 5];
			temp[i + 5] = buf;
			i = 0;
		}
		i += 3;
	}
	return (temp);
}

void	calc_sprite(t_main *t_m, t_sprite *t_s)
{
	int i;
	int *temp;
	int j;

	i = 0;
	j = 0;
	t_s->n_s = 0;
	if (!(temp = malloc(sizeof(int) * (((int)t_m->tot_sprite * 3) + 1))))
		return ;
	while (i / 2 != t_m->tot_sprite)
	{
		temp[j] = ((t_m->position_x - t_m->sprite_spot[i + 1]) *
(t_m->position_x - t_m->sprite_spot[i + 1]) + (t_m->position_y -
t_m->sprite_spot[i]) * (t_m->position_y - t_m->sprite_spot[i]));
		temp[j + 1] = t_m->sprite_spot[i];
		temp[j + 2] = t_m->sprite_spot[i + 1];
		j += 3;
		i += 2;
	}
	temp[j] = '\0';
	t_s->ordered_sprite = sort_sprite(temp);
}

void	sprite_size(t_sprite *t_s, t_main *t_m, int k)
{
	t_s->spriteX = (t_s->ordered_sprite[k + 2] + 0.5) - t_m->position_x;
	t_s->spriteY = (t_s->ordered_sprite[k + 1] + 0.5) - t_m->position_y;
	t_s->invDet = 1.0 / (t_m->camera_x * t_m->direction_y - t_m->direction_x *
t_m->camera_y);
	t_s->transformX = t_s->invDet * (t_m->direction_y * t_s->spriteX -
t_m->direction_x * t_s->spriteY);
	t_s->transformY = t_s->invDet * ((t_m->camera_y * -1) * t_s->spriteX +
t_m->camera_x * t_s->spriteY);
	t_s->spriteScreenX = (int)((t_m->res_w / 2) * (1 + t_s->transformX /
t_s->transformY));
	t_s->sprite_h = fabs(t_m->res_h / t_s->transformY);
	t_s->start_h = (t_s->sprite_h * -1) / 2 + t_m->res_h / 2;
	if (t_s->start_h < 0)
		t_s->start_h = 0;
	t_s->end_h = t_s->sprite_h / 2 + t_m->res_h / 2;
	if (t_s->end_h >= t_m->res_h)
		t_s->end_h = t_m->res_h - 1;
	t_s->sprite_w = fabs(t_m->res_h / t_s->transformY);
	t_s->start_w = (t_s->sprite_w * -1) / 2 + t_s->spriteScreenX;
	if (t_s->start_w < 0)
		t_s->start_w = 0;
	t_s->end_w = t_s->sprite_w / 2 + t_s->spriteScreenX;
	if (t_s->end_w >= t_m->res_w)
		t_s->end_w = t_m->res_w - 1;
	t_s->wall_x = t_s->start_w;
}

int		actual_print(t_main *t_m, t_sprite *t_s, t_tex tex_sp)
{
	int d;

	d = t_s->wall_y * 256 - t_m->res_h * 128 + t_s->sprite_h * 128;
	t_s->tex_y = ((d * BLOC_SIZE) / t_s->sprite_h) / 256;
	t_s->color = color_pixel(tex_sp.content[t_s->tex_x * 4 +
	tex_sp.sl * t_s->tex_y + 2], tex_sp.content[t_s->tex_x * 4 +
	tex_sp.sl * t_s->tex_y + 1], tex_sp.content[t_s->tex_x * 4 +
	tex_sp.sl * t_s->tex_y]);
	if (t_s->color != 0)
	{
		t_m->img.content[t_s->wall_x * 4 + t_s->wall_y * t_m->img.sl + 3] =
tex_sp.content[t_s->tex_x * 4 + tex_sp.sl * t_s->tex_y + 3];
		t_m->img.content[t_s->wall_x * 4 + t_s->wall_y * t_m->img.sl] =
tex_sp.content[t_s->tex_x * 4 + tex_sp.sl * t_s->tex_y];
		t_m->img.content[t_s->wall_x * 4 + t_s->wall_y * t_m->img.sl + 1] =
tex_sp.content[t_s->tex_x * 4 + tex_sp.sl * t_s->tex_y + 1];
		t_m->img.content[t_s->wall_x * 4 + t_s->wall_y * t_m->img.sl + 2] =
tex_sp.content[t_s->tex_x * 4 + tex_sp.sl * t_s->tex_y + 2];
	}
	return (t_s->wall_y + 1);
}

void	print_sprite(t_main *t_m, t_sprite *t_s)
{
	t_tex	tex_sp;

	tex_sp = get_tex_sp(t_m);
	if (tex_sp.address == NULL)
		ft_quit_map(t_m, "Error\nCannot open sprite texture");
	calc_sprite(t_m, t_s);
	while (t_s->n_s / 3 != t_m->tot_sprite)
	{
		sprite_size(t_s, t_m, t_s->n_s);
		while (t_s->wall_x < t_s->end_w)
		{
			t_s->tex_x = (int)(256 * (t_s->wall_x - ((t_s->sprite_w * -1) / 2 +
t_s->spriteScreenX)) * BLOC_SIZE / t_s->sprite_w) / 256;
			if (t_s->transformY > 0 && t_s->transformY <=
t_s->buffer[t_s->wall_x])
			{
				t_s->wall_y = t_s->start_h;
				while (t_s->wall_y < t_s->end_h)
					t_s->wall_y = actual_print(t_m, t_s, tex_sp);
			}
			t_s->wall_x++;
		}
		t_s->n_s += 3;
	}
	free(t_s->ordered_sprite);
}
