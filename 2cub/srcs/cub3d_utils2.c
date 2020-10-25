/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:20:44 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/21 16:42:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_res(t_main *t_m)
{
	int rh;
	int rw;

	mlx_get_screen_size(t_m->mlx_prog, &rw, &rh);
	if (t_m->res_w > rw)
		t_m->res_w = rw;
	if (t_m->res_h > rh)
		t_m->res_h = rh;
}

char	*set_reste(char *reste)
{
	reste = malloc(1);
	reste[0] = '\0';
	return (reste);
}

t_tex	get_tex_sp(t_main *t_m)
{
	int		size;
	t_tex	tex_sp;

	size = (int)BLOC_SIZE;
	if ((tex_sp.address = mlx_xpm_file_to_image(t_m->mlx_prog,
t_m->tex_sprite, &size, &size)) == NULL)
		return (tex_sp);
	tex_sp.content = mlx_get_data_addr(tex_sp.address, &tex_sp.bits_per_pixel,
&tex_sp.sl, &tex_sp.endian);
	return (tex_sp);
}

char	*line_copy(char *src, int i)
{
	int		j;
	char	*dst;

	j = 0;
	if (!(dst = malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (j < i)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

char	**ft_split_map(t_main *t_m)
{
	int		i;
	int		k;

	k = 0;
	i = 0;
	if (!(t_m->maptab = malloc(sizeof(char *) * (t_m->line + 1))))
		return (NULL);
	while (k < t_m->line)
	{
		t_m->maptab[k] = line_copy(&t_m->map[i], t_m->column_size[k]);
		i += t_m->column_size[k];
		k++;
	}
	t_m->maptab[k] = NULL;
	return (t_m->maptab);
}
