/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:07:28 by sdonny            #+#    #+#             */
/*   Updated: 2022/02/07 13:07:30 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	heart(t_mlx *mlx, long double xx, long double yy)
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
	while (++i < (MAX_ITER + 2 * mlx->zoom_iter
		&& x2 + y2 < 10000))
	{
		y = fabsl(x) * y * 2 + yy;
		x = x2 - y2 + xx;
		x2 = x * x;
		y2 = y * y;
	}
	if (i == MAX_ITER + 2 * mlx->zoom_iter)
		return (-1);
	return (i);
}

int	tricorn(t_mlx *mlx, long double x, long double y)
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
	while (++i < (MAX_ITER + 2 * mlx->zoom_iter)
		&& x2 + y2 < 4)
	{
		y = -(x + x) * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
	}
	if (i == MAX_ITER + 2 * mlx->zoom_iter)
		return (-1);
	return (i);
}

int	mndlbrt(t_mlx *mlx, long double x, long double y)
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
	while (++i < (MAX_ITER + 2 * mlx->zoom_iter)
		&& x2 + y2 <= 4)
	{
		y = (x + x) * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
	}
	if (i == MAX_ITER + 2 * mlx->zoom_iter)
		return (-1);
	return (i);
}

int	julia(t_mlx *mlx, long double x, long double y)
{
	int			i;
	long double	x2;
	long double	y2;

	i = -1;
	x2 = x * x;
	y2 = y * y;
	while (x2 + y2 < 4
		&& ++i < (MAX_ITER + 2 * mlx->zoom_iter))
	{
		y = (x + x) * y + mlx->y;
		x = x2 - y2 + mlx->x;
		x2 = x * x;
		y2 = y * y;
	}
	if (i == MAX_ITER + 2 * mlx->zoom_iter)
		return (-1);
	return (i);
}

int	perp(t_mlx *mlx, long double xx, long double yy)
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
	while (++i < (MAX_ITER + 2 * mlx->zoom_iter)
		&& x2 + y2 < 10000)
	{
		y = fabsl(x) * y * (-2) + yy;
		x = fabsl(x2 - y2) + xx;
		x2 = x * x;
		y2 = y * y;
	}
	if (i == MAX_ITER + 2 * mlx->zoom_iter)
		return (-1);
	return (i);
}
