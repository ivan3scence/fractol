#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <pthread.h>
# include "../libft/libft.h"
//# include "../mlx_linux/mlx.h"
# include <mlx.h>

# define WIDTH 1000
# define HEIGHT 1000
# define MAX_ITER 50
# define THREADS 10
//errors
# define INVALID_ARGS 1
# define MALLOC 2
# define THREADS_ERR 3
//keycodes
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define MOUSE_CLICK 1
//linux
//# define ESC 65307
//# define PLUS 65451
//# define MINUS 65453
//# define ARR_UP 65362
//# define ARR_RIGHT 65363
//# define ARR_LEFT 65361
//# define ARR_DOWN 65364
//# define J 106
//MacOS
# define ESC 53
# define PLUS 69
# define MINUS 78
# define J 106


typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			(*f)(struct s_mlx *, long double, long double);
	long double	p1[2];
	long double	p2[2];
	long double	x;
	long double	y;
	int			flag;
	int			**array_iters;
}	t_mlx;

typedef struct s_thread
{
	t_mlx	*mlx;
	int		thread;
}	t_thread;

#endif
