/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_geometry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:56:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/27 19:04:31 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// typedef struct s_var_texture{
	
// 	t_vec2	uv;
// 	t_color color;
// 	t_vec3	normal;
// }				t_var_texture;

t_vec3	get_normal_from_map(unsigned int color)
{
	t_vec3	normal;

	normal.z  = color & 0x000000FF;
	normal.y = (color & 0x0000FF00) >> 8;
	normal.x = (color & 0x00FF0000) >> 16;
	normal = vec_normalize(normal);
	return (normal);
}

t_var_texture	find_ray_texture(t_objet obj, t_vec3 p)
{
	t_vec3			n;
	t_var_texture	info;
	
	n = vec_normalize(vec_substact(p, obj.pos));
	info.uv = get_uv_sp(n, obj);
	if (obj.mat.albedo)
		info.color = color_shift_revert(obj.mat.albedo[info.uv.v][info.uv.u]);
	else
		info.color = obj.color;
	if (obj.mat.normal_map)
		info.normal = get_normal_from_map(obj.mat.normal_map[info.uv.v][info.uv.u]);
	else
		info.normal = n;
	return (info);
}

t_color	light_sp(t_mini *mini, t_objet obj, t_ray ray, double t)
{
	t_vec3	p;
	t_vec3	to_light;
	double	dot;
	t_var_texture	var;
	
	//if (shadow_ray(mini, ray_dir, t))
	//	return ((t_color){0, 0, 0, 1});
	p = vec_add(ray.origin, vec_scale(ray.dir, t));
	to_light = vec_substact(mini->sc.light[1].pos, obj.pos);
	var = find_ray_texture(obj, p);
	dot = vec_dot(vec_normalize(var.normal), vec_normalize(to_light));
	if (dot < 0)
		dot = 0;
	return (color_scalar(color_multiplie(var.color,
				color_scalar(mini->sc.light[1].color,
					mini->sc.light[1].ratio)), dot));
}

t_color	light_pl(t_mini *mini, t_objet obj, t_ray ray, double t)
{
	t_vec3	p;
	t_vec3	to_light;
	double	dot;

	if (shadow_ray(mini, ray, t))
		return ((t_color){0, 0, 0, 1});
	p = vec_add(ray.origin, vec_scale(ray.dir, t));
	to_light = vec_substact(mini->sc.light[1].pos, p);
	dot = fabs(vec_dot(obj.vec_dir, vec_normalize(to_light)));
	return (color_scalar(color_multiplie(obj.color,
				color_scalar(mini->sc.light[1].color,
					mini->sc.light[1].ratio)), dot));
}

t_color	light_tr(t_mini *mini, t_objet obj, t_ray ray, double t)
{
	t_vec3	p;
	t_vec3	to_light;
	double	dot;

	//if (shadow_ray(mini, ray_dir, t))
	//	return ((t_color){0, 0, 0, 1});
	p = vec_add(ray.origin, vec_scale(ray.dir, t));
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

t_color	light_cy(t_mini *mini, t_objet obj, t_ray ray, double t)
{
	t_vec3	p;
	t_vec3	to_light;
	t_vec3	normal;
	t_vec3	base;
	double	dot;

	if (shadow_ray(mini, ray, t))
		return ((t_color){0, 0, 0, 1});
	p = vec_add(ray.origin, vec_scale(ray.dir, t));
	to_light = vec_substact(mini->sc.light[1].pos, p);
	if (t == intersect_cap(ray.origin, ray.dir, obj))
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
