/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_geometry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:56:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/19 15:24:39 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	light_sp(t_mini *mini, t_objet obj, t_vec3 ray_dir, double t)
{
	t_vec3	p;
	t_vec3	to_light;
	t_vec3	normal;
	double	dot;
	t_vec2	uv;
	
	//if (shadow_ray(mini, ray_dir, t))
	//	return ((t_color){0, 0, 0, 1});
	p = vec_add(mini->sc.cam[mini->cam_lock].pos, vec_scale(ray_dir, t));
	to_light = vec_substact(mini->sc.light[1].pos, obj.pos);
	normal = vec_normalize(vec_substact(p, obj.pos));
	dot = vec_dot(vec_normalize(normal), vec_normalize(to_light));
	if (dot < 0)
		dot = 0;
	if (obj.mat.albedo)
	{
		uv = get_uv_sp(normal, obj);
		//return (color_scalar(color_multiplie(color_shift_revert(obj.mat.albedo[uv.v][uv.u]),
		//	color_scalar(mini->sc.light[1].color,
		//		mini->sc.light[1].ratio)), dot));
		return (color_shift_revert(obj.mat.albedo[uv.v][uv.u]));
	} 
	return (color_scalar(color_multiplie(obj.color,
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
