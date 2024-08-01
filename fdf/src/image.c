/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:19:02 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/29 20:16:24 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	create_lines(t_fdf *fdf, size_t i, size_t j)
{
	t_draw_point	p_a;
	t_draw_point	p_b;

	if (j < fdf->matrix_width - 1)
	{
		p_a.z = fdf->map[i][j].z;
		p_a.coords = isometric_coordinates(fdf, j, i, p_a.z);
		p_a.color = fdf->map[i][j].color;
		p_b.z = fdf->map[i][j + 1].z;
		p_b.coords = isometric_coordinates(fdf, j + 1, i, p_b.z);
		p_b.color = fdf->map[i][j + 1].color;
		ft_draw_line(fdf, &p_a, &p_b);
	}
	if (i < fdf->matrix_height - 1)
	{
		p_a.z = fdf->map[i][j].z;
		p_a.coords = isometric_coordinates(fdf, j, i, p_a.z);
		p_a.color = fdf->map[i][j].color;
		p_b.z = fdf->map[i + 1][j].z;
		p_b.coords = isometric_coordinates(fdf, j, i + 1, p_b.z);
		p_b.color = fdf->map[i + 1][j].color;
		ft_draw_line(fdf, &p_a, &p_b);
	}
}

static t_coord	get_height(t_fdf *fdf)
{
	t_coord	height;
	size_t	i;
	size_t	j;

	height.x = fdf->map[0][0].z;
	height.y = fdf->map[0][0].z;
	i = 0;
	while (i < fdf->matrix_height)
	{
		j = 0;
		while (j < fdf->matrix_width)
		{
			height.x = ft_min(height.x, fdf->map[i][j].z);
			height.y = ft_max(height.y, fdf->map[i][j].z);
			j++;
		}
		i++;
	}
	return (height);
}

static t_coord	get_min_coords(t_fdf *fdf)
{
	int				i;
	int				j;
	t_coord			min;
	t_coord			coords;

	min = isometric_non_scaled(fdf, 0, 0, fdf->map[0][0].z);
	i = -1;
	while ((size_t)(++i) < fdf->matrix_height)
	{
		j = -1;
		while ((size_t)(++j) < fdf->matrix_width)
		{
			coords = isometric_non_scaled(fdf, j, i, fdf->map[i][j].z);
			min.x = ft_mind(min.x, coords.x);
			min.y = ft_mind(min.y, coords.y);
		}
	}
	return (min);
}

static t_coord	get_isometric_scale(t_fdf *fdf)
{
	int				i;
	int				j;
	t_coord			max;
	t_coord			coords;

	max = isometric_non_scaled(fdf, 0, 0, fdf->map[0][0].z);
	i = -1;
	while ((size_t)(++i) < fdf->matrix_height)
	{
		j = -1;
		while ((size_t)(++j) < fdf->matrix_width)
		{
			coords = isometric_non_scaled(fdf, j, i, fdf->map[i][j].z);
			max.x = ft_maxd(max.x, coords.x);
			max.y = ft_maxd(max.y, coords.y);
		}
	}
	coords.x = (fdf->width - (2 * SCREEN_OFFSET_W)) / max.x;
	coords.y = (fdf->height - (2 * SCREEN_OFFSET_H)) / max.y;
	return (coords);
}

void	ft_process_image(t_fdf *fdf)
{
	size_t			i;
	size_t			j;

	ft_draw_background(fdf, BACKGROUND_COLOR);
	fdf->z_coords = get_height(fdf);
	fdf->min = get_min_coords(fdf);
	fdf->scale = get_isometric_scale(fdf);
	i = 0;
	while (i < fdf->matrix_height)
	{
		j = 0;
		while (j < fdf->matrix_width)
			create_lines(fdf, i, j++);
		i++;
	}
}
