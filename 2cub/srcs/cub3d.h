/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 12:18:55 by budal-bi          #+#    #+#             */
/*   Updated: 2020/10/23 12:18:08 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "./mlx/mlx.h"
# include <errno.h>
# include <math.h>

# define BS 1000
# define BLOC_SIZE 64.0
# define CHARARCTER_SIZE 32
# define FOV 60.0

# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK 1L
# define KEYRELEASEMASK 2L
# define KEY_S 122
# define KEY_Z 115
# define KEY_Q 113
# define KEY_D 100
# define KEY_A 65361
# define KEY_E 65363
# define KEY_ESC 65307

typedef struct s_gnl		t_gnl;
struct						s_gnl
{
	char					*line;
	char					*buffer;
	int						fd;
	int						res;
	int						deb;
	int						end;
	int						check;
};

typedef struct s_save		t_save;
struct						s_save
{
	int						size;
	int						bpp;
	int						zero;
	int						header;
	int						info;
	short int				one;
	int						w;
	int						h;
};

typedef struct s_tex		t_tex;
struct						s_tex
{
	int						bits_per_pixel;
	int						sl;
	int						endian;
	void					*address;
	char					*content;
};

typedef struct s_col		t_col;
struct						s_col
{
	int						r;
	int						g;
	int						b;
};

typedef struct s_main		t_main;
struct						s_main
{
	void					*mlx_prog;
	void					*mlx_win;
	void					*mlx_img;
	t_tex					img;
	float					res_w;
	float					res_h;
	t_col					color_floor;
	t_col					color_ceiling;
	char					*tex_n;
	char					*tex_w;
	char					*tex_s;
	char					*tex_e;
	char					*tex_sprite;
	char					*map;
	int						column;
	int						column_size[1024];
	int						line;
	char					**maptab;
	char					orientation;
	double					direction_x;
	double					direction_y;
	double					camera_x;
	double					camera_y;
	double					position_x;
	double					position_y;
	int						wall_size;
	int						tot_sprite;
	char					*sprite_spot;
	t_tex					n_tex;
	t_tex					s_tex;
	t_tex					e_tex;
	t_tex					w_tex;
	t_tex					sp_tex;
};

typedef struct s_raycast	t_raycast;
struct						s_raycast
{
	float					side_x;
	float					side_y;
	float					delta_x;
	float					delta_y;
	float					wall_dist;
	int						step_x;
	int						step_y;
	int						side;
	int						map_y;
	int						map_x;
	int						hit;
	float					camerax;
	float					ray_x;
	float					ray_y;
};

typedef struct s_print		t_print;
struct						s_print
{
	int						deb;
	int						end;
	double					wall_x;
	int						wall_y;
	int						tex_x;
	int						tex_y;
	double					step;
	double					texpos;
	unsigned int			color;
};

typedef struct s_sprite		t_sprite;
struct						s_sprite
{
	int						is_sprite;
	unsigned int			color;
	float					*buffer;
	int						*ordered_sprite;
	int						sprite_h;
	int						sprite_w;
	int						start_h;
	int						start_w;
	int						end_h;
	int						end_w;
	float					sprite_x;
	float					sprite_y;
	float					invdet;
	float					trans_x;
	float					trans_y;
	int						screen_x;
	int						wall_x;
	int						tex_x;
	int						tex_y;
	int						wall_y;
	int						n_s;
};

void						raycasting(t_main *t_m);
void						check_step(t_raycast *t_r, t_main *t_m);
char						*ft_itoa(int n);

int							ft_chrlen(const char *s, char c);
void						end_gnl(t_gnl *t_g);

/*
** cub3d_utils
*/
int							ft_issave(char *txt);
void						give_angle_ew(t_main *t_m);
void						give_angle(t_main *t_m);
int							check_for_obstacle(int x, int y, t_main *t_m,
t_sprite *t_s);
int							new_image(t_main *t_m);

/*
** cub3d_utils2
*/
char						*set_reste(char *reste);
void						check_res(t_main *t_m);
t_tex						get_tex_sp(t_main *t_m);
char						*line_copy(char *src, int i);
char						**ft_split_map(t_main *t_m);

/*
** cub3d_utils3
*/
int							ft_chrlen(const char *s, char c);
void						end_gnl(t_gnl *t_g);
int							ft_strlen(const char *s);
int							go_line(t_gnl *t_g, t_main *t_m);

/*
** get_texture
*/
t_tex						get_tex_n(t_main *t_m);
t_tex						get_tex_w(t_main *t_m);
t_tex						get_tex_e(t_main *t_m);
t_tex						get_tex_s(t_main *t_m);
void						get_texture(t_main *t_m);

/*
** cub3D.c
*/
int							check_for_obstacle(int x, int y, t_main *t_m,
t_sprite *t_s);
int							ft_quit(t_main *t_m);
int							main(int argc, char **argv);

/*
** file_handling
*/
int							get_res(char *line, int i, t_main *t_m, t_gnl *t_g);
void						fill_map(char *line, t_main *t_m);
int							get_content(char *line, t_main *t_m, t_gnl *t_g);
int							file_handling(char *name, t_main *t_m);

/*
** map_checking
*/
void						sprite_roundup(t_main *t_m, int x, int y);
int							init_map(t_main *t_m, int y, int x);
void						check_map(t_main *t_m);

/*
** map_checking_dir
*/
void						check_rotate(t_main *t_m);
int							check_e(t_main *t_m, int x, int y);
int							check_s(t_main *t_m, int x, int y);
int							check_w(t_main *t_m, int x, int y);
int							check_n(t_main *t_m, int x, int y);

/*
**ft_save
*/
int							minimize(t_main *t_m);
int							ft_quit_save(t_main *t_m);
void						write_img(t_main *t_m, int fd);
void						init_save(t_main *t_m, t_save *t_s, int fd);
void						ft_save(t_main *t_m);

/*
** sprite
*/
int							actual_print(t_main *t_m, t_sprite *t_s);
int							*sort_sprite(int *temp);
void						calc_sprite(t_main *t_m, t_sprite *t_s);
void						sprite_size(t_sprite *t_s, t_main *t_m, int k);
void						print_sprite(t_main *t_m, t_sprite *t_s);

/*
** move
*/
void						ft_move_updown(t_main *t_m, int m);
int							ft_move(t_main *t_m);

/*
** print_screen
*/
void						give_udlr(t_main *t_m);
void						find_vert_dist(t_main *t_m, float ray);
void						find_hor_dist(t_main *t_m, float ray);
void						print_column(t_main *t_m, int i, int side);
void						new_screen(t_main *t_m);

/*
** ft_error
*/
void						error_color(t_main *t_m, char c);
void						error_sanity_check(t_main *t_m);
void						ft_quit_map(t_main *t_m, char *str);
void						error_res(t_main *t_m);
int							error_handling_start(int argc, char **argv);

/*
** get_color
*/
int							get_color(char *line, int i, t_main *t_m);
int							get_green(char *line, int i);
int							get_blue(char *line, int i);
unsigned int				color_pixel(int r, int g, int b);

/*
** get_texture
*/
t_tex						*get_tex(t_main *t_m, char *path);
void						init_texture(t_main *t_m);
t_tex						choose_texture(t_main *t_m, t_raycast *t_r);

/*
** texture
*/
void						text_print(t_tex t_t, t_print *t_p, t_main *t_m,
int index);
void						print_cf(t_main *t_m, int h, int i, int g);
void						print_wall(t_main *t_m, t_raycast *t_r, int i,
t_print *t_p);
void						calc_texture(t_main *t_m, t_raycast *t_r, int i);

/*
** get_next_line_utilis
*/
char						*ft_strjoin(char *s1, char *s2);
char						*ft_strdup(const char *src);
int							ft_custom_strchr(const char *s);
char						*ft_substr(char const *s, int start, int len);

/*
** libft1
*/
char						*ft_strtrim(char const *s1, char const *set);
int							ft_atoi(const char *str);

/*
** libft2
*/
int							ft_keyboard_release(int key, t_main *t_m);
int							ft_keyboard_press(int key, t_main *t_m);
int							ft_isdigit(int c);
void						*ft_memmove(void *dst, const void *src, size_t len);

/*
** libft3
*/
void						ft_putstr_fd(char *s, int fd);

#endif
