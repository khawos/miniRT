/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-14 10:09:47 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-14 10:09:47 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


typedef	struct s_var_tr
{
	double	t;
	double	dot;
	t_vec3	p;
	t_vec3	p0_to_p1;
	t_vec3	p1_to_p2;
	t_vec3	p2_to_p0;
	t_vec3	p0_to_p;
	t_vec3	p1_to_p;
	t_vec3	p2_to_p;

}				t_var_tr;

t_var_tr	intersect_tr_utils(t_objet object, t_vec3 p)
{
	t_var_tr	var;

	var.p0_to_p1 = vec_substact(object.p1, object.p0);
	var.p1_to_p2 = vec_substact(object.p2, object.p1);
	var.p2_to_p0 = vec_substact(object.p0, object.p2);
	var.p0_to_p = vec_substact(p, object.p0);
	var.p1_to_p = vec_substact(p, object.p1);
	var.p2_to_p = vec_substact(p, object.p2);
	return (var);
}

double	intersect_tr(t_vec3 origin, t_vec3 ray_direction, t_objet object)
{
	t_var_tr	var;
	double		t;

	var.dot = vec_dot(ray_direction, object.tr_normal);
	object.vec_dir = vec_normalize(object.tr_normal);
	if (fabs(var.dot) < 1e-6)
		return (0);
	t = vec_dot(vec_substact(object.p0, origin), object.vec_dir) / var.dot;
	var.p = vec_add(origin, vec_scale(ray_direction, t));
	var = intersect_tr_utils(object, var.p);
	double c0 = vec_dot(object.tr_normal, vec_cross(var.p0_to_p1, var.p0_to_p));
	double c1 = vec_dot(object.tr_normal, vec_cross(var.p1_to_p2, var.p1_to_p));
	double c2 = vec_dot(object.tr_normal, vec_cross(var.p2_to_p0, var.p2_to_p));
	if ((c0 >= 0 && c1 >= 0 && c2 >= 0) || (c0 <= 0 && c1 <= 0 && c2 <= 0))
		return (t);
	return (0);
}

void	set_normal_tr(t_mini *mini)
{
	int		i;
	t_objet	*obj;

	i = 0;
	while (i < mini->N_OBJ)
	{
		obj = &mini->sc.objet[i];
		if (obj->type == tr)
		{
			obj->tr_normal = vec_cross(vec_substact(obj->p1, obj->p0), vec_substact(obj->p2, obj->p0));
			obj->tr_normal = vec_normalize(obj->tr_normal);
			//obj->p0 = vec_scale(obj->p0, 3);
			//obj->p1 = vec_scale(obj->p1, 3);
			//obj->p2 = vec_scale(obj->p2, 3);
		}
		i++;
	}
}