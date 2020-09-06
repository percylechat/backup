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

void	check_intersec(t_raycast *t_raycast, data_t *data_t)
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
	if (check_for_obstacle(t_raycast->mapX, t_raycast->mapY, data_t) > 0)
		t_raycast->hit = 1;
}

void 	print_wall(data_t *data_t, t_raycast *t_raycast, int i)
{
	t_tex tex_to_use;
	int h;

	h = 0;
	tex_to_use = choose_texture(data_t, t_raycast, i);
	while (h < data_t->res_h)
	{
		while (h < t_raycast->deb)
			mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, h++, data_t->color_floor);
		while (h > t_raycast->deb && h < t_raycast->end)
		{
			t_raycast->texY = (int)t_raycast->texPos & ((int)BLOC_SIZE - 1);
			t_raycast->texPos += t_raycast->step;
			t_raycast->color = color_pixel(tex_to_use.content[t_raycast->texX * 4 + tex_to_use.size_line * t_raycast->texY + 2], tex_to_use.content[t_raycast->texX * 4 + tex_to_use.size_line * t_raycast->texY + 1], tex_to_use.content[t_raycast->texX * 4 + tex_to_use.size_line * t_raycast->texY]);
			mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, h++, t_raycast->color);
		}
		mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, h++, data_t->color_ceiling);
	}
}

void 	calc_texture(data_t *data_t, t_raycast *t_raycast, int i)
{
	t_raycast->deb = data_t->res_h / 2 - data_t->wall_size / 2;
	if (t_raycast->deb < 0)
		t_raycast->deb = 0;
	t_raycast->end = t_raycast->deb + data_t->wall_size;
	if (t_raycast->end > data_t->res_h)
		t_raycast->end = data_t->res_h;
	if (t_raycast->side == 0)
		t_raycast->wallX = data_t->position_y + t_raycast->perpWallDist * t_raycast->ray_y;
	else
		t_raycast->wallX = data_t->position_x + t_raycast->perpWallDist * t_raycast->ray_x;
	t_raycast->wallY = floor((t_raycast->wallX - floor(t_raycast->wallX)) * BLOC_SIZE);
	t_raycast->wallX -= (int)t_raycast->wallX;
	t_raycast->texX = (int)(t_raycast->wallX * BLOC_SIZE);
	if (t_raycast->side == 0 && t_raycast->ray_x > 0)
		t_raycast->texX = BLOC_SIZE - t_raycast->texX - 1;
	if (t_raycast->side == 1 && t_raycast->ray_y < 0)
		t_raycast->texX = BLOC_SIZE - t_raycast->texX - 1;
	t_raycast->step = 1.0 * BLOC_SIZE / data_t->wall_size;
	t_raycast->texPos = (t_raycast->deb - data_t->res_h / 2 + data_t->wall_size / 2) * t_raycast->step;
	print_wall(data_t, t_raycast, i);
}

void drawRays3d(data_t *data_t)
{
	int i;
	t_raycast t_raycast[256];

	i = 0;
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
			check_intersec(t_raycast, data_t);
		if (t_raycast->side == 0)
			t_raycast->perpWallDist = (t_raycast->mapX - data_t->position_x + (1 - t_raycast->stepX) / 2) / t_raycast->ray_x;
		else
			t_raycast->perpWallDist = (t_raycast->mapY - data_t->position_y + (1 - t_raycast->stepY) / 2) / t_raycast->ray_y;
		data_t->wall_size = (int)(data_t->res_h / t_raycast->perpWallDist);
		calc_texture(data_t, t_raycast, i);
		data_t->wall_size = 0;
		i += 1;
	}
}
