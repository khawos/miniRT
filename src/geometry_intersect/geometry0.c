/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:49:03 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/01 17:00:31 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_equation	inters_sp_init(t_vec3 ray_d, t_objet obj, t_vec3 cam_to_obj)
{
	t_equation	var;

	var.a = vec_dot(ray_d, ray_d);
	var.b = vec_dot(vec_scale(ray_d, -2.0),
			cam_to_obj);
	var.c = vec_dot(cam_to_obj,
			cam_to_obj) - pow(obj.diameter / 2.0, 2);
	var.delta = pow(var.b, 2) - 4 * var.a * var.c;
	return (var);
}

double	intersect_sp(t_vec3 origin, t_vec3 ray_direction, t_objet object)
{
	t_equation	var;
	t_vec3		cam_to_object;
	double		denum;
	double		sqrt_delta;

	cam_to_object = vec_substact(object.pos, origin);
	var = inters_sp_init(ray_direction, object, cam_to_object);
	if (var.delta > 0)
	{
		denum = 2 * var.a;
		sqrt_delta = sqrt(var.delta);
		var.s1 = (-var.b + sqrt_delta) / denum;
		var.s2 = (-var.b - sqrt_delta) / denum;
		if (var.s1 < 0 && var.s2 < 0)
			return (-1);
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

	t = vec_dot(vec_substact(object.pos, origin), object.vec_dir) / dot;
	return (t);
}
