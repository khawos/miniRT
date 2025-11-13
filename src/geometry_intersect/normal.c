/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:28:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/02 13:12:51 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_normal	get_normal_object_bis(t_objet obj, t_ray *ray)
{
	t_normal	normal;
	t_vec3		base_cy;
	t_vec3		p;

	p = vec_add(ray->origin, vec_scale(ray->current_dir, ray->t));
	if (obj.type == cy && ray->t != intersect_cap(ray->origin,
			ray->current_dir, obj))
	{
		base_cy = vec_substact(obj.pos, vec_scale(obj.vec_dir, obj.height / 2));
		normal.geometric = vec_normalize(vec_substact(p,
					vec_add(base_cy, vec_scale(obj.vec_dir,
							vec_dot(vec_substact(p, base_cy), obj.vec_dir)))));
		normal.texture = vec_create(222, 0, 0);
	}
	else
	{
		normal.geometric = obj.vec_dir;
		normal.texture = vec_create(222, 0, 0);
	}
	return (normal);
}

t_normal	get_object_normals(t_mini *mini, t_objet obj, t_ray *ray)
{
	t_normal	normal;

	if (obj.type == sp)
		normal = get_normal_sp_from_map(mini, obj, ray);
	if (obj.type == tr)
	{
		normal.geometric = obj.normal;
		normal.texture = vec_create(222, 0, 0);
	}
	if (obj.type == pl)
	{
		normal.geometric = vec_normalize(obj.vec_dir);
		normal.texture = vec_create(222, 0, 0);
	}
	if (obj.type == cy)
		normal = get_normal_object_bis(obj, ray);
	return (normal);
}
