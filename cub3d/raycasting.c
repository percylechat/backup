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

void 	print_sprite(data_t *data_t, int i, t_sprite *t_sprite, t_raycast *t_raycast)
{
	t_list *latest;
	float buffer;
	t_tex tex_sprite;

	tex_sprite = get_tex_sp(data_t);
	buffer = t_raycast->perpWallDist;
	while (t_sprite->nbr_sprite != 0)
	{
		latest = ft_lstlast(t_sprite->list);
		double spriteX = latest->x - data_t->position_x;
		double spriteY = latest->y - data_t->position_y;
		double invDet = 1.0 / (data_t->camera_x * data_t->direction_y - data_t->direction_x * data_t->camera_y); //required for correct matrix multiplication
		double transformX = invDet * (data_t->direction_y * spriteX - data_t->direction_x * spriteY);
		double transformY = invDet * ((data_t->camera_y * -1)* spriteX + data_t->camera_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
		int spriteScreenX = (int)((data_t->res_w / 2) * (1 + transformX / transformY));//calculate height of the sprite on screen
		int spriteHeight = abs((int)(data_t->res_h / transformY)); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + data_t->res_h / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + data_t->res_h / 2;
 		if (drawEndY >= data_t->res_h)
			drawEndY = data_t->res_h - 1;//calculate width of the sprite
		int spriteWidth = abs((int)data_t->res_h / transformY);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= data_t->res_w)
			drawEndX = data_t->res_w - 1;
		for(int stripe = drawStartX; stripe < drawEndX; stripe++) //loop through every vertical stripe of the sprite on screen
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * BLOC_SIZE / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < data_t->res_w && transformY < t_raycast->perpWallDist)
			{
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - data_t->res_h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * BLOC_SIZE) / spriteHeight) / 256;//bloc_size = texheight, a mod?
					t_sprite->color = color_pixel(tex_sprite.content[texX * 4 + tex_sprite.size_line * texY], tex_sprite.content[texX * 4 + tex_sprite.size_line * texY + 1], tex_sprite.content[texX * 4 + tex_sprite.size_line * texY + 2]);
					mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, texY++, t_sprite->color);
					// Uint32 color = texture[sprite[spriteOrder[i]].texture][tex_sprite.size_line * texY + texX]; //get current color from the texture
					// if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
				}
			}
		}
	t_sprite->nbr_sprite--;
	free(latest);
	}
}

void	drawRays3d(data_t *data_t)
{
	int i;
	t_raycast t_raycast[1];
	t_sprite t_sprite[1];
	float *buffer;

	i = 0;
	if (!(buffer = malloc(sizeof(float) * data_t->res_w)))
		return;
	while (i <= data_t->res_w)
	{
		t_sprite->nbr_sprite = 0;
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
		if (t_sprite->nbr_sprite > 0)
			print_sprite(data_t, i, t_sprite, t_raycast);
		data_t->wall_size = 0;
		i += 1;
	}
}
