/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:44:26 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/29 20:16:06 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_z_color_point	**ft_lst_to_array(t_list *list, t_fdf *fdf,
		const char *filename)
{
	t_list				*temp;
	size_t				i;
	t_z_color_point		**matrix;

	i = 0;
	fdf->matrix_height = ft_lstsize(list);
	matrix = malloc((fdf->matrix_height + 1) * sizeof(t_z_color_point *));
	while (i < fdf->matrix_height)
	{
		if (list->content == NULL)
			print_error(FDF_INVALID_MAP, fdf, filename);
		matrix[i] = (t_z_color_point *) list->content;
		temp = list;
		list = list->next;
		free(temp);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}

static t_z_color_point	*matrix_line(t_fdf *fdf, char *line,
	size_t len, const char *filename)
{
	t_z_color_point		*map_line;
	char				**words;
	char				**pairs;
	int					i;

	if (line == NULL)
		return (NULL);
	map_line = ft_calloc(len + 1, sizeof(t_z_color_point));
	words = ft_split(ft_str_in_trim(line, " \n"), ' ');
	i = -1;
	while ((size_t)(++i) < len && words != NULL && words[i] != NULL)
	{
		pairs = ft_split(words[i], ',');
		if (pairs == NULL)
			print_error(FDF_INVALID_MAP, fdf, filename);
		map_line[i].z = ft_atoi(pairs[0]);
		map_line[i].color = (ft_atohex(pairs[1]) << 8) | 0xFF;
		free(pairs[0]);
		free(pairs[1]);
		free(pairs);
		free(words[i]);
	}
	while (words[i] != NULL)
		free(words[i++]);
	return (free(words), map_line);
}

static size_t	count_words(const char *line)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		count++;
		while (line[i] && line[i] != ' ')
			i++;
		while (line[i] == ' ')
			i++;
	}
	return (count);
}

static t_z_color_point	**ft_init_map(const char *filename, t_fdf *fdf)
{
	int		fd;
	char	*line;
	t_list	*list;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error(FDF_INVALID_MAP, fdf, filename);
	line = get_next_line(fd);
	if (line == NULL)
		print_error(FDF_INVALID_MAP, fdf, filename);
	fdf->matrix_width = count_words(line);
	list = ft_lstnew(matrix_line(fdf, line, fdf->matrix_width, filename));
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		ft_lstadd_back(&list, ft_lstnew(
				matrix_line(fdf, line, fdf->matrix_width, filename)));
	}
	close(fd);
	return (ft_lst_to_array(list, fdf, filename));
}

t_fdf	*ft_init_fdf(uint32_t width, uint32_t height,
		bool resize, const char *filename)
{
	t_fdf	*fdf;
	int		res;

	fdf = ft_calloc(1, sizeof(t_fdf));
	if (fdf == NULL)
		print_error(FDF_INIT_ERROR, fdf, NULL);
	fdf->width = width;
	fdf->height = height;
	fdf->map = ft_init_map(filename, fdf);
	fdf->mlx = mlx_init(width, height, WINDOW_TITLE, resize);
	if (fdf->mlx == NULL)
		print_error(FDF_INIT_ERROR, fdf, NULL);
	fdf->image = mlx_new_image(fdf->mlx, width, height);
	if (fdf->image == NULL)
		print_error(FDF_INIT_ERROR, fdf, NULL);
	res = mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
	if (res < 0)
		print_error(FDF_INIT_ERROR, fdf, NULL);
	fdf->scale = (t_coord){1, 1};
	fdf->rotation = (t_rotation){1, 3, 0};
	return (fdf);
}
