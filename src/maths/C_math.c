/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C_math.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-13 09:45:03 by jbayonne          #+#    #+#             */
/*   Updated: 2025-09-13 09:45:03 by jbayonne         ###   ########.fr       */
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

	result.r = (unsigned char)((double)i.r * ratio);
	result.g = (unsigned char)((double)i.g * ratio);
	result.b = (unsigned char)((double)i.b * ratio);
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