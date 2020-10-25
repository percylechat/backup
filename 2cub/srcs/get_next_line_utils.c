/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:33:17 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/23 12:08:04 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		k;
	char	*dest;

	i = ft_chrlen(s1, '\0') + ft_chrlen(s2, '\0');
	j = 0;
	k = 0;
	if (!(dest = malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (s1[j])
	{
		dest[j] = s1[j];
		j++;
	}
	while (s2[k])
		dest[j++] = s2[k++];
	dest[j] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		j;
	int		i;

	i = 0;
	if (!src)
	{
		dest = malloc(1);
		dest[0] = '\0';
		return (dest);
	}
	else
		j = ft_chrlen(src, '\0');
	if (!(dest = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, int start, int len)
{
	int		i;
	int		l;
	char	*dest;

	i = (s) ? ft_chrlen(s, '\0') : 0;
	l = 0;
	if (!s || start > i)
	{
		if (!(dest = malloc(1)))
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	if (!(dest = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while ((l < len) && s[start])
		dest[l++] = s[start++];
	dest[l] = '\0';
	return (dest);
}

char	*new_buffer(char *buffer, char *reste)
{
	char *temp;

	temp = ft_strdup(buffer);
	free(buffer);
	buffer = ft_strjoin(reste, temp);
	free(temp);
	return (buffer);
}
