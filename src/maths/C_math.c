/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C_math.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:45:03 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/28 13:09:12 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	color_substract(t_color i, t_color j)
{
	t_color	result;

	result.r = i.r - j.r;
	result.g = i.g - j.g;
	result.b = i.b - j.b;
	return (result);
}

t_color	color_add(t_color i, t_color j)
{
	t_color	result;

	result.r = i.r + j.r;
	result.g = i.g + j.g;
	result.b = i.b + j.b;
	return (result);
}

t_color	color_scalar(t_color i, double ratio)
{
	t_color	result;

	result.r = (unsigned char)((double)i.r * ratio);
	result.g = (unsigned char)((double)i.g * ratio);
	result.b = (unsigned char)((double)i.b * ratio);
	return (result);
}

t_color	color_multiplie(t_color i, t_color j)
{
	t_color	result;

	result.r = (i.r * j.r) / 255;
	result.g = (i.g * j.g) / 255;
	result.b = (i.b * j.b) / 255;
	return (result);
}

t_color	mix_colors(t_color c1, t_color c2)
{
	t_color	result;

	result.r = (c1.r + c2.r) / 2;
	result.g = (c1.g + c2.g) / 2;
	result.b = (c1.b + c2.b) / 2;
	return (result);
}

t_color	mix_layer(t_color c1, t_color c2)
{
	t_color	result;
	if (false == c2.hit)
		return (c1);
	result.r = (c1.r + c2.r) / 2;
	result.g = (c1.g + c2.g) / 2;
	result.b = (c1.b + c2.b) / 2;
	return (result);
}
