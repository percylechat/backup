/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:22:42 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/10 15:48:45 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int 	*sort_sprite(int *temp)
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
			temp[i + 1] = temp [i + 4];
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

void	calc_sprite(data_t *data_t, t_sprite *t_sprite)
{
	int i;
	int *temp;
	int j;

	i = 0;
	j = 0;
	if (!(temp = malloc(sizeof(int) * (((int)data_t->tot_sprite * 3) + 1))))
		return;
	while (i / 2 != data_t->tot_sprite)
	{
		temp[j] = ((data_t->position_x - data_t->sprite_spot[i + 1]) * (data_t->position_x - data_t->sprite_spot[i + 1]) + (data_t->position_y - data_t->sprite_spot[i]) * (data_t->position_y - data_t->sprite_spot[i]));
		temp[j + 1] = data_t->sprite_spot[i];
		temp[j + 2] = data_t->sprite_spot[i + 1];
		j += 3;
		i += 2;
	}
	temp[j] = '\0';
	t_sprite->ordered_sprite = sort_sprite(temp);
}

void	sprite_size(t_sprite *t_sprite, data_t *data_t)
{
	t_sprite->sprite_h = fabs(data_t->res_h / t_sprite->transformY);
	t_sprite->start_h = (t_sprite->sprite_h * -1) / 2 + data_t->res_h / 2;
	if (t_sprite->start_h < 0)
		t_sprite->start_h = 0;
	t_sprite->end_h = t_sprite->sprite_h / 2 + data_t->res_h / 2;
	if (t_sprite->end_h >= data_t->res_h)
		t_sprite->end_h = data_t->res_h - 1;
	t_sprite->sprite_w = fabs(data_t->res_h / t_sprite->transformY);
	t_sprite->start_w = (t_sprite->sprite_w * -1) / 2 + t_sprite->spriteScreenX;
	if (t_sprite->start_w < 0)
		t_sprite->start_w = 0;
	t_sprite->end_w = t_sprite->sprite_w / 2 + t_sprite->spriteScreenX;
	if (t_sprite->end_w >= data_t->res_w)
		t_sprite->end_w = data_t->res_w - 1;
}

void 	print_sprite(data_t *data_t, t_sprite *t_sprite)
{
	t_tex tex_sprite;
	int k;

	k = 0;
	tex_sprite = get_tex_sp(data_t);
	if (tex_sprite.address == NULL)
		ft_quit_map(data_t, "Error\nCannot open sprite texture");
	calc_sprite(data_t, t_sprite);
	while (k / 3 != data_t->tot_sprite)
	{
		t_sprite->spriteX = (t_sprite->ordered_sprite[k + 2] + 0.5) - data_t->position_x;
		t_sprite->spriteY = (t_sprite->ordered_sprite[k + 1] + 0.5) - data_t->position_y;
		t_sprite->invDet = 1.0 / (data_t->camera_x * data_t->direction_y - data_t->direction_x * data_t->camera_y);
		t_sprite->transformX = t_sprite->invDet * (data_t->direction_y * t_sprite->spriteX - data_t->direction_x * t_sprite->spriteY);
		t_sprite->transformY = t_sprite->invDet * ((data_t->camera_y * -1) * t_sprite->spriteX + data_t->camera_x * t_sprite->spriteY);
		t_sprite->spriteScreenX = (int)((data_t->res_w / 2) * (1 + t_sprite->transformX / t_sprite->transformY));
		sprite_size(t_sprite, data_t);
		t_sprite->wall_x = t_sprite->start_w;
		while (t_sprite->wall_x < t_sprite->end_w)
		{
			t_sprite->tex_x = (int)(256 * (t_sprite->wall_x - ((t_sprite->sprite_w * -1) / 2 + t_sprite->spriteScreenX)) * BLOC_SIZE / t_sprite->sprite_w) / 256;
			if (t_sprite->transformY > 0 && t_sprite->transformY <= t_sprite->buffer[t_sprite->wall_x])
			{
				t_sprite->wall_y = t_sprite->start_h;
				while (t_sprite->wall_y < t_sprite->end_h)
				{
					int d = t_sprite->wall_y * 256 - data_t->res_h * 128 + t_sprite->sprite_h * 128;
					t_sprite->tex_y = ((d * BLOC_SIZE) / t_sprite->sprite_h) / 256;
					// if (tex_sprite.endian == 0)
						t_sprite->color = color_pixel(tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line * t_sprite->tex_y + 2], tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line * t_sprite->tex_y + 1], tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line * t_sprite->tex_y]);
					// else
					// 	t_sprite->color = color_pixel(tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line * texY], tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line * texY + 1], tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line * texY + 2]);
					if (t_sprite->color != 0)
						{data_t->img.content[t_sprite->wall_x * 4 + t_sprite->wall_y * data_t->img.size_line + 3] = tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line
				* t_sprite->tex_y + 3];
						data_t->img.content[t_sprite->wall_x * 4 + t_sprite->wall_y * data_t->img.size_line] = tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line
				* t_sprite->tex_y];
						data_t->img.content[t_sprite->wall_x * 4 + t_sprite->wall_y * data_t->img.size_line + 1] = tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line
				* t_sprite->tex_y + 1];
						data_t->img.content[t_sprite->wall_x * 4 + t_sprite->wall_y * data_t->img.size_line + 2] = tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line
				* t_sprite->tex_y + 2];}
						// mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, t_sprite->wall_x, t_sprite->wall_y, t_sprite->color);
					t_sprite->wall_y++;
				}
			}
			t_sprite->wall_x++;
		}
	k += 3;
	}
	free(t_sprite->ordered_sprite);
}
