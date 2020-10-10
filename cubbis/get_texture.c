#include "cub3d.h"

t_tex get_tex_N(data_t *data_t)
{
	int size;
	t_tex tex_N;

	size = (int)BLOC_SIZE;
	if ((tex_N.address = mlx_xpm_file_to_image(data_t->mlx_prog, data_t->tex_N, &size, &size)) == NULL)
		return (tex_N);
	tex_N.content = mlx_get_data_addr(tex_N.address ,&tex_N.bits_per_pixel, &tex_N.size_line, &tex_N.endian);
	return (tex_N);
}

t_tex get_tex_S(data_t *data_t)
{
	int size;
	t_tex tex_S;

	size = (int)BLOC_SIZE;
	if ((tex_S.address = mlx_xpm_file_to_image(data_t->mlx_prog, data_t->tex_S, &size, &size)) == NULL)
		return (tex_S);
	tex_S.content = mlx_get_data_addr(tex_S.address ,&tex_S.bits_per_pixel, &tex_S.size_line, &tex_S.endian);
	return (tex_S);
}

t_tex get_tex_W(data_t *data_t)
{
	int size;
	t_tex tex_W;

	size = (int)BLOC_SIZE;
	if ((tex_W.address = mlx_xpm_file_to_image(data_t->mlx_prog, data_t->tex_W, &size, &size)) == NULL)
		return (tex_W);
	tex_W.content = mlx_get_data_addr(tex_W.address ,&tex_W.bits_per_pixel, &tex_W.size_line, &tex_W.endian);
	return (tex_W);
}

t_tex get_tex_E(data_t *data_t)
{
	int size;
	t_tex tex_E;

	size = (int)BLOC_SIZE;
	if ((tex_E.address = mlx_xpm_file_to_image(data_t->mlx_prog, data_t->tex_E, &size, &size)) == NULL)
		return (tex_E);
	tex_E.content = mlx_get_data_addr(tex_E.address ,&tex_E.bits_per_pixel, &tex_E.size_line, &tex_E.endian);
	return (tex_E);
}

t_tex get_tex_sp(data_t *data_t)
{
	int size;
	t_tex tex_sp;

	size = (int)BLOC_SIZE;
	if ((tex_sp.address = mlx_xpm_file_to_image(data_t->mlx_prog, data_t->tex_sprite, &size, &size)) == NULL)
		return (tex_sp);
	tex_sp.content = mlx_get_data_addr(tex_sp.address ,&tex_sp.bits_per_pixel, &tex_sp.size_line, &tex_sp.endian);
	return (tex_sp);
}

t_tex choose_texture(data_t *data_t,t_raycast *t_raycast)
{
	t_tex tex_return;

	if (t_raycast->side == 1)
	{
		if (t_raycast->ray_y > 0)
			return (tex_return = data_t->N_tex);
		else
			return (tex_return = data_t->S_tex);
	}
	else
	{
		if (t_raycast->ray_x > 0)
			return (tex_return = data_t->W_tex);
		else
			return (tex_return = data_t->E_tex);
	}
}
