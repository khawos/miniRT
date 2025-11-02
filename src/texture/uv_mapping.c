/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:40:06 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/30 23:16:31 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec2	get_uv(t_vec3 normal, t_vec2 size, t_vec3 p, t_objet obj)
{
	t_vec2	texture;

	texture = (t_vec2){0, 0};
	if (obj.type == sp)
		return (get_uv_sp(normal, size));
	if (obj.type == pl)
		return (get_uv_pl(normal, size, p));
	return (texture);
}

t_vec2	get_uv_sp(t_vec3 normal, t_vec2 size)
{
	t_vec2	texture;
	double	phi;
	double	theta;

	phi = atan2(normal.z, normal.x);
	theta = acos(normal.y);
	texture.u = ((-phi + M_PI) / (2 * M_PI)) * (size.u - 1);
	texture.v = (theta / M_PI) * (size.v - 1);
	return (texture);
}

t_vec2	get_uv_pl(t_vec3 normal, t_vec2 size, t_vec3 p)
{
	t_vec3	e1;
	t_vec3	e2;
	t_vec2	texture;

	e1 = vec_normalize(vec_cross(normal, (t_vec3){1, 0, 0}));
	if (e1.x + e1.y + e2.z  == 0)
		e1 = vec_normalize(vec_cross(normal, (t_vec3){0, 0, 1}));
	e2 = vec_normalize(vec_cross(normal, e1));
	texture.u = vec_dot(e1, p) * size.u;
	texture.v = vec_dot(e2, p) * size.v;
	return (texture);
}
