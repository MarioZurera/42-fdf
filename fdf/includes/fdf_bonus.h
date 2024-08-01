/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:32:39 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/30 15:51:38 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "../libft/colors.h"
# include "../libft/libft.h"
# include <MLX42/MLX42.h>
# include <math.h>
# include <sys/time.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

/* CONSTANTS */
# define SCREEN_WIDTH 2000
# define SCREEN_HEIGHT 2000
# define SCREEN_OFFSET_H 125
# define SCREEN_OFFSET_W 125
# define MOVEMENT_FACTOR 100
# define ZOOM_FACTOR 1.25
# define WINDOW_TITLE "FdF"

/* COLORS */
# define HIGH_COLOR 0xFF0000FF
# define LOW_COLOR 0xFFFF00FF
# define BACKGROUND_COLOR 0x000000FF

typedef enum e_error
{
	FDF_INIT_ERROR = 1,
	FDF_INVALID_MAP = 2
}	t_error;

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_draw_point
{
	t_coord	coords;
	double	z;
	int		color;
}	t_draw_point;

typedef struct s_z_color_point
{
	int			z;
	uint32_t	color;
}	t_z_color_point;

typedef struct s_rotation
{
	double	x;
	double	y;
	double	z;
}	t_rotation;

typedef struct s_fdf
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_z_color_point	**map;
	size_t			width;
	size_t			height;
	size_t			matrix_width;
	size_t			matrix_height;
	t_coord			scale;
	t_coord			z_coords;
	t_coord			min;
	t_rotation		rotation;
	t_coord			movement;
	t_coord			zoom;
	char			perspective;
	struct timeval	t1;
	struct timeval	t2;
}	t_fdf;

typedef struct s_color
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;
}	t_color;

/**
 * @brief Initialize the fdf structure
 * @param width The width of the window
 * @param height The height of the window
 * @param resize If the window can be resized
 * @param filename The name of the map file
 * @return The fdf structure
 * @note The fdf structure should be freed with free_fdf
*/
t_fdf		*ft_init_fdf(uint32_t width, uint32_t height,
				bool resize, const char *filename);

/**
 * @brief Free the fdf structure and all its internal elements
 * @param ptr_fdf The pointer to the fdf structure
*/
void		free_fdf(t_fdf **ptr_fdf);

/**
 * @brief Get the color gradient with the specified factor
 * @param hex1 The low color
 * @param hex2 The high color
 * @param factor The factor to calculate the gradient, a number between 0 and 1
 * @return The color between hex1 and hex2 by a factor percentage
*/
uint32_t	ft_color_gradient(uint32_t hex1, uint32_t hex2, double factor);

/**
 * @brief Get the isometric coordinates of a point in 3D space
 * @param fdf The fdf structure
 * @param x The x coordinate
 * @param y The y coordinate
 * @param z The z coordinate
 * @return The isometric coordinates of the point
 */
t_coord		isometric_non_scaled(t_fdf *fdf, int x, int y, int z);

/**
 * @brief Get the isometric coordinates of a point in 3D space
 * @param fdf The fdf structure
 * @param x The x coordinate
 * @param y The y coordinate
 * @param z The z coordinate
 * @return The isometric coordinates of the point
 * @note The coordinates are scaled and normalized to the screen size
 */
t_coord		isometric_coordinates(t_fdf *fdf, int x, int y, int z);

/**
 * @brief Draw the screen background with the specified color
 * @param fdf The fdf structure
 * @param color The color to draw the background
 * @note The color should be in the format 0xRRGGBBAA
*/
void		ft_draw_background(t_fdf *fdf, uint32_t color);

/**
 * @brief Draw a line between two points on the screen
 * @param fdf The fdf structure
 * @param pA The first point
 * @param pB The second point
*/
void		ft_draw_line(t_fdf *fdf, t_draw_point *pA, t_draw_point *pB);

/**
 * @brief Print the fdf map on the screen
 * @param fdf The fdf structure
*/
void		ft_process_image(t_fdf *fdf);

/**
 * @brief Print an error message, free the fdf structure and exit the program
 * @param code The error code
 * @param fdf The fdf structure
*/
void		print_error(t_error code, t_fdf *fdf, const char *msg);

int			main(int argc, char **argv);

#endif /* FDF_BONUS_H */
