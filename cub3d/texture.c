#include "cub3d.h"

void	text_print(t_tex tex, int h, t_print *t_print, data_t *data_t, int i)
{
	t_print->texY = (int)t_print->texPos & ((int)BLOC_SIZE - 1);
	t_print->texPos += t_print->step;
	t_print->color = color_pixel(tex.content[t_print->texX * 4 + tex.size_line
* t_print->texY + 2], tex.content[t_print->texX * 4 + tex.size_line *
t_print->texY + 1], tex.content[t_print->texX * 4 + tex.size_line *
t_print->texY]);
	mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, h, t_print->color);
}

void	print_wall(data_t *data_t, t_raycast *t_raycast, int i, t_print *t_print)
{
	t_tex tex;
	int h;

	h = 0;
	t_print->step = 1.0 * BLOC_SIZE / data_t->wall_size;
	t_print->texPos = (t_print->deb - data_t->res_h / 2 + data_t->wall_size / 2)
 * t_print->step;
	tex = choose_texture(data_t, t_raycast, i);
	while (h < data_t->res_h)
	{
		while (h < t_print->deb)
			mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, h++,
data_t->color_floor);
		while (h > t_print->deb && h < t_print->end)
		{
			text_print(tex, h, t_print, data_t, i);
			h++;
		}
		mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, i, h++,
data_t->color_ceiling);
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
		t_print->wallX = data_t->position_y + t_raycast->perpWallDist *
t_raycast->ray_y;
	else
		t_print->wallX = data_t->position_x + t_raycast->perpWallDist *
t_raycast->ray_x;
	t_print->wallY = floor((t_print->wallX - floor(t_print->wallX)) *
BLOC_SIZE);
	t_print->wallX -= (int)t_print->wallX;
	t_print->texX = (int)(t_print->wallX * BLOC_SIZE);
	if (t_raycast->side == 0 && t_raycast->ray_x > 0)
		t_print->texX = BLOC_SIZE - t_print->texX - 1;
	if (t_raycast->side == 1 && t_raycast->ray_y < 0)
		t_print->texX = BLOC_SIZE - t_print->texX - 1;
	print_wall(data_t, t_raycast, i, t_print);
}
