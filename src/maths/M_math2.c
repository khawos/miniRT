/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   M_math2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:37:28 by amedenec          #+#    #+#             */
/*   Updated: 2025/09/25 14:37:30 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	vec_dot(t_vec3 i, t_vec3 j)
{
	return (i.x * j.x + i.y * j.y + i.z * j.z);
}

t_vec3	vec_substact(t_vec3 i, t_vec3 j)
{
	t_vec3	result;

	result.x = i.x - j.x;
	result.y = i.y - j.y;
	result.z = i.z - j.z;
	return (result);
}

t_vec3	vec_add(t_vec3 i, t_vec3 j)
{
	t_vec3	result;

	result.x = i.x + j.x;
	result.y = i.y + j.y;
	result.z = i.z + j.z;
	return (result);
}

t_vec3	vec_normalize(t_vec3 i)
{
	t_vec3	result;
	double	norme;

	norme = vec_get_norme(i);
	if (norme == 0)
		return (vec_create(0, 0, 0));
	result = vec_scale(i, 1 / norme);
	return (result);
}

t_vec3	vec_scale(t_vec3 i, double n)
{
	t_vec3	result;

	result.x = i.x * n;
	result.y = i.y * n;
	result.z = i.z * n;
	return (result);
}
