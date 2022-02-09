/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:08:10 by sdonny            #+#    #+#             */
/*   Updated: 2022/02/07 13:08:11 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	iter_count(t_mlx *mlx)
{
	int			h;
	int			w;
	long double	x;
	long double	y;

	w = -1;
	x = mlx->p1[0];
	while (++w < WIDTH)
	{
		h = -1;
		y = mlx->p1[1];
		while (++h < HEIGHT)
		{
			mlx->array_iters[w][h] = mlx->f(mlx, x, y);
			y -= (mlx->p1[1] - mlx->p2[1]) / HEIGHT;
		}
		x += (mlx->p2[0] - mlx->p1[0]) / WIDTH;
	}
}

void	*clean_array(double **hue, int **array_iters, int *numiters)
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

void	end_hue(double **a, int index, t_mlx *mlx)
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

double	**get_hue(t_mlx *mlx)
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

void	set_hue(double **hue, int **array_iters, int *numiters, int total)
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
