#include "cub3d.h"

void	check_step(t_raycast *t_raycast, data_t *data_t)
{
	t_raycast->deltaDistX = (t_raycast->ray_y == 0) ? 0 : ((t_raycast->ray_x == 0) ? 1 : fabs(1 / t_raycast->ray_x));
	t_raycast->deltaDistY = (t_raycast->ray_x == 0) ? 0 : ((t_raycast->ray_y == 0) ? 1 : fabs(1 / t_raycast->ray_y));
	if (t_raycast->ray_x < 0)
	{
		t_raycast->stepX = -1;
		t_raycast->sideDistX = (data_t->position_x - t_raycast->mapX) * t_raycast->deltaDistX;
	}
	else
	{
		t_raycast->stepX = 1;
		t_raycast->sideDistX = (t_raycast->mapX + 1.0 - data_t->position_x) * t_raycast->deltaDistX;
	}
	if (t_raycast->ray_y < 0)
	{
		t_raycast->stepY = -1;
		t_raycast->sideDistY = (data_t->position_y - t_raycast->mapY) * t_raycast->deltaDistY;
	}
	else
	{
		t_raycast->stepY = 1;
		t_raycast->sideDistY = (t_raycast->mapY + 1.0 - data_t->position_y) * t_raycast->deltaDistY;
	}
}

void	check_intersec(t_raycast *t_raycast, data_t *data_t, t_sprite *t_sprite)
{
	if (t_raycast->sideDistX < t_raycast->sideDistY)
	{
		t_raycast->sideDistX += t_raycast->deltaDistX;
		t_raycast->mapX += t_raycast->stepX;
		t_raycast->side = 0;
	}
	else
	{
		t_raycast->sideDistY += t_raycast->deltaDistY;
		t_raycast->mapY += t_raycast->stepY;
		t_raycast->side = 1;
	}
	if (check_for_obstacle(t_raycast->mapX, t_raycast->mapY, data_t, t_sprite) > 0)
		t_raycast->hit = 1;
}

void 	print_wall(data_t *data_t, t_raycast *t_raycast, int i, t_print *t_print)
{
	t_tex tex_to_use;
	int h;

	h = 0;
	tex_to_use = choose_texture(data_t, t_raycast, i);
	while (h < data_t->res_h)
	{
		while (h < t_print->deb)
			mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, h++, data_t->color_floor);
		while (h > t_print->deb && h < t_print->end)
		{
			t_print->texY = (int)t_print->texPos & ((int)BLOC_SIZE - 1);
			t_print->texPos += t_print->step;
			if (tex_to_use.endian == 0)
				t_print->color = color_pixel(tex_to_use.content[t_print->texX * 4 + tex_to_use.size_line * t_print->texY + 2], tex_to_use.content[t_print->texX * 4 + tex_to_use.size_line * t_print->texY + 1], tex_to_use.content[t_print->texX * 4 + tex_to_use.size_line * t_print->texY]);
			else
				t_print->color = color_pixel(tex_to_use.content[t_print->texX * 4 + tex_to_use.size_line * t_print->texY], tex_to_use.content[t_print->texX * 4 + tex_to_use.size_line * t_print->texY + 1], tex_to_use.content[t_print->texX * 4 + tex_to_use.size_line * t_print->texY + 2]);
			mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, h++, t_print->color);
		}
		mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, h++, data_t->color_ceiling);
	}
}

void 	calc_texture(data_t *data_t, t_raycast *t_raycast, int i)
{
	t_print t_print[1];

	t_print->deb = data_t->res_h / 2 - data_t->wall_size / 2;
	if (t_print->deb < 0)
		t_print->deb = 0;
	t_print->end = t_print->deb + data_t->wall_size;
	if (t_print->end > data_t->res_h)
		t_print->end = data_t->res_h;
	if (t_raycast->side == 0)
		t_print->wallX = data_t->position_y + t_raycast->perpWallDist * t_raycast->ray_y;
	else
		t_print->wallX = data_t->position_x + t_raycast->perpWallDist * t_raycast->ray_x;
	t_print->wallY = floor((t_print->wallX - floor(t_print->wallX)) * BLOC_SIZE);
	t_print->wallX -= (int)t_print->wallX;
	t_print->texX = (int)(t_print->wallX * BLOC_SIZE);
	if (t_raycast->side == 0 && t_raycast->ray_x > 0)
		t_print->texX = BLOC_SIZE - t_print->texX - 1;
	if (t_raycast->side == 1 && t_raycast->ray_y < 0)
		t_print->texX = BLOC_SIZE - t_print->texX - 1;
	t_print->step = 1.0 * BLOC_SIZE / data_t->wall_size;
	t_print->texPos = (t_print->deb - data_t->res_h / 2 + data_t->wall_size / 2) * t_print->step;
	print_wall(data_t, t_raycast, i, t_print);
}

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

void	calc_sprite(data_t *data_t, t_sprite *t_sprite, t_raycast *t_raycast)
{
	int i;
	int *temp;
	int j;

	i = 0;
	j = 0;
	if (!(temp = malloc(sizeof(int) * (data_t->tot_sprite * 3) + 1)))
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
	t_sprite->sprite_h = abs(data_t->res_h / t_sprite->transformY);
	t_sprite->start_h = (t_sprite->sprite_h * -1) / 2 + data_t->res_h / 2;
	if (t_sprite->start_h < 0)
		t_sprite->start_h = 0;
	t_sprite->end_h = t_sprite->sprite_h / 2 + data_t->res_h / 2;
	if (t_sprite->end_h >= data_t->res_h)
		t_sprite->end_h = data_t->res_h - 1;
	t_sprite->sprite_w = abs(data_t->res_h / t_sprite->transformY);
	t_sprite->start_w = (t_sprite->sprite_w * -1) / 2 + t_sprite->spriteScreenX;
	if (t_sprite->start_w < 0)
		t_sprite->start_w = 0;
	t_sprite->end_w = t_sprite->sprite_w / 2 + t_sprite->spriteScreenX;
	if (t_sprite->end_w >= data_t->res_w)
		t_sprite->end_w = data_t->res_w - 1;
}

void 	print_sprite(data_t *data_t, int i, t_sprite *t_sprite, t_raycast *t_raycast)
{
	t_tex tex_sprite;
	int k;

	k = 0;
	tex_sprite = get_tex_sp(data_t);
	calc_sprite(data_t, t_sprite, t_raycast);
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
					int texY = ((d * BLOC_SIZE) / t_sprite->sprite_h) / 256;
					if (tex_sprite.endian == 0)
						t_sprite->color = color_pixel(tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line * texY + 2], tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line * texY + 1], tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line * texY]);
					else
						t_sprite->color = color_pixel(tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line * texY], tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line * texY + 1], tex_sprite.content[t_sprite->tex_x * 4 + tex_sprite.size_line * texY + 2]);
					if (t_sprite->color != 0)
						mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, t_sprite->wall_x, t_sprite->wall_y, t_sprite->color);
					t_sprite->wall_y++;
				}
			}
			t_sprite->wall_x++;
		}
	k += 3;
	}
}

void	drawRays3d(data_t *data_t)
{
	int i;
	t_raycast t_raycast[1];
	t_sprite t_sprite[1];
	float *buffer;

	i = 0;
	t_sprite->is_sprite = 0;
	if (!(t_sprite->buffer = malloc(sizeof(float) * data_t->res_w)))
		return;
	while (i <= data_t->res_w)
	{
		t_raycast->hit = 0;
		t_raycast->mapX = (int)data_t->position_x;
		t_raycast->mapY = (int)data_t->position_y;
		t_raycast->camerax = 2 * i / data_t->res_w - 1;
		t_raycast->ray_x = data_t->direction_x + data_t->camera_x * t_raycast->camerax;
		t_raycast->ray_y = data_t->direction_y + data_t->camera_y * t_raycast->camerax;
		check_step(t_raycast, data_t);
		while (t_raycast->hit == 0)
			check_intersec(t_raycast, data_t, t_sprite);
		if (t_raycast->side == 0)
			t_raycast->perpWallDist = (t_raycast->mapX - data_t->position_x + (1 - t_raycast->stepX) / 2) / t_raycast->ray_x;
		else
			t_raycast->perpWallDist = (t_raycast->mapY - data_t->position_y + (1 - t_raycast->stepY) / 2) / t_raycast->ray_y;
		data_t->wall_size = (int)(data_t->res_h / t_raycast->perpWallDist);
		calc_texture(data_t, t_raycast, i);
		t_sprite->buffer[i] = t_raycast->perpWallDist;
		data_t->wall_size = 0;
		i += 1;
	}
	if (t_sprite->is_sprite > 0)
		print_sprite(data_t, i, t_sprite, t_raycast);
}
