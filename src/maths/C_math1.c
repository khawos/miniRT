/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C_math1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:34:41 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/27 19:18:16 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	mix_colors(t_color c1, t_color c2)
{
	t_color	result;

	result.r = (c1.r + c2.r) / 2;
	result.g = (c1.g + c2.g) / 2;
	result.b = (c1.b + c2.b) / 2;
	return (result);
}

t_color	mix_colors_ratio(t_color c1, t_color c2, double ratio)
{
	t_color	result;
	double	r1;
	double	r2;

	r1 = ratio;
	r2 = 1 - ratio;
	result.r = (c1.r * r1 + c2.r * r2);
	result.g = (c1.g * r1 + c2.g * r2);
	result.b = (c1.b * r1 + c2.b * r2);
	return (result);
}

t_color	mix_layer(t_color c1, t_color c2)
{
	t_color	result;

	result.r = (c1.r + c2.r) / 2;
	result.g = (c1.g + c2.g) / 2;
	result.b = (c1.b + c2.b) / 2;
	return (result);
}

t_color	mix_ray(t_color *ray_color)
{
	int	i;	
	int	r;	
	int	b;	
	int	g;

	i = 0;
	r = 0;
	b = 0;
	g = 0;
	while (i < SAMPLE_MAX)
	{
		r += ray_color[i].r;
		g += ray_color[i].g;
		b += ray_color[i].b;
		i++;
	}
	return ((t_color){(unsigned char)(r / SAMPLE_MAX),
				(unsigned char)(g / SAMPLE_MAX),
					(unsigned char)(b / SAMPLE_MAX)});
}
