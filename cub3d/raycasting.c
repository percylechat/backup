#include "cub3d.h"

void drawRays3d(data_t *data_t)
{
	int j = 0;
	int mapX = (int)data_t->position_x;
	int mapY = (int)data_t->position_y;
	float sideDistX;
	float sideDistY;
	float deltaDistX;
	float deltaDistY;
	float perpWallDist;
	int stepX;
	int stepY;
	int hit = 0; //was there a wall hit?
	int side; //was a NS or a EW wall hit?
	int i = 1;
	while (i <= data_t->res_w)
	{
		mapX = (int)data_t->position_x;
		mapY = (int)data_t->position_y;
		float camerax = 2 * i / data_t->res_w - 1;
		float ray_x = data_t->direction_x + data_t->camera_x * camerax;
		float ray_y = data_t->direction_y + data_t->camera_y * camerax;
		// printf("%s\n", );
		printf("ray y %f\n", ray_y);
		printf("ray x %f\n", ray_x);
		if (ray_x != 0)
			deltaDistX = abs(1 / ray_x);
		else
			deltaDistX = 1;
		if (ray_y != 0)
			deltaDistY = abs(1 / ray_y);
		else
			deltaDistY = 1;
		if (ray_x < 0)
		{
			stepX = -1;
			sideDistX = (data_t->position_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data_t->position_x) * deltaDistX;
		}
		if (ray_y < 0)
		{
			stepY = -1;
			sideDistY = (data_t->position_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data_t->position_y) * deltaDistY;
		}
		// printf("mapx: %d mapy %d\n", mapX, mapY);
		while (hit == 0 && j < 8)
		{
//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
	  //Check if ray has hit a wall
			// printf("mapxbis: %d mapybis: %d\n", mapX, mapY);
			if (check_for_obstacle(mapX, mapY, data_t) > 0)
				hit = 1;
			j++;
		}
		j = 0;
		hit = 0;
		if (side == 0)
			perpWallDist = (mapX - data_t->position_x + (1 - stepX) / 2) / ray_x;
		else
			perpWallDist = (mapY - data_t->position_y + (1 - stepY) / 2) / ray_y;
		data_t->wall_size = (int)(data_t->res_h / perpWallDist);
		// printf("wall: %d\n", data_t->wall_size);
		print_column(data_t, i, side);
		i += 30;
	}
}

void	print_column(data_t *data_t, int i, int side)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	// printf("%d", data_t->wall_size);
	while (j < data_t->res_h)
	{
		while (j < ((data_t->res_h - data_t->wall_size) / 2))
		{
			mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, j,
	data_t->color_ceiling);
			j++;
		}
		while (k < data_t->wall_size && j < data_t->res_h)
		{
			if (side == 0)
				mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, j, (255
	+(255<<16)+(1<<8)));
			else
			mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, j, (255
+(1<<16)+(255<<8)));
			k++;
			j++;
		}
		mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, j,
	data_t->color_floor);
	j++;
	}
}
