#include "cub3d.h"

t_tex get_tex_N(data_t *data_t)
{
	int size;
	t_tex tex_N;

	size = (int)BLOC_SIZE;
	tex_N.address = mlx_xpm_file_to_image(data_t->mlx_prog, data_t->tex_N, &size, &size);
	tex_N.content = mlx_get_data_addr(tex_N.address ,&tex_N.bits_per_pixel, &tex_N.size_line, &tex_N.endian);
	data_t->tex_N_s = &tex_N;
	return (tex_N);
}

t_tex get_tex_S(data_t *data_t)
{
	int size;
	t_tex tex_S;

	size = (int)BLOC_SIZE;
	tex_S.address = mlx_xpm_file_to_image(data_t->mlx_prog, data_t->tex_S, &size, &size);
	tex_S.content = mlx_get_data_addr(tex_S.address ,&tex_S.bits_per_pixel, &tex_S.size_line, &tex_S.endian);
	data_t->tex_S_s = &tex_S;
	return (tex_S);
}

t_tex get_tex_W(data_t *data_t)
{
	int size;
	t_tex tex_W;

	size = (int)BLOC_SIZE;
	tex_W.address = mlx_xpm_file_to_image(data_t->mlx_prog, data_t->tex_W, &size, &size);
	tex_W.content = mlx_get_data_addr(tex_W.address ,&tex_W.bits_per_pixel, &tex_W.size_line, &tex_W.endian);
	data_t->tex_W_s = &tex_W;
	return (tex_W);
}

t_tex get_tex_E(data_t *data_t)
{
	int size;
	t_tex tex_E;

	size = (int)BLOC_SIZE;
	tex_E.address = mlx_xpm_file_to_image(data_t->mlx_prog, data_t->tex_E, &size, &size);
	tex_E.content = mlx_get_data_addr(tex_E.address ,&tex_E.bits_per_pixel, &tex_E.size_line, &tex_E.endian);
	data_t->tex_E_s = &tex_E;
	return (tex_E);
}
t_tex get_tex_sp(data_t *data_t)
{
	int size;
	t_tex tex_sp;

	size = (int)BLOC_SIZE;
	tex_sp.address = mlx_xpm_file_to_image(data_t->mlx_prog, data_t->tex_sprite, &size, &size);
	tex_sp.content = mlx_get_data_addr(tex_sp.address ,&tex_sp.bits_per_pixel, &tex_sp.size_line, &tex_sp.endian);
	data_t->tex_Sp_s = &tex_sp;
	return (tex_sp);
}

void 	init_texture(data_t *data_t)
{
	get_tex_sp(data_t);
	// get_tex_N(data_t);
	printf("%x\n", data_t->tex_Sp_s);
	printf("%x\n", data_t->tex_N_s);
	get_tex_S(data_t);
	get_tex_W(data_t);
	get_tex_E(data_t);
	printf("%x\n", data_t->tex_N_s);
		printf("%x\n", data_t->tex_S_s);
}

t_tex choose_texture(data_t *data_t,t_raycast *t_raycast, int i)
{
	t_tex tex_return;

	if (t_raycast->side == 1)
	{
		if (t_raycast->ray_y > 0)
			return (tex_return = get_tex_N(data_t));
		else
			return (tex_return = get_tex_S(data_t));
	}
	else
	{
		if (t_raycast->ray_x > 0)
			return (tex_return = get_tex_W(data_t));
		else
			return (tex_return = get_tex_E(data_t));
	}
}
