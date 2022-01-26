#include "../includes/fractol.h"

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

static int	palette(float hue)
{
	int	r[2];
	int	g[2];
	int	b[2];

	r[0] = 75;
	r[1] = 255;
	g[0] = 0;
	g[1] = 182;
	b[0] = 50;
	b[1] = 200;
	//return (iter * iter);
	if (hue == -1)
		return (0);
	return (create_trgb(0,
						r[0] + hue * (r[1] - r[0]),
						g[0] + hue * (g[1] - g[0]),
						b[0] + hue * (b[1] - b[0])
						));
	//return (create_trgb(0, get_r(iter / MAX_ITER * 255), get_g(iter / MAX_ITER * 255),
	//			get_b(iter / MAX_ITER * 255)));
}

static int	*get_numiters(int **arr, t_mlx *mlx)
{
	int	x;
	int	y;
	int	*ret;

	ret = (int *)malloc(sizeof(int) * (MAX_ITER + log2(4 /
					(mlx->p2[0] - mlx->p1[0])) + 1));
	if (!ret)
		exit(1);
	x = -1;
	while (++x <= MAX_ITER + log2(4 / (mlx->p2[0] - mlx->p1[0])))
		ret[x] = 0;
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		y++;
		(void)arr;
		while (++y < HEIGHT)
		{
			if (arr[x][y] > -1)
				ret[arr[x][y]] += 1;
		}
	}
	return (ret);
}

static int	get_total(int *numiters, t_mlx *mlx)
{
	int	x;
	int	total;

	x = -1;
	while (++x <= MAX_ITER + log2(4 / (mlx->p2[0] - mlx->p1[0])))
		total += numiters[x];
	return (total);
}

/*static int	mndlbrt(t_mlx *mlx, long double x, long double y)
{
	int		i;
	long double	x2=x * x;
	long double	y2=y * y;
	long double	x0=x;
	long double	y0=y;

	i = -1;
	x2 = x * x;
	y2 = y * y;
	x0 = x;
	y0 = y;
	//printf("%g\n", (MAX_ITER + MAX_ITER * log2(4 / (mlx->p2[0] - mlx->p1[0]))));
	while (x2 + y2 <= 4
			&& ++i < (MAX_ITER + log2(4 / (mlx->p2[0] - mlx->p1[0]))))
	{
		y = (x + x) * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
	}
	return (i);
}*/

static int	julia(t_mlx *mlx, long double x, long double y)
{
	int		i;
	long double	x2=x * x;
	long double	y2=y * y;
	long double	x0=x;
	long double	y0=y;

	i = -1;
	x2 = x * x;
	y2 = y * y;
	x0 = x;
	y0 = y;
	//printf("%g\n", (MAX_ITER + MAX_ITER * log2(4 / (mlx->p2[0] - mlx->p1[0]))));
	while (x2 + y2 <= 16
			&& ++i < (MAX_ITER + log2(4 / (mlx->p2[0] - mlx->p1[0]))))
	{
		y = (x + x) * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
	}
	return (i);
}

static int		**iter_count(t_mlx *mlx)
{
	int		**array_iters;
	int		h;
	int		w;
	long double		x;
	long double		y;

	array_iters = (int **)malloc(sizeof(int *) * WIDTH);
	if (!array_iters)
		exit(1);
	w = -1;
	x = mlx->p1[0];
	while (++w < WIDTH)
	{
		array_iters[w] = (int *)malloc(sizeof(int) * HEIGHT);
		if (!array_iters)
			exit(1);
		h = -1;
		y = mlx->p1[1];
		while (++h < HEIGHT)
		{
			//array_iters[w][h] = mndlbrt(mlx, x, y);
			array_iters[w][h] = julia(mlx, x, y);
			if (array_iters[w][h] == MAX_ITER + log2(4
						/ (mlx->p2[0] - mlx->p1[0])))
				array_iters[w][h] = -1;
			//printf("%d %g %g\n", array_iters[w][h],x,y);
			y -= (mlx->p1[1] - mlx->p2[1]) / HEIGHT;
		}
		x += (mlx->p2[0] - mlx->p1[0]) / WIDTH;
	}
	return (array_iters);
}

static void	clean_array(double **hue, int **array_iters, int *numiters)
{
	int	w;

	w = -1;
	while (++w < WIDTH)
	{
		free(hue[w]);
		free(array_iters[w]);
	}
	free(hue);
	free(array_iters);
	free(numiters);
}

static double	**get_hue(void)
{
	int		xx;
	int		yy;
	double	**hue;

	xx = -1;
	yy = -1;
	hue = (double **)malloc(sizeof(double *) * WIDTH);
	if (!hue)
		exit(1);
	while (++xx < WIDTH)
	{
		yy = -1;
		hue[xx] = (double *)malloc(sizeof(double) * HEIGHT);
		if (!hue[xx])
			exit(1);
		while (++yy < HEIGHT)
			hue[xx][yy] = 0;
	}
	return (hue);
}

static void	set_hue(double **hue, int **array_iters, int *numiters, int total)
{
	int	iter;
	int	i;
	int	w;
	int	h;

	w = -1;
	while (++w < WIDTH)
	{
		h = -1;
		while (++h < HEIGHT)
		{
			iter = array_iters[w][h];
			if (iter == -1)
				hue[w][h] = -1;
			else
			{
				i = -1;
				while (++i <= iter)
				{
					hue[w][h] += (float) numiters[i] / total;
				}
			}
		}
	}
}

static void	draw_pic(t_mlx *mlx, double **hue)
{
	int	w;
	int	h;

	w = -1;
	while (++w < WIDTH)
	{
		h = -1;
		while (++h < HEIGHT)
			my_mlx_pixel_put(mlx, w, h, palette(hue[w][h]));
	}
}

static void start(t_mlx *mlx)
{
	int		**array_iters;
	int		*numiters;
	int		total;
	double	**hue;

	array_iters = iter_count(mlx);
	numiters = get_numiters(array_iters, mlx);
	total = get_total(numiters, mlx);
	hue = get_hue();
	set_hue(hue, array_iters, numiters, total);
	draw_pic(mlx, hue);
	clean_array(hue, array_iters, numiters);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

static void	zoomout(t_mlx *mlx, int x, int y,float mult)
{
	long double	cursor_x;
	long double	cursor_y;

	cursor_x = mlx->p1[0] + (mlx->p2[0] - mlx->p1[0]) / WIDTH * x;
	cursor_y = mlx->p1[1] - (mlx->p1[1] - mlx->p2[1]) / HEIGHT * y;
	printf("delta_x %Lg\ndelta_y: %Lg\n", cursor_x, cursor_y);
	mlx->p1[0] = cursor_x - (cursor_x - mlx->p1[0]) / mult;
	mlx->p1[1] = cursor_y + (mlx->p1[1] - cursor_y) / mult;
	mlx->p2[0] = cursor_x + (mlx->p2[0] - cursor_x) / mult;
	mlx->p2[1] = cursor_y - (cursor_y - mlx->p2[1]) / mult;
	printf("p1[0] %Lg; p1[1] %Lg\n", mlx->p1[0], mlx->p1[1]);
	printf("p2[0] %Lg; p2[1] %Lg\n", mlx->p2[0], mlx->p2[1]);
	printf("%g\n", (MAX_ITER + log2(4 / (mlx->p2[0] - mlx->p1[0]))));
	start(mlx);
	return ;
}

static void	zoom(t_mlx *mlx, int x, int y,float mult)
{
	long double	cursor_x;
	long double	cursor_y;

	if (mult < 1)
	{
		zoomout(mlx, x, y, mult);
		return ;
	}
	cursor_x = mlx->p1[0] + (mlx->p2[0] - mlx->p1[0]) / WIDTH * x;
	cursor_y = mlx->p1[1] - (mlx->p1[1] - mlx->p2[1]) / HEIGHT * y;
	printf("delta_x %Lg\ndelta_y: %Lg\n", cursor_x, cursor_y);
	mlx->p1[0] = cursor_x - (cursor_x - mlx->p1[0]) / mult;
	mlx->p1[1] = cursor_y + (mlx->p1[1] - cursor_y) / mult;
	mlx->p2[0] = cursor_x + (mlx->p2[0] - cursor_x) / mult;
	mlx->p2[1] = cursor_y - (cursor_y - mlx->p2[1]) / mult;
	printf("p1[0] %Lg; p1[1] %Lg\n", mlx->p1[0], mlx->p1[1]);
	printf("p2[0] %Lg; p2[1] %Lg\n", mlx->p2[0], mlx->p2[1]);
	printf("%g\n", (MAX_ITER + log2(4 / (mlx->p2[0] - mlx->p1[0]))));
	start(mlx);
}

int	key(int keycode, t_mlx *mlx)
{
	if (keycode == 65307
			|| keycode == 53)     //MocOs
	{
		//mlx_destroy_image(
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	if (keycode == 69 || keycode == 65451)
		zoom(mlx, WIDTH / 2, HEIGHT / 2, 2);
	else if (keycode == 78 || keycode == 65453)
		zoom(mlx, WIDTH / 2, HEIGHT / 2, 0.5);
	printf("Hello from key_hook!\n%d\n", keycode); //4-zoom in.....5-zoom out
	return (0);
}

static int	mouse(int keycode, int x, int y, t_mlx *mlx)
{
	printf("Mouse keycode: %d X: %d\nY: %d\n", keycode, x, y);
	if (keycode == 4)
		zoom(mlx, x, y, 2);
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

	start(&mlx);
	mlx_mouse_hook(mlx.win, mouse, &mlx);
	mlx_key_hook(mlx.win, key, &mlx);
	mlx_loop(mlx.mlx);
	
}
