/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-14 09:23:29 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-14 09:23:29 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	find_bounds_utils(t_var_bounds *var, t_bounds old_bounds)
{
    var->mid_x = (old_bounds.min.x + old_bounds.max.x) / 2.0;
    var->mid_y = (old_bounds.min.y + old_bounds.max.y) / 2.0;
    var->mid_z = (old_bounds.min.z + old_bounds.max.z) / 2.0;
    var->dx = old_bounds.max.x - old_bounds.min.x;
    var->dy = old_bounds.max.y - old_bounds.min.y;
    var->dz = old_bounds.max.z - old_bounds.min.z;
}

t_vec3	try_max_bound(t_objet obj, t_vec3 max)
{
	if (obj.p0.x > max.x)
		max.x = obj.p0.x;
	if (obj.p0.y > max.y)
		max.y = obj.p0.y;
	if (obj.p0.z > max.z)
		max.z = obj.p0.z;
	if (obj.p1.x > max.x)
		max.x = obj.p1.x;
	if (obj.p1.y > max.y)
		max.y = obj.p1.y;
	if (obj.p1.z > max.z)
		max.z = obj.p1.z;	
	if (obj.p2.x > max.x)
		max.x = obj.p2.x;
	if (obj.p2.y > max.y)
		max.y = obj.p2.y;
	if (obj.p2.z > max.z)
		max.z = obj.p2.z;
	return (max);
}

t_vec3	try_min_bound(t_objet obj, t_vec3 min)
{
	if (obj.p0.x < min.x)
		min.x = obj.p0.x;
	if (obj.p0.y < min.y)
		min.y = obj.p0.y;
	if (obj.p0.z < min.z)
		min.z = obj.p0.z;
	if (obj.p1.x < min.x)
		min.x = obj.p1.x;
	if (obj.p1.y < min.y)
		min.y = obj.p1.y;
	if (obj.p1.z < min.z)
		min.z = obj.p1.z;
	if (obj.p2.x < min.x)
		min.x = obj.p2.x;
	if (obj.p2.y < min.y)
		min.y = obj.p2.y;
	if (obj.p2.z < min.z)
		min.z = obj.p2.z;
	return (min);
}

// t_boolean	tr_is_in_bounds(t_objet	tr, t_bounds bounds)
// {
// 	return ((tr.p0.x >= bounds.min.x  && tr.p0.x <= bounds.max.x)
// 		&& (tr.p0.y >= bounds.min.y  && tr.p0.y <= bounds.max.y)
// 		&& (tr.p0.z >= bounds.min.z  && tr.p0.z <= bounds.max.z)) ||
// 		((tr.p1.x >= bounds.min.x  && tr.p1.x <= bounds.max.x)
// 		&& (tr.p1.y >= bounds.min.y  && tr.p1.y <= bounds.max.y)
// 		&& (tr.p1.z >= bounds.min.z  && tr.p1.z <= bounds.max.z)) ||
// 		((tr.p2.x >= bounds.min.x  && tr.p2.x <= bounds.max.x)
// 		&& (tr.p2.y >= bounds.min.y  && tr.p2.y <= bounds.max.y)
// 		&& (tr.p2.z >= bounds.min.z  && tr.p2.z <= bounds.max.z));
// }

// t_boolean	tr_is_in_bounds(t_objet tr, t_bounds bounds)
// {
// 	t_boolean	in_p0;
// 	t_boolean	in_p1;
// 	t_boolean	in_p2;

// 	//printVec(tr.p0);

// 	in_p0 = (tr.p0.x >= bounds.min.x && tr.p0.x <= bounds.max.x)
// 		&& (tr.p0.y >= bounds.min.y && tr.p0.y <= bounds.max.y)
// 		&& (tr.p0.z >= bounds.min.z && tr.p0.z <= bounds.max.z);
// 	in_p1 = (tr.p1.x >= bounds.min.x && tr.p1.x <= bounds.max.x)
// 		&& (tr.p1.y >= bounds.min.y && tr.p1.y <= bounds.max.y)
// 		&& (tr.p1.z >= bounds.min.z && tr.p1.z <= bounds.max.z);
// 	in_p2 = (tr.p2.x >= bounds.min.x && tr.p2.x <= bounds.max.x)
// 		&& (tr.p2.y >= bounds.min.y && tr.p2.y <= bounds.max.y)
// 		&& (tr.p2.z >= bounds.min.z && tr.p2.z <= bounds.max.z);
// 	return (in_p0 || in_p1 || in_p2);
// }

t_boolean	tr_is_in_bounds(t_objet tr, t_bounds bounds)
{
	t_vec3 tri_min;
	t_vec3 tri_max;

	tri_min.x = fmin(fmin(tr.p0.x, tr.p1.x), tr.p2.x);
	tri_min.y = fmin(fmin(tr.p0.y, tr.p1.y), tr.p2.y);
	tri_min.z = fmin(fmin(tr.p0.z, tr.p1.z), tr.p2.z);

	tri_max.x = fmax(fmax(tr.p0.x, tr.p1.x), tr.p2.x);
	tri_max.y = fmax(fmax(tr.p0.y, tr.p1.y), tr.p2.y);
	tri_max.z = fmax(fmax(tr.p0.z, tr.p1.z), tr.p2.z);

	return (!(tri_max.x < bounds.min.x || tri_min.x > bounds.max.x
		|| tri_max.y < bounds.min.y || tri_min.y > bounds.max.y
		|| tri_max.z < bounds.min.z || tri_min.z > bounds.max.z));
}
