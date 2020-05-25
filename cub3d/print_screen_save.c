#include "cub3d.h"

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
