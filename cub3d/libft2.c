/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:36:39 by budal-bi          #+#    #+#             */
/*   Updated: 2020/07/12 19:31:49 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//joins 2 char arrays for the map?
char	*ft_strjoin_map(char *s1, char *s2)
{
	int		j;
	int		k;
	char	*dest;

	j = 0;
	k = 0;
	if (!(dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2)))
		return (NULL);
	while (s1[j])
	{
		dest[j] = s1[j];
		j++;
	}
	dest[j++] = '\n';
	while (s2[k])
		dest[j++] = s2[k++];
	dest[j] = '\0';
	return (dest);
}

//tells if character is a digit or not.
int		ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

//moves memory from a place to another.
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
