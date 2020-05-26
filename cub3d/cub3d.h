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
# define BLOC_SIZE 64
# define CHARARCTER_SIZE 32
# define FOV 60.0

# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK 1
# define KEYRELEASEMASK 10
# define KEY_S 122
# define KEY_Z 115

// #define XK_Left                          0xff51  /* Move left, left arrow */
// #define XK_Up                            0xff52  /* Move up, up arrow */
// #define XK_Right                         0xff53  /* Move right, right arrow */
// #define XK_Down                          0xff54  /* Move down, down arrow */

typedef struct data_t data_t;
struct data_t
{
  //uti mlx
    void          *mlx_prog;
    void          *mlx_win;
    void          *mlx_img;
    float           res_w;
    float           res_h;
    // info map
    int           color_floor;
    int           color_ceiling;
    char          *tex_N;
    char          *tex_W;
    char          *tex_S;
    char          *tex_E;
    char          *tex_sprite;
    char          *map;
    int           column;
    int           line;
    //info character
    char          orientation;
    int           direction;
    int           updown;
    int           leftright;
    int           position_x;
    int           position_y;
    int           sub_position_x;
    int           sub_position_y;
    //screen display
    int           dist_vert;
    int           dist_hor;
    int           wall_size;
};

/*
** cub3D.c
*/
int error_handling_start(int argc, char **argv);
int check_for_obstacle(int x, int y, data_t *data_t);
int	accurate_position(data_t *data_t, int i);
int main(int argc, char **argv);

/*
** get_color
*/
void get_color(char *line, int i, data_t *data_t);
int get_red(char *line, int i);
int get_green(char *line, int i);
int get_blue(char *line, int i);
int color_pixel(int r, int g, int b);

/*
** file_handling
*/
void get_res(char *line, int i, data_t *data_t);
char *get_path(char *line, int i);
void fill_map(char *line, data_t *data_t);
void get_content(char *line, data_t *data_t);
void file_handling(char *name, data_t *data_t);

/*
** map_checking
*/
void check_map(data_t *data_t);
int check_E(data_t *data_t, int i);
int check_S(data_t *data_t, int i);
int check_W(data_t *data_t, int i);
int check_N(data_t *data_t, int i);

/*
** print_screen
*/
int give_udlr(data_t *data_t, int i);
void find_vert_dist(data_t *data_t, float ray);
void find_hor_dist(data_t *data_t, float ray);
void print_column(data_t *data_t, int i);
void new_screen(data_t *data_t);

/*
** print_minimap
*/
void    print_minimap(data_t *data_t);
int	check_for_obstacle_m(int x, int y, data_t *data_t);

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

#endif
