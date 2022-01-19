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

/*
 * 00 7f ff 00
 * 00 00 fa 9a
 */

static int	color(int iter, int sumiter)
{
	int	r[2];
	int	g[2];
	int	b[2];

	r[0] = 135;
	r[1] = 0;
	g[0] = 206;
	g[1] = 250;
	b[0] = 235;
	b[1] = 154;
	//return (iter * iter);
	return (create_trgb(0, get_r(r[0] + iter / sumiter), get_g(g[0] + iter / sumiter),
				get_b(b[0] + iter / sumiter)));
}

static int	draw_pixel(t_mlx *mlx, double x, double y, int w, int h)
{
	int	i;
	double	x2=0;	
	double	y2=0;	
	double	x0 = x;
	double	y0 = y;

	i = -1;
	while (++i < 500 && x2 + y2 <= 4)
	{
		y = (x + x) * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
	}
	if (i == 500)
		my_mlx_pixel_put(mlx, w, h, 0);
	else
		my_mlx_pixel_put(mlx, w, h, color(i, 183335119));
	//printf("%d\n", i);
	return (i);
}

static void mandelbrot(t_mlx *mlx)
{
	double	x=mlx->p1[0];
	double	y=mlx->p1[1];
	int		w=-1;
	int		h;
	long long int		sum=0;

	while (++w < WIDTH)
	{
		h = -1;
		y = mlx->p1[1];
		while (++h < HEIGHT)
		{
			sum += draw_pixel(mlx, x, y, w, h);
			//printf("%g, %g\n", x, y);
			y += (mlx->p2[1] - mlx->p1[1]) / HEIGHT;
		}
		x += (mlx->p2[0] - mlx->p1[0]) / WIDTH;
	}
	ft_putnbr_fd(sum, 1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
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
	cursor_x = mlx->p1[0] + pixel_x * cursor_x;
	cursor_y = mlx->p1[1] - pixel_y * cursor_y;
	printf("delta_x %g\ndelta_y: %g\n", cursor_x, cursor_y);

	mlx->p1[0] = (3 * mlx->p1[0] + mlx->p2[0]) / mult + cursor_x;
	mlx->p1[1] = (3 * mlx->p1[1] + mlx->p2[1]) / mult + cursor_y;
	mlx->p2[0] = (3 * mlx->p2[0] + temp0) / mult + cursor_x;
	mlx->p2[1] = (3 * mlx->p2[1] + temp1) / mult + cursor_y;

	printf("p1[0] %g; p1[1] %g\n", mlx->p1[0], mlx->p1[1]);
	printf("p2[0] %g; p2[1] %g\n", mlx->p2[0], mlx->p2[1]);
	mandelbrot(mlx);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 65307
			|| keycode == 53)     //MocOs
	{
		//mlx_destroy_image(
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	if (keycode == 69)
		zoom(mlx, WIDTH / 2, HEIGHT / 2, 4);
	else if (keycode == 78)
		zoom(mlx, WIDTH / 2, HEIGHT / 2, 0.5);
	printf("Hello from key_hook!\n%d\n", keycode); //4-zoom in.....5-zoom out
	return (0);
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
	mlx.p1[0] = -2;
	mlx.p1[1] = 2;
	mlx.p2[0] = 2;
	mlx.p2[1] = -2;

	mandelbrot(&mlx);
	mlx_mouse_hook(mlx.win, mouse, &mlx);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.mlx);
	
}
