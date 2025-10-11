/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:40:56 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/06 11:23:13 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_var_cy(t_vec3 origin, t_vec3 ray_d, t_objet *obj, t_equation *var)
{
	t_vec3	hb;
	t_vec3	vec_dir_scale;
	double	dot_ray_chap;
	double	dot_w_chap;

	vec_dir_scale = vec_scale(obj->vec_dir, obj->height / 2);
	var->B = vec_substact(obj->pos, vec_dir_scale);
	var->H = vec_add(obj->pos, vec_dir_scale);
	var->W = vec_substact(origin, var->B);
	hb = vec_normalize(vec_substact(var->H, var->B));
	dot_w_chap = vec_dot(var->W, hb);
	dot_ray_chap = vec_dot(ray_d, hb);
	var->a = vec_dot(ray_d, ray_d) - pow(dot_ray_chap, 2);
	var->b = 2 * (vec_dot(ray_d, var->W) - dot_ray_chap * dot_w_chap);
	var->c = vec_dot(var->W, var->W) - pow(dot_w_chap, 2)
		- pow(obj->diameter / 2, 2);
	var->delta = pow(var->b, 2) - 4 * var->a * var->c;
}

double	inter_cy_2(t_vec3 origin, t_vec3 ray_d, t_objet *obj, t_equation *var)
{
	double	dot;

	if (var->s1 > var->s2)
	{
		var->intersect = vec_add(origin, vec_scale(ray_d, var->s2));
		var->intersect = vec_substact(var->intersect, var->B);
		dot = vec_dot(var->intersect, obj->vec_dir);
		if (dot < 0 || dot > obj->height)
			return (-1);
		return (var->s2);
	}
	else
	{
		var->intersect = vec_add(origin, vec_scale(ray_d, var->s1));
		var->intersect = vec_substact(var->intersect, var->B);
		dot = vec_dot(var->intersect, obj->vec_dir);
		if (dot < 0 || dot > obj->height)
			return (-1);
		return (var->s1);
	}
}

double	intersect_cy(t_vec3 origin, t_vec3 ray_direction, t_objet object)
{
	t_equation	var;

	init_var_cy(origin, ray_direction, &object, &var);
	if (var.delta > 0)
	{
		var.s1 = (-var.b + sqrt(var.delta)) / (2 * var.a);
		var.s2 = (-var.b - sqrt(var.delta)) / (2 * var.a);
		if ((var.s1 < 0 && var.s2 < 0))
			return (-1);
		return (inter_cy_2(origin, ray_direction, &object, &var));
	}
	if (0 == var.delta)
		return (-var.b / (2 * var.a));
	return (-1);
}
