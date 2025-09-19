/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C_math.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:45:03 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/15 13:51:05 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "miniRT.h"

unsigned int	color_shift(t_color rgb)
{
	return ((unsigned int)(0 << 24 | rgb.r << 16 | rgb.g << 8 | rgb.b));
}

t_color	color_substract(t_color i, t_color j)
{
	t_color result;

	result.r = i.r - j.r;
	result.g = i.g - j.g;
	result.b = i.b - j.b;
	return (result);
}

t_color	color_add(t_color i, t_color j)
{
	t_color result;

	result.r = i.r + j.r;
	result.g = i.g + j.g;
	result.b = i.b + j.b;
	return (result);
}

t_color	color_scalar(t_color i, double ratio)
{
	t_color	result;

	if (((double)i.r * ratio) > 255)
		i.r = 0;
	else
		result.r = (unsigned char)((double)i.r * ratio);
	if (((double)i.g * ratio) > 255)
		i.r = 0;
	else
		result.g = (unsigned char)((double)i.g * ratio);
	if (((double)i.b * ratio) > 255)
		i.r = 0;
	else
		result.b = (unsigned char)((double)i.b * ratio);
	result.hit = true;
	return (result);
}

t_color	color_mix(t_color i, t_color j)
{
	t_color result;

	result.r = i.r * j.r;
	result.g = i.g * j.g;
	result.b = i.b * j.b;
	return (result);	
}