/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:09:28 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/23 20:44:26 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	key_hook(mlx_key_data_t keydata, void *data)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) data;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->mlx);
}

static void	hook(void *data)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) data;
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_name>\n", argv[0]);
		exit(1);
	}
	fdf = ft_init_fdf(SCREEN_WIDTH, SCREEN_HEIGHT, false, argv[1]);
	ft_process_image(fdf);
	mlx_key_hook(fdf->mlx, &key_hook, fdf);
	mlx_loop_hook(fdf->mlx, &hook, fdf);
	mlx_loop(fdf->mlx);
	free_fdf(&fdf);
	return (0);
}
