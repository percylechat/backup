// i hate makefiles so it doesn't work yet

NAME = cub3d.a

CC = gcc

FLAGS = -lmlx -lXext -lX11

OBJS = ${SRC:.c=.o}

SRC =							\
		cub3d.c					\
		file_handling.c			\
		map_checking.c			\
		print_screen.c			\
		get_color.c				\
		get_next_line.c			\
		get_next_line_utils.c	\
		libft1.c				\
		libft2.c				\

LIBR = includes

AR = ar rc

$(NAME):	${OBJS}
			@${AR} ${NAME} ${OBJS}

all:	$(NAME)

%.o: %.c	${GCC} ${FLAGS} -c -o $@ $< -I ${LIBR}

clean:
		@${RM} ${OBJS}

fclean:	clean
		@${RM} ${NAME}

re:	fclean all

.PHONY:	fclean
		clean
		make
		bonus
		all
		re
