/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:49:03 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/08 16:35:23 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

double	compute_tr_area(t_vec3 a, t_vec3 b, t_vec3 c)
{
	double	area;

	area = 0.5 * vec_get_norme(vec_cross(vec_substact(a, b), vec_substact(a, c)));
	return (area);
}

// double	intersect_tr(t_vec3 origin, t_vec3 ray_direction, t_objet object)
// {
// 	double	t;
// 	double	dot;

// 	t_vec3	p;
// 	t_vec3	p0_to_p1;
// 	t_vec3	p0_to_p2;
// 	t_vec3	p1_to_p2;
// 	t_vec3	p0_to_p;
// 	t_vec3	p1_to_p;
// 	t_vec3	p2_to_p;

// 	double	dot0;
// 	double	dot1;
// 	double	dot2;

// 	dot = vec_dot(ray_direction, object.tr_normal);
// 	object.vec_dir = vec_normalize(object.tr_normal);
// 	if (dot == 0)
// 		return (0);
// 	t = vec_dot(vec_substact(object.p1, origin), object.vec_dir) / dot;
// 	p = vec_add(origin, vec_scale(ray_direction, t));
// 	p0_to_p1 = vec_substact(object.p1, object.p0);
// 	p0_to_p2 = vec_substact(object.p2, object.p0);
// 	p1_to_p2 = vec_substact(object.p2, object.p1);
// 	p0_to_p = vec_substact(p, object.p0);
// 	p1_to_p = vec_substact(p, object.p1);
// 	p2_to_p = vec_substact(p, object.p2);
// 	if (vec_dot(object.tr_normal, vec_cross(p0_to_p1, p0_to_p)) > 0 
// 	&& vec_dot(object.tr_normal, vec_cross(p1_to_p2, p1_to_p)) > 0 
// 	&& vec_dot(object.tr_normal, vec_cross(p0_to_p2, p2_to_p)) > 0)
// 		return (t);
// 	return (0);
// }

// GTPTO

double	intersect_tr(t_vec3 origin, t_vec3 ray_direction, t_objet object)
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

	dot = vec_dot(ray_direction, object.tr_normal);
	object.vec_dir = vec_normalize(object.tr_normal);
	if (fabs(dot) < 1e-6)
		return (0); // rayon parallèle au plan

	t = vec_dot(vec_substact(object.p0, origin), object.vec_dir) / dot;
	p = vec_add(origin, vec_scale(ray_direction, t));

	// Arêtes
	p0_to_p1 = vec_substact(object.p1, object.p0);
	p1_to_p2 = vec_substact(object.p2, object.p1);
	p2_to_p0 = vec_substact(object.p0, object.p2);

	// Vecteurs point -> sommets
	p0_to_p = vec_substact(p, object.p0);
	p1_to_p = vec_substact(p, object.p1);
	p2_to_p = vec_substact(p, object.p2);

	double c0 = vec_dot(object.tr_normal, vec_cross(p0_to_p1, p0_to_p));
	double c1 = vec_dot(object.tr_normal, vec_cross(p1_to_p2, p1_to_p));
	double c2 = vec_dot(object.tr_normal, vec_cross(p2_to_p0, p2_to_p));

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
			obj->p0 = vec_scale(obj->p0, 3);
			obj->p1 = vec_scale(obj->p1, 3);
			obj->p2 = vec_scale(obj->p2, 3);
		}
		i++;
	}
	printf("nb tr : %d ", mini->n_tr);
}
