/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:49:03 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/08 16:12:18 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	intersect_sp(t_vec3 origin, t_vec3 ray_direction, t_objet object)
{
	t_equation	var;
	t_vec3	cam_to_object;
	
	cam_to_object = vec_substact(object.pos, origin);
	var.a = vec_dot(ray_direction, ray_direction);
	var.b = vec_dot(vec_scale(ray_direction, -2.0),
			cam_to_object);
	var.c = vec_dot(cam_to_object,
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
	t = vec_dot(vec_substact(object.pos, origin), object.vec_dir) / dot;
	return (t);
}

double	compute_tr_area(t_vec3 a, t_vec3 b, t_vec3 c)
{
	double	area;

	area = 0.5 * vec_get_norme(vec_cross(vec_substact(a, b), vec_substact(a, c)));
	return (area);
}

double	intersect_tr(t_vec3 origin, t_vec3 ray_direction, t_objet object)
{
	double	a0;
	double	a1;
	double	a2;
	double	a3;
	double	t;
	double	dot;
	t_vec3	p;

	dot = vec_dot(ray_direction, object.tr_normal);
	object.vec_dir = vec_normalize(object.tr_normal);
	if (dot == 0)
		return (0);
	t = vec_dot(vec_substact(object.pos, origin), object.tr_normal) / dot;
	p = vec_add(origin, vec_scale(ray_direction, t));
	a0 = compute_tr_area(object.p0, object.p1, object.p2);
	a1 = compute_tr_area(p, object.p1, object.p2);
	a2 = compute_tr_area(object.p0, p, object.p2);
	a3 = compute_tr_area(object.p0, object.p1, p);
	if (a1 + a2 + a3 > a0)
		return (0);
	return (t);
}

void	set_normal_tr(t_mini *mini)
{
	int		i;
	t_objet	*obj;

	i = 0;
	obj = mini->sc.objet;
	while (i < mini->N_OBJ)
	{
		if (obj->type == tr)
		{
			obj->tr_normal = vec_cross(vec_substact(obj->p0, obj->p1), vec_substact(obj->p0, obj->p2));
			obj->tr_normal = vec_normalize(obj->tr_normal);
		}
		i++;
	}
}
