/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:36:39 by budal-bi          #+#    #+#             */
/*   Updated: 2020/05/09 13:57:59 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int		ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}
