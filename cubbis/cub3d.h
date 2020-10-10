#ifndef CUB3D_H

# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <errno.h>
# include <publib.h>
# include <math.h>

# define BUFFER_SIZE 300
# define BLOC_SIZE 64.0
# define CHARARCTER_SIZE 32
# define FOV 60.0

# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK 1
# define KEYRELEASEMASK 10
# define KEY_S 122
# define KEY_Z 115
# define KEY_Q 113
# define KEY_D 100
# define KEY_A 97
# define KEY_E 101
# define KEY_ESC 65307
# define DR 0.0174533

typedef struct s_sav t_save;
struct s_sav
{
	int size;
	int bpp;
	int sl;
	int endian;
	int zero;
	int header;
	int info;
	short int one;
	int w;
	int h;
	char *img;
};

typedef struct s_tex t_tex;
struct s_tex
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	void	*address;
	char	*content;
};

typedef struct s_col t_col;
struct s_col
{
	int r;
	int g;
	int b;
};

typedef struct data_t data_t;
struct data_t
{
  //uti mlx
	void		  *mlx_prog;
	void		  *mlx_win;
	void		  *mlx_img;
	t_tex		img;
	float		   res_w;
	float		   res_h;
	// info map
	t_col		   color_floor;
	t_col		   color_ceiling;
	char		  *tex_N;
	char		  *tex_W;
	char		  *tex_S;
	char		  *tex_E;
	char		  *tex_sprite;
	char		  *map;
	int		   column;
	int			column_size[1024];
	int		   line;
	char		**maptab;
	//info character
	char		orientation;
	double		direction_x;
	double		direction_y;
	double		camera_x;
	double		camera_y;
	double		position_x;
	double		position_y;
	// //screen display
	int		   wall_size;
	int			tot_sprite;
	char		*sprite_spot;
	t_tex N_tex;
	t_tex S_tex;
	t_tex E_tex;
	t_tex W_tex;
};

typedef struct s_raycast t_raycast;
struct s_raycast
{
	float sideDistX;
	float sideDistY;
	float deltaDistX;
	float deltaDistY;
	float perpWallDist;
	int stepX;
	int stepY;
	int side;
	int mapY;
	int mapX;
	int hit;
	float camerax;
	float ray_x;
	float ray_y;
};

typedef struct s_print t_print;
struct s_print
{
	int deb;
	int end;
	double wallX;
	int wallY;
	int texX;
	double step;
	double texPos;
	int texY;
	unsigned int color;
};

typedef struct s_sprite t_sprite;
struct s_sprite
{
	int		is_sprite;
	unsigned int		color;
	float	*buffer;
	int		*ordered_sprite;
	int		sprite_h;
	int		sprite_w;
	int		start_h;
	int		start_w;
	int		end_h;
	int		end_w;
	float spriteX;
	float spriteY;
	float invDet;
	float transformX;
	float transformY;
	int spriteScreenX;
	int wall_x;
	int tex_x;
	int tex_y;
	int wall_y;
};

t_tex get_tex_sp(data_t *data_t);
void drawRays3d(data_t *data_t);
void	check_step(t_raycast *t_raycast, data_t *data_t);
char		*ft_itoa(int n);
char	*ft_strdup_map(const char *src);
void	get_texture(data_t *data_t);
int		new_image(data_t *data_t);

/*
** cub3d_utils
*/
void get_res(char *line, int i, data_t *data_t);
void	give_angle(data_t *data_t);
void	print_black(data_t *data_t);
char	*ft_strdup_map(const char *src);
char	*ft_strjoin_map(char *s1, char *s2);

/*
** cub3d_utils2
*/
void	*ft_memcpy_line(void *dst, const void *src, size_t n);
char		**ft_split_map(data_t *data_t);

/*
** texture
*/
void	text_print(t_tex tex, int h, t_print *t_print, data_t *data_t, int i);
void	print_wall(data_t *data_t, t_raycast *t_raycast, int i, t_print *t_print);
void 	calc_texture(data_t *data_t, t_raycast *t_raycast, int i);

/*
** get_texture
*/
t_tex get_tex_N(data_t *data_t);
t_tex get_tex_W(data_t *data_t);
t_tex get_tex_E(data_t *data_t);
t_tex get_tex_S(data_t *data_t);

/*
** cub3D.c
*/
int error_handling_start(int argc, char **argv);
int check_for_obstacle(int x, int y, data_t *data_t, t_sprite *t_sprite);
void		ft_quit(data_t *data_t);
int main(int argc, char **argv);

/*
** file_handling
*/
void	get_res(char *line, int i, data_t *data_t);
void fill_map(char *line, data_t *data_t);
void get_content(char *line, data_t *data_t);
void file_handling(char *name, data_t *data_t);

/*
** map_checking
*/
void	sprite_roundup(data_t *data_t, int x, int y);
int 	init_map(data_t *data_t, int y, int x);
void check_map(data_t *data_t);

/*
** map_checking_dir
*/
int check_E(data_t *data_t, int x, int y);
int check_S(data_t *data_t, int x, int y);
int check_W(data_t *data_t, int x, int y);
int check_N(data_t *data_t, int x, int y);

/*
**ft_save
*/
void	ft_save(data_t *data_t);

/*
** sprite
*/
int 	*sort_sprite(int *temp);
void	calc_sprite(data_t *data_t, t_sprite *t_sprite);
void	sprite_size(t_sprite *t_sprite, data_t *data_t);
void 	print_sprite(data_t *data_t, t_sprite *t_sprite);

/*
** move
*/
void ft_keyboard_release(int key, data_t *data_t);
int  ft_keyboard_press(int key, data_t *data_t);
void ft_move_updown(data_t *data_t, int m);

/*
** print_screen
*/
void   give_udlr(data_t *data_t);
void find_vert_dist(data_t *data_t, float ray);
void find_hor_dist(data_t *data_t, float ray);
void print_column(data_t *data_t, int i, int side);
void new_screen(data_t *data_t);

/*
** print_minimap
*/
void	print_black(data_t *data_t);
void	print_minimap(data_t *data_t);
int	check_for_obstacle_m(int x, int y, data_t *data_t);

/*
** ft_error
*/
void	error_color(data_t *data_t);
void	error_sanity_check(data_t *data_t);
void 	ft_quit_map(data_t *data_t, char *str);

/*
** get_color
*/
void get_color(char *line, int i, data_t *data_t);
int get_green(char *line, int i);
int get_blue(char *line, int i);
unsigned int color_pixel(int r, int g, int b);

/*
** get_texture
*/
t_tex	*get_tex(data_t *data_t, char *path);
void 	init_texture(data_t *data_t);
t_tex choose_texture(data_t *data_t,t_raycast *t_raycast);


/*
** get_next_line
*/
char	*new_buffer(char *buffer, char *reste);
char	*ft_run(char *reste, char *buffer, char **line);
char	*ulti_run(char *reste, char **line, int bs);
char	*ft_run_end(char *reste, char **line);
int		get_next_line(int fd, char **line);

/*
** get_next_line_utilis
*/
int		ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *src);
int		ft_custom_strchr(const char *s);
char	*ft_substr(char const *s, int start, int len);

/*
** libft1
*/
char	*ft_strtrim(char const *s1, char const *set);
int		ft_atoi(const char *str);

/*
** libft2
*/
int		ft_isdigit(int c);
char	*ft_strjoin_map(char *s1, char *s2);
void	*ft_memmove(void *dst, const void *src, size_t len);

/*
** libft3
*/
void	ft_putstr_fd(char *s, int fd);
#endif
