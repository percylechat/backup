#include "cub3d.h"

//WIP
//should create a bmp file of the first screen of option is called during execution.
//should be called by main.


void	ft_save(data_t *data_t)
{
	int fd;
	int size;
	int zero;
	int header;
	int info;
	short int one;
	short int four;
	int bpp;
	int sl;
	int endian;

	one = 1;
	four = 32;
	info = 54;
	header = 40;
	zero = 0;
	if ((fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0)
	{
		ft_quit(data_t);
		return;
	}
	mlx_get_data_addr(data_t->mlx_img, &bpp, &sl, &endian);
        size = 54 + (data_t->res_h * sl);
	printf("%d %d %d", bpp, sl, size);
	write(fd, "BM", 2);
//hardoding of res, need math and hexa convertor
	write(fd, &size, sizeof(int));
	write(fd, &zero, sizeof(int));
	write(fd, &info, sizeof(int));
	write(fd, &header, sizeof(int));
	write(fd, &data_t->res_w, sizeof(int));
	write(fd, &data_t->res_h, sizeof(int));
	write(fd, &one, sizeof(short int));
	write(fd, &bpp, sizeof(short int));
	write(fd, &zero, sizeof(int));
	write(fd, &zero, sizeof(int));
	write(fd, &zero, sizeof(int));
	write(fd, &zero, sizeof(int));
	write(fd, &zero, sizeof(int));
	write(fd, &zero, sizeof(int));
	zero = data_t->res_h * data_t->res_w * 4;
	while (zero > 0)
	{
		write(fd, &data_t->mlx_win[zero--], 1);
	}
	write(1, "ping", 4);
	close(fd);
	//ft_quit(data_t);
}
