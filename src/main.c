/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:07:44 by sdonny            #+#    #+#             */
/*   Updated: 2022/02/07 13:07:46 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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

static int	close_win(void *mlx)
{
	end(ESC, (t_mlx *)mlx);
	return (0);
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
	mlx_hook(mlx.win, 6, 1L << 6, julia_motion, &mlx);
	mlx_hook(mlx.win, 17, 0, close_win, &mlx);
	mlx_loop(mlx.mlx);
}
