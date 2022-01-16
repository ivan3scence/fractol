#include "../includes/fractol.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static int	tone(int cycle)
{
	//int	trgb;

	//if (cycle < 1)
	//	return (0);
	//trgb = create_trgb(0, get_r(cycle), get_g(cycle),
//			255);
	//printf("%d\n", trgb);
	//return (trgb);
	return (255 + cycle*255);
}

static int	inset(double x, double y)
{
	int	i;
	double	p = x;
	double	q = y;
	double	x_temp;
	double	sqr;

	i = -1;
	while (++i < 10000)
	{
		sqr = x * x + y * y;
		if (sqr * sqr > 4)
			return (tone(i));
		x_temp = x;
		x = x * x - y * y + p;
		y = 2 * x_temp * y + q;
	}
	return (0x0000ff00);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	double x=-960;
	double y;
	while (++x < 960)
	{
		y = 540;
		while (--y > -540)
		{
			my_mlx_pixel_put(&img, x + 960, abs((int)(y - 540)),
					inset(x / 500 - 1, y / 500));
			printf("%g, %g\n", x / 500 - 1, y / 500);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
