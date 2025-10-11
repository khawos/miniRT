/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:30:55 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/25 14:35:45 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	my_mlx_pixel_put(t_mini *mini, int x, int y, unsigned int color)
{
	char	*dst;

	if (!(x > WIDTH || y > HEIGHT || x < 0 || y < 0))
	{
		dst = mini->display.img.addr + (y * mini->display.img.line_length + x
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
