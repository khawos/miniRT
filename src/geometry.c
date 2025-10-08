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
	t = vec_dot(vec_substact(object.pos, origin), object.vec_dir)
		/ dot;
	return (t);
}

void	get_normal_tr(t_objet *tr, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return ;
	tr->tr_normal = vec_cross(vec_substact(tr->p0, tr->p1), vec_substact(tr->p0, tr->p2));
	tr->tr_normal = vec_normalize(tr->tr_normal);
}

void	set_normal-_tr(t_mini *mini)
{

}

double	intersect_tr(t_vec3 origin, t_vec3 ray_direction, t_objet object)
{

}