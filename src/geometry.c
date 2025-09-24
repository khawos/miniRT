/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-24 16:49:03 by jbayonne          #+#    #+#             */
/*   Updated: 2025-09-24 16:49:03 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

typedef	struct s_equation
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	s1;
	double	s2;
	double  t;
	t_vec3	intersect;
	t_vec3	H;
	t_vec3	B;
	t_vec3	H_chapeau;
	t_vec3	W;
}				t_equation;

double	intersect_sp(t_vec3 origin, t_vec3 ray_direction, t_objet *object)
{
	t_equation	var;

	var.a = vec_dot(ray_direction, ray_direction);
	var.b = vec_dot(vec_scale(ray_direction, -2.0),
			vec_substact(object->pos, origin));
	var.c = vec_dot(vec_substact(object->pos, origin),
			vec_substact(object->pos, origin
				)) - pow(object->diameter / 2.0, 2);
	var.delta = pow(var.b, 2) - 4 * var.a * var.c;
	if (var.delta > 0)
	{
		object->color.hit = true;
		var.s1 = (-var.b + sqrt(var.delta)) / (2 * var.a);
		var.s2 = (-var.b - sqrt(var.delta)) / (2 * var.a);
		if (var.s1 < 0 && var.s2 < 0)
			return (object->color.hit = false, -1);
		if (var.s1 > var.s2)
			return (var.s2);
		else
			return (var.s1);
	}
	if (0 == var.delta)
		return (-var.b / (2 * var.a));
	return (-1);	
}

double intersect_pl(t_vec3 origin, t_vec3 ray_direction, t_objet *object)
{
	double	t;

	object->color.hit = true;
	object->vec_dir = vec_normalize(object->vec_dir);
	if (vec_dot(ray_direction, object->vec_dir) == 0)
		return (object->color.hit = false, 0);
	t = vec_dot(vec_substact(object->pos, origin), object->vec_dir) / vec_dot(ray_direction, object->vec_dir);
	if (t < 0)
		object->color.hit = false;
	return (t);
}

double	intersect_cy(t_vec3 origin, t_vec3 ray_direction, t_objet *object)
{
	t_equation  var;

	var.B = vec_substact(object->pos, vec_scale(object->vec_dir, object->height / 2));
	var.W = vec_substact(origin, var.B);
	var.H = vec_add(object->pos, vec_scale(object->vec_dir, object->height / 2));
	var.H_chapeau = vec_div(vec_substact(var.H, var.B), vec_get_norme(vec_substact(var.H, var.B)));
	var.a = vec_dot(ray_direction, ray_direction) - pow(vec_dot(ray_direction, var.H_chapeau), 2);
	var.b = 2 * (vec_dot(ray_direction, var.W) - vec_dot(ray_direction, var.H_chapeau) * vec_dot(var.W ,var.H_chapeau));
	var.c = vec_dot(var.W, var.W) - pow(vec_dot(var.W ,var.H_chapeau), 2) - pow(object->diameter / 2, 2);
	var.delta = pow(var.b, 2) - 4 * var.a * var.c;
	if ( var.delta > 0)
	{
		object->color.hit = true;
		var.s1 = (-var.b + sqrt(var.delta)) / (2 * var.a);
		var.s2 = (-var.b - sqrt(var.delta)) / (2 * var.a);
		if ((var.s1 < 0 && var.s2 < 0))
			return (object->color.hit = false, -1);
		if (var.s1 > var.s2)
		{
			var.intersect = vec_add(origin, vec_scale(ray_direction, var.s2));
			var.intersect = vec_substact(var.intersect, var.B);
			if (vec_dot(var.intersect, object->vec_dir) < 0 || vec_dot(var.intersect, object->vec_dir) > object->height)
				return (object->color.hit = false, -1);
			return (var.s2);
		}
		else
		{
			var.intersect = vec_add(origin, vec_scale(ray_direction, var.s1));
			var.intersect = vec_substact(var.intersect, var.B);
			if (vec_dot(var.intersect, object->vec_dir) < 0 || vec_dot(var.intersect, object->vec_dir) > object->height)
				return (object->color.hit = false, -1);
			return (var.s1);
		}
	}
	if (0 == var.delta)
		return (-var.b / (2 * var.a));
	return (-1);
}

double  intersect_cap(t_vec3 origin, t_vec3 ray_direction, t_objet *object)
{
	t_equation  var;

	(void) origin;
	var.B = vec_substact(object->pos, vec_scale(object->vec_dir, object->height / 2));
	var.H = vec_add(object->pos, vec_scale(object->vec_dir, object->height / 2));

	var.s1 = vec_dot(vec_substact(var.H, origin), object->vec_dir) / vec_dot(object->vec_dir, ray_direction);
	var.s2 = vec_dot(vec_substact(var.B, origin), object->vec_dir) / vec_dot(object->vec_dir, ray_direction);
	var.intersect = vec_add(origin, vec_scale(ray_direction, var.s2));
	if (pow(vec_get_norme(vec_substact(var.intersect, var.H)), 2) <= pow(object->diameter / 2, 2))
	{
		object->color.hit = true;
		return (var.s2);
	}
	return (-1);
}
