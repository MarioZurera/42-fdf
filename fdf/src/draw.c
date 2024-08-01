/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:58:23 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/29 20:16:48 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_background(t_fdf *fdf, uint32_t color)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			mlx_put_pixel(fdf->image, j, i, color);
			j++;
		}
		i++;
	}
}

static void	ft_draw_point(t_fdf *fdf, t_coord *coords,
		int height, uint32_t color)
{
	double		factor;

	if (coords->x < 0 || (size_t) coords->x >= fdf->width
		|| coords->y < 0 || (size_t) coords->y >= fdf->height)
		return ;
	if (color <= 0xFF)
	{
		factor = (height - fdf->z_coords.x);
		if (fdf->z_coords.y != fdf->z_coords.x)
			factor /= (fdf->z_coords.y - fdf->z_coords.x);
		color = ft_color_gradient(LOW_COLOR, HIGH_COLOR, factor);
	}
	mlx_put_pixel(fdf->image, coords->x, coords->y, color);
}

void	ft_draw_line(t_fdf *fdf, t_draw_point *pA, t_draw_point *pB)
{
	double	num_pixels;
	double	delta_x;
	double	delta_y;
	double	delta_z;

	delta_x = pB->coords.x - pA->coords.x;
	delta_y = pB->coords.y - pA->coords.y;
	delta_z = pB->z - pA->z;
	num_pixels = round(sqrt((delta_x * delta_x) + (delta_y * delta_y)));
	delta_x /= num_pixels;
	delta_y /= num_pixels;
	delta_z /= num_pixels;
	while (num_pixels--)
	{
		ft_draw_point(fdf, &pA->coords, pA->z, pA->color);
		pA->coords.x += delta_x;
		pA->coords.y += delta_y;
		pA->z += delta_z;
	}
}
