#include "cub3d.h"

//WIP
//should create a bmp file of the first screen of option is called during execution.
//should be called by main.

void 	write_img(data_t *data_t, t_save *t_save, int fd)
{
	int x;
	unsigned int index;
	int y;

	y = (int)data_t->res_h;
	while (y)
	{
		x = 0;
		while (x < data_t->res_w)
		{
			index = (y * t_save->sl+ x * 4);
			write(fd, &data_t->img.content[index], 1);
			write(fd, &data_t->img.content[index + 1], 1);
			write(fd, &data_t->img.content[index + 2], 1);
			x++;
		}
		y--;
	}
}

void 		init_save(data_t *data_t, t_save *t_save)
{
	t_save->one = 1;
	t_save->info = 54;
	t_save->header = 40;
	t_save->zero = 0;
	t_save->h = (int)data_t->res_h;
	t_save->w = (int)data_t->res_w;
	t_save->size = t_save->info + (t_save->h * data_t->img.size_line);
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
