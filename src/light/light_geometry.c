/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_geometry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:56:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/28 12:07:33 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_var_texture{
	
	t_vec2	uv;
	t_color color;
	t_vec3	normal_texture;
	t_vec3	normal;
}				t_var_texture;

t_vec3	get_normal_from_map(unsigned int color, t_vec3 n, t_vec3 up_world)
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


t_var_texture	find_ray_texture(t_objet obj, t_vec3 p, t_vec3 up_world)
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
	if (obj.mat.normal.map)
	{
		info.uv = get_uv_sp(n, obj.mat.normal.size);
		info.normal = get_normal_from_map(obj.mat.normal.map[info.uv.v][info.uv.u], n, up_world);
	}
	else
		info.normal = n;
	return (info);
}

t_color	light_sp(t_mini *mini, t_objet obj, t_vec3 ray_dir, double t)
{
	t_vec3	p;
	t_vec3	to_light;
	double	dot;
	t_var_texture	var;
	
	//if (shadow_ray(mini, ray_dir, t))
	//	return ((t_color){0, 0, 0, 1});
	p = vec_add(mini->sc.cam[mini->cam_lock].pos, vec_scale(ray_dir, t));
	to_light = vec_substact(mini->sc.light[1].pos, obj.pos);
	var = find_ray_texture(obj, p, mini->up_world);
	dot = vec_dot(vec_normalize(var.normal), vec_normalize(to_light));
	if (dot < 0)
		dot = 0;
	return (color_scalar(color_multiplie(var.color,
				color_scalar(mini->sc.light[1].color,
					mini->sc.light[1].ratio)), dot));
}

t_color	light_pl(t_mini *mini, t_objet obj, t_vec3 ray_dir, double t)
{
	t_vec3	p;
	t_vec3	to_light;
	double	dot;

	if (shadow_ray(mini, ray_dir, t))
		return ((t_color){0, 0, 0, 1});
	p = vec_add(mini->sc.cam[mini->cam_lock].pos, vec_scale(ray_dir, t));
	to_light = vec_substact(mini->sc.light[1].pos, p);
	dot = fabs(vec_dot(obj.vec_dir, vec_normalize(to_light)));
	return (color_scalar(color_multiplie(obj.color,
				color_scalar(mini->sc.light[1].color,
					mini->sc.light[1].ratio)), dot));
}

t_color	light_tr(t_mini *mini, t_objet obj, t_vec3 ray_dir, double t)
{
	t_vec3	p;
	t_vec3	to_light;
	double	dot;

	//if (shadow_ray(mini, ray_dir, t))
	//	return ((t_color){0, 0, 0, 1});
	p = vec_add(mini->sc.cam[mini->cam_lock].pos, vec_scale(ray_dir, t));
	to_light = vec_substact(mini->sc.light[1].pos, p);
	dot = fabs(vec_dot(obj.tr_normal, vec_normalize(to_light)));
	return (color_scalar(color_multiplie(obj.color,
				color_scalar(mini->sc.light[1].color,
					mini->sc.light[1].ratio)), dot));
}

void	light_cy_util(double *dot, t_vec3 *normal, t_objet obj, t_vec3 to_light)
{
	*normal = obj.vec_dir;
	*dot = fabs(vec_dot(*normal, vec_normalize(to_light)));
}	

t_color	light_cy(t_mini *mini, t_objet obj, t_vec3 ray_dir, double t)
{
	t_vec3	p;
	t_vec3	to_light;
	t_vec3	normal;
	t_vec3	base;
	double	dot;

	if (shadow_ray(mini, ray_dir, t))
		return ((t_color){0, 0, 0, 1});
	p = vec_add(mini->sc.cam[mini->cam_lock].pos, vec_scale(ray_dir, t));
	to_light = vec_substact(mini->sc.light[1].pos, p);
	if (t == intersect_cap(mini->sc.cam[mini->cam_lock].pos, ray_dir, obj))
		light_cy_util(&dot, &normal, obj, to_light);
	else
	{
		base = vec_substact(obj.pos, vec_scale(obj.vec_dir, obj.height / 2));
		normal = vec_normalize(vec_substact(p,
					vec_add(base, vec_scale(obj.vec_dir,
							vec_dot(vec_substact(p, base), obj.vec_dir)))));
		dot = vec_dot(normal, vec_normalize(to_light));
		if (dot < 0)
			dot = 0;
	}
	return (color_scalar(color_multiplie(obj.color,
				color_scalar(mini->sc.light[1].color,
					mini->sc.light[1].ratio)), dot));
}
