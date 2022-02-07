/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:07:20 by sdonny            #+#    #+#             */
/*   Updated: 2022/02/07 13:07:21 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	zoom(t_mlx *mlx, int x, int y, float mult)
{
	long double	cursor_x;
	long double	cursor_y;

	if ((mlx->zoom_iter > -10 && mult < 1)
		|| (mlx->zoom_iter < 70 && mult > 1))
	{
		cursor_x = mlx->p1[0] + (mlx->p2[0] - mlx->p1[0]) / WIDTH * x;
		cursor_y = mlx->p1[1] - (mlx->p1[1] - mlx->p2[1]) / HEIGHT * y;
		mlx->p1[0] = cursor_x - (cursor_x - mlx->p1[0]) / mult;
		mlx->p1[1] = cursor_y + (mlx->p1[1] - cursor_y) / mult;
		mlx->p2[0] = cursor_x + (mlx->p2[0] - cursor_x) / mult;
		mlx->p2[1] = cursor_y - (cursor_y - mlx->p2[1]) / mult;
		if (mult < 1)
			mlx->zoom_iter -= 1;
		else if (mult > 1)
			mlx->zoom_iter += 1;
	}
	printf("raznica %d\n", mlx->zoom_iter);
	start(mlx);
}

static void	move(int keycode, t_mlx *mlx)
{
	long double	delta_x;
	long double	delta_y;

	delta_x = (mlx->p2[0] - mlx->p1[0]) / 5;
	delta_y = (mlx->p1[1] - mlx->p2[1]) / 5;
	if (keycode == 126 || keycode == 125)
	{
		mlx->p1[1] += delta_y + (keycode + keycode - 252) * delta_y;
		mlx->p2[1] += delta_y + (keycode + keycode - 252) * delta_y;
	}
	else if (keycode == 124 || keycode == 123)
	{
		mlx->p1[0] += delta_x + (keycode + keycode - 248) * delta_x;
		mlx->p2[0] += delta_x + (keycode + keycode - 248) * delta_x;
	}
	start(mlx);
}

int	julia_motion(int x, int y, t_mlx *mlx)
{
	long double	xx;
	long double	yy;

	if (mlx->flag == 0 || mlx->f != (void *)&julia)
		return (0);
	xx = 4 * ((double)x / WIDTH - 0.5);
	yy = 4 * ((double)(HEIGHT - y) / HEIGHT - 0.5);
	if ((mlx->x < 0.005 + xx || mlx->x > 0.005 + xx)
		&& (mlx->y < 0.005 + yy || mlx->y > 0.005 + yy))
	{
		mlx->x = xx;
		mlx->y = yy;
		start(mlx);
	}
	return (1);
}

int	key(int keycode, t_mlx *mlx)
{
	if (keycode == ESC)
		end(ESC, mlx);
	else if (keycode == PLUS)
		zoom(mlx, WIDTH / 2, HEIGHT / 2, 2);
	else if (keycode == MINUS)
		zoom(mlx, WIDTH / 2, HEIGHT / 2, 0.5);
	else if (keycode < 127 && keycode > 122)
		move(keycode, mlx);
	if (keycode == 106 && mlx->flag == 0)
		mlx->flag = 1;
	else if (keycode == 106 && mlx->flag == 1)
		mlx->flag = 0;
	else if (keycode == TAB || keycode == ZERO)
	{
		if (keycode == TAB)
			mlx->change_color = 1;
		else
			mlx->change_color = -1;
		start(mlx);
	}
	else if (keycode == JAY && mlx->flag == 0)
		mlx->flag = 1;
	else if (keycode == JAY && mlx->flag == 1)
		mlx->flag = 0;
	return (0);
}

int	mouse(int keycode, int x, int y, t_mlx *mlx)
{
	if (keycode == 4)
		zoom(mlx, x, y, 2);
	else if (keycode == 5)
		zoom(mlx, x, y, 0.5);
	return (1);
}
