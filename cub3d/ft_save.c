#include "cub3d.h"

//WIP
//should create a bmp file of the first screen of option is called during execution.
//should be called by main.


void	ft_save(data_t *data_t)
{
	int fd;
	unsigned int size;
	int zero;
	unsigned int header;
	unsigned int info;

	info = 54;
	header = 40;
	zero = 0;
	size = 54 + data_t->res_h * data_t->res_w * 4;
	if (fd = open("/home/budal-bi/Workspace/C/cub3d/save.bmp", O_CREAT, S_IRWXO) < 0)
	{
		error;
	}

	write(fd, "BM", 2);
//hardoding of res, need math and hexa convertor
	write(fd, &size, sizeof(int));
	write(fd, &zero, sizeof(int));
	write(fd, &info, sizeof(int));
	write(fd, &header, sizeof(int));
	write(fd, &data_t->res_w, sizeof(int));
	write(fd, &data_t->res_h, sizeof(int));
	write(fd, &(zero + 1), sizeof(short int));
	write(fd, &(zero + 4), sizeof(short int));
	write(fd, &zero, sizeof(int));
	write(fd, &zero, sizeof(int));
	write(fd, &zero, sizeof(int));
	write(fd, &zero, sizeof(int));
	write(fd, &zero, sizeof(int));
	write(fd, &zero, sizeof(int));
	while (zero < (data_t->res_h * data_t->res_w * 4))
	{
		write(fd, &data_t->mlx_win[i], 1);
	}
}
