/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:20:44 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/11 15:19:28 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**ft_split_map(data_t *t_m)
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
