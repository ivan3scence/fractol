/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:08:02 by sdonny            #+#    #+#             */
/*   Updated: 2022/02/07 13:08:03 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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

// static void	threading(t_mlx *mlx)
// {
// 	int			i;
// 	t_thread	*thr;
// 	pthread_t	tid[THREADS];

// 	i = -1;
// 	while (++i < THREADS)
// 	{
// 		thr = (t_thread *)malloc(sizeof(t_thread));
// 		if (!thr)
// 			end(MALLOC, mlx);
// 		thr->thread = i;
// 		thr->mlx = mlx;
// 		if (pthread_create(&tid[i], NULL, iter_count, thr) != 0)
// 			end(THREADS_ERR, mlx);
// 	}
// 	i = -1;
// 	while (++i < THREADS)
// 	{
// 		if (pthread_join(tid[i], NULL) != 0)
// 			end(THREADS_ERR, mlx);
// 	}
// }

void	start(t_mlx *mlx)
{
	int		*numiters;
	int		total;
	double	**hue;

	mlx->array_iters = get_array_iters(mlx);
	iter_count(mlx);
	numiters = get_numiters(mlx->array_iters, mlx);
	total = get_total(numiters, mlx);
	hue = get_hue(mlx);
	set_hue(hue, mlx->array_iters, numiters, total);
	draw_pic(mlx, hue);
	mlx->array_iters = clean_array(hue, mlx->array_iters, numiters);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
