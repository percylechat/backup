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
		t_raycast->deltaDistX = (t_raycast->ray_y == 0) ? 0 : ((t_raycast->ray_x == 0) ? 1 : fabs(1 / t_raycast->ray_x));
		t_raycast->deltaDistY = (t_raycast->ray_x == 0) ? 0 : ((t_raycast->ray_y == 0) ? 1 : fabs(1 / t_raycast->ray_y));
		check_step(t_raycast, data_t);
		while (t_raycast->hit == 0)
			check_intersec(t_raycast, data_t);
		if (t_raycast->side == 0)
			t_raycast->perpWallDist = (t_raycast->mapX - data_t->position_x + (1 - t_raycast->stepX) / 2) / t_raycast->ray_x;
		else
			t_raycast->perpWallDist = (t_raycast->mapY - data_t->position_y + (1 - t_raycast->stepY) / 2) / t_raycast->ray_y;
		data_t->wall_size = (int)(data_t->res_h / t_raycast->perpWallDist);
		int deb = data_t->res_h / 2 - data_t->wall_size / 2;
		if (deb < 0)
			deb = 0;
		int end = deb + data_t->wall_size;
		if (end > data_t->res_h)
			end = data_t->res_h;

		// How much to increase the texture coordinate per screen pixel
	// double step = 1.0 * BLOC_SIZE / data_t->wall_size;
	int bits_per_pixel;
	int size_line;
	int endian;
	int size;
	char *test;

	size = 64;
	data_t->img_N_p = mlx_xpm_file_to_image(data_t->mlx_prog, data_t->tex_N, &size, &size);
	if ((test = mlx_get_data_addr(data_t->img_N_p ,&bits_per_pixel, &size_line, &endian)) == NULL)
		write(1, "error", 5);

		double wallX; //where exactly the wall was hit
	    if (t_raycast->side == 0) wallX = data_t->position_y + t_raycast->perpWallDist * t_raycast->ray_y;
	    else wallX = data_t->position_x + t_raycast->perpWallDist * t_raycast->ray_x;
		int wallY= floor((wallX - floor(wallX)) * BLOC_SIZE);


		wallX -= (int)wallX;
				// printf("%f\n", wallX);
		// printf("%d\n", wallX);
	    //x coordinate on the texture
	    // int texX = (int)wallX * (double)BLOC_SIZE;
		int texX = (int)(wallX * BLOC_SIZE);
	    if(t_raycast->side == 0 && t_raycast->ray_x > 0) texX = BLOC_SIZE - texX - 1;
	    if(t_raycast->side == 1 && t_raycast->ray_y < 0) texX = BLOC_SIZE - texX - 1;
		// printf("%d\n", texX);
		double step = 1.0 * BLOC_SIZE / data_t->wall_size;
	// Starting texture coordinate
	double texPos = (deb - data_t->res_h / 2 + data_t->wall_size / 2) * step;
	for(int y = deb; y<end; y++)
	{
	  // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
	  int texY = (int)texPos & ((int)BLOC_SIZE - 1);
	  texPos += step;
	  // printf("%d %d %f %f\n", texX, texY, step, texPos);
// (X position * 4 + 4 * Line size * Y position)
	  int color = color_pixel(test[texX * 4 + size_line * texY + 2], test[texX * 4 + size_line * texY + 1], test[texX * 4 + size_line * texY]);
//TRY WITHOUT COLOR CODING
	  // color = mlx_get_color_value(data_t->mlx_prog, color);
	  // printf("%d\n", color);
	  mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, y, color);
	}
	  //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
	  // if(side == 1) color = (color >> 1) & 8355711;
	  // buffer[y][x] = color;

		// print_column(data_t, i, t_raycast->side);
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
		mlx_put_image_to_window(data_t->mlx_prog,data_t->mlx_win,data_t->img_N_p,5, 5);
	// int i = size_line * 2;
	// printf("%d\n", endian);
	// printf("%d\n", bits_per_pixel);
	// printf("%d\n", size_line);
	// while (i < size_line * 3)
	// {
	// 	unsigned int icitri = test[i];
	// 	int r = (icitri >> 16)&0xff;
	// 	int g = (icitri >> 8)&0xff;
	// 	int b = (icitri)&0xff;
	// 	mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i++ - size_line, 0, icitri);
	// }
	// 	// printf("%d %d, %d\n", r, g, b);
	// 	// printf("%u\n",mlx_get_color_value(data_t->mlx_prog, test[i++]));
	// // unsigned int ici = test[size_line * 3 + 4];
	// // unsigned int icibis = test[size_line * 3 + 5];
	// // int icitri = test[size_line * 3 + 6];
	// // char ski = test[size_line * 3 + 4];
	// // char skii = test[size_line * 3 + 5];
	// // char skiii = test[size_line * 3 + 6];
	// // printf("%c %c %c\n", ski, skii, skiii);
	// // // printf("%u\n", mlx_get_color_value(data_t->mlx_prog, test[size_line * 3 + 7]));
	// // // printf("%u\n",mlx_get_color_value(data_t->mlx_prog, ici));
	// // // printf("%u\n",mlx_get_color_value(data_t->mlx_prog, icibis));
	// // // printf("%u\n",mlx_get_color_value(data_t->mlx_prog, icitri));
	// // printf("%d\n", (int)icitri);
	// // printf("%u\n", icitri);
	// //
	// // // // (unsigned int)color = mlx_get_color_value(data_t->mlx_prog, color);
	// //
	// //
	// // // color = rgb3(player->struct_side.pixel[2], player->struct_side.pixel[1],
	// // // player->struct_side.pixel[0]);
	// //
	// // r = (color >> 16)&0xff; // == color / 65536; && is used to mask other bits out    g = (color >> 8)&0xff;  // == color / 256    b = (color)&0xff;
	// // int r = (icitri >> 16)&0xff;
	// // int g = (icitri >> 8)&0xff;
	// // int b = (icitri)&0xff;
	// // printf("%d %d, %d\n", r, g, b);
	// // printf("%d\n", r<<16);
	// //
	// // int color = color_pixel(r, g, b);
	//
	// // int		index;
	// // char	*img;
	// // int		size_line;
	// //
	// // img = game->actual_text.img_data;
	// // size_line = game->actual_text.size_line;
	// // index = (int)(y * size_line + x * 4);
	// // return (ft_color(img[index + 2], img[index + 1], img[index]));
	//
	// // int index = color_pixel(test[size_line * 3 + 2 * 4], test[size_line * 3 + 2 * 4 + 1], test[size_line * 3 + 2 * 4 + 2]);
	// // // printf("%u\n", (unsigned int)index);
	// //
	// // new.r = (color1->r / 255) * (color2.r / 255) * 255;
	// // new.g = (color1->g / 255) * (color2.g / 255) * 255;
	// // new.b = (color1->b / 255) * (color2.b / 255) * 255;
	//
	// // mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, 30, 30, color_pixel(r, g, b));
	sleep(3);
}
