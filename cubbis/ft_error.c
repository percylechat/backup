#include "cub3d.h"

void 	ft_quit_map(data_t *data_t, char *str)
{
	int i;

	i = 0;
	ft_putstr_fd(str, 1);
	free(data_t->tex_n);
	free(data_t->tex_s);
	free(data_t->tex_w);
	free(data_t->tex_e);
	free(data_t->tex_sprite);
	free(data_t->map);
	while (i < data_t->line + 1)
		free(data_t->maptab[i++]);
	free(data_t->maptab);
	if (data_t->sprite_spot)
		free(data_t->sprite_spot);
	if (data_t->mlx_prog)
		free(data_t->mlx_prog);
	if (data_t->mlx_win)
		free(data_t->mlx_win);
	if (data_t->mlx_img)
		free (data_t->mlx_img);
	exit(0);
}

void	error_sanity_check(data_t *data_t)
{
	ft_putstr_fd("Error\nIncomplete map data.", 1);
	if (data_t->tex_n)
		free(data_t->tex_n);
	if (data_t->tex_s)
		free(data_t->tex_s);
	if (data_t->tex_w)
		free(data_t->tex_w);
	if (data_t->tex_e)
		free(data_t->tex_e);
	if (data_t->tex_sprite)
		free(data_t->tex_sprite);
	free(data_t->map);
	exit(0);
}

void	error_color(data_t *data_t)
{
	ft_putstr_fd("Error\nColors should be separated by commas, each value between 0 and 255", 1);
	if (data_t->tex_n)
		free(data_t->tex_n);
	if (data_t->tex_s)
		free(data_t->tex_s);
	if (data_t->tex_w)
		free(data_t->tex_w);
	if (data_t->tex_e)
		free(data_t->tex_e);
	if (data_t->tex_sprite)
		free(data_t->tex_sprite);
	exit(0);
}
