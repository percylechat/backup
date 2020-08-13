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
	int j;
	int i;
	t_raycast t_raycast[256];

	i = 0;
	j = 0;
	t_raycast->hit = 0;
	while (i <= data_t->res_w)
	{
		t_raycast->mapX = (int)data_t->position_x;
		t_raycast->mapY = (int)data_t->position_y;
		t_raycast->camerax = 2 * i / data_t->res_w - 1;
		t_raycast->ray_x = data_t->direction_x + data_t->camera_x * t_raycast->camerax;
		t_raycast->ray_y = data_t->direction_y + data_t->camera_y * t_raycast->camerax;
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
		while (t_raycast->hit == 0)
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
		j = 0;
		t_raycast->hit = 0;
		if (t_raycast->side == 0)
			t_raycast->perpWallDist = (t_raycast->mapX - data_t->position_x + (1 - t_raycast->stepX) / 2) / t_raycast->ray_x;
		else
			t_raycast->perpWallDist = (t_raycast->mapY - data_t->position_y + (1 - t_raycast->stepY) / 2) / t_raycast->ray_y;
		data_t->wall_size = (int)(data_t->res_h / t_raycast->perpWallDist);
		//
		// double wallX; //where exactly the wall was hit
	    // if (side == 0) wallX = data_t->position_y + perpWallDist * ray_y;
	    // else wallX = data_t->position_x + perpWallDist * ray_x;
	    // wallX -= (int)wallX;
		//
	    // //x coordinate on the texture
		// //texWidth largeur de image
	    // int texX = int(wallX * double(texWidth));
	    // if(side == 0 && ray_x > 0) texX = texWidth - texX - 1;
	    // if(side == 1 && ray_y < 0) texX = texWidth - texX - 1;

		print_column(data_t, i, t_raycast->side);
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

void	get_texture(data_t *data_t)
{
	int bits_per_pixel;
	int size_line;
	int endian;
	int size;
	char *test;

	size = 64;
	data_t->img_N_p = mlx_xpm_file_to_image(data_t->mlx_prog, data_t->tex_N, &size, &size);
	if ((test = mlx_get_data_addr(data_t->img_N_p ,&bits_per_pixel, &size_line, &endian)) == NULL)
		write(1, "error", 5);
}
