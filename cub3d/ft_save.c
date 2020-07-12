#include "cub3d.h"

//WIP
//should create a bmp file of the first screen of option is called during execution.
//should be called by main.


void	ft_save(data_t *data_t)
{
	int fd;
	int size;

	if (fd = open("/home/budal-bi/Workspace/C/cub3d/save.bmp", O_CREAT, S_IRWXO) < 0)
	{
		error;
	}
	write(fd, "BM", 2);
//hardoding of res, need math and hexa convertor
	write(fd, "0x36 0xB8 0x0B 0x00 0x00 0x00 0x00 0x00 0x36 0x00 0x00 0x00", 57);




	size = data_t->res_h * data_t->res_w * 4;
}
