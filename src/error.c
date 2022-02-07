/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:07:09 by sdonny            #+#    #+#             */
/*   Updated: 2022/02/07 13:07:13 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	print_help(void)
{
	ft_putstr_fd("\nfractol gets only 2 arguments\n", 1);
	ft_putstr_fd("\ttry one of these:\n\n$> ./fractol Mandelbrot\n", 1);
	ft_putstr_fd("$> ./fractol Julia\n$> ./fractol Buffalo\n", 1);
	ft_putstr_fd("$> ./fractol Tricorn\n$> ./fractol 'Burning Ship'\n", 1);
	ft_putstr_fd("$> ./fractol 'Perpendicular Celtic'\n", 1);
	ft_putstr_fd("$> ./fractol 'Mandelbrot Heart'\n\n", 1);
	ft_putstr_fd("ESC: quit;\nnumpad +/-: zoom in/out\nTAB: color change\n",
		1);
	ft_putstr_fd("arrows: move\n\n", 1);
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
	exit(1);
}

static void	free_col(t_mlx *mlx)
{
	if (mlx->color)
		free(mlx->color);
	mlx->color = NULL;
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
		free_col(mlx);
	}
	perry(id);
}
