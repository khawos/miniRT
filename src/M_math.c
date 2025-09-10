/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   M_math.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:45:58 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/07 21:39:29 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3 vec_cross(t_vec3 i, t_vec3 j)
{
	t_vec3	result;

	result.x = i.y * j.z - i.z * j.y;
	result.y = i.z * j.x - i.x * j.z;
	result.z = i.x * j.y - i.y * j.x;
	return (result);
}

double  vec_cross_x(t_vec3 i, t_vec3 j)
{
    double result;

	result = i.y * j.z - i.z * j.y;
	printf("result x : %f\n", result);
    return (result);
}

double  vec_cross_y(t_vec3 i, t_vec3 j)
{
    double result;

	result = i.z * j.x - i.x * j.z;
	printf("result y : %f\n", result);
    return (result);
}

double  vec_cross_z(t_vec3 i, t_vec3 j)
{
    double result;

	result = i.x * j.y - i.y * j.x;
	printf("result z : %f\n", result);
    return (result);
}

double  vec_get_norme(t_vec3 i)
{
	double	result;

    result = sqrtf(powf(i.x, 2) + powf(i.y, 2) + powf(i.z, 2));
    return (result);
}
