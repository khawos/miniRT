/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:32:50 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/05 20:10:38 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

double	intersect_cap(t_vec3 o, t_vec3 d, t_objet obj)
{
	t_equation	var;
	double		t1;
	double		t2;

	t1 = -1;
	t2 = -1;
	init_var_cap(o, d, &obj, &var);
	t1 = calc_cap_inter(o, d, var.cap_center_top, &obj);
	t2 = calc_cap_inter(o, d, var.cap_center_bottom, &obj);
	if (t1 > 0 && (t2 < 0 || t1 < t2))
		return (t1);
	if (t2 > 0)
		return (t2);
	return (-1);
}
