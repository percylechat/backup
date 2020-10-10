#include "cub3d.h"

//WIP
//should create a bmp file of the first screen of option is called during execution.
//should be called by main.

void 	write_img(data_t *data_t, t_save *t_save, int fd)
{
	int x;
	unsigned int index;
	int y;
	unsigned char test;
	unsigned char test1;
	unsigned char test2;
	unsigned char test3;
	unsigned char r;

	x = 0;
	r = 255;
	unsigned char g = 255;
	unsigned char b = 0;

	y = (int)data_t->res_h;

	// index = 0;
	// while (index < t_save->sl)
	// {
	// 	write(1, &t_save->img[index], 1);
	// 	printf("%s\n", &t_save->img[index++]);
	// }

	while (y)
	{
		x = 0;
		while (x < data_t->res_w)
		{
			index = (y * t_save->sl+ x * 4);
			// printf("%c\n", t_save->img[index]);
			// printf("%c\n", t_save->img[index + 1]);
			// printf("%c\n", t_save->img[index + 2]);
			write(fd, &t_save->img[index], 1);
			write(fd, &t_save->img[index + 1], 1);
			write(fd, &t_save->img[index + 2], 1);
			x++;
			// index = (y * t_save->sl) + (x * 4);
			// test = t_save->img[index];
			// test1 = t_save->img[index + 1];
			// test2 = t_save->img[index + 2];
			// printf("%c %c %c\n", test, test1, test2);
			// write(fd, &b, 1);
			// write(fd, &b, 1);
			// write(fd, &r, 1);
			// x++;
		}
		y--;
	}
}

void 		init_save(data_t *data_t, t_save *t_save)
{
	t_save->img = mlx_get_data_addr(data_t->mlx_img, &t_save->bpp, &t_save->sl, &t_save->endian);
	printf("%s\n", t_save->img);
	t_save->one = 1;
	t_save->info = 54;
	t_save->header = 40;
	t_save->zero = 0;
	t_save->h = (int)data_t->res_h;
	t_save->w = (int)data_t->res_w;
	t_save->size = t_save->info + (t_save->h * t_save->sl);
}


void		write_header_2(char *file, int x, int y)
{
	file[0x1c] = 0x18;
	file[0x1d] = 0;
	memcpy(file + 0x1e, "\0\0\0\0", sizeof(char) * 4);
	file[0x22] = (x * y) % 256;
	file[0x23] = ((x * y) / 256) % 256;
	file[0x24] = (((x * y) / 256) / 256) % 256;
	file[0x25] = ((((x * y) / 256) / 256) / 256) % 256;
	file[0x26] = 0x13;
	file[0x27] = 0x0b;
	memcpy(file + 0x28, "\0\0", sizeof(char) * 2);
	file[0x2a] = 0x13;
	file[0x2b] = 0x0b;
	memcpy(file + 0x2c, "\0\0", sizeof(char) * 2);
	memcpy(file + 0x2e, "\0\0\0\0\0\0\0\0", sizeof(char) * 8);
}

void		write_header(char *file, int x, int y)
{
	int size;

	size = x * y * 3;
	file[0] = 'B';
	file[1] = 'M';
	file[2] = (size + 54) % 256;
	file[3] = ((size + 54) / 256) % 256;
	file[4] = (((size + 54) / 256) / 256) % 256;
	file[5] = ((((size + 54) / 256) / 256) / 256) % 256;
	memcpy(file + 6, "\0\0\0\0", sizeof(char) * 4);
	file[0xa] = 54;
	memcpy(file + 0xb, "\0\0\0", sizeof(char) * 4);
	file[0xe] = 40;
	memcpy(file + 0xf, "\0\0\0", sizeof(char) * 4);
	file[0x12] = (x) % 256;
	file[0x13] = ((x) / 256) % 256;
	file[0x14] = (((x) / 256) / 256) % 256;
	file[0x15] = ((((x) / 256) / 256) / 256) % 256;
	file[0x16] = (y) % 256;
	file[0x17] = ((y) / 256) % 256;
	file[0x18] = (((y) / 256) / 256) % 256;
	file[0x19] = ((((y) / 256) / 256) / 256) % 256;
	file[0x1a] = 1;
	file[0x1b] = 0;
	write_header_2(file, x, y);
}

void	ft_save(data_t *data_t)
{
	int fd;
	t_save t_save[1];
	char *file;

	if ((fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0)
	{
		ft_quit(data_t);
		return;
	}
	init_save(data_t, t_save);
	write(fd, "BM", 2);
	write(fd, &t_save->size, sizeof(int));
	write(fd, &t_save->zero, sizeof(int));
	write(fd, &t_save->info, sizeof(int));
	write(fd, &t_save->header, sizeof(int));
	write(fd, &t_save->w, sizeof(int));
	write(fd, &t_save->h, sizeof(int));
	write(fd, &t_save->one, sizeof(short int));
	int t = 24;
	write(fd, &t, sizeof(short int));
	write(fd, &t_save->zero, sizeof(int));
	write(fd, &t_save->zero, sizeof(int));
	write(fd, &t_save->zero, sizeof(int));
	write(fd, &t_save->zero, sizeof(int));
	write(fd, &t_save->zero, sizeof(int));
	write(fd, &t_save->zero, sizeof(int));

	int x = data_t->res_w;
	int y = data_t->res_h;
	if (!(file = malloc(sizeof(char) * (t_save->size))))
		return;
	// write_header(file, x, y);

	write_img(data_t, t_save, fd);
	// write(fd, file, t_save->size);
	write(1, "ping", 4);
	sleep(4);
	close(fd);
	ft_quit(data_t);
}
