/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:56:36 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/23 15:20:05 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fdf(t_fdf **ptr_fdf)
{
	t_fdf	*fdf;
	int		i;

	fdf = *ptr_fdf;
	if (fdf == NULL)
		return ;
	if (fdf->mlx != NULL)
	{
		mlx_close_window(fdf->mlx);
		mlx_terminate(fdf->mlx);
	}
	if (fdf->map != NULL)
	{
		i = -1;
		while ((size_t)(++i) < fdf->matrix_height)
			free(fdf->map[i]);
		free(fdf->map);
	}
	free(fdf);
	*ptr_fdf = NULL;
}

void	print_error(t_error code, t_fdf *fdf, const char *msg)
{
	free_fdf(&fdf);
	if (msg == NULL)
		msg = "";
	if (code == FDF_INIT_ERROR)
		ft_printf("fdf: error while creating internal fdf structure\n");
	if (code == FDF_INVALID_MAP)
		ft_printf("fdf: invalid map: '%s'\n", msg);
	exit(1);
}
