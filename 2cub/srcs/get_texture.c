/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:45:02 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/12 15:55:11 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex	get_tex_n(t_main *t_m)
{
	int		size;
	t_tex	tex_n;

	size = (int)BLOC_SIZE;
	if ((tex_n.address = mlx_xpm_file_to_image(t_m->mlx_prog, t_m->tex_n,
&size, &size)) == NULL)
		return (tex_n);
	tex_n.content = mlx_get_data_addr(tex_n.address, &tex_n.bits_per_pixel,
&tex_n.sl, &tex_n.endian);
	return (tex_n);
}

t_tex	get_tex_s(t_main *t_m)
{
	int		size;
	t_tex	tex_s;

	size = (int)BLOC_SIZE;
	if ((tex_s.address = mlx_xpm_file_to_image(t_m->mlx_prog, t_m->tex_s,
&size, &size)) == NULL)
		return (tex_s);
	tex_s.content = mlx_get_data_addr(tex_s.address, &tex_s.bits_per_pixel,
&tex_s.sl, &tex_s.endian);
	return (tex_s);
}

t_tex	get_tex_w(t_main *t_m)
{
	int		size;
	t_tex	tex_w;

	size = (int)BLOC_SIZE;
	if ((tex_w.address = mlx_xpm_file_to_image(t_m->mlx_prog, t_m->tex_w,
&size, &size)) == NULL)
		return (tex_w);
	tex_w.content = mlx_get_data_addr(tex_w.address, &tex_w.bits_per_pixel,
&tex_w.sl, &tex_w.endian);
	return (tex_w);
}

t_tex	get_tex_e(t_main *t_m)
{
	int		size;
	t_tex	tex_e;

	size = (int)BLOC_SIZE;
	if ((tex_e.address = mlx_xpm_file_to_image(t_m->mlx_prog, t_m->tex_e,
	&size, &size)) == NULL)
		return (tex_e);
	tex_e.content = mlx_get_data_addr(tex_e.address, &tex_e.bits_per_pixel,
	&tex_e.sl, &tex_e.endian);
	return (tex_e);
}

t_tex	choose_texture(t_main *t_m, t_raycast *t_r)
{
	if (t_r->side == 1)
	{
		if (t_r->ray_y > 0)
			return (t_m->n_tex);
		else
			return (t_m->s_tex);
	}
	else
	{
		if (t_r->ray_x > 0)
			return (t_m->w_tex);
		else
			return (t_m->e_tex);
	}
}
