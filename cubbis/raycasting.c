#include "cub3d.h"

void	check_step(t_raycast *t_raycast, data_t *data_t)
{
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

void	init_raycast(data_t *data_t, t_raycast *t_raycast, t_sprite *t_sprite, int i)
{
	t_raycast->hit = 0;
	t_raycast->mapX = (int)data_t->position_x;
	t_raycast->mapY = (int)data_t->position_y;
	t_raycast->camerax = 2 * i / data_t->res_w - 1;
	t_raycast->ray_x = data_t->direction_x + data_t->camera_x *
t_raycast->camerax;
	t_raycast->ray_y = data_t->direction_y + data_t->camera_y *
t_raycast->camerax;
t_raycast->deltaDistX = (t_raycast->ray_y == 0) ? 0 : ((t_raycast->ray_x == 0) ?
 1 : fabs(1 / t_raycast->ray_x));
t_raycast->deltaDistY = (t_raycast->ray_x == 0) ? 0 : ((t_raycast->ray_y == 0) ?
 1 : fabs(1 / t_raycast->ray_y));
	check_step(t_raycast, data_t);
	while (t_raycast->hit == 0)
		check_intersec(t_raycast, data_t, t_sprite);
	if (t_raycast->side == 0)
		t_raycast->perpWallDist = (t_raycast->mapX - data_t->position_x + (1 -
t_raycast->stepX) / 2) / t_raycast->ray_x;
	else
		t_raycast->perpWallDist = (t_raycast->mapY - data_t->position_y + (1 -
t_raycast->stepY) / 2) / t_raycast->ray_y;
}

void	drawRays3d(data_t *data_t)
{
	int i;
	t_raycast t_raycast[1];
	t_sprite t_sprite[1];

	i = 0;
	t_sprite->is_sprite = 0;
	if (!(t_sprite->buffer = malloc(sizeof(float*) * data_t->res_w + 1)))
	{
		ft_quit_map(data_t ,"ERROR\nInsufficient memory");
		return;
	}
	while (i <= data_t->res_w)
	{
		init_raycast(data_t, t_raycast, t_sprite, i);
		data_t->wall_size = (int)(data_t->res_h / t_raycast->perpWallDist);
		calc_texture(data_t, t_raycast, i);
		t_sprite->buffer[i] = t_raycast->perpWallDist;
		data_t->wall_size = 0;
		i += 1;
	}
	if (t_sprite->is_sprite > 0)
		print_sprite(data_t, t_sprite);
	free(t_sprite->buffer);
	mlx_put_image_to_window(data_t->mlx_prog, data_t->mlx_win, data_t->mlx_img, 0, 0);
}
