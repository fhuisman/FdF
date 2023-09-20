# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fhuisman <fhuisman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/25 12:25:31 by fhuisman      #+#    #+#                  #
#    Updated: 2023/04/05 10:36:35 by fhuisman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

FLAGS = -Wall -Wextra -Werror

MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -fast

SRC = main.c init_map.c init_fdf.c utils.c exit.c rotate.c draw.c hooks1.c hooks2.c projection.c

OBJS = ${SRC:.c=.o}

HEADERS = fdf.h

LIBFT = libft/libft.a

MLX = ./MLX42/build/libmlx42.a -Iinclude -lglfw3

all: ${NAME}

${NAME}: ${OBJS}
	${MAKE} -C ./libft
	${MAKE} -C ./MLX42/build
	${CC} ${MLXFLAGS} ${FLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${MLX}

%.o: %.c ${HEADERS}
	${CC} -c ${FLAGS} -o $@ $<

clean:
	rm -f ${OBJS}
	${MAKE} clean -C libft

fclean: clean
	rm -f ${NAME}
	${MAKE} fclean -C libft
	${MAKE} clean -C ./MLX42/build

re: fclean all

.PHONY: all clean fclean re