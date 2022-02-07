/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:08:18 by sdonny            #+#    #+#             */
/*   Updated: 2022/02/07 13:08:19 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	plus(t_mlx *mlx)
{
	mlx->color->r[0] = (mlx->color->r[0] + 50) % 255;
	mlx->color->r[1] = (mlx->color->r[1] + 50) % 255;
	mlx->color->g[0] = (mlx->color->g[0] + 50) % 255;
	mlx->color->g[1] = (mlx->color->g[1] + 50) % 255;
	mlx->color->b[0] = (mlx->color->b[0] + 50) % 255;
	mlx->color->b[1] = (mlx->color->b[1] + 50) % 255;
	mlx->change_color = 0;
}

int	palette(float hue, t_mlx *mlx)
{
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
		plus(mlx);
	if (hue == -1)
		return (0);
	return (create_trgb(0,
			mlx->color->r[0] + hue * (mlx->color->r[1] - mlx->color->r[0]),
			mlx->color->g[0] + hue * (mlx->color->g[1] - mlx->color->g[0]),
			mlx->color->b[0] + hue * (mlx->color->b[1] - mlx->color->b[0])));
}

int	*get_numiters(int **arr, t_mlx *mlx)
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

int	get_total(int *numiters, t_mlx *mlx)
{
	int	x;
	int	total;

	x = -1;
	total = 0;
	while (++x <= MAX_ITER + 2 * log2(4 / (mlx->p2[0] - mlx->p1[0])))
		total += numiters[x];
	return (total);
}
