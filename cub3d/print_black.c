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
			mlx_pixel_put(data_t->mlx_prog, data_t->mlx_win, j, i , (1+(1<<16)+(1<<8));
			i++;
		}
		i = 0;
		j++;
	}
}
