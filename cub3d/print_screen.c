#include "cub3d.h"

int		give_udlr(data_t *data_t, int i)
{
	int		a;
	int		b;

	a = FOV / data_t->res_w * i;
	b = FOV - (30 - a);
	if (b > 0 && b < 180)
		data_t->updown = 1;
	else
		data_t->updown = 0;
	if (b > 90 && b < 270)
		data_t->leftright = 0;
	else
		data_t->leftright = 1;
	if (b > data_t->res_w / 2)
		b = data_t->direction - b;
	else if (b < data_t->res_w / 2)
		b = data_t->direction + b;
	printf("%d", b);
	return (b);
}

void	find_vert_dist(data_t *data_t, float ray)
{
	int		inter_x;
	int		inter_y;
	int		coeff_x;
	int		coeff_y;

	if (data_t->leftright == 1)
	{
		inter_x = (accurate_position(data_t, 1) / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
		coeff_x = BLOC_SIZE;
	}
	else
	{
		inter_x = (accurate_position(data_t, 1) / BLOC_SIZE) * BLOC_SIZE - 1;
		coeff_x = BLOC_SIZE * -1;
	}
	inter_y = accurate_position(data_t, 0) + (accurate_position(data_t, 1) - inter_x) * tan(ray * M_PI / 180);
	coeff_y = BLOC_SIZE / tan(ray * M_PI / 180);
	while (check_for_obstacle((inter_x + coeff_x), (inter_y + coeff_y), data_t)
	!= 1)
	{
		inter_x += coeff_x;
		inter_y += coeff_y;
	}
	// printf("wall found");
	data_t->dist_vert = sqrt(exp(accurate_position(data_t, 1) - (inter_x + coeff_x)) + exp(accurate_position(data_t, 0) - (inter_y + coeff_y)));
	// fabs(accurate_position(data_t, 0) - (inter_y + coeff_y) / cos(ray * M_PI / 180));
}

void	find_hor_dist(data_t *data_t, float ray)
{
	int		inter_x;
	int		inter_y;
	int		coeff_x;
	int		coeff_y;

	if (data_t->updown == 1)
	{
		inter_y = (accurate_position(data_t, 0)/BLOC_SIZE) * (BLOC_SIZE) - 1;
		coeff_y = BLOC_SIZE * -1;
	}
	else
	{
		inter_y = (accurate_position(data_t, 0)/BLOC_SIZE) * (BLOC_SIZE) + BLOC_SIZE;
		coeff_y = BLOC_SIZE;
	}
	inter_x = accurate_position(data_t, 1) + (accurate_position(data_t, 0) - inter_y) / tan(ray * M_PI / 180);
	coeff_x = BLOC_SIZE / tan(ray * M_PI / 180);
	while (check_for_obstacle((inter_x + coeff_x), (inter_y + coeff_y), data_t)
	!= 1)
	{
		inter_x += coeff_x;
		inter_y += coeff_y;
	}
	data_t->dist_hor = sqrt(exp(accurate_position(data_t, 1) - (inter_x + coeff_x)) + exp(accurate_position(data_t, 0) - (inter_y + coeff_y)));
	// fabs(accurate_position(data_t, 1) - (inter_x + coeff_x) / cos(ray * M_PI / 180));
}

void	print_column(data_t *data_t, int i)
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
		while (k < data_t->wall_size)
		{
			mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, j, (255
	+(255<<16)+(1<<8)));
			k++;
			j++;
		}
		mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, j++,
	data_t->color_floor);
	}
}

void	new_screen(data_t *data_t)
{
	int		i;
	int		b;
	float	ray;
	float	ray_change;
	i = 0;
	b = give_udlr(data_t, i);
	ray = b;
	ray_change = FOV / data_t->res_w;

	while (i < data_t->res_w)
	{
		find_vert_dist(data_t, ray);
		find_hor_dist(data_t, ray);
		if (data_t->dist_hor > data_t->dist_vert)
			data_t->wall_size = data_t->dist_vert;
		else
			data_t->wall_size = data_t->dist_hor;
	// // printf("vert: %d", data_t->dist_vert);
	// // printf("hor: %d", data_t->dist_hor);
	// 	// if (data_t->dist_vert < data_t->dist_hor)
	// 	// 	data_t->dist_hor =  data_t->dist_vert;
	// 	// if (i < data_t->res_w / 2)
	// 		// data_t->wall_size = (BLOC_SIZE / (data_t->dist_hor * cos((FOV/2) * M_PI / 180))) * ((data_t->res_w / 2) / tan((FOV/2) * M_PI / 180));
	// 	// else
	//   	// 	data_t->wall_size = (BLOC_SIZE / (data_t->dist_hor * cos((FOV / 2) * -1))) * ((data_t->res_w / 2) / tan((FOV/2) * M_PI / 180));
		print_column(data_t, i);
	  	i++;
		ray -= ray_change;
	}
}
