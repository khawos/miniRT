/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:49:03 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/06 11:13:09 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	intersect_sp(t_vec3 origin, t_vec3 ray_direction, t_objet object)
{
	t_equation	var;

	var.a = vec_dot(ray_direction, ray_direction);
	var.b = vec_dot(vec_scale(ray_direction, -2.0),
			vec_substact(object.pos, origin));
	var.c = vec_dot(vec_substact(object.pos, origin),
			vec_substact(object.pos, origin
				)) - pow(object.diameter / 2.0, 2);
	var.delta = pow(var.b, 2) - 4 * var.a * var.c;
	if (var.delta > 0)
	{
		object.color.hit = true;
		var.s1 = (-var.b + sqrt(var.delta)) / (2 * var.a);
		var.s2 = (-var.b - sqrt(var.delta)) / (2 * var.a);
		if (var.s1 < 0 && var.s2 < 0)
			return (object.color.hit = false, -1);
		if (var.s1 > var.s2)
			return (var.s2);
		else
			return (var.s1);
	}
	if (0 == var.delta)
		return (-var.b / (2 * var.a));
	return (-1);
}

double	intersect_pl(t_vec3 origin, t_vec3 ray_direction, t_objet object)
{
	double	t;
	double	dot;

	dot = vec_dot(ray_direction, object.vec_dir);
	object.vec_dir = vec_normalize(object.vec_dir);
	if (dot == 0)
		return (0);
	t = vec_dot(vec_substact(object.pos, origin), object.vec_dir)
		/ dot;
	return (t);
}
