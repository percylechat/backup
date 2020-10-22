/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:36:39 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/11 13:16:11 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	size_t			j;
	unsigned char	*buffer_d;
	unsigned char	*buffer_s;
	unsigned char	buffer[len];

	if (!len || (dst == src) || (!dst && !src))
		return (dst);
	buffer_s = (unsigned char *)src;
	buffer_d = (unsigned char *)dst;
	i = 0;
	j = 0;
	while (i < len)
	{
		buffer[i] = buffer_s[i];
		i++;
	}
	while (j < len)
	{
		buffer_d[j] = buffer[j];
		j++;
	}
	return (dst);
}
