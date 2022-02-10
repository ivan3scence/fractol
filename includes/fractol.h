/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:08:32 by sdonny            #+#    #+#             */
/*   Updated: 2022/02/07 13:08:34 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "../libft/libft.h"
# include <mlx.h>

# define WIDTH 500
# define HEIGHT 500
# define MAX_ITER 40
# define THREADS 10
//errors
# define INVALID_ARGS 1
# define MALLOC 2
# define THREADS_ERR 3
//keycodes
//mac
//# define MOUSE_WHEEL_UP 4
//# define MOUSE_WHEEL_DOWN 5
//# define MOUSE_CLICK 1
//# define ESC 53
//# define PLUS 69
//# define MINUS 78
//# define JAY 38
//# define TAB 48
//# define ZERO 29
//linux
# include "../mlx/mlx.h"
# define ESC 65307
# define PLUS 65451
# define MINUS 65453
# define ARR_UP 65362
# define ARR_RIGHT 65363
# define ARR_LEFT 65361
# define ARR_DOWN 65364
# define JAY 106
# define TAB 65289
# define ZERO 48

typedef struct s_col
{
	int	r[2];
	int	g[2];
	int	b[2];
}	t_col;

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
	t_col		*color;
	int			change_color;
	int			zoom_iter;
}	t_mlx;

int		heart(t_mlx *mlx, long double xx, long double yy);
int		tricorn(t_mlx *mlx, long double x, long double y);
int		mndlbrt(t_mlx *mlx, long double x, long double y);
int		burnship(t_mlx *mlx, long double x, long double y);
int		buffalo(t_mlx *mlx, long double xx, long double yy);
int		julia(t_mlx *mlx, long double x, long double y);
int		perp(t_mlx *mlx, long double xx, long double yy);
void	start(t_mlx *mlx);
void	iter_count(t_mlx *mlx);
void	*clean_array(double **hue, int **array_iters, int *numiters);
void	end_hue(double **a, int index, t_mlx *mlx);
double	**get_hue(t_mlx *mlx);
void	set_hue(double **hue, int **array_iters, int *numiters, int total);
void	end(int id, t_mlx *mlx);
int		julia_motion(int x, int y, t_mlx *mlx);
int		key(int keycode, t_mlx *mlx);
int		mouse(int keycode, int x, int y, t_mlx *mlx);
int		get_total(int *numiters, t_mlx *mlx);
int		*get_numiters(int **arr, t_mlx *mlx);
int		palette(float hue, t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);

#endif
