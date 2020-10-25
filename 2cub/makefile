# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/12 11:44:20 by budal-bi          #+#    #+#              #
#    Updated: 2020/10/17 10:40:58 by budal-bi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ./srcs/cub3d_utils.c\
		./srcs/cub3d_utils2.c\
		./srcs/cub3d.c\
		./srcs/file_handling.c\
		./srcs/ft_error.c\
		./srcs/ft_save.c\
		./srcs/texture.c\
		./srcs/move.c\
		./srcs/get_color.c\
		./srcs/cub3d_utils3.c\
		./srcs/get_next_line_utils.c\
		./srcs/get_texture.c\
		./srcs/libft1.c\
		./srcs/libft2.c\
		./srcs/libft3.c\
		./srcs/map_checking_dir.c\
		./srcs/map_checking.c\
		./srcs/raycasting.c\
		./srcs/sprite.c\

RENAME		= mv a.out cub3D
OBJ			= $(SRCS:.c=.o)
NAME		= cub3D
BITMAP		= save.bmp
FS			= a.out.dSYM Cub3D.dSYM
CC			= gcc
INCL		= -L. ./srcs/mlx/libmlx.a -lXext -lX11 -lm -lbsd
RM			= rm -f
RM_DIR		= rm -rf
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address
$(NAME):		$(OBJ)
				@$(CC) $(CFLAGS) $(SRCS) $(INCL)
				@$(RENAME)
all:			$(NAME)
clean:
				@$(RM) $(OBJ)
fclean:			clean
				@$(RM) $(NAME) $(BITMAP)
				@$(RM_DIR) $(FS)
re:				fclean all
.PHONY:			all clean fclean re
