#include "cub3d.h"

char	*ft_strdup_map(const char *src)
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
	dest[i] = '\n';
	return (dest);
}

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
	while (s1[j] != '\n')
	{
		dest[j] = s1[j];
		j++;
	}
	dest[j] = '\n';
	j++;
	while (s2[k])
		dest[j++] = s2[k++];
	dest[j] = '\n';
	return (dest);
}

//called by ft_keyboard_press in move.c
//print black frame to reprint on without artefacts.
void	print_black(data_t *data_t)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < data_t->res_w)
	{
		while (i < data_t->res_h)
		{
			mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, j, i , (1+(1<<16)+(1<<8)));
			i++;
		}
		i = 0;
		j++;
	}
}

/* Called by check_map in map_checking.c
** Extract angle information in map and gives appropriates information in struct for raycasting.c */

void	give_angle(data_t *data_t)
{
	if (data_t->orientation == 'N')
	{
		data_t->direction_x = 0;
		data_t->direction_y = -1;
		data_t->camera_x = 2 * atan(0.66/1.0);
		data_t->camera_y = 0;
	}
	else if (data_t->orientation == 'E')
	{
		data_t->direction_x = 1;
		data_t->direction_y = 0;
		data_t->camera_x = 0;
		data_t->camera_y = 2 * atan(0.66/1.0);
	}
	else if (data_t->orientation == 'W')
	{
		data_t->direction_x = -1;
		data_t->direction_y = 0;
		data_t->camera_x = 0;
		data_t->camera_y = -(2 * atan(0.66/1.0));
	}
	else if (data_t->orientation == 'S')
	{
		data_t->direction_x = 0;
		data_t->direction_y = 1;
		data_t->camera_x = -(2 * atan(0.66/1.0));
		data_t->camera_y = 0;
	}
}
