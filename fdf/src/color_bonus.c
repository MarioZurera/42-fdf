/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:39:22 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/25 16:31:20 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static t_color	ft_hex_to_color(uint32_t hex)
{
	t_color	color;

	color.red = (uint8_t)(hex >> 24);
	color.green = (uint8_t)(hex >> 16);
	color.blue = (uint8_t)(hex >> 8);
	color.alpha = (uint8_t)(hex & 0xFF);
	return (color);
}

static uint32_t	ft_color_to_hex(t_color color)
{
	uint32_t	hex;

	hex = 0;
	hex |= color.red << 24;
	hex |= color.green << 16;
	hex |= color.blue << 8;
	hex |= color.alpha;
	return (hex);
}

uint32_t	ft_color_gradient(uint32_t hex1, uint32_t hex2, double factor)
{
	t_color	color;
	t_color	color2;

	if (factor < 0)
		factor = 0;
	if (factor > 1)
		factor = 1;
	color = ft_hex_to_color(hex1);
	color2 = ft_hex_to_color(hex2);
	color.red += round((color2.red - color.red) * factor);
	color.green += round((color2.green - color.green) * factor);
	color.blue += round((color2.blue - color.blue) * factor);
	color.alpha += round((color2.alpha - color.alpha) * factor);
	return (ft_color_to_hex(color));
}
