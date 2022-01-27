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
# include "../libft/libft.h"
//# include "../mlx_linux/mlx.h"
# include <mlx.h>

# define WIDTH 1000
# define HEIGHT 1000
# define MAX_ITER 50
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
}	t_mlx;
# endif
