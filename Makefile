CFLAGS = -pthread -fsanitize=address
#-Wall -Wextra -Werror

HDRS = fractol.h

HDRS_BONUS = pipex_bonus.h get_next_line_bonus.h

HEADERS = $(addprefix includes/, ${HDRS})

HEADERS_BONUS = $(addprefix includes_bonus/, ${HDRS_BONUS})

CC = cc

RM = rm -f

NAME = fractol

BONUS = .bonus

SRC = fractol.c

SRC_BONUS = fractol.c

LIBFT_NAME = libft.a

LIBFTDIR = ./libft/

LIBFT = $(addprefix ${LIBFTDIR}, ${LIBFT_NAME})

SOURCES = $(addprefix src/, ${SRC})

SOURCES_BONUS = $(addprefix src_bonus/, ${SRC_BONUS})

.PHONY:	clean all bonus fclean re

all:	${NAME}

${LIBFT}:
	${MAKE} -C ${LIBFTDIR}

${NAME}:	${LIBFT} ${SOURCES} ${HEADERS}
	cc ${CFLAGS} -I /usr/local/include ${SOURCES} -L /usr/local/lib -lmlx\
		-L./libft -lft\
		-framework OpenGL -framework AppKit -o $@

bonus:	${BONUS}

${BONUS}:	${LIBFT} ${SOURCES_BONUS} ${HEADERS_BONUS}
	cc -Wall -Wextra -Werror -L ${LIBFTDIR} -lft ${SOURCES_BONUS} -o pipex
	@touch $@

clean:
	${MAKE} clean -C ${LIBFTDIR}
	@${RM} ${BONUS}

fclean:		clean
	${RM} ${NAME}
	${MAKE} fclean -C ${LIBFTDIR}

re:	fclean all
