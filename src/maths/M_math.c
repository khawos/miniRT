/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   M_math.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:45:58 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/12 14:48:45 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec_create(void)
{
	t_vec3	vec;

	vec.x = 0;
	vec.y = 0;
	vec.z = 0;
	return (vec);
}

t_vec3	vec_cross(t_vec3 i, t_vec3 j)
{
	t_vec3	result;

	result.x = i.y * j.z - i.z * j.y;
	result.y = i.z * j.x - i.x * j.z;
	result.z = i.x * j.y - i.y * j.x;
	printVec(result);
	return (result);
}

double	vec_get_norme(t_vec3 i)
{
	return (sqrt(pow(i.x, 2) + pow(i.y, 2) + pow(i.z, 2)));
}
