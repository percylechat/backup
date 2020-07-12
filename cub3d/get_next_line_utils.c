/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:33:17 by budal-bi          #+#    #+#             */
/*   Updated: 2020/07/12 19:19:14 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//OLD PROJECT, subordinate functions
//read line by line in a file, took me 2 months -_-
//shouldn't be a source of issues since it has been debugged.

int		ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		k;
	char	*dest;

	i = ft_strlen(s1) + ft_strlen(s2);
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
		j = ft_strlen((char *)src);
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

int		ft_custom_strchr(const char *s)
{
	int		i;

	i = 0;
	if (!s || s == NULL)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_substr(char const *s, int start, int len)
{
	int		i;
	int		l;
	char	*dest;

	i = (s) ? ft_strlen(s) : 0;
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
