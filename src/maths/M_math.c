/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   M_math.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:45:58 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/25 14:37:14 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec_create(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	vec_cross(t_vec3 i, t_vec3 j)
{
	t_vec3	result;

	if (i.x == 0 && i.y == 0)
	{
		i.y = 0.000001;
	}
	result.x = i.y * j.z - i.z * j.y;
	result.y = i.z * j.x - i.x * j.z;
	result.z = i.x * j.y - i.y * j.x;
	return (result);
}

double	vec_get_norme(t_vec3 i)
{
	return (sqrt(pow(i.x, 2) + pow(i.y, 2) + pow(i.z, 2)));
}

double	convert_range(double v, double max_src, double min_dst, double max_dst)
{
	return (min_dst + v * (max_dst - min_dst) / max_src);
}

t_vec3	vec_div(t_vec3 i, double n)
{
	t_vec3	result;

	result.x = i.x / n;
	result.y = i.y / n;
	result.z = i.z / n;
	return (result);
}
