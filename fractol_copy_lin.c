//linux
//# include "../mlx_Linux/mlx.h"
//# define ESC 65307
//# define PLUS 65451
//# define MINUS 65453
//# define ARR_UP 65362
//# define ARR_RIGHT 65363
//# define ARR_LEFT 65361
//# define ARR_DOWN 65364
//# define J 106
//# define TAB 65289
//# define ZERO 48

//MacOS//static void	move_lin2(int keycode, t_mlx *mlx, long double delta_x,
//		long double delta_y)
//{
//	if (keycode == ARR_RIGHT)
//	{
//		mlx->p1[0] += delta_x;
//		mlx->p2[0] += delta_x;
//	}
//	else if (keycode == ARR_LEFT)
//	{
//		mlx->p1[0] -= delta_x;
//		mlx->p2[0] -= delta_x;
//	}
//}
//
//static void	move_lin(int keycode, t_mlx *mlx)
//{
//	long double	delta_x;
//	long double	delta_y;
//
//	delta_x = (mlx->p2[0] - mlx->p1[0]) / 5;
//	delta_y = (mlx->p1[1] - mlx->p2[1]) / 5;
//	if (keycode == ARR_UP)
//	{
//		mlx->p1[1] += delta_y;
//		mlx->p2[1] += delta_y;
//	}
//	else if (keycode == ARR_DOWN)
//	{
//		mlx->p1[1] -= delta_y;
//		mlx->p2[1] -= delta_y;
//	}
//	else
//		move_lin2(keycode, mlx, delta_x, delta_y);
//	start(mlx);
//}


