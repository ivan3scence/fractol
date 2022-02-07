#include "../includes/fractol.h"

static void	print_help(void)
{
	ft_putstr_fd("\nfractol gets only 2 arguments\n", 1);
	ft_putstr_fd("\ttry one of these:\n\n$> ./fractol Mandelbrot\n", 1);
	ft_putstr_fd("$> ./fractol Julia\n$> ./fractol Buffalo\n", 1);
	ft_putstr_fd("$> ./fractol Tricorn\n$> ./fractol 'Burning Ship'\n", 1);
	ft_putstr_fd("$> ./fractol 'Perpendicular Celtic'\n", 1);
	ft_putstr_fd("$> ./fractol 'Mandelbrot Heart'\n\n", 1);
	return ;
}

static void	perry(int id)
{
	if (id == 2)
		perror("Malloc rip");
	else if (id == 3)
		perror("Error has occured while working with threads");
	else if (id == ESC)
	{
		ft_putstr_fd("fract'ol has been successfully closed\n", 1);
		exit(0);
	}
	return ;
}

void	end(int id, t_mlx *mlx)
{
	int	w;

	w = -1;
	if (id == 1)
		print_help();
	if (mlx)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		if (mlx->array_iters)
		{
			while (++w < WIDTH)
			{
				if (mlx->array_iters[w])
				{
					free(mlx->array_iters[w]);
					mlx->array_iters[w] = NULL;
				}
			}
			free(mlx->array_iters);
			mlx->array_iters = NULL;
		}
		if (mlx->color)
			free(mlx->color);
		mlx->color = NULL;
	}
	perry(id);
	exit(1);
}

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
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
 * 00 7f ff 00
 * 00 00 fa 9a
 */

static int	palette(float hue, t_mlx *mlx)
{
	/*r[0] = 75;
	r[1] = 255;
	g[0] = 0;
	g[1] = 182;
	b[0] = 50;
	b[1] = 200;*/
	if (mlx->color == 0 || mlx->change_color == -1)
	{
		if (!mlx->color)
			mlx->color = (t_col *)malloc(sizeof(t_col));
		if (!mlx->color)
			end(MALLOC, mlx);
		mlx->color->r[0] = 51;
		mlx->color->r[1] = 255;
		mlx->color->g[0] = 0;
		mlx->color->g[1] = 153;
		mlx->color->b[0] = 0;
		mlx->color->b[1] = 204;
	}
	else if (mlx->change_color == 1)
	{
		mlx->color->r[0] = (mlx->color->r[0] + 50) % 255;
		mlx->color->r[1] = (mlx->color->r[1] + 50) % 255;
		mlx->color->g[0] = (mlx->color->g[0] + 50) % 255;
		mlx->color->g[1] = (mlx->color->g[1] + 50) % 255;
		mlx->color->b[0] = (mlx->color->b[0] + 50) % 255;
		mlx->color->b[1] = (mlx->color->b[1] + 50) % 255;
		mlx->change_color = 0;
	}
	//mlx->color = 0;
	//b[1] = 204;
	//return (iter * iter);
	/*r[0] = 51;
	r[1] = 255;
	g[0] = 0;
	g[1] = 153;
	b[0] = 0;
	b[1] = rand();*/
    if (hue == -1)
		return (0);
	return (create_trgb(255 - 255 * hue, ///with shadow
			mlx->color->r[0] + hue * (mlx->color->r[1] - mlx->color->r[0]),
			mlx->color->g[0] + hue * (mlx->color->g[1] - mlx->color->g[0]),
			mlx->color->b[0] + hue * (mlx->color->b[1] - mlx->color->b[0])));	//int cl;
	//r[0]=g[0]=b[0]=0;
	//if ((int)(hue * 100) % 3 == 2)
	//	r[0] = 255;
	//else if ((int)(hue * 100) % 3 == 1)
	//	g[0] = 255;
	//else
	//	b[0] = 255;
	//return (create_trgb(0,               ///with shadow
	//					r[0],
	//					g[0],
	//					b[0]
	//					));
	//return (create_trgb(255 - 255 * hue,
	//					hue * 255,
	//					0,
	//					0
	//					));
	//return (create_trgb(0, get_r(iter / MAX_ITER * 255),
	//get_g(iter / MAX_ITER * 255),
	//			get_b(iter / MAX_ITER * 255)));
}

static t_mlx *change_colore(t_mlx *mlx)
{
    return (mlx);
}

static int	*get_numiters(int **arr, t_mlx *mlx)
{
	int	x;
	int	y;
	int	*ret;

	ret = (int *)malloc(sizeof(int) * (MAX_ITER + 2 * log2(4
					/ (mlx->p2[0] - mlx->p1[0])) + 1));
	if (!ret)
		end(MALLOC, mlx);
	x = -1;
	while (++x <= MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		ret[x] = 0;
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		y++;
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
	while (++x <= MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		total += numiters[x];
	return (total);
}

static int	burnship(t_mlx *mlx, long double x, long double y)
{
	int			i;
	long double	x2;
	long double	y2;
	long double	x0;
	long double	y0;

	i = -1;
	x2 = x * x;
	y2 = y * y;
	x0 = x;
	y0 = y;
	while (++i < (MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		&& x2 + y2 < 4)
	{
		y = fabsl(x * y) * (-2) + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
	}
	if (i == MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		return (-1);
	return (i);
}

static int	buffalo(t_mlx *mlx, long double xx, long double yy)
{
	int			i;
	long double	x2;
	long double	y2;
	long double	x;
	long double	y;

	i = -1;
	x = 0;
	y = 0;
	x2 = x * x;
	y2 = y * y;
	while (++i < (MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		&& x2 + y2 < 10000)
	{
		y = fabsl(y * x) * (-2) + yy;
		x = fabsl(x2 - y2) + xx;
		x2 = x * x;
		y2 = y * y;
	}
	if (i == MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		return (-1);
	return (i);
}

static int	heart(t_mlx *mlx, long double xx, long double yy)
{
	int			i;
	long double	x2;
	long double	y2;
	long double	x;
	long double	y;

	i = -1;
	x = 0;
	y = 0;
	x2 = x * x;
	y2 = y * y;
	while (++i < (MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		&& x2 + y2 < 10000)
	{
		y = fabsl(x) * y * 2 + yy;
		x = x2 - y2 + xx;
		x2 = x * x;
		y2 = y * y;
	}
	if (i == MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		return (-1);
	return (i);
}

static int	tricorn(t_mlx *mlx, long double x, long double y)
{
	int			i;
	long double	x2;
	long double	y2;
	long double	x0;
	long double	y0;

	i = -1;
	x2 = x * x;
	y2 = y * y;
	x0 = x;
	y0 = y;
	while (++i < (MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		&& x2 + y2 < 4)
	{
		y = -(x + x) * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
	}
	if (i == MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		return (-1);
	return (i);
}

static int	mndlbrt(t_mlx *mlx, long double x, long double y)
{
	int			i;
	long double	x2;
	long double	y2;
	long double	x0;
	long double	y0;

	i = -1;
	x2 = x * x;
	y2 = y * y;
	x0 = x;
	y0 = y;
	while (++i < (MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		&& x2 + y2 <= 4)
	{
		y = (x + x) * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
	}
	if (i == MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		return (-1);
	return (i);
}

static int	julia(t_mlx *mlx, long double x, long double y)
{
	int			i;
	long double	x2;
	long double	y2;
	/*long double	x0=-0.8;
	//long double	y0=0.156;
	//long double	x0=-0.4;
	//long double	y0=0.6;
	//long double	x0=-0.7382;
	//long double	y0=0.0827;*/
	i = -1;
	x2 = x * x;
	y2 = y * y;
	while (x2 + y2 < 4
		&& ++i < (MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0]))))
	{
		y = (x + x) * y + mlx->y;
		x = x2 - y2 + mlx->x;
		x2 = x * x;
		y2 = y * y;
	}
	if (i == MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		return (-1);
	return (i);
}

static int	perp(t_mlx *mlx, long double xx, long double yy)
{
	int			i;
	long double	x2;
	long double	y2;
	long double	x;
	long double	y;

	i = -1;
	x = 0;
	y = 0;
	x2 = x * x;
	y2 = y * y;
	while (++i < (MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		&& x2 + y2 < 10000)
	{
		y = fabsl(x) * y * (-2) + yy;
		x = fabsl(x2 - y2) + xx;
		x2 = x * x;
		y2 = y * y;
	}
	if (i == MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		return (-1);
	return (i);
}

static void	*iter_count(void *t)
{
	int			h;
	int			w;
	long double	x;
	long double	y;
	t_thread	*thr;

	thr = (t_thread *)t;
	w = -1 + thr->thread * WIDTH / THREADS;
	x = thr->mlx->p1[0]
		+ (thr->mlx->p2[0] - thr->mlx->p1[0]) / THREADS * thr->thread;
	while (++w < WIDTH / THREADS * (thr->thread + 1))
	{
		h = -1;
		y = thr->mlx->p1[1];
		while (++h < HEIGHT)
		{
			thr->mlx->array_iters[w][h] = thr->mlx->f(thr->mlx, x, y);
			y -= (thr->mlx->p1[1] - thr->mlx->p2[1]) / HEIGHT;
		}
		x += (thr->mlx->p2[0] - thr->mlx->p1[0]) / WIDTH;
	}
	free(t);
	return (NULL);
}

static void	*clean_array(double **hue, int **array_iters, int *numiters)
{
	int	w;

	w = -1;
	if (hue && array_iters)
	{
		while (++w < WIDTH)
		{
			if (hue[w])
				free(hue[w]);
			hue[w] = NULL;
			if (array_iters[w])
				free(array_iters[w]);
			array_iters[w] = NULL;
		}
		free(hue);
		hue = NULL;
		free(array_iters);
		array_iters = NULL;
	}
	if (numiters)
	{
		free(numiters);
		numiters = NULL;
	}
	return (NULL);
}

static void	end_hue(double **a, int index, t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < index)
	{
		free(a[i]);
		a[i] = NULL;
	}
	free(a);
	a = NULL;
	end(MALLOC, mlx);
}

static double	**get_hue(t_mlx *mlx)
{
	int		xx;
	int		yy;
	double	**hue;

	xx = -1;
	yy = -1;
	hue = (double **)malloc(sizeof(double *) * WIDTH);
	if (!hue)
		end(MALLOC, mlx);
	while (++xx < WIDTH)
	{
		yy = -1;
		hue[xx] = (double *)malloc(sizeof(double) * HEIGHT);
		if (!hue[xx])
			end_hue(hue, xx, mlx);
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
			my_mlx_pixel_put(mlx, w, h, palette(hue[w][h], mlx));
	}
}

static void	end_arr(int **a, int index, t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < index)
	{
		free(a[i]);
		a[i] = NULL;
	}
	free(a);
	a = NULL;
	end(MALLOC, mlx);
}

static int	**get_array_iters(t_mlx *mlx)
{
	int	**array_iters;
	int	w;

	w = -1;
	array_iters = (int **)malloc(sizeof(int *) * WIDTH);
	if (!array_iters)
		end(MALLOC, mlx);
	while (++w < WIDTH)
	{
		array_iters[w] = (int *)malloc(sizeof(int) * HEIGHT);
		if (!array_iters[w])
			end_arr(array_iters, w, mlx);
	}
	return (array_iters);
}

static void	threading(t_mlx *mlx)
{
	int			i;
	t_thread	*thr;
	int			*j;
	pthread_t	tid[THREADS];

	i = -1;
	while (++i < THREADS)
	{
		thr = (t_thread *)malloc(sizeof(t_thread));
		if (!thr)
			end(MALLOC, mlx);
		thr->thread = i;
		thr->mlx = mlx;
		if (pthread_create(&tid[i], NULL, iter_count, thr) != 0)
			end(THREADS_ERR, mlx);
	}
	i = -1;
	while (++i < THREADS)
	{
		if (pthread_join(tid[i], NULL) != 0)
			end(THREADS_ERR, mlx);
	}
}

static void	start(t_mlx *mlx)
{
	int		*numiters;
	int		total;
	double	**hue;

	mlx->array_iters = get_array_iters(mlx);
	threading(mlx);
	numiters = get_numiters(mlx->array_iters, mlx);
	total = get_total(numiters, mlx);
	hue = get_hue(mlx);
	set_hue(hue, mlx->array_iters, numiters, total);
	draw_pic(mlx, hue);
	mlx->array_iters = clean_array(hue, mlx->array_iters, numiters);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	ft_putstr_fd("zoomed\n", 1);
}

static void	zoom(t_mlx *mlx, int x, int y, float mult)
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
	printf("%g\n", (MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0]))));
	start(mlx);
}

//static void	move(int keycode, t_mlx *mlx)
//{
//	long double	delta_x;
//	long double	delta_y;
//
//	delta_x = (mlx->p2[0] - mlx->p1[0]) / 5;
//	delta_y = (mlx->p1[1] - mlx->p2[1]) / 5;
//	if (keycode == 126 || keycode == 125)
//	{
//		mlx->p1[1] += delta_y + (keycode + keycode - 252) * delta_y;
//		mlx->p2[1] += delta_y + (keycode + keycode - 252) * delta_y;
//	}
//	else if (keycode == 124 || keycode == 123)
//	{
//		mlx->p1[0] += delta_x + (keycode + keycode - 248) * delta_x;
//		mlx->p2[0] += delta_x + (keycode + keycode - 248) * delta_x;
//	}
//	start(mlx);
//}
static void	move_lin2(int keycode, t_mlx *mlx, long double delta_x,
		long double delta_y)
{
	if (keycode == ARR_RIGHT)
	{
		mlx->p1[0] += delta_x;
		mlx->p2[0] += delta_x;
	}
	else if (keycode == ARR_LEFT)
	{
		mlx->p1[0] -= delta_x;
		mlx->p2[0] -= delta_x;
	}
}

static void	move_lin(int keycode, t_mlx *mlx)
{
	long double	delta_x;
	long double	delta_y;

	delta_x = (mlx->p2[0] - mlx->p1[0]) / 5;
	delta_y = (mlx->p1[1] - mlx->p2[1]) / 5;
	if (keycode == ARR_UP)
	{
		mlx->p1[1] += delta_y;
		mlx->p2[1] += delta_y;
	}
	else if (keycode == ARR_DOWN)
	{
		mlx->p1[1] -= delta_y;
		mlx->p2[1] -= delta_y;
	}
	else
		move_lin2(keycode, mlx, delta_x, delta_y);
	start(mlx);
}

static int	julia_motion(int x, int y, t_mlx *mlx)
{
	long double	xx;
	long double	yy;

	if (mlx->flag == 0)
		return (0);
	xx = 4 * ((double)x / WIDTH - 0.5);
	yy = 4 * ((double)(HEIGHT - y) / HEIGHT - 0.5);
	if (mlx->x != xx)
	{
		mlx->x = xx;
		mlx->y = yy;
		start(mlx);
		printf("x %d\ny %d\n", x, y);
		sleep(1);
	}
	return (1);
}

int	key(int keycode, t_mlx *mlx)
{
	if (keycode == ESC)
		end(ESC, mlx);
	if (keycode == PLUS)
		zoom(mlx, WIDTH / 2, HEIGHT / 2, 2);
	else if (keycode == MINUS)
		zoom(mlx, WIDTH / 2, HEIGHT / 2, 0.5);
	//else if (keycode < 127 && keycode > 122) //MACOS
	//	move(keycode, mlx);
	else if (keycode > 65360 && keycode < 65365)
		move_lin(keycode, mlx);
	if (keycode == 106 && mlx->flag == 0)
		mlx->flag = 1;
	else if (keycode == 106 && mlx->flag == 1)
		mlx->flag = 0;
	printf("Hello from key_hook!\n%d\n", keycode);
    if (keycode == TAB)
	{
        mlx->change_color = 1;
		start(mlx);
	}
	else if (keycode == ZERO)
	{
		mlx->change_color = -1;
		start(mlx);
	}
	return (0);
}

static int	mouse(int keycode, int x, int y, t_mlx *mlx)
{
	printf("Mouse keycode: %d X: %d\nY: %d\n", keycode, x, y);
	if (keycode == 4)
		zoom(mlx, x, y, 2);
	else if (keycode == 5)
		zoom(mlx, x, y, 0.5);
	return (1);
}

static void	*validation(int argc, char **argv)
{
	if (argc != 2)
		end(INVALID_ARGS, NULL);
	if (!ft_strncmp("Mandelbrot", argv[1], 11))
		return ((void *)&mndlbrt);
	else if (!ft_strncmp("Mandelbrot", argv[1], 11))
		return ((void *)&mndlbrt);
	else if (!ft_strncmp("Julia", argv[1], 6))
		return ((void *)&julia);
	else if (!ft_strncmp("Burning Ship", argv[1], 13))
		return ((void *)&burnship);
	else if (!ft_strncmp("Tricorn", argv[1], 8))
		return ((void *)&tricorn);
	else if (!ft_strncmp("Perpendicular Celtic", argv[1], 21))
		return ((void *)&perp);
	else if (!ft_strncmp("Buffalo", argv[1], 8))
		return ((void *)&buffalo);
	else if (!ft_strncmp("Mandelbrot Heart", argv[1], 17))
		return ((void *)&heart);
	else
		end(INVALID_ARGS, NULL);
	return (NULL);
}

static void	init(t_mlx *mlx, char **argv)
{
	mlx->p1[0] = -2;
	mlx->p1[1] = 2;
	mlx->p2[0] = 2;
	mlx->p2[1] = -2;
	if (argv[1][0] == 'J')
	{
		mlx->x = -0.7382;
		mlx->y = 0.0827;
		mlx->flag = 0;
	}
	mlx->color = NULL;
	mlx->change_color = 0;
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	mlx.f = validation(argc, argv);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "fract'ol");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_length,
			&mlx.endian);
	init(&mlx, argv);
	start(&mlx);
	mlx_mouse_hook(mlx.win, mouse, &mlx);
	mlx_key_hook(mlx.win, key, &mlx);
	if (argv[1][0] == 'J')
		mlx_hook(mlx.win, 6, 1L << 6, julia_motion, &mlx);
	mlx_loop(mlx.mlx);
}
