/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_from_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:15:37 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/01 11:16:36 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	transform_normal_from_map(unsigned int color, t_vec3 n, t_vec3 up_world)
{
	t_vec3	normal_tangent;
	t_vec3	tangeante;
	t_vec3	bitangente;
	t_vec3	normal_world;

	normal_tangent.z = (color & 0x000000FF) / 255.0;
	normal_tangent.y = ((color & 0x0000FF00) >> 8) / 255.0;
	normal_tangent.x = ((color & 0x00FF0000) >> 16) / 255.0;
	normal_tangent.x = normal_tangent.x * 2.0 - 1.0;
	normal_tangent.y = normal_tangent.y * 2.0 - 1.0;
	normal_tangent.z = normal_tangent.z * 2.0 - 1.0;
	normal_tangent = vec_normalize(normal_tangent);
	if (fabs(vec_dot(up_world, n)) > 0.999)
		up_world = (t_vec3){0.0, 0.0, 1.0};
	tangeante = vec_normalize(vec_cross(up_world, n));
	bitangente = vec_normalize(vec_cross(n, tangeante));
	normal_world = vec_add(vec_add(vec_scale(tangeante, normal_tangent.x),
				vec_scale(bitangente, normal_tangent.y)),
					vec_scale(n, normal_tangent.z));
	return (vec_normalize(normal_world));
}

double	get_roughness_from_map(t_objet obj, double spec, t_vec3 geometric_normal)
{
	t_var_texture	info;
	int				grey_scale;
	double			roughness;

	roughness = spec;
	grey_scale = 0;
	if (obj.type == sp && obj.mat.roughness.map)
	{
		info.uv = get_uv_sp(geometric_normal, obj.mat.roughness.size);
		grey_scale = obj.mat.roughness.map[info.uv.v][info.uv.u] & 0x000000FF;
		roughness = convert_range(grey_scale, 255, 0, 1);
	}
	return (roughness);
}

t_normal	get_normal_sp_from_map(t_mini *mini, t_objet obj, t_ray *ray)
{
	t_vec3			intersect;
	t_normal		normal;
	t_var_texture	info;
	
	intersect = vec_add(ray->origin, vec_scale(ray->current_dir, ray->t));
	normal.geometric = vec_normalize(vec_substact(intersect, obj.pos));
	if (obj.mat.normal.map)
	{
		info.uv = get_uv_sp(normal.geometric, obj.mat.normal.size);
		normal.texture = transform_normal_from_map(obj.mat.normal.map[info.uv.v][info.uv.u], normal.geometric, mini->up_world);
	}
	else
		normal.texture = vec_create(222, 0, 0);
	return (normal);
}

t_color	get_color_from_map(t_objet obj, t_vec3 p)
{
	t_vec3			n;
	t_var_texture	info;
	
	n = vec_normalize(vec_substact(p, obj.pos));
	if (obj.mat.albedo.map)
	{	
		info.uv = get_uv_sp(n, obj.mat.albedo.size);
		info.color = color_shift_revert(obj.mat.albedo.map[info.uv.v][info.uv.u]);
	}
	else
		info.color = obj.color;
	return (info.color);
}
