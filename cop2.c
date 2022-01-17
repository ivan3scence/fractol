#include "../includes/fractol.h"

//typedef struct	s_data {
//	void	*img;
//	char	*addr;
//	int		bits_per_pixel;
//	int		line_length;
//	int		endian;
//	double	p1[2];
//	double	p2[2];
//}				t_data;

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static int	draw_pixel(t_mlx *mlx, double x, double y, int w, int h)
{
	int	i;
	double	p = x;
	double	q = y;
	double	x_temp;
	double	sqr;

	i = -1;
	//printf("%g\n", sqrt(3.84 / (mlx->p2[0] - mlx->p1[0])) * 70); 
	//while (++i < (int)sqrt(3.84 / (mlx->p2[0] - mlx->p1[0])) * 70)
	while (++i < 100)
	{
		sqr = x * x + y * y;
		if (sqr * sqr > 4)
			break ;
		x_temp = x;
		x = x * x - y * y + p;
		y = 2 * x_temp * y + q;
	}
	//if (i == (int)sqrt(3.84 / (mlx->p2[0] - mlx->p1[0])) * 70)
	if (i == 100)
		my_mlx_pixel_put(mlx, w, h, 0x00000000);
	else
		my_mlx_pixel_put(mlx, w, h, i * i);
	//printf("%d\n", i);
	return (1);
}

static void mandelbrot(t_mlx *mlx)
{
	double	x=mlx->p1[0];
	double	y=mlx->p1[1];
	double	yy=y;
	int		w=-1;
	int		h;

	while (++w < WIDTH)
	{
		h = -1;
		y = yy;
		while (++h < HEIGHT)
		{
			draw_pixel(mlx, x, y, w, h);
			//printf("%g, %g\n", x, y);
			y += (mlx->p2[1] - mlx->p1[1]) / HEIGHT;
		}
		x += (mlx->p2[0] - mlx->p1[0]) / WIDTH;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
	{
		//mlx_destroy_image(
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	printf("Hello from key_hook!\n%d\n", keycode); //4-zoom in.....5-zoom out
	return (0);
}

static void	zoom(t_mlx *mlx, int x, int y,float mult)
{
	double temp0=mlx->p1[0];
	double temp1=mlx->p1[1];
	double	cursor_x=x;
	double	cursor_y=y;
	double	pixel_x = (mlx->p2[0] - mlx->p1[0]) / WIDTH;
	double	pixel_y = (mlx->p1[1] - mlx->p2[1]) / HEIGHT;

	if (mult < 1)
	{
		mlx->p1[0] = (3 * mlx->p1[0] - mlx->p2[0]) * mult;
		mlx->p1[1] = (3 * mlx->p1[1] - mlx->p2[1]) * mult;
		mlx->p2[0] = (3 * mlx->p2[0] - temp0) * mult;
		mlx->p2[1] = (3 * mlx->p2[1] - temp1) * mult;
		printf("into if\np1[0] %g; p1[1] %g\n", mlx->p1[0], mlx->p1[1]);
		printf("p2[0] %g; p2[1] %g\n", mlx->p2[0], mlx->p2[1]);
		mandelbrot(mlx);
		return ;
	}
	cursor_x = temp0 + pixel_x * cursor_x;
	cursor_y = temp1 - pixel_y * cursor_y;
	printf("delta_x %g\ndelta_y: %g\n", cursor_x, cursor_y);

	mlx->p1[0] = (3 * mlx->p1[0] + mlx->p2[0]) / mult + cursor_x;
	mlx->p1[1] = (3 * mlx->p1[1] + mlx->p2[1]) / mult + cursor_y;
	mlx->p2[0] = (3 * mlx->p2[0] + temp0) / mult + cursor_x;
	mlx->p2[1] = (3 * mlx->p2[1] + temp1) / mult + cursor_y;

	printf("p1[0] %g; p1[1] %g\n", mlx->p1[0], mlx->p1[1]);
	printf("p2[0] %g; p2[1] %g\n", mlx->p2[0], mlx->p2[1]);
	mandelbrot(mlx);
}

static int	mouse(int keycode, int x, int y, t_mlx *mlx)
{
	printf("Mouse keycode: %d X: %d\nY: %d\n", keycode, x, y);
	if (keycode == 4)
		zoom(mlx, x, y, 4);
	else if (keycode == 5)
		zoom(mlx, x , y, 0.5);
	return (1);
}

int	main(void)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "fract'ol");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_length,
								&mlx.endian);
	mlx.p1[0] = -1.92;
	mlx.p1[1] = 1.08;
	mlx.p2[0] = 1.92;
	mlx.p2[1] = -1.08;

	mandelbrot(&mlx);
	mlx_mouse_hook(mlx.win, mouse, &mlx);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.mlx);
	
}
