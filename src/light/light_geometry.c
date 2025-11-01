/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_geometry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:56:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/01 16:56:39 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	light_sp(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils)
{
	t_vec3			p;
	t_vec3			to_light;
	double			dot;
	t_var_texture	texture;
	t_vec3			normal;

	if (is_null_vector(utils.normal.texture))
		normal = utils.normal.geometric;
	else
		normal = utils.normal.texture;
	if (shadow_ray(mini, *ray, ray->t, utils.i))
		return ((t_color){0, 0, 0});
	p = vec_add(ray->origin, vec_scale(ray->current_dir, ray->t));
	to_light = vec_substact(mini->sc.light[utils.i].pos, obj.pos);
	texture.color = get_color_from_map(obj, p);
	dot = vec_dot(vec_normalize(normal), vec_normalize(to_light));
	if (dot < 0)
		dot = 0;
	return (color_scalar(color_multiplie(texture.color,
				color_scalar(mini->sc.light[utils.i].color,
					mini->sc.light[utils.i].ratio)), dot));
}

t_color	light_pl(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils)
{
	t_vec3	p;
	t_vec3	to_light;
	double	dot;
	t_vec3	normal;
	
	if (is_null_vector(utils.normal.texture))
		normal = utils.normal.geometric;
	else
		normal = utils.normal.texture;
	if (shadow_ray(mini, *ray, ray->t, utils.i))
		return ((t_color){0, 0, 0});
	p = vec_add(ray->origin, vec_scale(ray->current_dir, ray->t));
	to_light = vec_substact(mini->sc.light[utils.i].pos, p);
	dot = fabs(vec_dot(normal, vec_normalize(to_light)));
	return (color_scalar(color_multiplie(obj.color,
				color_scalar(mini->sc.light[utils.i].color,
					mini->sc.light[utils.i].ratio)), dot));
}

t_color	light_tr(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils)
{
	t_vec3	p;
	t_vec3	to_light;
	double	dot;

	if (shadow_ray(mini, *ray, ray->t, utils.i))
		return ((t_color){0, 0, 0});
	p = vec_add(ray->origin, vec_scale(ray->current_dir, ray->t));
	to_light = vec_substact(mini->sc.light[utils.i].pos, p);
	dot = fabs(vec_dot(obj.normal, vec_normalize(to_light)));
	return (color_scalar(color_multiplie(obj.color,
				color_scalar(mini->sc.light[utils.i].color,
					mini->sc.light[utils.i].ratio)), dot));
}

void	light_cy_util(double *dot, t_vec3 *normal, t_objet obj, t_vec3 to_light)
{
	*normal = obj.vec_dir;
	*dot = fabs(vec_dot(*normal, vec_normalize(to_light)));
}	

t_color	light_cy(t_mini *mini, t_objet obj, t_ray *ray, t_light_utils utils)
{
	t_vec3	p;
	t_vec3	to_light;
	t_vec3	normal;
	t_vec3	base;
	double	dot;

	if (shadow_ray(mini, *ray, ray->t, utils.i))
		return ((t_color){0, 0, 0});
	p = vec_add(ray->origin, vec_scale(ray->current_dir, ray->t));
	to_light = vec_substact(mini->sc.light[utils.i].pos, p);
	if (ray->t == intersect_cap(ray->origin, ray->current_dir, obj))
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
				color_scalar(mini->sc.light[utils.i].color,
					mini->sc.light[utils.i].ratio)), dot));
}
