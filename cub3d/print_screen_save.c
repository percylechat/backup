#include "cub3d.h"


float		give_udlr(data_t *data_t, int i)
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
	// if (b > data_t->res_w / 2)
	// 	b = data_t->direction - b;
	// else if (b < data_t->res_w / 2)
	// 	b = data_t->direction + b;
	// printf("%d", b);
	return (0.0);
}

void dist_finder(data_t *data_t, int inter_x, int inter_y, int i)
{
	float exp_x;
	float exp_y;
	float res_exp;

	// printf("%d\n", ((data_t->position_x) * 64 + data_t->sub_position_x));
	// printf("%d\n", inter_x);
	// printf("%d\n", ((data_t->position_y) * 64 + data_t->sub_position_y));
	// printf("%d\n", inter_y);
	exp_x = (((data_t->position_x) * 64 + data_t->sub_position_x) - (inter_x)) * (((data_t->position_x) * 64 + data_t->sub_position_x) - (inter_x));

	exp_y = ((data_t->position_y * 64 + data_t->sub_position_y) - inter_y) * ((data_t->position_y * 64 + data_t->sub_position_y) - inter_y);
	// printf("%f\n", exp_x);
	// printf("%f\n", exp_y);
	res_exp =  exp_x + exp_y;
	// printf("%f\n", res_exp);
	if (i == 1)
		data_t->dist_vert = (int)sqrt(res_exp);
	else
		data_t->dist_hor = (int)sqrt(res_exp);
	printf("dist %d\n", (int)data_t->dist_hor);
}

// printf("pos y; %d\n", data_t->position_y);
// printf("pos x; %d\n", data_t->position_x);
// printf("inter y; %d\n", inter_y);
// printf("coeff y; %d\n", coeff_y);
// printf("inter x; %d\n", inter_x);
// printf("coeff x; %d\n", coeff_x);
// printf("wall found");

void	find_vert_dist(data_t *data_t, int ray)
{
	int		inter_x;
	int		inter_y;
	int		coeff_x;
	int		coeff_y;
	float	ray_rad;

	ray_rad = ray * M_PI / 180;
	if (data_t->leftright == 1)
	{
		inter_x = (((data_t->position_x) * 64 + data_t->sub_position_x) / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
		coeff_x = BLOC_SIZE;
	}
	else
	{
		inter_x = (((data_t->position_x) * 64 + data_t->sub_position_x) / BLOC_SIZE) * BLOC_SIZE - 1;
		coeff_x = BLOC_SIZE * -1;
	}
	inter_y = ((data_t->position_y) * 64 + data_t->sub_position_y) + (((data_t->position_x) * 64 + data_t->sub_position_x) - inter_x) * tan(ray * M_PI / 180);
	coeff_y = BLOC_SIZE * tan(ray * M_PI / 180);
	printf("%f\n", BLOC_SIZE);
	printf("ray %d\n", ray);
	printf("ray rad %f\n", ray_rad);
	printf("tan ray %f\n", tan(ray_rad));
	printf("pos y; %d\n", data_t->position_y);
	printf("pos x; %d\n", data_t->position_x);
	printf("inter y; %d\n", inter_y);
	printf("coeff y; %d\n", coeff_y);
	printf("inter x; %d\n", inter_x);
	printf("coeff x; %d\n", coeff_x);
	while (check_for_obstacle(inter_x, inter_y, data_t) != 1)
	{
		inter_x += coeff_x;
		inter_y -= coeff_y;
	}
	dist_finder(data_t, inter_x, inter_y, 1);
}

void	find_hor_dist(data_t *data_t, float ray)
{
	int		inter_x;
	int		inter_y;
	int		coeff_x;
	int		coeff_y;

	if (data_t->updown == 1)
	{
		inter_y = (((data_t->position_y - 1) * 64 + data_t->sub_position_y)/BLOC_SIZE) * (BLOC_SIZE) - 1;
		coeff_y = BLOC_SIZE * -1;
	}
	else
	{
		inter_y = (((data_t->position_y - 1) * 64 + data_t->sub_position_y)/BLOC_SIZE) * (BLOC_SIZE) + BLOC_SIZE;
		coeff_y = BLOC_SIZE;
	}
	inter_x = (data_t->position_x * 64 + data_t->sub_position_x) + (((data_t->position_y - 1) * 64 + data_t->sub_position_y) - inter_y) / tan(ray * M_PI / 180);
	coeff_x = BLOC_SIZE / tan(ray * M_PI / 180);
	while (check_for_obstacle(inter_x, inter_y, data_t)
	!= 1)
	{
		inter_x += coeff_x;
		inter_y += coeff_y;
	}
	dist_finder(data_t, inter_x, inter_y, 0);
}

void	print_column(data_t *data_t, int i)
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
	// 		mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, j,
	// data_t->color_ceiling);
			j++;
		}
		while (k < data_t->wall_size && j < data_t->res_h)
		{
			mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, j, (255
	+(255<<16)+(1<<8)));
			k++;
			j++;
		}
		mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, j,
	data_t->color_floor);
	j++;
	}
}

float get_res_f(data_t *data_t)
{
	float i;
	int j;
	j = 0;
	i = 0.0;
	while (j != data_t->res_w)
	{
		j++;
		i += 1.0;
	}
	// printf("%f\n", i);
	return (i);
}

void	new_screen(data_t *data_t)
{
	int		i;
	float	b;
	float	ray;
	float	ray_change;
	float res;
	i = 1;
	ray = 87.0;
	res = get_res_f(data_t);
	ray_change = FOV/res;
	// while (i <= data_t->res_w)
	// {
		b = give_udlr(data_t, i);
		printf("ray%f\n", ray);
		// if (ray != 90.0)
			find_vert_dist(data_t, (int)ray);
		find_hor_dist(data_t, ray);
		if (data_t->dist_hor > data_t->dist_vert)
			data_t->wall_size = data_t->dist_vert;
		else
			data_t->wall_size = data_t->dist_hor;
		print_column(data_t, i);
	  	i++;
		// printf("%.5f\n", ray_change);
		ray += ray_change;
	// }
}

// // printf("vert: %d", data_t->dist_vert);
// // printf("hor: %d", data_t->dist_hor);
// 	// if (data_t->dist_vert < data_t->dist_hor)
// 	// 	data_t->dist_hor =  data_t->dist_vert;
// 	// if (i < data_t->res_w / 2)
// 		// data_t->wall_size = (BLOC_SIZE / (data_t->dist_hor * cos((FOV/2) * M_PI / 180))) * ((data_t->res_w / 2) / tan((FOV/2) * M_PI / 180));
// 	// else
//   	// 	data_t->wall_size = (BLOC_SIZE / (data_t->dist_hor * cos((FOV / 2) * -1))) * ((data_t->res_w / 2) / tan((FOV/2) * M_PI / 180));


********************************************************************

int give_udlr(data_t *data_t, int i)
{
  int a;
  int b;

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
  return (b);
}

void find_vert_dist(data_t *data_t, int b)
{
  int inter_x;
  int inter_y;
  int coeff_x;
  int coeff_y;

  if (data_t->leftright == 1)
  {
    inter_x = data_t->position_x * BLOC_SIZE + BLOC_SIZE;
    coeff_x = BLOC_SIZE;
  }
  else
  {
    inter_x = data_t->position_x * BLOC_SIZE - 1;
    coeff_x = BLOC_SIZE * -1;
  }
  inter_y = data_t->position_y + (data_t->position_x - inter_x) * tan(b * M_PI / 180);
  coeff_y = BLOC_SIZE / tan(b * M_PI / 180);
  while (check_for_obstacle((inter_x + coeff_x), (inter_y + coeff_y), data_t) != 1)
  {
    inter_x += coeff_x;
    inter_y += coeff_y;
  }
  data_t->dist_vert = abs(data_t->position_x - ((inter_x + coeff_x))) / cos(b * M_PI / 180);
}

void find_hor_dist(data_t *data_t, int b)
{
  int inter_x;
  int inter_y;
  int coeff_x;
  int coeff_y;

  if (data_t->updown == 1)
  {
    inter_y = data_t->position_y * BLOC_SIZE - 1;
    coeff_y = BLOC_SIZE * -1;
  }
  else
  {
    inter_y = data_t->position_y * BLOC_SIZE + BLOC_SIZE;
    coeff_y = BLOC_SIZE;
  }
  inter_x = data_t->position_x + (data_t->position_y - inter_y) / tan(b * M_PI / 180);
  coeff_x = BLOC_SIZE / tan(b * M_PI / 180);
  while (check_for_obstacle((inter_x + coeff_x), (inter_y + coeff_y), data_t) != 1)
  {
    inter_x += coeff_x;
    inter_y += coeff_y;
  }
  data_t->dist_hor = abs(data_t->position_x - ((inter_x + coeff_x))) / cos(b * M_PI / 180);
}

void print_column(data_t *data_t, int i)
{
  int j;

  j = 0;
  while (j < data_t->res_h)
  {
    while (j < (data_t->wall_size / 4))
    {
      mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, j, data_t->color_ceiling);
      j++;
    }
    while (j < ((data_t->wall_size / 4) + data_t->wall_size))
    {
      mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, j, (255 +(255<<16)+(1<<8)));
      j++;
    }
    mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, j++, data_t->color_floor);
    j++;
  }
}

void new_screen(data_t *data_t)
{
  int i;
  int b;

  i = 0;
  // while (i < data_t->res_w)
  // {
    b = give_udlr(data_t, i);
    find_vert_dist(data_t, b);
    find_hor_dist(data_t, b);
    printf("hor%d\n", data_t->dist_hor);
        printf("vert%d\n", data_t->dist_vert);
    if (data_t->dist_vert < data_t->dist_hor)
      data_t->dist_hor =  data_t->dist_vert;
    // if (i < data_t->res_w / 2)
      data_t->wall_size = (BLOC_SIZE / (data_t->dist_hor * cos((FOV/2) * M_PI / 180))) * ((data_t->res_w / 2) / tan((FOV/2) * M_PI / 180));
    // else
      // data_t->wall_size = (BLOC_SIZE / (data_t->dist_hor * cos((FOV / 2) * -1))) * ((data_t->res_w / 2) / tan((FOV/2) * M_PI / 180)));
    print_column(data_t, i);
  //   i++;
  // }
}
