/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:11:00 by amedenec          #+#    #+#             */
/*   Updated: 2025/09/28 13:29:49 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_boolean	shadow_ray(t_mini *mini, t_vec3 ray_direction, double t)
{
	t_vec3		secondary_ray;
	t_vec3		p_intersect;
	t_boolean	result;

	p_intersect = vec_add(mini->sc.cam[mini->cam_lock].pos,
			vec_scale(ray_direction, t));
	secondary_ray = vec_substact(mini->sc.light[1].pos, p_intersect);
	result = is_intersect(mini, vec_normalize(secondary_ray), p_intersect);
	return (result);
}

static t_color	light_sp(t_mini *mini, t_objet obj, t_vec3 ray_dir, double t)
{
	t_vec3	p;
	t_vec3	to_light;
	t_vec3	normal;
	double	dot;

	if (shadow_ray(mini, ray_dir, t))
		return ((t_color){0, 0, 0, 1});
	p = vec_add(mini->sc.cam[mini->cam_lock].pos, vec_scale(ray_dir, t));
	to_light = vec_substact(mini->sc.light[1].pos, obj.pos);
	normal = vec_normalize(vec_substact(p, obj.pos));
	dot = vec_dot(vec_normalize(normal), vec_normalize(to_light));
	if (dot < 0)
		dot = 0;
	return (color_scalar(color_multiplie(obj.color,
				color_scalar(mini->sc.light[1].color,
					mini->sc.light[1].ratio)), dot));
}

static t_color	light_pl(t_mini *mini, t_objet obj, t_vec3 ray_dir, double t)
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

static void	light_cy_util(double *dot, t_vec3 *normal, t_objet obj, t_vec3 to_light)
{
	*normal = obj.vec_dir;
	*dot = fabs(vec_dot(*normal, vec_normalize(to_light)));
}	

static t_color	light_cy(t_mini *mini, t_objet obj, t_vec3 ray_dir, double t)
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
	if (obj.cap)
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

t_color	light_ray(t_mini *mini, t_vec3 ray_dir, double t, t_objet obj)
{
	t_color	diffuse_direct;
	t_color	ambiant;
	t_color	spec;
	t_color	final;
	
	if (obj.type == sp)
		diffuse_direct = light_sp(mini, obj, ray_dir, t);
	else if (obj.type == pl)
		diffuse_direct = light_pl(mini, obj, ray_dir, t);
	else
		diffuse_direct = light_cy(mini, obj, ray_dir, t);
	spec = specular(mini, obj, ray_dir, t);
	ambiant = apply_ambiant(mini, obj.color);		
	final = mix_colors(diffuse_direct, ambiant);
	final = mix_layer(final, spec);
	return (final);
}
