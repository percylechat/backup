#include "cub3d.h"

void	*ft_memcpy_line(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*buffer_d;
	char	*buffer_s;

	if ((dst == src) || (!dst && !src) || !n)
		return ((void *)dst);
	buffer_s = (char *)src;
	buffer_d = dst;
	i = 0;
	while (i < n)
	{
		buffer_d[i] = buffer_s[i];
		i++;
	}
	buffer_d[i] = '\0';
	return ((void *)dst);
}

char		**ft_split_map(data_t *data_t)
{
	int		i;
	int		j;
	int		k;
	char *test;

	j = 0;
	k = 0;
	i = 0;
	if (!(data_t->maptab = malloc(sizeof(char *) * (data_t->line + 1))))
		return (NULL);
	while (k < data_t->line)
	{
		test = ft_memcpy_line(&data_t->maptab[k], &data_t->map[i], data_t->column_size[k]);
		data_t->maptab[k] = ft_strdup(test);
		i += data_t->column_size[k];
		k++;
	}
	data_t->maptab[k] = NULL;
	return (data_t->maptab);
}
