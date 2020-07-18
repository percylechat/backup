#include "cub3d.h"

//painstackingly tries to display a wall
//more bugged than fallout 76

//called by ft_keyboard_press in move.c and by main

//SO
//basically we have the coordinates of the player (position x and y), the global direction of the ray (direction x and y) and the camera plane (camera x and y).
//first you calculate the specific ray (camerax) and the first intersection for horizontal coordinates (ray x) and vertical ones (ray y)
//these intersections give the global ray dorection and indications with whick we can move further along (deltadirx and deltadiry, then stepx and stepy).
//sidedist x and y tell you which intersection you should check first (because it's the closest to the player).
//then you check each intersection and add little by little to move along (j should be smaller than 8 so we don't check to much and if it's too far too bad for this wall).
//finally you calculate the wall size and print it.

//This is how i understand it. Please see the tutorial below that i blatantly ripped off
//https://lodev.org/cgtutor/raycasting.html
//please send help

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
	int hit = 0;
	int side;
	int i = 0;
	while (i <= data_t->res_w)
	{
		mapX = (int)data_t->position_x;
		mapY = (int)data_t->position_y;
		float camerax = 2 * i / data_t->res_w - 1;
		float ray_x = data_t->direction_x + data_t->camera_x * camerax;
		float ray_y = data_t->direction_y + data_t->camera_y * camerax;

		double deltaDistX = (ray_y == 0) ? 0 : ((ray_x == 0) ? 1 : fabs(1 / ray_x));
        double deltaDistY = (ray_x == 0) ? 0 : ((ray_y == 0) ? 1 : fabs(1 / ray_y));
		// if (ray_x != 0)
		// 	deltaDistX = abs(1 / ray_x);
		// else
		// 	deltaDistX = 1;
		// if (ray_y != 0)
		// 	deltaDistY = abs(1 / ray_y);
		// else
		// 	deltaDistY = 1;
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
		while (hit == 0 && j < 8)
		{
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
		print_column(data_t, i, side);
		data_t->wall_size = 0;
		i += 1;
	}
}

//print the pixel line for each ray.
void	print_column(data_t *data_t, int i, int side)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
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
