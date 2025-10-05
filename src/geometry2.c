/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-25 12:40:56 by jbayonne          #+#    #+#             */
/*   Updated: 2025-09-25 12:40:56 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_var_cy(t_vec3 origin, t_vec3 ray_d, t_objet *obj, t_equation *var)
{
	t_vec3	hb;
	t_vec3	vec_dir_scale;
	double	dot_ray_chap;
	double	dot_w_chap;

	vec_dir_scale = vec_scale(obj->vec_dir, obj->height / 2);
	obj->vec_dir = vec_normalize(obj->vec_dir);
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
			return (obj->color.hit = false, -1);
		return (var->s2);
	}
	else
	{
		var->intersect = vec_add(origin, vec_scale(ray_d, var->s1));
		var->intersect = vec_substact(var->intersect, var->B);
		dot = vec_dot(var->intersect, obj->vec_dir);
		if (dot < 0 || dot > obj->height)
			return (obj->color.hit = false, -1);
		return (var->s1);
	}
}

double	intersect_cy(t_vec3 origin, t_vec3 ray_direction, t_objet *object)
{
	t_equation	var;

	init_var_cy(origin, ray_direction, object, &var);
	if (var.delta > 0)
	{
		object->color.hit = true;
		var.s1 = (-var.b + sqrt(var.delta)) / (2 * var.a);
		var.s2 = (-var.b - sqrt(var.delta)) / (2 * var.a);
		if ((var.s1 < 0 && var.s2 < 0))
			return (object->color.hit = false, -1);
		return (inter_cy_2(origin, ray_direction, object, &var));
	}
	if (0 == var.delta)
		return (-var.b / (2 * var.a));
	return (-1);
}

void	init_var_cap(t_vec3 origin, t_vec3 ray_d, t_objet *obj, t_equation *var)
{
	t_vec3	scale;

	scale = vec_scale(obj->vec_dir, obj->height / 2);
	var->cap_center_top = vec_add(obj->pos, scale);
	var->cap_center_bottom = vec_substact(obj->pos, scale);
	var->s1 = vec_dot(vec_substact(var->cap_center_top, origin), obj->vec_dir)
		/ vec_dot(ray_d, obj->vec_dir);
}


double	calc_cap_inter(t_vec3 o, t_vec3 d, t_vec3 c, t_objet *obj)
{
	double	denom;
	double	num;
	double	t;
	t_vec3	inter;

	denom = vec_dot(d, obj->vec_dir);
	if (fabs(denom) < 1e-6)
		return (-1);
	num = vec_dot(vec_substact(c, o), obj->vec_dir);
	t = num / denom;
	if (t <= 0)
		return (-1);
	inter = vec_add(o, vec_scale(d, t));
	if (vec_get_norme(vec_substact(inter, c)) <= obj->diameter / 2.0)
		return (t);
	return (-1);
}

double	intersect_cap(t_vec3 o, t_vec3 d, t_objet *obj)
{
	t_equation	var;
	double		t1;
	double		t2;

	t1 = -1;
	t2 = -1;
	init_var_cap(o, d, obj, &var);
	t1 = calc_cap_inter(o, d, var.cap_center_top, obj);
	t2 = calc_cap_inter(o, d, var.cap_center_bottom, obj);
	if (t1 > 0 && (t2 < 0 || t1 < t2))
	{
		obj->color.hit = true;
		obj->cap = true;
		return (t1);
	}
	if (t2 > 0)
	{
		obj->color.hit = true;
		obj->cap = true;
		return (t2);
	}
	return (-1);
}

