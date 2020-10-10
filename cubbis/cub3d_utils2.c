/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:20:44 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/10 18:20:45 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *line_copy(char *src, int i)
{
	int j;
	char *dst;

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

char		**ft_split_map(data_t *data_t)
{
	int		i;
	int		k;

	k = 0;
	i = 0;
	if (!(data_t->maptab = malloc(sizeof(char *) * (data_t->line + 1))))
		return (NULL);
	while (k < data_t->line)
	{
		data_t->maptab[k] = line_copy(&data_t->map[i], data_t->column_size[k]);
		i += data_t->column_size[k];
		k++;
	}
	data_t->maptab[k] = NULL;
	return (data_t->maptab);
}
