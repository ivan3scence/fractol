# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdonny <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 13:08:47 by sdonny            #+#    #+#              #
#    Updated: 2022/02/07 13:08:49 by sdonny           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -pthread -fsanitize=address -Wall -Wextra -Werror

INCLUDES = -I${MLXDIR} -I${LIBFTDIR}

HDRS = fractol.h

HEADERS = $(addprefix includes/, ${HDRS})

LIBS =  -L${MLXDIR} -lmlx -lm\
		-L${LIBFTDIR} -lft\
		-framework OpenGL -framework AppKit

CC = cc

RM = rm -f

NAME = fractol

SRC = rgb.c error.c events.c fractls.c fractls2.c\
		main.c start.c start2.c utils.c

LIBFT_NAME = libft.a

LIBFTDIR = ./libft/

MLXDIR = ./mlx/

MLX_NAME = libmlx.a

MLX = $(addprefix ${MLXDIR}, ${MLX_NAME})

LIBFT = $(addprefix ${LIBFTDIR}, ${LIBFT_NAME})

SOURCES = $(addprefix src/, ${SRC})

.PHONY:	clean all fclean re

all:	${NAME}

${LIBFT}:
	${MAKE} -C ${LIBFTDIR}

${MLX}:
	${MAKE} -C ${MLXDIR}

${NAME}:	${LIBFT} ${SOURCES} ${HEADERS}
	$(CC) ${CFLAGS} $(SOURCES) -L./libft -lft -Lmlx -lmlx_Linux\
		-L/usr/lib -Imlx \
		-lXext -lX11 -lm -lz -o $(NAME)

clean:
	${MAKE} clean -C ${LIBFTDIR}
	${MAKE} clean -C ${MLXDIR}

fclean:		clean
	${RM} ${NAME}
	${MAKE} fclean -C ${LIBFTDIR}
	${MAKE} clean -C ${MLXDIR}

re:	fclean all
