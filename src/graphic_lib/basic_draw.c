/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:30:55 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/19 15:23:50 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	my_mlx_pixel_put(t_mini *mini, t_var_trace var
	, t_vec2 index, unsigned int color)
{
	char	*dst;

	if (!(var.j + index.v + mini->block_size > WIDTH
			|| (var.i + index.u) > var.max || (var.j + index.v) < 0
			|| (var.i + index.u) < 0))
	{
		dst = mini->display.img.addr + ((var.i + index.u)
				* mini->display.img.line_length + (var.j + index.v)
				* (mini->display.img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
		return (0);
	}
	return (-1);
}

unsigned int	color_shift(t_color rgb)
{
	return ((unsigned int)(0 << 24 | rgb.r << 16 | rgb.g << 8 | rgb.b));
}

t_color	color_shift_revert(unsigned int color)
{
	t_color	rgb;

	rgb.b = color & 0x000000FF;
	rgb.g = (color & 0x0000FF00) >> 8;
	rgb.r = (color & 0x00FF0000) >> 16;
	return (rgb);
}
