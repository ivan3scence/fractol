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

# define WIDTH 500
# define HEIGHT 500
# define MAX_ITER 50
# define THREADS 5
typedef struct s_mlx
{
	void	*mlx;
	void	*win;

	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	long double	p1[2];
	long double	p2[2];
	long double	x;
	long double	y;
	int		thread;
	int		**array_iters;
}	t_mlx;
# endif
