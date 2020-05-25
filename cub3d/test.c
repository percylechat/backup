
#include "cub3d.h"

int	color_map_1(void *win, void *mlx,int w,int h)
{
  int	x;
  int	y;
  int	color;

  x = w;
  while (x--)
    {
      y = h;
      while (y--)
        {
          color = (x*255)/w+((((w-x)*255)/w)<<16)+(((y*255)/h)<<8);
          // si w = 480 et h = 640
          // et x = 300 et y = 500
          // color = (300 * 255) / 480 +((((480 - 300)*255) / 480)<<16)+(((500*255)/640)<<8);
          // color = 76500 / 480 +((45900 / 480)<<16)+((127500/640)<<8);
          // color = 159 +(96<<16)+(199<<8);
	  mlx_pixel_put(mlx,win,x,y,color);
        }
    }
}

int main(void)
{
    // data_t        data;

    void          *mlx_ptr;
    void          *mlx_win;
    void          *mlx_img;

    if ((mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((mlx_win = mlx_new_window(mlx_ptr, 640, 480, "Hello world")) == NULL)
        return (EXIT_FAILURE);
    // mlx_loop(mlx_ptr);
    // color_map_1(mlx_win, mlx_ptr, 640,480);
    // data.mlx_img = mlx_new_image(data.mlx_ptr,640, 480);
    int i = 0;
    int color = 255 +(255<<16)+(1<<8);
    int color2 = 1 +(255<<16)+(255<<8);
    int color3 = 1 +(1<<16)+(255<<8);
    // while (i > 480)
    // {
      mlx_pixel_put(mlx_ptr, mlx_win, 100, 100, color);
      mlx_pixel_put(mlx_ptr, mlx_win, 100, 101, color);
      mlx_pixel_put(mlx_ptr, mlx_win, 101, 100, color);
      mlx_pixel_put(mlx_ptr, mlx_win, 101, 101, color);

      mlx_pixel_put(mlx_ptr, mlx_win, 200, 200, color2);
      mlx_pixel_put(mlx_ptr, mlx_win, 200, 201, color2);
      mlx_pixel_put(mlx_ptr, mlx_win, 201, 200, color2);
      mlx_pixel_put(mlx_ptr, mlx_win, 201, 201, color2);

      mlx_pixel_put(mlx_ptr, mlx_win, 200, 100, color3);
      mlx_pixel_put(mlx_ptr, mlx_win, 200, 101, color3);
      mlx_pixel_put(mlx_ptr, mlx_win, 201, 100, color3);
      mlx_pixel_put(mlx_ptr, mlx_win, 201, 101, color3);
      // i--;
    // }
    sleep(4);
    // mlx_put_image_to_window(data.mlx_ptr,data.mlx_win,data.mlx_img,100, 100);
    return (EXIT_SUCCESS);
}
