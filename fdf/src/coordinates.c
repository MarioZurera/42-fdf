/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:46:31 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/29 20:17:20 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate(int *x, int *y, double angle)
{
	int	old_x;
	int	yy;

	yy = *y;
	old_x = *x;
	*x = round(((*x) * (cos(angle))) - ((*y) * (sin(angle))));
	*y = round(((old_x) * (sin(angle))) + ((*y) * (cos(angle))));
}

static void	ft_rotation(t_fdf *fdf, int *x, int *y, int *z)
{
	rotate(y, z, fdf->rotation.x * M_PI / 2);
	rotate(x, z, fdf->rotation.y * M_PI / 2);
	rotate(x, y, fdf->rotation.z * M_PI / 2);
}

t_coord	isometric_non_scaled(t_fdf *fdf, int x, int y, int z)
{
	t_coord	coords;

	ft_rotation(fdf, &x, &y, &z);
	coords.x = ((sqrt(2) / 2) * (x - z));
	coords.y = ((1 / sqrt(6)) * (x + 2 * y + z));
	coords.x -= fdf->min.x;
	coords.y -= fdf->min.y;
	return (coords);
}

t_coord	isometric_coordinates(t_fdf *fdf, int x, int y, int z)
{
	t_coord	coords;

	ft_rotation(fdf, &x, &y, &z);
	if (fdf->scale.x == 0 || fdf->scale.y == 0)
		fdf->scale = (t_coord){1, 1};
	coords.x = ((sqrt(2) / 2) * (x - z));
	coords.y = ((1 / sqrt(6)) * (x + 2 * y + z));
	coords.x -= fdf->min.x;
	coords.y -= fdf->min.y;
	coords.x *= fdf->scale.x;
	coords.y *= fdf->scale.y;
	coords.x += SCREEN_OFFSET_W;
	coords.y += SCREEN_OFFSET_H;
	coords.x = round(coords.x);
	coords.y = round(coords.y);
	return (coords);
}
