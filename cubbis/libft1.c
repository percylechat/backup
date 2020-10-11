/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:49:16 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/11 13:16:54 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		conv_char_int(char str, int k)
{
	k *= 10;
	k += str - 48;
	return (k);
}

int				ft_atoi(const char *str)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||
		str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j++;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		k = conv_char_int(str[i], k);
		i++;
	}
	if (j % 2 != 0)
		return (k * -1);
	return (k);
}

static int		trim_first(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (set[j] && s1[i])
	{
		while (s1[i] != set[j] && set[j])
			j++;
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
	}
	return (i);
}

static int		trim_last(char const *s1, char const *set, int k)
{
	int		j;

	j = 0;
	while (set[j])
	{
		while (s1[k] != set[j] && set[j])
			j++;
		if (s1[k] == set[j])
		{
			k--;
			j = 0;
		}
	}
	return (k);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*dest;

	if (!set)
		return (ft_strdup(s1));
	k = ft_strlen(s1);
	i = trim_first(s1, set);
	if (i == k)
	{
		if (!(dest = malloc(1)))
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	j = trim_last(s1, set, k);
	dest = ft_substr((char *)s1, i, j - i + 1);
	return (dest);
}
