/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:30:55 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/12 14:34:10 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
